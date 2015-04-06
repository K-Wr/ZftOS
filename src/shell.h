#include "kernel.h"
#ifndef SHELL_H
#define SHELL_H


class Shell
{
public:
	Shell();
	void run();
	void calc();
	void setGMT();
	void cowsay();
	void printTime();
	~Shell();
private:
	void runMemTest();
	char buff[60];
	void getCommand();
};


#endif /*SHELL_H*/