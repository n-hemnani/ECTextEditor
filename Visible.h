#ifndef Visible_h
#define Visible_h

#include "ECTextViewImp.h"
#include <iostream>
#include <string>
#include <vector>

class Paragraph;

class Visible {
public:
    Visible(int rows, int cols, std::vector<std::string> text, ECTextViewImp &wnd);
    ~Visible() {}

    void Compose(std::vector<std::string> text);
    std::vector<std::string> ComposeParagraph(std::string paragraph);
    std::vector<std::string> SplitWords(std::string paragraph);
private:
    int height;
    int width;
    std::vector<std::string> paragraphs;
    ECTextViewImp &_wnd;
};

#endif