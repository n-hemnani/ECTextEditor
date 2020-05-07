#ifndef Visible_h
#define Visible_h

#include "ECTextViewImp.h"
#include <iostream>
#include <string>
#include <vector>

class Editor;

class Visible {
public:
    Visible(int rows, int cols, std::vector<std::string> text, ECTextViewImp &wnd);
    ~Visible() {}

    void Compose(std::vector<std::string> text);
    std::vector<std::string> ComposeParagraph(std::string paragraph);
    std::vector<std::string> SplitWords(std::string paragraph);

    void ComposeCursor(int length, Editor &editor);

    std::vector<std::string> GetViewText();
private:
    int height;
    int width;
    std::vector<std::string> paragraphs;
    std::vector<std::string> wrappedText;
    ECTextViewImp &_wnd;
};

#endif