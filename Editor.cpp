#include "Editor.h"
#include <iostream>

using namespace std;

Editor::Editor() {
    numRows = 0;
    ECTextViewImp wnd;
    KeyHandler kh = KeyHandler(wnd);
    wnd.Attach(this); 
    wnd.AddStatusRow("left", "right", false);
    
    this->AddLine("CSE 3150");
    this->AddLine("This is a very simple demo of the ECTextViewImp functionalities.");
    this->AddLine("Press ctrl-q to quit");
    for (auto line : text)
        wnd.AddRow(line);

    wnd.Show();
}

/* KEY ENUMERATION FOR REFERENCE
    TAB = 9,
    ENTER = 13,
    CTRL_Q = 17,
    CTRL_Y = 25,
    CTRL_Z = 26,
    ESC = 27,
    BACKSPACE =  127,
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN
  KEY ENUMERATION FOR REFERENCE */

void Editor::Update() {
    keyPressed = wnd.GetPressedKey();
    kh.Handle(keyPressed);
    wnd.Refresh();
}

void Editor::AddLine(std::string line) {
    text.push_back(line);
    numRows += 1;
}

bool KeyHandler::Handle(int keyPressed) {
    return true;
}