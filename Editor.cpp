// IMPLEMENTATION FOR OBSERVER

#include "Editor.h"
#include <iostream>

using namespace std;

// ********
// Commands
// ********

// command to insert text
class InsertCommand : public Command {
public:
    InsertCommand(int cX, int cY, int keyPressed, Editor &editor): 
        _cX(cX),
        _cY(cY),
        _key(keyPressed),
        _editor(editor)
    {};
	
    ~InsertCommand() { delete this; }
    
    void Execute() {
        _editor.InsertCharAt(_cX, _cY, static_cast<char>(_key));
        _editor.SetCursor(_cX + 1, _cY);
    }
    
    void UnExecute() {
        _editor.SetCursor(_cX, _cY);
        _editor.RemoveCharAt(_cX, _cY);
    }
private:
    int _cX, _cY, _key;
    Editor &_editor;
};

// command to remove text
class RemoveCommand : public Command {
public:
    RemoveCommand(int cX, int cY, Editor &editor): 
        _cX(cX),
        _cY(cY),
        _editor(editor)
    {};
	
    ~RemoveCommand() { delete this; }
    
    void Execute() {
        _key_deleted = _editor.GetText()[_cY][_cX - 1];
        _editor.SetCursor(_cX - 1, _cY);
        _editor.RemoveCharAt(_cX - 1, _cY);
    }
    
    void UnExecute() {
        _editor.InsertCharAt(_cX - 1, _cY, _key_deleted);
        _editor.SetCursor(_cX, _cY);
    }
private:
    int _cX, _cY;
    char _key_deleted;
    Editor &_editor;
};

// command to remove row with backspace
class RowBackspaceCommand : public Command {
public:
    RowBackspaceCommand(int cX, int cY, Editor &editor): 
        _cX(cX),
        _cY(cY),
        _editor(editor)
    {};
	
    ~RowBackspaceCommand() { delete this; }
    
    void Execute() {
        _row_deleted = _editor.GetText()[_cY];
        _row_length = (int)_row_deleted.size();

        int new_x = (int)_editor.GetText()[_cY - 1].size();
        _editor.SetCursor(new_x, _cY - 1);
        
        _editor.RemoveRowAt(_cY);
    }
    
    void UnExecute() {
        _editor.InsertRowAt(_cY, _row_deleted, _row_length);
        _editor.SetCursor(0, _cY);
    }
private:
    int _cX, _cY, _row_length;
    std::string _row_deleted;
    Editor &_editor;
};

// command to insert row with enter
class EnterCommand : public Command {
public:
    EnterCommand(int cX, int cY, Editor &editor): 
        _cX(cX),
        _cY(cY),
        _editor(editor)
    {};
	
    ~EnterCommand() { delete this; }
    
    void Execute() {
        _row_entered = _editor.GetText()[_cY].substr(_cX, (int)_editor.GetText()[_cY].size());
        _row_length = (int)_row_entered.size();

        _editor.InsertRowAt(_cY + 1, _row_entered, _row_length);
        _editor.SetCursor(0, _cY + 1);
    }
    
    void UnExecute() {
        _editor.RemoveRowAt(_cY + 1);
        _editor.SetCursor(_cX, _cY);
    }
private:
    int _cX, _cY, _row_length;
    std::string _row_entered;
    Editor &_editor;
};



// ****************************
// Controller for text document
// ****************************

ECTextDocumentCtrl :: ECTextDocumentCtrl(Editor &docIn) : doc(docIn) {}
ECTextDocumentCtrl :: ~ECTextDocumentCtrl() {}

void ECTextDocumentCtrl :: InsertTextAt(int xPos, int yPos, int ch, Editor &editor) {
    InsertCommand *insert = new InsertCommand(xPos, yPos, ch, editor);
    histCmds.ExecuteCmd(insert);
}

void ECTextDocumentCtrl :: RemoveTextAt(int xPos, int yPos, Editor &editor) {
    RemoveCommand *remove = new RemoveCommand(xPos, yPos, editor);
    histCmds.ExecuteCmd(remove);
}

void ECTextDocumentCtrl :: RemoveRowAt(int xPos, int yPos, Editor &editor) {
    RowBackspaceCommand *rowBackspace = new RowBackspaceCommand(xPos, yPos, editor);
    histCmds.ExecuteCmd(rowBackspace);
}

void ECTextDocumentCtrl :: InsertRowAt(int xPos, int yPos, Editor &editor) {
    EnterCommand *enter = new EnterCommand(xPos, yPos, editor);
    histCmds.ExecuteCmd(enter);
}

void ECTextDocumentCtrl :: Undo() { histCmds.Undo(); }
void ECTextDocumentCtrl :: Redo() { histCmds.Redo(); }



// ********************************
// Implementation of observer class
// ********************************

 // constructor to initialize the window and the observer
Editor::Editor() : docCtrl(*this) {
    numRows = 0;
    wnd.AddStatusRow("", "", false);    // status row to temporarily fix bug of first row not showing
    
    // add three lines of example text using AddLine function
    this->InsertRow("");
    this->InsertRow("Press ctrl-q to quit");

    // add the lines in the observer to the window
    for (auto line : text)
        wnd.AddRow(line);

    wnd.Attach(this);   // attach this observer to the window
    wnd.Show();         // start the editor
}

void Editor::Update() {     // function called by window using Notify()
    keyPressed = wnd.GetPressedKey();

    if (keyPressed >= 1000 && keyPressed <= 1003) {     // handle arrow key
        ArrowHandle(keyPressed);
    } else if (keyPressed == 13) {                      // handle enter key
        EnterHandle();
    } else if (keyPressed == 127) {                     // handle backspace key
        BackspaceHandle();
    } else if (keyPressed == 26) {                      // handle undo key
        docCtrl.Undo();
    } else if (keyPressed == 25) {                      // handle redo key
        docCtrl.Redo();
    } else {                                            // insert character
        CharHandle(keyPressed);
    }
    
    // refresh the window after changes
    wnd.InitRows();
    for (auto line : text)
        wnd.AddRow(line);
}

// set the cursor
void Editor::SetCursor(int x, int y) {
    cX = x;
    cY = y;
    wnd.SetCursorX(cX);
    wnd.SetCursorY(cY);
}

// function to insert a single char at position
void Editor::InsertCharAt(int xPos, int yPos, char ch) {
    text[yPos].insert(xPos, 1, ch);     // insert ch at xPos
}

// function erase a single char at position
void Editor::RemoveCharAt(int xPos, int yPos) {
    text[yPos].erase(xPos, 1);          // remove char at xPos
}

// function used to add a line to the editor
void Editor::InsertRow(std::string line) {
    text.push_back(line);
    numRows += 1;
}

// function used for backspace / enter when merging two rows
void Editor::RemoveRowAt(int yPos) {
    //text[yPos - 1] += " ";
    text[yPos - 1] += text[yPos];
    text.erase(text.begin() + yPos);
    numRows -= 1;
}

// function used for enter / backspace when unmerging two lines
void Editor::InsertRowAt(int yPos, std::string _row_deleted, int row_length) {
    text[yPos - 1] = text[yPos - 1].substr(0, (int)text[yPos - 1].size() - row_length);
    text.insert(text.begin() + yPos, _row_deleted);
    numRows += 1;
}

std::vector<std::string> Editor::GetText() { return text; }



// ***************************************************************
// Handler functions for arrows, characters, enter/backspace, etc.
// ***************************************************************

// function used to handle arrow keys for cursor movement
void Editor::ArrowHandle(int keyPressed) {
    
    cX = wnd.GetCursorX();  // get the x-position of the cursor 
    cY = wnd.GetCursorY();  // get the y-position of the cursor

    // these if-statments basically check if the key is left, right, up, or down,
    // and then moves the cursor while making sure the new position is valid.
    if (keyPressed == 1000) {           // left
        if (cX > 0) {
            cX -= 1;
        } else if (cX == 0 && cY > 0) {
            cY -= 1;
            cX = (int)text[cY].size();
        }
    } else if (keyPressed == 1001) {    // right
        if (cX < (int)text[cY].size()) {
            cX += 1;
        } else if (cX == (int)text[cY].size() && cY < numRows) {
            cX = 0;
            cY += 1;
        }
    } else if (keyPressed == 1002) {    // up
        if (cY > 0) {
            if (cX < (int)text[cY - 1].size()) {
                cY -= 1;
            } else {
                cX = (int)text[cY - 1].size();
                cY -= 1;
            }
        }
    } else if (keyPressed == 1003) {    // down
        if (cY < numRows) {
            if (cX < (int)text[cY + 1].size()) {
                cY += 1;
            } else {
                cX = (int)text[cY + 1].size();
                cY += 1;
            }
        }
    }

    wnd.SetCursorX(cX);     // set the new x-position of the cursor
    wnd.SetCursorY(cY);     // set the new y-position of the cursor
}

// function used to handle the Enter key
void Editor::EnterHandle() {
    if (cX == (int)text[cY].size()) {
        // insert a new row at the next position
    } else {
        // insert a new row, and split the remaining text into the new row
        docCtrl.InsertRowAt(cX, cY, *this);
    }
}

// function used to handle the backspace / delete key
void Editor::BackspaceHandle() {
    if (cX == 0) {
        // delete this row and merge it with the one above
        docCtrl.RemoveRowAt(cX, cY, *this);
    } else {
        // delete a character
        docCtrl.RemoveTextAt(cX, cY, *this);
    }
}

// function used to handle insertion of normal characters
void Editor::CharHandle(int keyPressed) {
    docCtrl.InsertTextAt(cX, cY, keyPressed, *this);
}