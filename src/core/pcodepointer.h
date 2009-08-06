#ifndef P_CODE_POINTER
#define P_CODE_POINTER

//// includes

// piet core
#include "penums.h"

// C++
// none

// STL
// none

// Qt
#include <QImage>
#include <QRgb>

/** \file pcodepointer.h
 * \brief plik nagłówkowy klasy PCodePointer
 *
 * Plik nagłówkowy zawiera definicję klasy PCodePointer.
 */

/** \brief głowica obrazu kodu
 *
 * Klasa pełniąca funkcję głowicy która porusza się po tzw. "obrazie kodu". Wykonuje wszystkie operacje bezpośrednio związane z odczytywaniem piksli z obrazu, posiada (zmieniające się w trakcie działania programu) współrzędne oraz dodatkowe elementy, takie jak 'codel chooser' i 'direction pointer' (patrz: specyfikacja języka Piet).

Obok managera kolorów i managera bloków koloru jest trzecim elementem wykorzystywanym przez tzw. "maszynę kodu" i (razem z nimi) służy do właściwej, jednoznacznej interpretacji kodu Pieta.
 */
class PCodePointer {

	static const int INIT_coord_x = 0, INIT_coord_y = 0;
	static const PCodelChooserValues INIT_cc = cc_left;
	static const PDirectionPointerValues INIT_dp = dp_right;

	protected:

		QImage *image; // obraz kodu (plik graficzny którego pixle będą interpretowane)

		int coord_x, coord_y; // współrzędne na które wskazuje głowica

		PCodelChooserValues codel_chooser;; // codel chooser
		void setCodelChooser(PCodelChooserValues);

		PDirectionPointerValues direction_pointer; // direction pointer
		void setDirectionPointer(PDirectionPointerValues);

		// w jaki sposób głowica powinna mieć dostęp do samego rysunku

	public:

		PCodePointer(QImage *);
		~PCodePointer();

		int getCoordX();
		int getCoordY();

		void turnDirectionPointerClockwise();
		void toggleCodelChooser();

		QRgb getPointedPixel();

		void clear();

	// development:

		void __dev__printCoordinates();
		void __dev__printConsole();

};

#endif
