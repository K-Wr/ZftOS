#include "shell.h"
#include "../string.h"
#include "../time.h"
#include "../output/speaker.h"
#include "../output/terminalstatebuffer.h"
#include "clock.h"
#include "../interrupts.h"
#include "kbblink.h"
#include "taskingtest.h"
#include "displayclock.h"


const char helptext[] = "\tZunft OS ver. 0.7\n"
						"\tDeveloped by Kravchenko Viktor. Minsk, 2015\n"
						"\tList of supported commands\n"
						"\t\thelp  --  views this message\n"
						"\t\texit  --  power off\n"
						"\t\treboot -- restart pc\n"
						"\t\tcolor -- change output color\n"
						"\t\tcowsay ... -- cow says what you want it to\n"
						"\t\ttime -- get current time printed\n"
						"\t\tclock -- launch clock setting application\n"
						"\t\tkb -- launch keyboard blink app\n"
						"\t\tbeep -- play default melody using system speaker\n"
						"\t\tpiano -- play on keyboard like on piano\n"
						"\t\tcalc -- calculate something\n"
						"\t\tsetgmt -- setting current gmt";




Shell::Shell() : Executable(true) {

}



Shell::~Shell() {
}



void Shell::getCommand() {
	Kernel::out.puts("\n > ");
	size_t index = 0;
	while (true) {
		char c = Kernel::in.getchar();
		if (c == '\n') {
			buff[index] = 0;
			if (!is_empty(buff)) {
				Kernel::out.newLine();
				return;
			}
			else {
				return getCommand();
			}
		}
		else if (c == '\b') {
			if (index) {
				buff[index] = 0;
				index--;
				Kernel::out.putchar('\b');
			}
		}
		else {
			if (index < 59) {
				buff[index++] = c;
				Kernel::out.putchar(c);
			}
		}
	}
}



void Shell::printTime() {
	Time time = Time::getCurrentTime();
	Kernel::out.puts("Time: ");
	Kernel::out.putuint(time.day);
	Kernel::out.putchar('.');
	Kernel::out.putuint(time.month);
	Kernel::out.putchar('.');
	Kernel::out.putuint(time.year + 2000);
	Kernel::out.putchar(' ');
	Kernel::out.putuint(time.hour);
	Kernel::out.putchar(':');
	Kernel::out.putuint(time.minute);
	Kernel::out.putchar(':');
	Kernel::out.putuint(time.second);

}



int Shell::run(Vector<char*> args) {
	Kernel::out.clear();
	Kernel::out.putsln("\t\t\t\t\t\tWELCOME TO ZUNFT OS ver 0.7 SHELL!"
						"\nType \"help\" to get list of available commands");
	printArgs(args);
	TerminalStateBuffer* terminalStateBuffer = nullptr;

	printTime();
	Kernel::out.setStatus("\t\t\t\t\t\t\tSHELL");
    /*DisplayClock displayClock;
    char buffer[25];
    strcpy(buffer, "ARG");
    args.push_back(buffer);
    displayClock.schedule(args);
	*/
    while (true) {
		getCommand();
		if (!strcmpic(buff, "help")) {
			Kernel::out.putsln(helptext);
		}
		else if (!strcmpic(buff, "exit")) {
			Kernel::exit(Kernel::SHUTDOWN);
		}
		else if (!strcmpic(buff, "reboot")) {
			Kernel::exit(Kernel::REBOOT);
		}
		else if (!strcmpic(buff, "color")) {
			Kernel::out.setColor((ColorByte) (Kernel::out.getColor() + 1));
			Kernel::out.redraw();
		}
		else if (!strcmpic(buff, "time")) {
			Kernel::out.putchar('\n');
			printTime();
			Kernel::out.putchar('\n');
		}
		else if (!strcmpic(buff, "alloctest")) {
			runMemTest();
		}
		else if (!strcmpic(buff, "setgmt")) {
			setGMT();
		}
		else if (!strcmpic(buff, "beep")) {
			Speaker::playDefaultMelody();
		}
		else if (!strcmpic(buff, "calc")) {
			calc();
		}
		else if (!strcmpic(buff, "cowsay")) {
			cowsay();
		}
		else if (!strcmpic(buff, "save")) {
			terminalStateBuffer = new TerminalStateBuffer(Kernel::out);
		}
		else if (!strcmpic(buff, "load")) {
			if (terminalStateBuffer != nullptr) {
				Kernel::out.restoreFromBuffer(terminalStateBuffer);
				delete terminalStateBuffer;
				terminalStateBuffer = nullptr;
			}
		}
		else if (!strcmpic(buff, "piano")) {
			piano();
		}
		else if (!strcmpic(buff, "clock")) {
			Clock().scheduleAbove(0);
		}
		else if (!strcmpic(buff, "alarm")) {
			Kernel::out.alarm("ALARM", 0);
		}
		else if (!strcmpic(buff, "kb")) {
			KbBlink().scheduleAbove(0);
		}
		else if (!strcmpic(buff, "ttest")) {
			TaskingTest().scheduleAbove(0);
		}
		else if (!strcmpic(buff, "pi")) {
			Kernel::scheduler.showTaskInfo();
		}
		else {
			Kernel::out.puts("Command invalid");
		}
	}
}



void Shell::runMemTest() {
	for(size_t i = 1; i < 100; ++i){

		char* array = nullptr;
		array = new char[i];
		delete[] array;

		uint64_t* array2 = nullptr;
		array2 = new uint64_t[i];
		delete []array2;

		uint32_t* array3 = nullptr;
		array3 = new uint32_t[i];
		delete []array3;


		uint8_t* singleValue = new uint8_t(1);
		*singleValue = 0;

		uint64_t val = (uint64_t) array;
		Kernel::out.puts("\n");
		Kernel::out.putuint(val);
		/*if (array == nullptr || array2 == nullptr || array3 == nullptr) {
			Kernel::out.putsln("FAIL");
			return;
		}*/
	}
	Kernel::out.putsln("\nSUCCESS");
}



void Shell::calc() {
	char* tempBuffer = new char[15];

	Kernel::in.getWord(tempBuffer, 15);
	Kernel::out.putchar(' ');
	int64_t operand0 = string_to_int(tempBuffer, 10);
	Kernel::in.getWord(tempBuffer, 2);
	Kernel::out.putchar(' ');
	char sign = *tempBuffer;
	Kernel::in.getWord(tempBuffer, 15);
	Kernel::out.putchar(' ');

	int64_t operand1 = string_to_int(tempBuffer, 10);

	Kernel::out.putchar('=');
	switch (sign) {
		case '+':
			Kernel::out.putint(operand0 + operand1);
			break;
		case '-':
			Kernel::out.putint(operand0 - operand1);
			break;
		case '*':
			Kernel::out.putint(operand0 * operand1);
			break;
		case '/':
			if(operand1) {
				Kernel::out.putint(operand0 / operand1);
			}
			else {
				Kernel::out.putchar('0');
			}
			break;
		default:
			Kernel::out.puts("Error: Undefined operation");
			break;
	}
	Kernel::out.newLine();

	delete[] tempBuffer;
}



void Shell::setGMT() {
	char* tempBuffer = new char[10];
	Kernel::in.getWord(tempBuffer, 10);
	int8_t gmt = (int8_t)string_to_int(tempBuffer, 10);
	Time::setGMT(gmt);
	delete[] tempBuffer;
	Kernel::out.puts("GMT set to ");
	Kernel::out.putint(Time::getGMT());
}



void Shell::cowsay() {

	char* tempBuffer = new char[64];
	Kernel::in.gets(tempBuffer, 64);

	size_t length = strlen(tempBuffer);
	Kernel::out.putchar(' ');
	for (size_t i = 0; i < length + 2; i++) {
		Kernel::out.putchar('_');
	}
	Kernel::out.puts("\n< ");
	Kernel::out.puts(tempBuffer);
	Kernel::out.puts(">\n ");
	for (size_t i = 0; i < length + 2; i++) {
		Kernel::out.putchar('-');
	}

	Kernel::out.putchar('\n');
	Kernel::out.puts("  \\ ^__^\n");
	Kernel::out.puts("    (oo)\\_______\n");
	Kernel::out.puts("    (__)\\       )\\/\\\n");
	Kernel::out.puts("        ||----w |\n");
	Kernel::out.puts("        ||     ||\n");
}



void Shell::piano() {
	const uint32_t notes[] = {261, 294, 330, 350, 392, 440, 494};
	while (true) {
		char c = Kernel::in.getchar_nolock();
		if (c > '0' && c <'8') {
			Speaker::play(notes[c - '0'], 200);

		}
		else if (c == 'q') {
			return;
		}
	}
}
