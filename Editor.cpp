// IMPLEMENTATION FOR OBSERVER

#include "Editor.h"
#include <iostream>

using namespace std;

// ********
// Commands
// ********

class InsertCommand : public Command {
public:
    InsertCommand(int cX, int cY, int keyPressed, Editor &editor): 
        _cX(cX),
        _cY(cY),
        _key(keyPressed),
        _editor(editor)
    {};
	
    ~InsertCommand() {
        delete this;
    }
    
    void Execute() {
        _editor.InsertCharAt(_cX, _cY, static_cast<char>(_key));
        _editor.SetCursor(_cX + 1, _cY);
    }
    
    void UnExecute() {
        _editor.SetCursor(_cX - 1, _cY);
        _editor.RemoveCharAt(_cX, _cY);
    }
private:
    int _cX;
    int _cY;
    int _key;
    Editor &_editor;
};



// ****************************
// Controller for text document
// ****************************

ECTextDocumentCtrl :: ECTextDocumentCtrl(Editor &docIn) : doc(docIn) {}

ECTextDocumentCtrl :: ~ECTextDocumentCtrl() {}

void ECTextDocumentCtrl :: InsertTextAt(int xPos, int yPos, int ch, Editor &editor)
{
  InsertCommand *insert = new InsertCommand(xPos, yPos, ch, editor);
  histCmds.ExecuteCmd(insert);
}

void ECTextDocumentCtrl :: Undo()
{
    histCmds.Undo();
}

void ECTextDocumentCtrl :: Redo()
{
    histCmds.Redo();
}



// ********************************
// Implementation of observer class
// ********************************

 // constructor to initialize the window and the observer
Editor::Editor() : docCtrl(*this) {
    numRows = 0;
    wnd.AddStatusRow("", "", false);    // status row to temporarily fix bug of first row not showing
    
    // add three lines of example text using AddLine function
    this->InsertRow("CSE 3150");
    this->InsertRow("This is a very simple demo of the ECTextViewImp functionalities.");
    this->InsertRow("Press ctrl-q to quit");

    // add the lines in the observer to the window
    for (auto line : text) {
        wnd.AddRow(line);
        numRows += 1;
    }

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
    } else if (keyPressed == 9) {                       // handle tab key
        TabHandle();
    } else {                                            // insert character
        CharHandle(keyPressed);
    }
}
// function to insert a single char at position
void Editor::InsertCharAt(int xPos, int yPos, char ch) {
    text[yPos].insert(xPos, 1, ch);
}

// function erase a single char at position
void Editor::RemoveCharAt(int xPos, int yPos) {
    text[yPos].erase(xPos);;
}

// function used to add a line to the editor
void Editor::InsertRow(std::string line) {
    text.push_back(line);
    numRows += 1;
}

void Editor::SetCursor(int x, int y) {
    cX = x;
    cY = y;
}



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
        // shift the cursor one row down, at the beginning of the new row
    } else {
        // insert a new row, and split the remaining text into the new row
         // shift the cursor one row down, at the beginning of the new row
    }
}

// function used to handle the backspace / delete key
void Editor::BackspaceHandle() {
    if (cX == 0) {
        // delete this row and merge it with the row above
        // move the cursor up one row, to the end of the row
    } else {
        // delete the preceding character
        // shift the cursor to the left by one
    }
}

// function used to handle the tab button
void Editor::TabHandle() {
    // insert four spaces at the current cursor position
}

// function used to handle insertion of normal characters
void Editor::CharHandle(int keyPressed) {
    docCtrl.InsertTextAt(cX, cY, keyPressed, *this);
}