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
 * opis
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

                PVirtualMachine(QString); // konstruktor, params: istniejący plik graficzny bmp
                ~PVirtualMachine(); // destruktor

                bool isRunning(); // czy maszyna działa (sprawdzany stan maszyny)
                bool isReady(); // czy maszyna jest gotowa do rozpoczęcia pracy
                void startMachine();
                void restartMachine();
                void stopMachine();

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
