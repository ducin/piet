//// includes

// header file
#include "pvirtualmachine.h"

// piet core
#include "../debug.h"
#include "penums.h"
#include "pstructs.h"
#include "pconsole.h"
#include "pcalcstack.h"

// C++
#include <iostream>

// STL
// none

// Qt
#include <QString>
#include <QImage>
#include <QRgb>

// konstruktor maszyny wirtualnej interpretującej dowolny program w języku Piet
// tworzy wszystkie pomocnicze obiekty których działanie jest wykorzystywane i koordynowane przez wirtualną maszynę.
PVirtualMachine::PVirtualMachine(QString filename, bool verbose_mode)
{
	debug("CONSTRUCTOR - virtual-machine START\n");

	// tryb gadatliwości (debugowanie)
	verbose = verbose_mode;

	// stworzenie obiektu obrazu kodu, po którym będzie poruszać się głowica
	image = new QImage(filename);

	// punkt współrzędnych początkowych - oraz stworzenie głowicy poruszającej się po powyższym obrazie
	PPoint initial;
	initial.x = initial.y = 0;
	pointer = new PCodePointer(image, initial, verbose);

	// obiekt odpowiedzialny za geometryczną interpretację bloków kolorów
	block_manager = new PBlockManager(image, pointer, verbose);

	// obiekt przetwarzający wszystko związane z kolorami
	color_manager = new PColorManager(verbose);

	// stos przechowujący tymczasowe wartości
	stack = new PCalcStack(verbose);

	// obiekt odpowiedzialny za wczytywanie i wyświetlanie danych od użytkownika
	console = new PConsole(verbose);

	// przygotowanie maszyny do uruchomienia ("wyzerowanie")
	prepareToExecute();

	debug("CONSTRUCTOR - virtual-machine END\n");
}

// destruktor wirtualnej maszyny Pieta. Wywołuje destruktory dla pomocniczych obiektów tworzonych w konstruktorze wirtualnej maszyny.
PVirtualMachine::~PVirtualMachine()
{
	debug("DESTRUCTOR - virtual-machine START\n");
	// likwidacja kolejnych pomocniczych obiektów używanych przez wirtualną maszynę
	image->~QImage();
	pointer->~PCodePointer();
	block_manager->~PBlockManager();
	color_manager->~PColorManager();
	stack->~PCalcStack();
	console->~PConsole();
	debug("DESTRUCTOR - virtual-machine END\n");
}

/** \brief przygotowanie do uruchomienia/zresetowania wirtualnej maszyny
 *
 * Metoda używana w celu przygotowania wirtualnej maszyny do uruchomienia. Maszyna mogła być w trakcie działania, mogła zakończyć działanie l
 * \return stan w jakim znajdowała się maszyna (PMachineStates)
 */
PMachineStates PVirtualMachine::prepareToExecute()
{
	stack->clear();
	pointer->clear();
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

// wykonuje pojedynczą instrukcję
bool PVirtualMachine::executeInstr()
{
	bool result = true; // czy operacja została wykonana
	int ivar;
	if ( isRunning() ) {
		PInstructions instruction = movePointerAndGetInstructionToExecute();
		// w zależności od tego jaką instrukcję zwróci maszyna kodu
		switch(instruction)
		{
		// wykonaj inną operację używając stosu
			case pietInstr_special_empty:
				// pusta instrukcja - głowica przesunięta po białym bloku
				break;
			case pietInstr_stack_push:
				stack->instrPush( block_manager->getCodelBlockCount() ); // połóż na stosie liczbę równą liczbie kodeli w bloku kolorów wskazywanym aktualnie przez głowicę
				break;
			case pietInstr_stack_pop:
				if (stack->hasAtLeastNElements(1)) {
					ivar = stack->instrPop(); // zdejmuje ze stosu liczbę (i nic z nią nie robi)
				} else {
					result = false;
				}
				break;
			case pietInstr_arithm_add:
				if (stack->hasAtLeastNElements(2)) {
					stack->instrAdd(); // zdejmuje 2 szczytowe elementy i odkłada ich sumę
				} else {
					result = false;
				}
				break;
			case pietInstr_arithm_subtract:
				if (stack->hasAtLeastNElements(2)) {
					stack->instrSubtract(); // zdejmuje 2 szczytowe elementy i odkłada ich różnicę
				} else {
					result = false;
				}
				break;
			case pietInstr_arithm_multiply:
				if (stack->hasAtLeastNElements(2)) {
					stack->instrMultiply(); // zdejmuje 2 szczytowe elementy i odkłada ich iloczyn
				} else {
					result = false;
				}
				break;
			case pietInstr_arithm_divide:
				if (stack->hasAtLeastNElements(2)) {
					stack->instrDivide(); // zdejmuje 2 szczytowe elementy i odkłada ich iloraz
				} else {
					result = false;
				}
				break;
			case pietInstr_arithm_modulo:
				if (stack->hasAtLeastNElements(2)) {
					stack->instrModulo(); // zdejmuje 2 szczytowe elementy i odkłada resztę z ich dzielenia
				} else {
					result = false;
				}
				break;
			case pietInstr_logic_not:
				if (stack->hasAtLeastNElements(1)) {
					stack->instrNot(); // zdejmuje element szczytowy i odkłada 1 (el = 0) lub 0 (el != 0)
				} else {
					result = false;
				}
				break;
			case pietInstr_logic_greater:
				if (stack->hasAtLeastNElements(2)) {
					stack->instrGreater(); // zdejmuje 2 szczytowe elementy i odkłada 1 (jeśli ostatni większy) lub 0 (przeciwnie)
				} else {
					result = false;
				}
				break;
			case pietInstr_runtime_pointer:
				if (stack->hasAtLeastNElements(1)) {
					for (int num = stack->instrPop(); num > 0; num--)
						pointer->toggleDirectionPointer();
				} else {
					result = false;
				}
				break;
			case pietInstr_runtime_switch:
				if (stack->hasAtLeastNElements(1)) {
					if (stack->instrPop() % 2)
						pointer->toggleCodelChooser();
				} else {
					result = false;
				}
				break;
			case pietInstr_stack_duplicate:
				if (stack->hasAtLeastNElements(1)) {
					stack->instrDuplicate();
				} else {
					result = false;
				}
				break;
			case pietInstr_stack_roll:
				if (stack->hasAtLeastNElements(2)) {
					stack->instrRoll();
				} else {
					result = false;
				}
				break;
			case pietInstr_io_in_number:
				stack->instrPush(console->readNumber());
				break;
			case pietInstr_io_in_char:
				stack->instrPush(console->readChar());
				break;
			case pietInstr_io_out_number:
				if (stack->hasAtLeastNElements(1)) {
					console->printNumber(stack->instrPop());
				} else {
					result = false;
				}
				break;
			case pietInstr_io_out_char:
				if (stack->hasAtLeastNElements(1)) {
					console->printChar(stack->instrPop());
				} else {
					result = false;
				}
				break;
			case pietInstr_special_terminate:
				// 8 nieudanych prób przesunięcia głowicy do następnego kodela kończy pracę interpretera
				if ( !stopMachine() ) {
					std::cout << "ERROR: bool PVirtualMachine::executeInstr()" << std::endl;
					exit(1);
				}
				break;
			default:
				std::cout << "ERROR: bool PVirtualMachine::executeInstr()" << std::endl;
				exit(1);
		}
	} else {
		result = false;
	}
	return result;
}

//==================================================================

bool PVirtualMachine::pointIsBlackOrOutside(PPoint point)
{
	bool black = false, outside = pointer->pointOutsideImage(point);
	if (!outside) {
		black = (color_manager->getColorName(pointer->getPixel(point)) == color_black );
	}
	return ( outside || black );
}

bool PVirtualMachine::pointIsWhite(PPoint point)
{
	return (color_manager->getColorName(pointer->getPixel(point)) == color_white );
}

void PVirtualMachine::slidePointerAcrossWhiteBlock()
{
	while (color_manager->getColorName(pointer->getPointedPixel()) == color_white)
	switch (pointer->getDirectionPointerValue()) {
		case dp_right:
			pointer->incCoordinateX();
			break;
		case dp_down:
			pointer->incCoordinateY();
			break;
		case dp_left:
			pointer->decCoordinateX();
			break;
		case dp_up:
			pointer->decCoordinateY();
			break;
	}
}

void PVirtualMachine::slideAcrossWhiteBlock(PPoint &point)
{
	while ( (!pointer->pointOutsideImage(point)) && (color_manager->getColorName(pointer->getPixel(point)) == color_white) )
	switch (pointer->getDirectionPointerValue()) {
		case dp_right:
			point.x++;
			if (verbose)
				std::cout << "right: " << point.x << "," << point.y << std::endl;
			break;
		case dp_down:
			point.y++;
			if (verbose)
				std::cout << "down: " << point.x << "," << point.y << std::endl;
			break;
		case dp_left:
			point.x--;
			if (verbose)
				std::cout << "left: " << point.x << "," << point.y << std::endl;
			break;
		case dp_up:
			point.y--;
			if (verbose)
				std::cout << "up: " << point.x << "," << point.y << std::endl;
			break;
	}
}

// Metoda nakazuje przesunięcie głowicy oraz wyznacza jaka instrukcja ma zostać wykonana (wszystko wykorzystując pomocnicze obiekty wirtualnej maszyny).
// Jedna z ważniejszych i bardziej skomplikowanych metod.
PInstructions PVirtualMachine::movePointerAndGetInstructionToExecute()
{
	PInstructions result_instr; // robocza zmienna wynikowa
	PPoint possible_point; // nowy, szukany kodel na który ma zostać przesunięta głowica
	QRgb old_color = pointer->getPointedPixel(); // kolor pierwotnego kodela, czyli wskazywanego przez głowicę przed jej przesunięciem
	block_manager->searchAndFillCodels(); // oblicza liczbę kodeli bloku koloru w którym się znajduje kodel wskazywany przez głowicę
	bool isWhite = false, isBlack;

	if (verbose)
		block_manager->__dev__showCountAndBorderCodels();

	int attempts = 0; // licznik prób wykonania przez głowicę ruchu (patrz: specyfikacja, "czarne bloki i granice") Jeśli po 8 próbach nie uda się wykonać ruchu, program kończy działanie.
	bool continued = true; // zmienna sterująca pętlą
	while (continued) {
		isBlack = false; // odznaczenie informacji na początek każdego obrotu pętli (odświeżenie)
		possible_point = block_manager->getNextPossibleCodel(); // wyznacz hipotetyczny nowy kodel
		if (verbose) {
			std::cout << "attempt " << attempts << ", possible next coords:" << possible_point.x << "," << possible_point.y;
			pointer->__dev__printConsole();
		}

		if ( pointIsBlackOrOutside(possible_point) ) {
			isBlack = true;
		} else if ( pointIsWhite(possible_point) ) {
			slideAcrossWhiteBlock(possible_point);
			isWhite = true;
			if ( pointIsBlackOrOutside(possible_point) ) {
				isBlack = true;
			}
		}

		if (isBlack) {
			// nie udało się
			attempts++;
			if (attempts % 2) {
				pointer->toggleCodelChooser();
			} else {
				pointer->toggleDirectionPointer();
			}
			continued = (attempts < 8);
		} else {
			pointer->setCoordinates(possible_point);
			if (verbose)
				std::cout << "coordinates set to: [" << possible_point.x << "," << possible_point.y << "]" << std::endl;
			continued = false;
		}
	}
	if (isWhite) {
		result_instr = pietInstr_special_empty;
	}
	// pętla zerwana - albo przesunięto głowicę albo program zakończony, poniżej selekcja
	if (attempts == 8) {
		result_instr = pietInstr_special_terminate; // zakończenie programu, 8 nieudanych prób
	} else { // głowica została przesunięta
		QRgb new_color = pointer->getPointedPixel(); // odczytanie koloru kodelu wskazywanego przez głowicę po przesunięciu
		result_instr = getInstructionByIndex( color_manager->getInstructionIndex(old_color, new_color) ); // interpretacja instrukcji do wykonanai na podstawie kolorów kodeli - starego i nowego
	}
	if (verbose) {
		std::cout << "instr: "; __dev__printInstruction(result_instr); std::cout << std::endl;
	}
	return result_instr; // zwrócenie wyniku (instrukcji do wykonania)
}

//==================================================================

PInstructions PVirtualMachine::getInstructionByIndex(int index)
{
	switch(index) {
		case 0:
			return pietInstr_special_empty;
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
		case 18:
			return pietInstr_special_terminate;
		default:
			std::cout << "ERROR: PInstructions PVirtualMachine::getInstructionByIndex(int index)" << std::endl;
			exit(1);
	}
}

//=========================================================

void PVirtualMachine::__dev__printInstruction(PInstructions instr)
{
	switch(instr) {
		case 0:
			std::cout << "empty";
			break;
		case 1:
			std::cout << "push";
			break;
		case 2:
			std::cout << "pop";
			break;
		case 3:
			std::cout << "add";
			break;
		case 4:
			std::cout << "subtract";
			break;
		case 5:
			std::cout << "multiply";
			break;
		case 6:
			std::cout << "divide";
			break;
		case 7:
			std::cout << "modulo";
			break;
		case 8:
			std::cout << "not";
			break;
		case 9:
			std::cout << "greater";
			break;
		case 10:
			std::cout << "pointer";
			break;
		case 11:
			std::cout << "switch";
			break;
		case 12:
			std::cout << "duplicate";
			break;
		case 13:
			std::cout << "roll";
			break;
		case 14:
			std::cout << "in-number";
			break;
		case 15:
			std::cout << "in-char";
			break;
		case 16:
			std::cout << "out-number";
			break;
		case 17:
			std::cout << "out-char";
			break;
		case 18:
			std::cout << "terminate";
			break;
	}
}

void PVirtualMachine::__dev__printImageInfo()
{
	std::cout << std::endl << "IMAGE/ " << "[" << image->width() << "x" << image->height() << "]";
}

void PVirtualMachine::__dev__printConsole()
{
	__dev__printImageInfo();
	pointer->__dev__printConsole();
	stack->__dev__printConsole();
}
