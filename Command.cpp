#include "Command.h"
#include "Editor.h"
#include <vector>

using namespace std;

// ******************************************************
// Implement command history

CommandHistory :: CommandHistory() {}

CommandHistory :: ~CommandHistory() {}

bool CommandHistory :: Undo() {
    if (!undoVec.empty()) {
        undoVec.back()->UnExecute();
        redoVec.push_back(undoVec.back());
        undoVec.pop_back();
        return true;
    }
    return false;
}

bool CommandHistory :: Redo() {
    if (!redoVec.empty()) {
        redoVec.back()->Execute();
        undoVec.push_back(redoVec.back());
        redoVec.pop_back();
        return true;
    }
    return false;
}

void CommandHistory :: ExecuteCmd( Command *pCmd ) {
    while (redoVec.size() != 0)
      redoVec.pop_back();
    pCmd->Execute();
    undoVec.push_back(pCmd);
}

// ****************************************************************
// Implement commands

// InsertCommand
InsertCommand::InsertCommand(int cX, int cY, int keyPressed, Editor &editor): 
    _cX(cX),
    _cY(cY),
    _key(keyPressed),
    _editor(editor)
{};

InsertCommand :: ~InsertCommand() { delete this; }

void InsertCommand::Execute() {
    _editor.InsertCharAt(_cX, _cY, static_cast<char>(_key));
    _editor.SetCursor(_cX + 1, _cY);
}

void InsertCommand::UnExecute() {
    _editor.SetCursor(_cX, _cY);
    _editor.RemoveCharAt(_cX, _cY);
}

// RemoveCommand
RemoveCommand::RemoveCommand(int cX, int cY, Editor &editor): 
    _cX(cX),
    _cY(cY),
    _editor(editor)
{};

RemoveCommand :: ~RemoveCommand() { delete this; }

void RemoveCommand::Execute() {
    _key_deleted = _editor.GetText()[_cY][_cX - 1];
    _editor.SetCursor(_cX - 1, _cY);
    _editor.RemoveCharAt(_cX - 1, _cY);
}

void RemoveCommand::UnExecute() {
    _editor.InsertCharAt(_cX - 1, _cY, _key_deleted);
    _editor.SetCursor(_cX, _cY);
}

// RowBackspaceCommand
RowBackspaceCommand::RowBackspaceCommand(int cX, int cY, Editor &editor): 
    _cX(cX),
    _cY(cY),
    _editor(editor)
{};

RowBackspaceCommand :: ~RowBackspaceCommand() { delete this; }

void RowBackspaceCommand::Execute() {
    _row_deleted = _editor.GetText()[_cY];
    _row_length = (int)_row_deleted.size();

    _cX = (int)_editor.GetText()[_cY - 1].size();
    _editor.SetCursor(_cX, _cY - 1);
    
    _editor.RemoveRowAt(_cY);
}

void RowBackspaceCommand::UnExecute() {
    _editor.InsertRowAt(_cY, _row_deleted, _row_length);
    _editor.SetCursor(0, _cY);
}

// EnterCommand
EnterCommand::EnterCommand(int cX, int cY, Editor &editor): 
    _cX(cX),
    _cY(cY),
    _editor(editor)
{};

EnterCommand :: ~EnterCommand() { delete this; }

void EnterCommand::Execute() {
    if (_cX == (int)_editor.GetText()[_cY].size()) {
        _row_entered = "";
        _row_length = 0;
    } else {
        _row_entered = _editor.GetText()[_cY].substr(_cX, (int)_editor.GetText()[_cY].size());
        _row_length = (int)_row_entered.size();
    }
    _editor.InsertRowAt(_cY + 1, _row_entered, _row_length);
    _editor.SetCursor(0, _cY + 1);
}

void EnterCommand::UnExecute() {
    _editor.RemoveRowAt(_cY + 1);
    _editor.SetCursor(_cX, _cY);
}