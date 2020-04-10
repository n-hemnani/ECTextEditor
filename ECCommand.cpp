#include "ECCommand.h"

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