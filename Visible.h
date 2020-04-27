#ifndef Visible_h
#define Visible_h

#include "Editor.h"

using namespace std;

class Paragraph;

class Visible {
public:
    Visible(int rows, int cols, vector<string> text, ECTextViewImp& wnd);
    ~Visible() {}

    void Compose(vector<string> text);
    vector<string> ComposeParagraph(string paragraph);
    vector<string> SplitWords(string paragraph);
private:
    ECTextViewImp &wnd;
    vector<string> paragraphs;
    int height;
    int width;
};

#endif