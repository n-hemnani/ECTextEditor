#include "Command.h"
#include "ECTextDocument.h"
#include <vector>

// ******************************************************
// Implement command history

ECCommandHistory :: ECCommandHistory() {}

ECCommandHistory :: ~ECCommandHistory() {}

bool ECCommandHistory :: Undo() {
	undoVec.back()->UnExecute();
    redoVec.push_back(undoVec.back());
    undoVec.pop_back();
    return true;
}

bool ECCommandHistory :: Redo() {
    redoVec.back()->Execute();
    undoVec.push_back(redoVec.back());
    redoVec.pop_back();
    return true;
}

void ECCommandHistory :: ExecuteCmd( ECCommand *pCmd ) {
	while (redoVec.size() != 0)
		redoVec.pop_back();
	pCmd->Execute();
	undoVec.push_back(pCmd);
}

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