#include "ECTextViewImp.h"

/* KEY ENUMERATION FOR REFERENCE
    TAB = 9,
    ENTER = 13,
    CTRL_Q = 17,
    CTRL_Y = 25,
    CTRL_Z = 26,
    ESC = 27,
    BACKSPACE =  127
  KEY ENUMERATION FOR REFERENCE */

// main observer of ECTextViewImp
class Editor : public ECObserver {
public:
    Editor();
    ~Editor() {}

    void Update();
    void ArrowHandle(int keyPressed);
    
    void AddLine(std::string line);
    
private:
    ECTextViewImp wnd;
    std::vector<std::string> text;
    int numRows;
    int cX;
    int cY;
    int keyPressed;
};