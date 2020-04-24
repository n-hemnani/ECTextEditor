// MAIN FILE FOR EDITOR

#include "Editor.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    string file;    // variable to hold filename
    if (argc == 2) {
        file = argv[1];         // set the provided filename
        Editor editor(file);    // start editor with provided filename
        return 0;               // return all good
    } else {
        cout << "Usage: ./ECTextEditor filename" << endl;   // tell user to include a filename
        return 1;
    }
}