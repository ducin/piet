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

/** \file pconsole.cpp
 * \brief Plik z kodem źródłowym klasy PConsole
 *
 * Plik zawiera kod źródłowy klasy PConsole.
 */

/**
 * Konstruktor konsoli wejścia/wyjścia. Nie robi nic szczególnego.
 */
PConsole::PConsole(std::stringstream &str) : stream(str)
{
	debug("CONSTRUCTOR ----- console START\n");
	verbose = false;
	debug("CONSTRUCTOR ----- console END\n");
}

/**
 * Destruktor konsoli wejścia/wyjścia. Nie robi nic szczególnego.
 */
PConsole::~PConsole()
{
	debug("DESTRUCTOR ----- console START\n");

	debug("DESTRUCTOR ----- console END\n");
}

/**
 * Ustala tryb gadatliwy.
 * @param verbosity tryb gadatliwy
 */
void PConsole::setVerbosity(bool verbosity)
{
	verbose = verbosity;
}

/**
 * Wyświetla liczbę na konsolę.
 * @param I liczba
 */
void PConsole::printNumber(int I)
{
	if (verbose)
		stream << "CONSOLE/out-number: ";
	stream << I;
	if (verbose)
		stream << std::endl;
}

/**
 * Wyświetla znak na konsolę.
 * @param I znak reprezentowany maszynowo przez liczbę
 */
void PConsole::printChar(int I)
{
	unsigned char UC = I;
	if (verbose)
		stream << "CONSOLE/out-char: ";
//	stream << std::setw(3) << UC;
	stream << UC;
	if (verbose)
		stream << " (" << I << ")" << std::endl;
}

/**
 * Wczytuje z konsoli liczbę.
 * @return wczytana liczba
 */
int PConsole::readNumber()
{
	int var;
	if (verbose) {
		stream << "CONSOLE/in-number: ";
	} else {
		stream << "? ";
	}
	std::cin >> var;
	return var;
}

/**
 * Wczytuje z konsoli znak.
 * @return wczytany znak reprezentowany maszynowo przez liczbę
 */
int PConsole::readChar()
{
	char C;
	if (verbose) {
		stream << "CONSOLE/in-char: ";
	} else {
		stream << "? ";
	}
	std::cin >> C;
	int I = (int) C;
	return I;
}
