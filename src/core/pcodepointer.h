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
 * opis
 */

class PCodePointer {

	static const int INIT_coord_x = 0, INIT_coord_y = 0;
	static const PCodelChooserValues INIT_cc = cc_left;
	static const PDirectionPointerValues INIT_dp = dp_right;

	protected:

		QImage *image; // obraz kodu (plik graficzny którego pixle będą interpretowane)

		int coord_x, coord_y; // współrzędne na które wskazuje głowica
		int getCoordX();
		int getCoordY();

		PCodelChooserValues codel_chooser;; // codel chooser
		void setCodelChooser(PCodelChooserValues);

		PDirectionPointerValues direction_pointer; // direction pointer
		void setDirectionPointer(PDirectionPointerValues);

		// w jaki sposób głowica powinna mieć dostęp do samego rysunku

	public:

		PCodePointer(QImage *);
		~PCodePointer();

		void turnDirectionPointerClockwise();

		QRgb getPointedPixel();

		void clear();

};

#endif
