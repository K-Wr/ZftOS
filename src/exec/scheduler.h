#include "../zftdef.h"
#include "executable.h"
#include "../vector.h"



#ifndef ZFTOS_DEV_SCHEDULER_H
#define ZFTOS_DEV_SCHEDULER_H



class Scheduler{
public:
    Scheduler();
    void createTask(Executable* task);
    void removeTask(Executable* task);
    bool isPresent(Executable* task);
    void switchToNextTask();
    void passControl();
    int64_t getLocation();
private:
    friend void switch_tasks_c();
    bool isControlPassed;
    Executable* getNextTask();
    Executable* currentTask;
    Vector<Executable*> tasks;
};



#endif //ZFTOS_DEV_SCHEDULER_H
