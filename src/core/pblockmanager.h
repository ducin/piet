#ifndef P_BLOCK_MANAGER
#define P_BLOCK_MANAGER

//// includes

// piet core
#include "penums.h"
#include "pstructs.h"
#include "pcodepointer.h"

// C++
// none

// STL
// none

// Qt
#include <QRgb>
#include <QImage>

/** \file pblockmanager.h
 * \brief plik nagłówkowy klasy PBlockManager
 *
 * Plik nagłówkowy zawiera definicję klasy PBlockManager.
 */

/** \brief manager bloków kolorów
 *
 * Klasa odpowiedzialna właściwie tylko za jedną, ale dosyć skomplikowaną operację - obliczanie ilości kodeli w danym bloku koloru. Ta wydzielona klasa posiada własne struktury danych i algorytm i zwraca maszynie kodu (klasie opakowującej) liczbę kodeli w danym bloku.
 */
class PBlockManager {

	private:

		int height, width; // wymiary obrazu kodu
		int **fields; // 2-wymiarowa tablica pomocnicza

		void allocateMultiArray();
		void deallocateMultiArray();

		void reqCrawlMultiArray(QRgb, PPoint);

		void countCodels(); // zlicza kodele bloku kolorów na który wskazuje głowica
		void findBorderCodels(); // wyznacza skrajne krawędzie bloków kolorów

		int findRowMostLeftCodel(int);
		int findRowMostRightCodel(int);
		int findColumnTopCodel(int);
		int findColumnBottomCodel(int);

		bool verbose;

	protected:

		QImage *image;
		PCodePointer *pointer;
		int codel_block_count; // zmienna przechowująca liczbę kodeli bloku kolorów, świeżo policzoną

		int border_right_codel, border_down_codel, border_left_codel, border_up_codel;

		void fillMultiArray(int);
		void clearMultiArray();

	public:

		PBlockManager(QImage *, PCodePointer *, bool);
		~PBlockManager();

		void searchAndFillCodels(); // przygotowuje pomoczniczą tablicę do użytku i podstawia potrzebną liczbę kodeli pod zmienną
		int getCodelBlockCount();

		PPoint getNextPossibleCodel();

	// development:

		void __dev__showMultiArray();
		void __dev__showCountAndBorderCodels();

};

#endif
