#ifndef P_CODE_MACHINE
#define P_CODE_MACHINE

//// includes

// piet core
#include "penums.h"
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
 * opis
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

		int countBlockCodels(); // liczy liczbę kodeli w bloku w którym jest głowica

	// development:

		void __dev__printImageInfo();

};

#endif
