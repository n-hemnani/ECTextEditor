#include "Editor.h"

Editor::Editor() {
    ECTextViewImp wndTest;
    wndTest.AddRow("CSE 3150");
    wndTest.AddRow("This is a very simple demo of the ECTextViewImp functionalities.");
    wndTest.AddRow("Press ctrl-q to quit");    
    wndTest.Show();
}

void Editor::Update() {
    ;
}