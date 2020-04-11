#include "ECTextDocument.h"
#include <iostream>
#include <cctype>

using namespace std;

// **********************************************************
// Controller for text document

ECTextDocumentCtrl :: ECTextDocumentCtrl(ECTextDocument &docIn) : doc(docIn) {}
ECTextDocumentCtrl :: ~ECTextDocumentCtrl() {}

void ECTextDocumentCtrl :: InsertTextAt(int pos, const std::vector<char> &listCharsToIns)
{
  InsertCommand *insert = new InsertCommand(pos, listCharsToIns, doc);
  histCmds.ExecuteCmd(insert);
}

void ECTextDocumentCtrl :: RemoveTextAt(int pos, int lenToRemove)
{
  RemoveCommand *remove = new RemoveCommand(pos, lenToRemove, doc);
  histCmds.ExecuteCmd(remove);
}

bool ECTextDocumentCtrl :: Undo()
{
  return histCmds.Undo();
}

bool ECTextDocumentCtrl :: Redo()
{
  return histCmds.Redo();
}

// **********************************************************
// Document for text document

ECTextDocument :: ECTextDocument() : docCtrl(*this) {}

ECTextDocument :: ~ECTextDocument() {}

ECTextDocumentCtrl & ECTextDocument :: GetCtrl()
{
    return docCtrl;
}

char ECTextDocument :: GetCharAt(int pos) const
{
    return listChars[pos];
}

void ECTextDocument :: InsertCharAt(int pos, char ch)
{
  listChars.insert(listChars.begin() + pos, ch);
}

void ECTextDocument :: RemoveCharAt(int pos)
{
  listChars.erase(listChars.begin() + pos);
}