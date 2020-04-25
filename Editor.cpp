// IMPLEMENTATION FOR OBSERVER AND CONTROLLER

#include "Editor.h"

using namespace std;

// **************************************************************************************
// Controller for text document
// **************************************************************************************

ECTextDocumentCtrl :: ECTextDocumentCtrl(/*Editor &docIn*/) /*: doc(docIn)*/ {}
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




// **************************************************************************************
// Implementation of observer class
// **************************************************************************************

 // constructor to initialize the window and the observer
Editor::Editor(string name) /*: docCtrl(*this)*/ {
    nameoffile = name;                  // initialize the filename that is passed in
    numRows = 0;                        // there are 0 rows at the beginning
    wnd.AddStatusRow("", "", false);    // status row to temporarily fix bug of first row not showing
    
    ifstream infile(name.c_str());
    if (infile.good()) {
        string temp;
        while (getline(infile, temp)) {
            this->InsertRow(temp);
        }
        infile.close();
        this->InsertRow("");
        this->SetCursor(0, numRows - 1);
    } else {
        std::ofstream file { nameoffile };
        this->InsertRow("");
        this->SetCursor(0, 0);
    }

    // add the lines in the observer to the window
    for (auto line : text)
        wnd.AddRow(line);
    
    wnd.Attach(this);   // attach this observer to the window
    wnd.Show();         // start the editor
}

// function called by window using Notify()
void Editor::Update() {
    keyPressed = wnd.GetPressedKey();   // obtain the key

    if (keyPressed >= 1000 && keyPressed <= 1003) {     // arrow
        ArrowHandle(keyPressed);
    } else if (keyPressed == 13) {                      // enter
        EnterHandle();
    } else if (keyPressed == 127) {                     // backspace
        BackspaceHandle();
    } else if (keyPressed == 26) {                      // undo / ctrl z
        docCtrl.Undo();
    } else if (keyPressed == 25) {                      // redo / ctrl y
        docCtrl.Redo();
    } else if (keyPressed == 19) {                      // save / ctrl s
        // save
    } else {                                            // insert character
        CharHandle(keyPressed);
    }
    
    // refresh the window after changes have been made
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

// function to insert a single char at given position
void Editor::InsertCharAt(int xPos, int yPos, char ch) {
    text[yPos].insert(xPos, 1, ch);     // insert ch at xPos
}

// function erase a single char at given position
void Editor::RemoveCharAt(int xPos, int yPos) {
    text[yPos].erase(xPos, 1);          // remove char at xPos
}

// function used to add a line to the editor
void Editor::InsertRow(std::string line) {
    text.insert(text.begin() + numRows, line);
    numRows += 1;
}

// function used for backspace / enter when merging two rows
void Editor::RemoveRowAt(int yPos) {
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
    // insert a new row, and split the remaining text into the new row
    docCtrl.InsertRowAt(cX, cY, *this);
}

// function used to handle the backspace / delete key
void Editor::BackspaceHandle() {
    if (cY > 0 || cX > 0) {
        if (cX == 0) {
            // delete this row and merge it with the one above
            docCtrl.RemoveRowAt(cX, cY, *this);
        } else {
            // delete a character
            docCtrl.RemoveTextAt(cX, cY, *this);
        }
    }
}

// function used to handle insertion of normal characters
void Editor::CharHandle(int keyPressed) {
    docCtrl.InsertTextAt(cX, cY, keyPressed, *this);
}