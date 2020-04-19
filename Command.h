//
//  Command.h
//  
//
//  Created by Yufeng Wu on 2/26/20.
//
//

#ifndef Command_h
#define Command_h

#include <vector>
#include <string>

class Editor;

// ******************************************************
// Implement command design pattern

class Command
{
public:
    virtual ~Command() {}
    virtual void Execute() = 0;
    virtual void UnExecute() = 0;
};

// ******************************************************
// Implement commands

class InsertCommand : public Command {
public:
    InsertCommand(int cX, int cY, int keyPressed, Editor &editor);
    ~InsertCommand();
    void Execute();
    void UnExecute();
private:
    int _cX, _cY, _key;
    Editor &_editor;
};

class RemoveCommand : public Command {
public:
    RemoveCommand(int cX, int cY, Editor &editor);
    ~RemoveCommand();
    void Execute();
    void UnExecute();
private:
    int _cX, _cY;
    char _key_deleted;
    Editor &_editor;
};

class RowBackspaceCommand : public Command {
public:
    RowBackspaceCommand(int cX, int cY, Editor &editor);
    ~RowBackspaceCommand();
    void Execute();
    void UnExecute();
private:
    int _cX, _cY, _row_length;
    std::string _row_deleted;
    Editor &_editor;
};

class EnterCommand : public Command {
public:
    EnterCommand(int cX, int cY, Editor &editor);
    ~EnterCommand();
    void Execute();
    void UnExecute();
private:
    int _cX, _cY, _row_length;
    std::string _row_entered;
    Editor &_editor;
};

// ******************************************************
// Implement command history

class CommandHistory
{
public:
    CommandHistory();
    virtual ~CommandHistory();
    bool Undo();
    bool Redo();
    void ExecuteCmd( Command *pCmd );
    
private:
    // your code goes here
    std::vector<Command*> undoVec;
    std::vector<Command*> redoVec;
};


#endif /* Command_h */
