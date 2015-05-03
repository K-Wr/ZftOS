#include "../zftdef.h"
#include "../vector.h"
#include "registers.h"



#ifndef _ZFTOS_DEV_EXECUTABLE_H_
#define _ZFTOS_DEV_EXECUTABLE_H_



typedef uint32_t pid_t;



class Executable {
public:
    Executable(bool _screenNeeded/*, void(*main)()*/);
    virtual int schedule(Vector<char*> args) final;
    virtual int run(Vector<char*> args);
    virtual bool isActive() final;
    virtual void printArgs(Vector<char*>& args);
    virtual pid_t getPid();
private:
    friend class Scheduler;
    void saveContext();
    void loadContext();
    Registers registers;
    pid_t pid;
    bool active;
    bool isNewScreenNeeded;
};



#endif //_ZFTOS_DEV_EXECUTABLE_H_
