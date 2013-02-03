#ifndef P_CODE_POINTER
#define P_CODE_POINTER

//// includes

// piet core
#include "p_enums.h"
#include "p_structs.h"

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

/** \brief Głowica obrazu kodu
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

		/**
		 * Pole logiczne definiujące tryb gadatliwy.
		 */
		bool verbose;

	protected:

		/**
		 * Referencja do obrazu kodu, po którym porusza się głowica.
		 */
		QImage *image; // obraz kodu (plik graficzny którego pixle będą interpretowane)

		/**
		 * Codel chooser (CC, selektor kodeli).
		 */
		PCodelChooserValues codel_chooser;
		void setCodelChooser(PCodelChooserValues);

		/**
		 * Direction pointer (DP, wskaźnik kierunku).
		 */
		PDirectionPointerValues direction_pointer; // direction pointer
		void setDirectionPointer(PDirectionPointerValues);

		void turnDirectionPointerClockwise();
		void turnDirectionPointerAnticlockwise();

	public:

		PCodePointer(QImage *, PPoint);
		~PCodePointer();

		void setVerbosity(bool);

		void clear();

		PPoint getCoordinates();
		void setCoordinateX(int);
		void incCoordinateX();
		void decCoordinateX();
		void setCoordinateY(int);
		void incCoordinateY();
		void decCoordinateY();
		void setCoordinates(PPoint);
		QRgb getPointedPixel();

		QRgb getPixel(PPoint);
		bool pointOutsideImage(PPoint);

		PDirectionPointerValues getDirectionPointerValue();
		PCodelChooserValues getCodelChooserValue();
		void toggleCodelChooser();
		void toggleDirectionPointer();
		void toggle();

};

#endif
