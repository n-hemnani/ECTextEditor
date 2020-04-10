#include "ECTextDocument.h"
#include <iostream>
#include <cctype>

using namespace std;

// **********************************************************
// Commands

// your code goes here /*
class InsertCommand : public ECCommand
{
public:
	InsertCommand(int pos, vector<char> listCharsToIns, ECTextDocument& doc): 
    position(pos),
    charsToIns(listCharsToIns),
    _doc(doc)
  {};
	
	~InsertCommand() {
		delete this;
	}
    
    void Execute() {
    	for (int i = 0; i < charsToIns.size(); i++) {
  			_doc.InsertCharAt(position + i, charsToIns[i]);
		  }
    }
    
    void UnExecute() {
      for (int i = 0; i < charsToIns.size(); i++) {
        _doc.RemoveCharAt(position);
      }
    }

private:
	int position;
	std::vector<char> charsToIns;
	ECTextDocument &_doc;
};


class RemoveCommand : public ECCommand
{
public:
	RemoveCommand(int pos, int lenToRemove, ECTextDocument& doc): 
    position(pos),
    _lenToRemove(lenToRemove),
    _doc(doc)
  {};
	
	~RemoveCommand() {
		delete this;
	}
    
  void Execute() {
    for (int i = 0; i < _lenToRemove; i++) {
      _doc.RemoveCharAt(position);
    }
  }
  
  void UnExecute() {
    for (int i = 0; i < charsToIns.size(); i++) {
      _doc.InsertCharAt(position + i, charsToIns[i]);
    }
  }

private:
	int position;
  int _lenToRemove;
	std::vector<char> charsToIns;
	ECTextDocument &_doc;
};


class CapCommand : public ECCommand
{
public:
	CapCommand(int pos, int lenToCap, ECTextDocument& doc): 
    position(pos),
    _lenToCap(lenToCap),
    _doc(doc)
  {};
	
	~CapCommand() {
		delete this;
	}
    
  void Execute() {
    for (int i = 0; i < _lenToCap; i++) {
  	  _doc.CapCharAt(position + i);
    }
  }
  
  void UnExecute() {
    for (int i = 0; i < _lenToCap; i++) {
  	  _doc.LowerCharAt(position + i);
    }
  }

private:
	int position;
  int _lenToCap;
	ECTextDocument &_doc;
};


class LowerCommand : public ECCommand
{
public:
	LowerCommand(int pos, int lenToLower, ECTextDocument& doc): 
    position(pos),
    _lenToLower(lenToLower),
    _doc(doc)
  {};
	
	~LowerCommand() {
		delete this;
	}
    
  void Execute() {
    for (int i = 0; i < _lenToLower; i++) {
  	  _doc.LowerCharAt(position + i);
    }
  }
  
  void UnExecute() {
    for (int i = 0; i < _lenToLower; i++) {
  	  _doc.CapCharAt(position + i);
    }
  }

private:
	int position;
  int _lenToLower;
	ECTextDocument &_doc;
};


// **********************************************************
// Controller for text document

ECTextDocumentCtrl :: ECTextDocumentCtrl(ECTextDocument &docIn) : doc(docIn)
{
}

ECTextDocumentCtrl :: ~ECTextDocumentCtrl()
{
}

void ECTextDocumentCtrl :: InsertTextAt(int pos, const std::vector<char> &listCharsToIns)
{
  // your code
  InsertCommand *insert = new InsertCommand(pos, listCharsToIns, doc);
  histCmds.ExecuteCmd(insert);
}

void ECTextDocumentCtrl :: RemoveTextAt(int pos, int lenToRemove)
{
  // your code
  RemoveCommand *remove = new RemoveCommand(pos, lenToRemove, doc);
  histCmds.ExecuteCmd(remove);
}

void ECTextDocumentCtrl :: CapTextAt(int pos, int lenToCap)
{
  // your code
  CapCommand *cap = new CapCommand(pos, lenToCap, doc);
  histCmds.ExecuteCmd(cap);
}

void ECTextDocumentCtrl :: LowerTextAt(int pos, int lenToLower)
{
  // your code
  LowerCommand *lower = new LowerCommand(pos, lenToLower, doc);
  histCmds.ExecuteCmd(lower);
}

bool ECTextDocumentCtrl :: Undo()
{
  // your code
  return histCmds.Undo();
}

bool ECTextDocumentCtrl :: Redo()
{
  // your code
  return histCmds.Redo();
}

// **********************************************************
// Document for text document


ECTextDocument :: ECTextDocument() : docCtrl(*this)
{
}

ECTextDocument :: ~ECTextDocument()
{
}

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
  // your code here
  listChars.insert(listChars.begin() + pos, ch);
}

void ECTextDocument :: RemoveCharAt(int pos)
{
  // your code here
  listChars.erase(listChars.begin() + pos);
}

void ECTextDocument :: CapCharAt(int pos)
{
  // your code here
  listChars[pos] = toupper(listChars[pos]);
}

void ECTextDocument :: LowerCharAt(int pos)
{
  // your code here
  listChars[pos] = tolower(listChars[pos]);
}