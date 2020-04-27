#include "Visible.h"

using namespace std;

Visible::Visible(int rows, int cols, vector<string> text, ECTextViewImp &wnd) :
    height(rows),
    width(cols),
    paragraphs(text),
    wnd(wnd) {}

void Visible::Compose(vector<string> text) {
    paragraphs = text;
    vector<string> wrappedText;
    for (auto paragraph : paragraphs) {
        if (paragraph.size() <= width) {
            wrappedText.push_back(paragraph);
        } else {
            vector<string> wrappedParagraph = this->ComposeParagraph(paragraph);
            for (auto line : wrappedParagraph)
                wrappedText.push_back(line);
        }
    }
    
    wnd.InitRows();
    for (auto line : wrappedText)
        wnd.AddRow(line);
}

vector<string> Visible::ComposeParagraph(string paragraph) {
    vector<string> splitWords = this->SplitWords(paragraph);
    vector<string> composed;
    composed.push_back("");
    int currLength = 0;
    int currLine = 0;

    for (int i = 0; i < splitWords.size(); i++) {
        string word = splitWords[i];
        if (currLength + word.size() <= width) {
            composed[currLine] += word;
            currLength += (int)word.size();
        } else {
            if (currLength > 0) {
                composed.push_back("");
                currLength = 0;
                currLine++;
            }

            // more code to split word if it's too long for a line

        }
    }
}

vector<string> Visible::SplitWords(string paragraph) {
    vector<string> splitWords;
    int i = 0;
    while (true) {
        int index = (int)paragraph.find(' ', i);
        if (index == -1) {
            splitWords.push_back(paragraph.substr(i));
            return splitWords;        
        }

        string word = paragraph.substr(i, index - i);
        char next = paragraph.substr(index, 1)[0];

       if (next == ' ' || next == '\t') {
            splitWords.push_back(word);
            string s(1, next);
            splitWords.push_back(s);
        }

        i = index + 1;
    }
    return splitWords;
}