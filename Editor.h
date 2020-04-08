#include "ECTextViewImp.h"

// first key handler: will chain down to other key handlers
class KeyHandler {
public:
    KeyHandler(ECTextViewImp& wnd) : wnd(wnd) {}
    ~KeyHandler() {}

    virtual bool Handle(int keyPressed);
private:
    ECTextViewImp &wnd;
};

// main observer of ECTextViewImp
class Editor : public ECObserver {
public:
    Editor();
    ~Editor() {}

    void Update();
    
    void AddLine(std::string line);
private:
    ECTextViewImp wnd;
    KeyHandler kh = KeyHandler(wnd);
    std::vector<std::string> text;
    int numRows;
    int keyPressed;
};