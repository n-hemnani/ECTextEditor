#include "ECTextDocument.h"
#include <iostream>
#include <cctype>

using namespace std;

// ****************************************************
// Command classes
// ****************************************************

class InsertCommand : public Command {
public:
    InsertCommand(int cX, int cY, int keyPressed, Editor &editor): 
        _cX(cX),
        _cY(cY),
        _key(keyPressed),
        _editor(editor)
    {};
	
    ~InsertCommand() {
        delete this;
    }
    
    void Execute() {
        _editor.InsertCharAt(_cX, _cY, static_cast<char>(_key));
        _editor.SetCursor(_cX + 1, _cY);
    }
    
    void UnExecute() {
        _editor.SetCursor(_cX - 1, _cY);
        _editor.RemoveCharAt(_cX, _cY);
    }
private:
    int _cX;
    int _cY;
    int _key;
    Editor &_editor;
};

// **********************************************************
// Controller for text document

ECTextDocumentCtrl :: ECTextDocumentCtrl(Editor &docIn) : doc(docIn) {}

ECTextDocumentCtrl :: ~ECTextDocumentCtrl() {}

void ECTextDocumentCtrl :: InsertTextAt(int xPos, int yPos, int ch, Editor &editor)
{
  InsertCommand *insert = new InsertCommand(xPos, yPos, ch, editor);
  histCmds.ExecuteCmd(insert);
}

void ECTextDocumentCtrl :: Undo()
{
    histCmds.Undo();
}

void ECTextDocumentCtrl :: Redo()
{
    histCmds.Redo();
}