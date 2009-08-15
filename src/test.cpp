//// includes

// piet core
#include "core/pvirtualmachine.h"
#include "core/penums.h"
#include "debug.h"

// C++
#include <iostream>
#include <fstream>
#include <string>

// STL
// none

// Qt
#include <QString>

bool verbose = false;

void setConsoleColor(int color)
{
	std::cout << "\033[" << color << "m";
}

void printFormattedError(std::string error)
{
	setConsoleColor(31);
	std::cout << error << std::endl;
	setConsoleColor(0);
}

void printFormattedMessage(std::string message)
{
	setConsoleColor(32);
	std::cout << message << std::endl;
	setConsoleColor(0);
}

PVirtualMachine *m;

int runMenu()
{
	std::cout << "wybierz opcję:" << std::endl;
	std::cout << "1. uruchom maszynę" << std::endl;
	std::cout << "2. zrestartuj maszynę" << std::endl;
	std::cout << "3. wykonaj instrukcję" << std::endl;
	std::cout << "4. wykonaj podaną ilość instrukcji" << std::endl;
	std::cout << "5. cofnij ostatnią instrukcję" << std::endl;
	std::cout << "6. cofnij o podaną ilość kroków" << std::endl;
	std::cout << "9. koniec" << std::endl;

	std::string answer;
	std::cout << std::endl << "> "; getline(std::cin, answer); std::cout << std::endl;
	while (!atoi(answer.c_str()))
	{
		std::cout << "> "; getline(std::cin, answer); std::cout << std::endl;
	}
	return atoi(answer.c_str());
}

int runProgram()
{
	int continued = 1, choice;
	int trace_step = 0;

	while (continued)
	{
		if (verbose)
			m->__dev__printConsole();

		choice = runMenu();

		switch (choice)
		{
			case 1:
				if ( m->startMachine() ) {
					printFormattedMessage("ok");
				} else {
					printFormattedError("machine not ready");
				}
				break;
			case 2:
				m->restartMachine();
				break;
			case 3:
				if (verbose)
					std::cout << "trace step: " << trace_step++ << std::endl;
				if ( m->executeInstr() ) {
					printFormattedMessage("ok");
				} else {
					printFormattedError("some kind of error");
				}
				break;
			case 4:
				// spytaj ile instrukcji do przodu ma pójść
				m->executeInstr();
				break;
			case 9:
				m->stopMachine();
				break;
		}
		
		continued = (choice != 9) && (m->isRunning() || m->isReady());
	}

	m->__dev__printConsole();

	if (choice != 9)
		printFormattedMessage("Application finished");
	else
		printFormattedError("Application aborted");
}

int main(int argc, char **argv)
{
	if ( argc != 2 ) // zle wywolany program
	{
		printFormattedMessage("Run the program with the code filename");
		return 1;
	}
	std::string STD_STR_code_path = "data/" + std::string(argv[1]);
	debug("MAIN HELLO\n");
	std::ifstream fin(STD_STR_code_path.c_str());
	if ( !fin )
	{
		printFormattedMessage("File doesn't exist, check code files and run again");
		return 2;
	}

	QString QSTR_code_path(STD_STR_code_path.c_str());

	m = new PVirtualMachine(QSTR_code_path, verbose);
	runProgram();
	m->~PVirtualMachine();
	debug("MAIN BYE\n");
}
