#ifndef P_CONSOLE_VIRTUAL_MACHINE
#define P_CONSOLE_VIRTUAL_MACHINE

//// includes

// piet core
#include "p_virtual_machine.h"

// C++
// none

// STL
// none

// Qt
// none

/** \file pconsolevirtualmachine.h
 * \brief plik nagłówkowy klasy PConsoleVirtualMachine
 *
 * Plik nagłówkowy zawiera definicję klasy PConsoleVirtualMachine.
 */

/** \brief Wirtualna maszyna Pieta dla aplikacji konsolowych
 *
 * Implementacja "wirtualnej maszyny Pieta" dla aplikacji konsolowych.
 */
class PConsoleVirtualMachine : public PVirtualMachine {

	public:

		PConsoleVirtualMachine(const char *, std::stringstream& );
  
	protected:

		virtual void readNumber();
		virtual void readChar();

};

#endif
