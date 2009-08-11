#ifndef P_CODE_MACHINE
#define P_CODE_MACHINE

//// includes

// piet core
#include "penums.h"
#include "pstructs.h"
#include "pblockmanager.h"
#include "pcolormanager.h"
#include "pcodepointer.h"
#include "pconsole.h"

// C++
// none

// STL
// none

// Qt
#include <QString>
#include <QImage>

/** \file pcodemachine.h
 * \brief plik nagłówkowy klasy PCodeMachine
 *
 * Plik nagłówkowy zawiera definicję klasy PCodeMachine.
 */

/** \brief maszyna kodu
 *
 * Klasa pełniąca funkcję tzw. "maszyny kodu" w interpreterze języka Piet. Wykonuje wszystkie najważniejsze operacje związane z odczytywaniem tzw. "obrazku kodu", używa pomocniczych obiektów do interpretacji kolorów i zliczania kodeli w blokach kolorów - czyli wszystko co związane z przetwarzaniem "obrazu kodu".

Stanowi jeden z dwóch obiektów potrzebnych do pełnej interpretacji kodu, używanych przez tzw. "wirtualną maszynę Pieta", najwyższy w hierarchi obiekt.
 */
class PCodeMachine {

	protected:

		// obiekty stworzone przez wirtualną maszynę
		PConsole *console;

		// obiekty tworzone tu, przez maszynę kodu
		QImage *image; // obraz kodu (plik graficzny którego pixle będą interpretowane)
		PCodePointer *pointer; // wskaźnik czytający obraz powyższy kodu
		PColorManager *color_manager; // maszyna zajmująca się przetwarzaniem i interpretacją kolorów
		PBlockManager *block_manager;

	public:

		PCodeMachine(PConsole *, QString);
		~PCodeMachine();

		PCodePointer* getPointer();

		void prepareToExecute();

		int getCodelBlockCount();

		PInstructions movePointerAndGetInstructionToExecute(); // jedna z najważniejszych metod tej klasy - koordynuje wykonywanie pojedynczego polecenia interpretera

		PInstructions getInstructionByIndex(int);

	// development:

		void __dev__printPointedCodelInfo();
		void __dev__printConsole();

};

#endif
