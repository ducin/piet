#ifndef P_VIRTUAL_MACHINE
#define P_VIRTUAL_MACHINE

//// includes

// piet core
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

	protected:

		PCodeMachine *code_machine; // maszyna kodu
		PStack *stack; // stos
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

		void clean(); // czyszczenie danych maszyny (zwalnianie pamięci pod obiekty)

		// TODO zastanowic sie jaki typ ma zwracac
		void executeAllInstr(); // wykonywanie instrukcji do końca działania programu
		void executeInstr(); // wykonanie jednej instrukcji
		bool revokeInstr(); // cofniecie jednej instrukcji
		bool goBack(int);

	// development:

		std::string __dev__transformBinaryStateToString(PMachineStates);
		void __dev__printConsole();
		void __dev__destroyGrid();
		void __dev__runProgram(); // TESTOWE // testowa metoda wykonywania programu dla maszyny, która wczytała już swój kod

};

#endif
