#include "Command.h"
#include <vector>

using namespace std;

// ******************************************************
// Implement command history

CommandHistory :: CommandHistory() {}

CommandHistory :: ~CommandHistory() {}

bool CommandHistory :: Undo() {
    undoVec.back()->UnExecute();
    redoVec.push_back(undoVec.back());
    undoVec.pop_back();
    return true;
}

bool CommandHistory :: Redo() {
    redoVec.back()->Execute();
    undoVec.push_back(redoVec.back());
    redoVec.pop_back();
    return true;
}

void CommandHistory :: ExecuteCmd( Command *pCmd ) {
    while (redoVec.size() != 0)
      redoVec.pop_back();
    pCmd->Execute();
    undoVec.push_back(pCmd);
}