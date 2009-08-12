//// includes

// header file
#include "pconsole.h"

// piet core
#include "../debug.h"
#include "penums.h"
#include "pstructs.h"

// C++
#include <iostream>
#include <iomanip>

// STL
// none

// Qt
// none

PConsole::PConsole()
{
	debug("CONSTRUCTOR ----- console START\n");

	debug("CONSTRUCTOR ----- console END\n");
}

PConsole::~PConsole()
{
	debug("DESTRUCTOR ----- console START\n");

	debug("DESTRUCTOR ----- console END\n");
}

void PConsole::printNumber(int I)
{
	std::cout << "CONSOLE/out-number: " << I << std::endl;
}

void PConsole::printChar(int I)
{
	unsigned char UC = I;
	std::cout << "CONSOLE/out-char: ";
	std::cout << std::setw(3) << UC << " (" << I << ")" << std::endl;
}

int PConsole::readNumber()
{
	int var;
	std::cout << "CONSOLE/in-number: ";
	std::cin >> var;
	return var;
}

int PConsole::readChar()
{
	char C;
	std::cout << "CONSOLE/in-char: ";
	std::cin >> C;
	int I = (int) C;
	return I;
}
