#include "ECTextViewImp.h"

class Editor : public ECObserver {
public:
    Editor();
    ~Editor() {}

    void Update();
private:
    ECTextViewImp wndTest;
};