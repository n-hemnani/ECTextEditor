// HEADER FILE FOR OBSERVER AND CONTROLLER

#ifndef Editor_h
#define Editor_h

#include "ECTextViewImp.h"
#include "Command.h"

class Editor;

class ECTextDocumentCtrl
{
public:
    ECTextDocumentCtrl(Editor &docIn);          // conroller constructor takes the document as input
    virtual ~ECTextDocumentCtrl();
    void InsertTextAt(int xPos, int yPos, int ch, Editor &editor);
    void RemoveTextAt(int xPos, int yPos, Editor &editor);
    void InsertRowAt(int xPos, int yPos, Editor &editor);
    void RemoveRowAt(int xPos, int yPos, Editor &editor);
    void Undo();
    void Redo();
    
private:
    Editor &doc;
    CommandHistory histCmds;
};

// main observer of ECTextViewImp
class Editor : public ECObserver {
public:
    Editor();
    ~Editor() {}

    void Update();                      // runs at every keystroke
    
    void ArrowHandle(int keyPressed);   // handles arrow key / cursor movement
    void EnterHandle();                 // handles Enter button
    void BackspaceHandle();             // handles backspace / delete button
    void CharHandle(int keyPressed);    // default key handler

    void SetCursor(int x, int y);                       // changes cursor position to x, y. for undo/redo commands
    void InsertCharAt(int xPos, int yPos, char ch);     // insert a single char at position
    void RemoveCharAt(int xPos, int yPos);              // erase a single char at position
    void InsertRow(std::string line, int yPos);         // insert a row
    void RemoveRowAt(int yPos);                         // remove a specific row             
    void InsertRowAt(int yPos, std::string _row_deleted, int row_length);   // insert a specific row
    
    std::vector<std::string> GetText(); // return text
    
private:
    ECTextViewImp wnd;                  // window/subject
    ECTextDocumentCtrl docCtrl;         // document controller
    std::vector<std::string> text;      // vector to hold all the lines of text
    int numRows;                        // number of lines of text in the editor
    int cX;                             // x-position of cursor
    int cY;                             // y-position of cursor
    int keyPressed;                     // alue of the key pressed, obtained from the window
};

#endif