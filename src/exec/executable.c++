#include "executable.h"
#include "../kernel.h"
#include "../output/terminalstatebuffer.h"


Executable::Executable(bool _screenNeeded) {
    isNewScreenNeeded = _screenNeeded;
}



int Executable::run(Vector<char*> args) {
    Kernel::out->puts("ERROR EXECUTING");
    args.empty();
    return -1;
}



bool Executable::isActive() {
    return active;
}



int Executable::schedule(Vector<char*> args) {
    char* previousStatus = new char[81];

    Kernel::out->getStatus(previousStatus);
    TerminalStateBuffer* buffer = nullptr;
    if (isNewScreenNeeded) {
        buffer = new TerminalStateBuffer();
        Kernel::out->saveToBuffer(buffer);
    }
    Kernel::scheduler->createTask(this);
    active = true;
    int retval = run(args);
    active = false;
    //Kernel::scheduler->removeTask(this);
    if (buffer != nullptr) {
        Kernel::out->restoreFromBuffer(buffer);

    }
    Kernel::out->setStatus(previousStatus);
    return retval;
}



void Executable::printArgs(Vector<char *> &args) {
    for (auto i = args.begin(); i != args.end(); ++i) {
        Kernel::out->putsln(*i);
    }
}