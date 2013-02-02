//// includes

// header file
#include "p_console_virtual_machine.h"

// piet core
#include "../debug.h"

// C++
// none

// STL
// none

// Qt
// none

/** \file pconsolevirtualmachine.cpp
 * \brief Plik z kodem źródłowym klasy PConsoleVirtualMachine
 *
 * Plik zawiera kod źródłowy klasy PConsoleVirtualMachine.
 */

PConsoleVirtualMachine::PConsoleVirtualMachine(const char * filepath, std::stringstream &str)
: PVirtualMachine(filepath, str)
{
}

void PConsoleVirtualMachine::readNumber()
{
	stack->instrPush(console->readNumber());
}

void PConsoleVirtualMachine::readChar()
{
	stack->instrPush(console->readChar());
}
