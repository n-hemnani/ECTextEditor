// HEADER FILE FOR OBSERVER

#include "ECTextViewImp.h"

/* KEY ENUMERATION FOR REFERENCE
    CTRL_Y = 25,
    CTRL_Z = 26,
  KEY ENUMERATION FOR REFERENCE */

// main observer of ECTextViewImp
class Editor : public ECObserver {
public:
    Editor();
    ~Editor() {}

    void Update();                      // runs at every keystroke
    void ArrowHandle(int keyPressed);   // handles arrow key / cursor movement
    void EnterHandle();                 // handles Enter button
    void BackspaceHandle();             // handles backspace / delete button
    void TabHandle();                   // handles tab character
    void CharHandle(int keyPressed);     // default key handler
    
    void AddLine(std::string line);
    
private:
    ECTextViewImp wnd;              // window/subject
    std::vector<std::string> text;  // vector to hold all the lines of text
    int numRows;                    // number of lines of text in the editor
    int cX;                         // x-position of cursor
    int cY;                         // y-position of cursor
    int keyPressed;                 // alue of the key pressed, obtained from the window
};