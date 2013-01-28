#ifndef P_CONSOLE
#define P_CONSOLE

//// includes

// piet core
#include "penums.h"
#include "pstructs.h"

// C++
#include <sstream>

// STL
// none

// Qt
//

/** \file pconsole.h
 * \brief plik nagłówkowy klasy PConsole
 *
 * Plik nagłówkowy zawiera definicję klasy PConsole.
 */

/** \brief Konsola wejścia/wyjścia
 *
 * Klasa realizująca wszystkie operacje wejścia wyjścia związane z instrukcjami Pieta.
 */
class PConsole {

	private:

		/**
		 * Pole logiczne definiujące tryb gadatliwy.
		 */
		bool verbose;

		std::stringstream &stream;

	public:

		PConsole(std::stringstream &);
		~PConsole();

		void setVerbosity(bool);

		void printChar(int);
		void printNumber(int);
		int readChar();
		int readNumber();

};

#endif
