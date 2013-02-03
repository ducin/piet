#ifndef P_VIRTUAL_MACHINE
#define P_VIRTUAL_MACHINE

//// includes

// piet core
#include "p_enums.h"
#include "p_structs.h"
#include "p_console.h"
#include "p_block_manager.h"
#include "p_color_manager.h"
#include "p_code_pointer.h"
#include "p_calc_stack.h"

// C++
#include <ostream>
#include <sstream>

// STL
// none

// Qt
#include <QImage>

/** \file pvirtualmachine.h
 * \brief plik nagłówkowy klasy PVirtualMachine
 *
 * Plik nagłówkowy zawiera definicję klasy PVirtualMachine.
 */

/** \brief Wirtualna maszyna Pieta
 *
 * Klasa realizująca tzw. "wirtualną maszynę Pieta", która posiada wszystkie mechanizmy potrzebne do egzekucji kodu Pieta.

Klasa sama w sobie posiada niewiele mechanizmów (precyzyjniej: najmniej jak to było możliwe), aby wszystkie szczegółowe operacje wydzielić dla pozostałych klas w obrębie projektu. Wirtualna maszyna zajmuje się (oprócz tworzenia pomocniczych obiektów) tylko egzekucją pojedynczych instrukcji Pieta (oraz związane z tym zatrzymywanie, uruchamianie, przygotowywanie maszyny).

Jej dwoma najważniejszymi elementami są: stos, na którym przechowywane są tymczasowe wartości, oraz tzw. "maszyna kodu", odpowiedzialna za pełną interpretację kodu.
 */
class PVirtualMachine {

	private:

		PMachineStates state;
		QImage *image; // obraz kodu (plik graficzny którego pixle będą interpretowane)
		PCodePointer *pointer; // wskaźnik czytający obraz powyższy kodu
		PColorManager *color_manager; // maszyna zajmująca się przetwarzaniem i interpretacją kolorów
		PBlockManager *block_manager;
		std::stringstream &stream;
		void construct();

		int step;

		bool verbose;
		void setVerbosityRecursively(bool);

	protected:

		/**
		 * Stos przechowujący wszystkie tymczasowe wartości
		 */
		PCalcStack *stack;
		/**
		 * Konsola wejścia/wyjścia Pieta, obsługująca operacje komunikacji z użytkownikiem
		 */
		PConsole *console;

		void setState(PMachineStates);

		void prepareToExecute();

		virtual void readNumber() = 0;
		virtual void readChar() = 0;

	public:

		PVirtualMachine(const char *, std::stringstream &);
		~PVirtualMachine();

		bool isReady();
		bool isRunning();
		bool isFinished();

		bool startMachine();
		bool restartMachine();
		bool stopMachine();

		bool isVerbose();
		void toggleVerbosity();
		void setVerbosity(bool);

		std::list<int>::iterator calc_stack_begin_iterator();
		std::list<int>::iterator calc_stack_end_iterator();

		const QImage* getImage() const;

		// TODO zastanowic sie jaki typ ma zwracac
		void executeAllInstr(); // wykonywanie instrukcji do końca działania programu
		bool executeSingleInstr(); // wykonanie jednej instrukcji

		bool pointIsBlackOrOutside(PPoint);
		bool pointIsWhite(PPoint);
		void slidePointerAcrossWhiteBlock();
		void slideAcrossWhiteBlock(PPoint &);

		PInstructions movePointerAndGetInstructionToExecute(); // jedna z najważniejszych metod tej klasy - koordynuje wykonywanie pojedynczego polecenia interpretera

		PInstructions getInstructionByIndex(int);

		PMachineStates getState();

		// code pointer
		PPoint getCodePointerCoordinates();
		PDirectionPointerValues getDirectionPointer();
		PCodelChooserValues getCodelChooser();

	// development:

		void __dev__printImageInfo();
		void __dev__printConsole();

};

#endif
