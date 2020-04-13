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
