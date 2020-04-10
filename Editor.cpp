#include "Editor.h"
#include "ECCommand.h"
#include <iostream>

using namespace std;

Editor::Editor() {
    numRows = 0;
    wnd.AddStatusRow("", "", false);
    
    this->AddLine("CSE 3150");
    this->AddLine("This is a very simple demo of the ECTextViewImp functionalities.");
    this->AddLine("Press ctrl-q to quit");
    for (auto line : text) {
        wnd.AddRow(line);
        numRows += 1;
    }

    wnd.SetCursorX(1);
    wnd.SetCursorY(1);
    wnd.Attach(this); 
    wnd.Show();
}

void Editor::Update() {
    keyPressed = wnd.GetPressedKey();
    if (keyPressed >= 1000 && keyPressed <= 1003) {
        ArrowHandle(keyPressed);
    }
}

void Editor::ArrowHandle(int keyPressed) {
    cX = wnd.GetCursorX();
    cY = wnd.GetCursorY();

    if (keyPressed == 1000) {           // left
        if (cX > 0) {
            cX -= 1;
            wnd.SetCursorX(cX);
        } else if (cX == 0 && cY > 0) {
            cY -= 1;
            cX = (int)text[cY].size();
            wnd.SetCursorX(cX);
            wnd.SetCursorY(cY);
        }
    } else if (keyPressed == 1001) {    // right

    } else if (keyPressed == 1002) {    // up
        
    } else if (keyPressed == 1003) {    // down
        
    }
}

void Editor::AddLine(std::string line) {
    text.push_back(line);
    numRows += 1;
}