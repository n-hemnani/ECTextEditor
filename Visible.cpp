#include "Visible.h"

Visible::Visible(int rows, int cols, std::vector<std::string> text, ECTextViewImp &wnd) :
    height(rows),
    width(cols),
    paragraphs(text),
    _wnd(wnd) {}

void Visible::Compose(std::vector<std::string> text) {
    paragraphs = text;
    std::vector<std::string> wrappedText;
    for (auto paragraph : paragraphs) {
        if (paragraph.length() <= width) {
            wrappedText.push_back(paragraph);
        } else {
            std::vector<std::string> wrappedParagraph = this->ComposeParagraph(paragraph);
            for (auto line : wrappedParagraph)
                wrappedText.push_back(line);
        }
    }

    _wnd.InitRows();
    for (auto line : wrappedText)
        _wnd.AddRow(line);
}

std::vector<std::string> Visible::ComposeParagraph(std::string paragraph) {
    std::vector<std::string> splitWords = this->SplitWords(paragraph);
    std::vector<std::string> composed;
    composed.push_back("");
    int currLength = 0;
    int currLine = 0;

    for (int i = 0; i < splitWords.size(); i++) {
        std::string word = splitWords[i];
        if (currLength + word.length() > width) {
            composed.push_back("");
            currLength = 0;
            currLine += 1;
        }
        composed[currLine] += word;
        currLength += word.size();
    }
    return composed;
}

std::vector<std::string> Visible::SplitWords(std::string paragraph) {
    std::vector<std::string> splitWords;
    int i = 0;
    while (true) {
        int index = (int)paragraph.find(' ', i);
        if (index == -1) {
            splitWords.push_back(paragraph.substr(i));
            return splitWords;        
        }

        std::string word = paragraph.substr(i, index - i);
        char next = paragraph.substr(index, 1)[0];

       if (next == ' ' || next == '\t') {
            splitWords.push_back(word);
            std::string s(1, next);
            splitWords.push_back(s);
        }

        i = index + 1;
    }
}