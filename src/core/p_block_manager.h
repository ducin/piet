#ifndef P_BLOCK_MANAGER
#define P_BLOCK_MANAGER

//// includes

// piet core
#include "p_enums.h"
#include "p_structs.h"
#include "p_code_pointer.h"

// C++
// none

// STL
#include <sstream>

// Qt
#include <QRgb>
#include <QImage>

/** \file pblockmanager.h
 * \brief plik nagłówkowy klasy PBlockManager
 *
 * Plik nagłówkowy zawiera definicję klasy PBlockManager.
 */

/** \brief Manager bloków kolorów
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

		/**
		 * Pole logiczne definiujące tryb gadatliwy.
		 */
		bool verbose;

		std::stringstream &stream;

	protected:

		/**
		 * Referencja do obrazu kodu.
		 */
		QImage *image;
		/**
		 * Referencja do glowicy obrazu kodu.
		 */
		PCodePointer *pointer;
		/**
		 * Pole przechowujące liczbę kodeli bloku kolorów (liczoną osobno przy wykonywaniu każdej instrukcji przez wirtualną maszynę).
		 */
		int codel_block_count;

		/** Pole określające odciętą (współrzędną) skrajnego kodela z prawej strony, znajdującego się w aktualnie badanym bloku koloru. */ int border_right_codel;
		/** Pole określające rzędną (współrzędną) skrajnego kodela z dołu, znajdującego się w aktualnie badanym bloku koloru. */ int border_down_codel;
		/** Pole określające odciętą (współrzędną) skrajnego kodela z lewej strony, znajdującego się w aktualnie badanym bloku koloru. */ int border_left_codel;
		/** Pole określające rzędną (współrzędną) skrajnego kodela z góry, znajdującego się w aktualnie badanym bloku koloru. */ int border_up_codel;

		void fillMultiArray(int);
		void clearMultiArray();

	public:

		PBlockManager(QImage *, PCodePointer *, std::stringstream &);
		~PBlockManager();

		void setVerbosity(bool);

		void searchAndFillCodels(); // przygotowuje pomoczniczą tablicę do użytku i podstawia potrzebną liczbę kodeli pod zmienną
		int getCodelBlockCount();

		PPoint getNextPossibleCodel();

	// development:

		void __dev__showMultiArray();
		void __dev__showCountAndBorderCodels();

};

#endif
