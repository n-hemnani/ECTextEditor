//
//  ECTextDocument.h
//  
//
//  Created by Yufeng Wu on 2/26/20.
//
//

#ifndef ECTextDocument_h
#define ECTextDocument_h

#include "Command.h"
#include "Editor.h"

// ******************************
// Controller for document editor
// ******************************

class ECTextDocumentCtrl
{
public:
    ECTextDocumentCtrl(Editor &docIn);          // conroller constructor takes the document as input
    virtual ~ECTextDocumentCtrl();
    void InsertTextAt(int xPos, int yPos, int ch, Editor &editor);
    void RemoveTextAt(int pos, int lenToRemove);
    void Undo();    // ctrl_z 26
    void Redo();    // ctrl_y 25
    
private:
    Editor &doc;
    CommandHistory histCmds;
};

#endif