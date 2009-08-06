//// includes

// header file
#include "pvirtualmachine.h"

// piet core
#include "../debug.h"
#include "penums.h"
#include "pcodemachine.h"
#include "pconsole.h"
#include "pstack.h"

// C++
// none

// STL
// none

// Qt
#include <QString>
#include <QImage>
#include <QRgb>

PVirtualMachine::PVirtualMachine(QString filename)
// constructor
{
	debug("CONSTRUCTOR - virtual-machine START\n");
	stack = new PStack();
	console = new PConsole();
	code_machine = new PCodeMachine(console, filename);
	prepareToExecute();
	debug("CONSTRUCTOR - virtual-machine END\n");
}

PVirtualMachine::~PVirtualMachine()
// destructor
{
	debug("DESTRUCTOR - virtual-machine START\n");
	stack->~PStack();
	code_machine->~PCodeMachine();
	debug("DESTRUCTOR - virtual-machine END\n");
}

//=========================================================

bool PVirtualMachine::isReady()
{
	return (state == state_ready);
}

bool PVirtualMachine::isRunning()
{
	return (state == state_running);
}

void PVirtualMachine::startMachine()
{
	setState(state_running);
}

void PVirtualMachine::restartMachine()
{
//
}

void PVirtualMachine::stopMachine()
{
//
}

/** \brief przygotowanie do uruchomienia/zresetowania wirtualnej maszyny
 *
 * Metoda używana w celu przygotowania wirtualnej maszyny do uruchomienia. Maszyna mogła być w trakcie działania, mogła zakończyć działanie l
 * \return stan w jakim znajdowała się maszyna (SMachineStates)
 */
PMachineStates PVirtualMachine::prepareToExecute()
{
/*
        // zapamiętaj dotychczasowy stan
        SMachineStates old = getState();

        // wyczyść logi obu pod-maszyn
        code_machine->clearStats();
        data_machine->clearStats();

        // wyczyść obraz danych
        data_machine->clearImage();

        // ustaw wskaźniki obu pod-maszyn na inicjalne
        code_machine->clearPointer();
        data_machine->clearPointer();

        // ustaw stan maszyny na "gotowy"
        setState(state_ready);

        // zwróć stan maszyny w którym znajdowała się dotychczas
        return old;
*/
}

//=============================================================================

/** \brief zwraca stan wirtualnej maszyny Salvadora
 *
 * W każdej chwili istnienia, wirtualna maszyna Pieta musi znajdować się w jakimś stanie (PMachineStates). Metoda zwraca aktualny stan wirtualnej maszyny.
 */
PMachineStates PVirtualMachine::getState()
{
	return state;
}

/** \brief ustawia stan wirtualnej maszyny Salvadora
 *
 * W każdej chwili istnienia, wirtualna maszyna Pieta musi znajdować się w jakimś stanie (PMachineStates). Metoda ustawia stan wirtualnej maszyny.
 * \param state stan jaki zostanie przypisany wirtualnej maszynie
 */
void PVirtualMachine::setState(PMachineStates state)
{
	this->state = state;
}

//=========================================================

/**
 * Wykonuje wszystkie instrukcje
 */
void PVirtualMachine::executeAllInstr()
{
	while (getState() != state_finished)
		executeInstr();
}

void PVirtualMachine::executeInstr()
{
/*
	switch(code_machine->getPointedInstruction())
        {
                case instr_data_left:
                        data_machine->executeTurnLeft();
                        break;
                case instr_data_right:
                        data_machine->executeTurnRight();
                        break;
        }
*/
}

bool PVirtualMachine::revokeInstr()
{
//
}

bool PVirtualMachine::goBack(int count)
{
//
}

void PVirtualMachine::clean()
{
//
}

//=========================================================

void PVirtualMachine::__dev__printConsole()
{
//
}

//=========================================================
