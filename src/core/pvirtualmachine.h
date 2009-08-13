#ifndef P_VIRTUAL_MACHINE
#define P_VIRTUAL_MACHINE

//// includes

// piet core
#include "penums.h"
#include "pstructs.h"
#include "pconsole.h"
#include "pblockmanager.h"
#include "pcolormanager.h"
#include "pcodepointer.h"
#include "pcalcstack.h"

// C++
// none

// STL
// none

// Qt
#include <QString>
#include <QImage>

/** \file pvirtualmachine.h
 * \brief plik nagłówkowy klasy PVirtualMachine
 *
 * Plik nagłówkowy zawiera definicję klasy PVirtualMachine.
 */

/** \brief wirtualna maszyna Pieta
 *
 * Klasa pełniąca funkcję tzw. "wirtualnej maszyny Pieta", która posiada wszystkie mechanizmy potrzebne do egzekucji kodu Pieta.

Klasa sama w sobie posiada niewiele mechanizmów (mówiąc dokładniej: najmniej jak to było możliwe), aby wszystkie szczegółowe operacje wydzielić dla pozostałych klas w obrębie projektu. Wirtualna maszyna zajmuje się (oprócz tworzenia pomocniczych obiektów) tylko egzekucją pojedynczych instrukcji Pieta (oraz związane z tym zatrzymywanie, uruchamianie, przygotowywanie maszyny).

Jej dwoma najważniejszymi elementami są: stos, na którym przechowywane są tymczasowe wartości, oraz tzw. "maszyna kodu", odpowiedzialna za pełną interpretację kodu.
 */
class PVirtualMachine {

	private:

		PMachineStates state;
		QImage *image; // obraz kodu (plik graficzny którego pixle będą interpretowane)
		PCodePointer *pointer; // wskaźnik czytający obraz powyższy kodu
		PColorManager *color_manager; // maszyna zajmująca się przetwarzaniem i interpretacją kolorów
		PBlockManager *block_manager;

	protected:

		PCalcStack *stack; // stos
		PConsole *console; // konsola I/O

		PMachineStates getState();
		void setState(PMachineStates);

		PMachineStates prepareToExecute();

	public:

		PVirtualMachine(QString); // konstruktor
		~PVirtualMachine(); // destruktor

		bool isRunning(); // czy maszyna działa (sprawdzany stan maszyny)
		bool isReady(); // czy maszyna jest gotowa do rozpoczęcia pracy
		bool isFinished();

		bool startMachine();
		bool restartMachine();
		bool stopMachine();

		// TODO zastanowic sie jaki typ ma zwracac
		bool executeAllInstr(); // wykonywanie instrukcji do końca działania programu
		bool executeInstr(); // wykonanie jednej instrukcji

		bool pointIsBlackOrOutside(PPoint);
		bool pointIsWhite(PPoint);
		PInstructions movePointerAndGetInstructionToExecute(); // jedna z najważniejszych metod tej klasy - koordynuje wykonywanie pojedynczego polecenia interpretera

		PInstructions getInstructionByIndex(int);


	// development:

		void __dev__printInstruction(PInstructions);
		void __dev__printImageInfo();
		void __dev__printPointedCodelInfo();
		void __dev__printConsole();

};

#endif
