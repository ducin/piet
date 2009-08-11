//// includes

// header file
#include "pvirtualmachine.h"

// piet core
#include "../debug.h"
#include "penums.h"
#include "pstructs.h"
#include "pcodemachine.h"
#include "pconsole.h"
#include "pcalcstack.h"

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
	stack = new PCalcStack();
	console = new PConsole();
	code_machine = new PCodeMachine(console, filename);
	prepareToExecute();
	debug("CONSTRUCTOR - virtual-machine END\n");
}

PVirtualMachine::~PVirtualMachine()
// destructor
{
	debug("DESTRUCTOR - virtual-machine START\n");
	stack->~PCalcStack();
	console->~PConsole();
	code_machine->~PCodeMachine();
	debug("DESTRUCTOR - virtual-machine END\n");
}

/** \brief przygotowanie do uruchomienia/zresetowania wirtualnej maszyny
 *
 * Metoda używana w celu przygotowania wirtualnej maszyny do uruchomienia. Maszyna mogła być w trakcie działania, mogła zakończyć działanie l
 * \return stan w jakim znajdowała się maszyna (PMachineStates)
 */
PMachineStates PVirtualMachine::prepareToExecute()
{
	code_machine->prepareToExecute();
	stack->prepareToExecute();
	setState(state_ready);
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

bool PVirtualMachine::isReady()
{
	return (state == state_ready);
}

bool PVirtualMachine::isRunning()
{
	return (state == state_running);
}

bool PVirtualMachine::isFinished()
{
	return (state == state_finished);
}

//=========================================================

bool PVirtualMachine::startMachine()
{
	if (isReady()) {
		setState(state_running);
		return true;
	} else {
		return false;
	}
}

bool PVirtualMachine::restartMachine()
{
//
}

bool PVirtualMachine::stopMachine()
{
	if (isRunning()) {
		setState(state_finished);
		return true;
	} else {
		return false;
	}
}

//=========================================================

/**
 * Wykonuje wszystkie instrukcje
 */
bool PVirtualMachine::executeAllInstr()
{
	if ( isRunning() ) {
		while (getState() != state_finished) {
			executeInstr();
		}
		return true;
	} else {
		return false;
	}
}

bool PVirtualMachine::executeInstr()
{
	int ivar; char cvar;
	if ( isRunning() ) {
		PInstructions instruction = code_machine->movePointerAndGetInstructionToExecute();
		// w zależności od tego jaką instrukcję zwróci maszyna kodu
		switch(instruction)
		{
		// wykonaj inną operację używając stosu
			case pietInstr_special_terminate:
				// 8 nieudanych prób przesunięcia głowicy do następnego kodela kończy pracę interpretera
				if ( !stopMachine() ) {
					exit(1);
				}
				break;
			case pietInstr_stack_push:
				stack->instrPush( code_machine->getCodelBlockCount() ); // połóż na stosie liczbę równą liczbie kodeli w bloku kolorów wskazywanym aktualnie przez głowicę
				break;
			case pietInstr_stack_pop:
				ivar = stack->instrPop(); // zdejmuje ze stosu liczbę (i nic z nią nie robi)
				break;
			case pietInstr_arithm_add:
				stack->instrAdd(); // zdejmuje 2 szczytowe elementy i odkłada ich sumę
				break;
			case pietInstr_arithm_subtract:
				stack->instrSubtract(); // zdejmuje 2 szczytowe elementy i odkłada ich różnicę
				break;
			case pietInstr_arithm_multiply:
				stack->instrMultiply(); // zdejmuje 2 szczytowe elementy i odkłada ich iloczyn
				break;
			case pietInstr_arithm_divide:
				stack->instrDivide(); // zdejmuje 2 szczytowe elementy i odkłada ich iloraz
				break;
			case pietInstr_arithm_modulo:
				stack->instrModulo(); // zdejmuje 2 szczytowe elementy i odkłada resztę z ich dzielenia
				break;
			case pietInstr_logic_not:
				stack->instrNot(); // zdejmuje element szczytowy i odkłada 1 (el = 0) lub 0 (el != 0)
				break;
			case pietInstr_logic_greater:
				stack->instrGreater(); // zdejmuje 2 szczytowe elementy i odkłada 1 (jeśli ostatni większy) lub 0 (przeciwnie)
				break;
			case pietInstr_runtime_pointer:
				for (int num = stack->instrPop(); num > 0; num--)
					code_machine->getPointer()->turnDirectionPointerClockwise();
				break;
			case pietInstr_runtime_switch:
				if (stack->instrPop() % 2)
					code_machine->getPointer()->toggleCodelChooser();
				break;
			case pietInstr_stack_duplicate:
				stack->instrDuplicate();
				break;
			case pietInstr_stack_roll:
				stack->instrRoll();
				break;
			case pietInstr_io_in_number:
				stack->instrPush(console->readNumber());
				break;
			case pietInstr_io_in_char:
				stack->instrPush(console->readChar());
				break;
			case pietInstr_io_out_number:
				console->printNumber(stack->instrPop());
				break;
			case pietInstr_io_out_char:
				console->printChar(stack->instrPop());
				break;
			default:
				// ERROR
				exit(1);
				break;
		}
		return true;
	} else {
		return false;
	}
}

void PVirtualMachine::clean()
{
//
}

//=========================================================

void PVirtualMachine::__dev__printConsole()
{
	code_machine->__dev__printConsole();
	stack->__dev__printConsole();
}
