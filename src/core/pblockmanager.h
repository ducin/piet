#ifndef P_BLOCK_MANAGER
#define P_BLOCK_MANAGER

//// includes

// piet core
#include "penums.h"

// C++
// none

// STL
// none

// Qt
#include <QImage>

/** \file pblockmanager.h
 * \brief plik nagłówkowy klasy PBlockManager
 *
 * Klasa odpowiedzialna właściwie tylko za jedną, ale dosyć skomplikowaną operację - obliczanie ilości kodeli w danym bloku koloru. Ta wydzielona klasa posiada własne struktury danych i algorytm i zwraca maszynie kodu (klasie opakowującej) liczbę kodeli w danym bloku.
 */

class PBlockManager {

	public:

		PBlockManager();
		~PBlockManager();

};

#endif
