#ifndef P_CODE_POINTER
#define P_CODE_POINTER

//// includes

// piet core
#include "penums.h"
#include "pstructs.h"

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

	static const PCodelChooserValues INIT_cc = cc_left;
	static const PDirectionPointerValues INIT_dp = dp_right;

	private:

		PPoint initial_coords;
		PPoint coords; // współrzędne na które wskazuje głowica

	protected:

		QImage *image; // obraz kodu (plik graficzny którego pixle będą interpretowane)

		void setCoordinateX(int);
		void setCoordinateY(int);

		PCodelChooserValues codel_chooser;; // codel chooser
		void setCodelChooser(PCodelChooserValues);

		PDirectionPointerValues direction_pointer; // direction pointer
		void setDirectionPointer(PDirectionPointerValues);

		// w jaki sposób głowica powinna mieć dostęp do samego rysunku

	public:

		PCodePointer(QImage *, PPoint);
		~PCodePointer();

		PPoint getCoordinates();
		void setCoordinates(int, int);
		void setCoordinates(PPoint);

		bool pointOutsideImage(PPoint);

		PDirectionPointerValues getDirectionPointerValue();
		void turnDirectionPointerClockwise();

		PCodelChooserValues getCodelChooserValue();
		void toggleCodelChooser();

		QRgb getPointedPixel();
		QRgb getPixel(PPoint);

		void clear();

	// development:

		void __dev__printCoordinates();
		void __dev__printDirectionPointer();
		void __dev__printCodelChooser();
		void __dev__printConsole();

};

#endif
