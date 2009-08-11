//// includes

// header file
#include "pcodemachine.h"

// piet core
#include "../debug.h"
#include "penums.h"
#include "pstructs.h"
#include "pblockmanager.h"
#include "pcolormanager.h"
#include "pcodepointer.h"
#include "pconsole.h"

// C++
#include <iostream>

// STL
// none

// Qt
#include <QString>

PCodeMachine::PCodeMachine(PConsole *given_console, QString given_filename)
{
	debug("CONSTRUCTOR ----- code-machine START\n");

	console = given_console;

	image = new QImage(given_filename);

	PPoint initial;
	initial.x = initial.y = 0;
	pointer = new PCodePointer(image, initial);

	block_manager = new PBlockManager(image, pointer);

	color_manager = new PColorManager();

	debug("CONSTRUCTOR ----- code-machine END\n");
}

PCodeMachine::~PCodeMachine()
{
	debug("DESTRUCTOR ----- code-machine START\n");
	image->~QImage();
	debug("DESTRUCTOR ----- code-machine END\n");
}

void PCodeMachine::prepareToExecute()
{
	pointer->clear();
}

//==================================================================
// tymczasowa, dopóki PCodeMachine i PVirtualMachine nie zostaną złączone w virtual machine...

PCodePointer* PCodeMachine::getPointer()
{
	return pointer;
}

//==================================================================

int PCodeMachine::getCodelBlockCount()
{
	return block_manager->getCodelBlockCount();
}

PInstructions PCodeMachine::movePointerAndGetInstructionToExecute()
{
	PInstructions result_instr;

	QRgb old_color = pointer->getPointedPixel();

	block_manager->searchAndFillCodels(); // oblicz liczbę kodeli bloku kolorów w którym sie znajduje kodel wskazywany przez głowicę
					block_manager->__dev__showCountAndBorderCodels();

	// licznik prób wykonania przez głowicę ruchu (patrz: specyfikacja, "czarne bloki i granice") Jeśli po 8 próbach nie uda się wykonać ruchu, program kończy działanie.
	int attempts = 0;
	bool continued = true;
	PPoint possible_point;

	while (continued) {
					std::cout << "attempt " << attempts << std::endl;
		possible_point = block_manager->getNextPossibleCodel();
					std::cout << "possible next coords:" << possible_point.x << "," << possible_point.y << std::endl;
		if ( color_manager->getColorName(pointer->getPixel(possible_point)) == color_black ) {
			// nie udało się
			attempts++;
			pointer->toggleCodelChooser();
			if (attempts % 2 == 0) { pointer->turnDirectionPointerClockwise(); } // co drugie niepowodzenie obróć direction pointer
			continued = (attempts < 8);
		} else {
			pointer->setCoordinates(possible_point);
			continued = false;
		}
	}

	if (attempts == 8) {
		result_instr = pietInstr_special_terminate;
	} else {
		QRgb new_color = pointer->getPointedPixel();
		result_instr = getInstructionByIndex( color_manager->getInstructionIndex(old_color, new_color) );
	}
	return result_instr;
}

//==================================================================

PInstructions PCodeMachine::getInstructionByIndex(int index)
{
	switch(index) {
		case 0:
			return pietInstr_special_terminate;
		case 1:
			return pietInstr_stack_push;
		case 2:
			return pietInstr_stack_pop;
		case 3:
			return pietInstr_arithm_add;
		case 4:
			return pietInstr_arithm_subtract;
		case 5:
			return pietInstr_arithm_multiply;
		case 6:
			return pietInstr_arithm_divide;
		case 7:
			return pietInstr_arithm_modulo;
		case 8:
			return pietInstr_logic_not;
		case 9:
			return pietInstr_logic_greater;
		case 10:
			return pietInstr_runtime_pointer;
		case 11:
			return pietInstr_runtime_switch;
		case 12:
			return pietInstr_stack_duplicate;
		case 13:
			return pietInstr_stack_roll;
		case 14:
			return pietInstr_io_in_number;
		case 15:
			return pietInstr_io_in_char;
		case 16:
			return pietInstr_io_out_number;
		case 17:
			return pietInstr_io_out_char;
		default:
			// error
			exit(1);
	}
}

//==================================================================

void PCodeMachine::__dev__printPointedCodelInfo()
{
	std::cout << std::endl;
	QRgb tmp = pointer->getPointedPixel();
	std::cout << "R: " << qRed(tmp) << std::endl;
	std::cout << "G: " << qGreen(tmp) << std::endl;
	std::cout << "B: " << qBlue(tmp) << std::endl;
	std::cout << std::endl;
}

void PCodeMachine::__dev__printConsole()
{
	pointer->__dev__printConsole();
	std::cout << "IMAGE/ h" << image->height() << " x w" << image->width() << std::endl;
	std::cout << std::endl;
}

