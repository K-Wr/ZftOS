#include "executable.h"
#include "../kernel.h"
#include "../output/terminalstatebuffer.h"
#include "../iob.h"


Executable::Executable(bool _screenNeeded) {
    pid = 0;
    isNewScreenNeeded = _screenNeeded;
    registers.ebp = 0;
    registers.eip = 0;
    registers.esp;
}



/*Is not pure virtual due to some problems with vatable while compiling */
int Executable::run(Vector<char*> args) {
    Kernel::out.puts("ERROR EXECUTING");
    args.empty();
    return -1;
}



bool Executable::isActive() {
    return active;
}



int Executable::schedule(Vector<char*> args) {
    char* previousStatus = new char[81];

    Kernel::out.getStatus(previousStatus);
    TerminalStateBuffer* buffer = nullptr;

    if (isNewScreenNeeded) {
        buffer = new TerminalStateBuffer();
        Kernel::out.saveToBuffer(buffer);

    }
    Kernel::out.putsln("\nSEND TO SCHEDULER TO CREATE TASK");
    Kernel::scheduler.createTask(this);
    Kernel::out.putsln("TASK CREATED");
    active = true;
    Kernel::out << "CALLED RUN\n";
    int retval = run(args);
    active = false;
    //Kernel::scheduler->removeTask(this);
    if (buffer != nullptr) {
        Kernel::out.restoreFromBuffer(buffer);

    }
    Kernel::out.setStatus(previousStatus);
    delete previousStatus;
    return retval;
}



void Executable::printArgs(Vector<char *> &args) {
    for (auto i = args.begin(); i != args.end(); ++i) {
        Kernel::out.putsln(*i);
    }
}



pid_t Executable::getPid() {
    return pid;
}



/*TODO: IMPLEMENT THESE*/
void Executable::saveContext() {

}



void Executable::loadContext() {

}
