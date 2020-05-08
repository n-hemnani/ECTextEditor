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
    
    ifstream infile(name.c_str());      // try opening the file
    if (infile.good()) {                // if the file exists, read it into the editor
        string temp;
        while (getline(infile, temp)) { // read the file line by line
            this->InsertRow(temp);      // and add each line to editor
        }
        infile.close();                     // close the file
    } else {
        std::ofstream file { nameoffile };  // else, create the new file and
        this->InsertRow("");                // initialize it to empty text
    }

    this->InsertRow("");

    this->SetCursor(0, 0);              // set the cursor
    this->Compose();

    wnd.Attach(this);   // attach this editor to the window
    wnd.Show();         // start the editor
}

// function called by window using Notify()
void Editor::Update() {
    keyPressed = wnd.GetPressedKey();   // obtain the key

    viewText = vis.GetViewText();
    rowsInView = (int)viewText.size();

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
        SaveHandle();
    } else if (keyPressed == 17) {                      // quit / ctrl q
        SaveHandle();
        wnd.Quit();
        for(int i = 0; i < 50; i++)
	        cout << endl;
    } else {                                            // insert character
        CharHandle(keyPressed);
    }

    this->Compose();
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
    if (text[yPos].size() != 0)
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

std::vector<std::string> Editor::GetViewText() { return viewText; }

int Editor::GetViewCols() { return wndCols; }

void Editor::Compose() { 
    vis.Compose(text);
    viewText = vis.GetViewText();
    rowsInView = (int)viewText.size();
}

 void Editor::ComposeCursor(int length) {
     vis.ComposeCursor(length, *this);
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
            cX = (int)viewText[cY].size();
        }
    } else if (keyPressed == 1001) {    // right
        if (cX < (int)viewText[cY].size()) {
            cX += 1;
        } else if (cX == (int)viewText[cY].size() && cY < rowsInView - 1) {
            cX = 0;
            cY += 1;
        }
    } else if (keyPressed == 1002) {    // up
        if (cY > 0) {
            if (cX < (int)viewText[cY - 1].size()) {
                cY -= 1;
            } else {
                cX = (int)viewText[cY - 1].size();
                cY -= 1;
            }
        }
    } else if (keyPressed == 1003) {    // down
        if (cY < rowsInView) {
            if (cX < (int)viewText[cY + 1].size()) {
                cY += 1;
            } else {
                cX = (int)viewText[cY + 1].size();
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
            // delete character at the beginning of the row (and merge paragraph if needed)
            int length = 0;
            for (int i = 0; i < cY; i++)
                length += (int)GetViewText()[i].size();
            
            int trueY = 0;
            int sum = 0;
            while (sum + GetText()[trueY].size() <= length) {
                sum += (int)GetText()[trueY].size();
                trueY++;
            }

            if (length - sum == 0) {
                docCtrl.RemoveRowAt(cX, cY, *this);
            } else {
                docCtrl.RemoveTextAt(cX, cY, *this);
            }
        } else {
            // delete a character
            docCtrl.RemoveTextAt(cX, cY, *this);
        }
    }
}

void Editor::SaveHandle() {
    fstream outfile;
    outfile.open(nameoffile);
    if (outfile.is_open()) {
        for (auto line : text) {
            outfile << line;
            outfile << "\n";
        }
    }
    outfile.close();
}

// function used to handle insertion of normal characters
void Editor::CharHandle(int keyPressed) {
    docCtrl.InsertTextAt(cX, cY, keyPressed, *this);
}