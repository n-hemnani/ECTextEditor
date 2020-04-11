#include "Editor.h"
#include "ECCommand.h"
#include <iostream>

using namespace std;

 // constructor to initialize the window and the observer
Editor::Editor() {
    numRows = 0;
    wnd.AddStatusRow("", "", false);    // status row to temporarily fix bug of first row not showing
    
    // add three lines of example text using AddLine function
    this->AddLine("CSE 3150");
    this->AddLine("This is a very simple demo of the ECTextViewImp functionalities.");
    this->AddLine("Press ctrl-q to quit");

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
    if (keyPressed >= 1000 && keyPressed <= 1003) {     // if it's an arrow key
        ArrowHandle(keyPressed);                        // ArrowHandle() will move the cursor
    }
}

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

// function used to add a line to the editor
void Editor::AddLine(std::string line) {
    text.push_back(line);
    numRows += 1;
}