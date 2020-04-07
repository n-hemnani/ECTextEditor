// Test code for editor
#include "ECTextViewImp.h"
#include <iostream>

using namespace  std;

int myCounter = 0;

int main(int argc, char *argv[])
{
    //
    ECTextViewImp wndTest;
    wndTest.AddRow("CSE 3150");
    wndTest.AddRow("This is a very simple demo of the ECTextViewImp functionalities.");
    wndTest.AddRow("Press ctrl-q to quit");    

    wndTest.Show();
    
    return 0;
}
