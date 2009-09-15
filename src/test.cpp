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
	std::cout << "1. uruchom maszynę i wykonuj instrukcje krok po kroku" << std::endl;
	std::cout << "2. uruchom maszynę i wykonaj wszystkie instrukcje" << std::endl;
	std::cout << "3. zrestartuj maszynę" << std::endl;
	std::cout << "4. włącz/wyłącz tryb gadatliwy (" << (m->isVerbose() ? "włączony" : "wyłączony" ) << ")" << std::endl;
	std::cout << "0. koniec" << std::endl;

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
	int final_choice = 0;

	while (continued)
	{
		choice = runMenu();

		switch (choice)
		{
			case 1:
				if ( m->startMachine() ) {
					printFormattedMessage("ok");
					std::string confirm_str;
					while (m->isRunning())
					{
						if ( m->executeSingleInstr() ) {
							printFormattedMessage("ok");
						} else {
							printFormattedError("some kind of error");
						}
						std::cout << "naciśnij enter"; std::cin >> confirm_str;
					}
				} else {
					printFormattedError("machine not ready");
				}
				break;
			case 2:
				if ( m->startMachine() ) {
					printFormattedMessage("machine started");
					m->executeAllInstr();
				} else {
					printFormattedError("machine not ready");
				}
				break;
			case 3:
				m->restartMachine();
				break;
			case 4:
				m->toggleVerbosity();
				break;
			case 0:
				m->stopMachine();
				break;
		}
		
		continued = (choice != final_choice) && (m->isRunning() || m->isReady());
	}

	if (choice != final_choice)
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

	bool verbose = true; // domyślna gadatliwość która będzie przypisana mazynie wirtualnej
	m = new PVirtualMachine(QSTR_code_path);
	runProgram();
	m->~PVirtualMachine();
	debug("MAIN BYE\n");
}
