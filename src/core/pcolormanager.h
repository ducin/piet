#ifndef P_COLOR_MANAGER
#define P_COLOR_MANAGER

//// includes

// piet core
#include "penums.h"

// C++
// none

// STL
// none

// Qt
#include <QRgb>

/** \file pcolormanager.h
 * \brief plik nagłówkowy klasy PColorManager
 *
 * Klasa odpowiedzialna za właściwe interpretowanie kolorów, determinowanie czy kolor jest standardowy, jeśli niestandardowy - przydziela go do odpowiedniego koloru standardowego wg odpowiedniego algorytmu.
 */

class PColorManager {

	public:

		PColorManager();
		~PColorManager();

	QRgb LIGHT_RED, NORMAL_RED, DARK_RED;
	QRgb LIGHT_YELLOW, NORMAL_YELLOW, DARK_YELLOW;
	QRgb LIGHT_GREEN, NORMAL_GREEN, DARK_GREEN;
	QRgb LIGHT_CYAN, NORMAL_CYAN, DARK_CYAN;
	QRgb LIGHT_BLUE, NORMAL_BLUE, DARK_BLUE;
	QRgb LIGHT_MAGENTA, NORMAL_MAGENTA, DARK_MAGENTA;
	QRgb WHITE, BLACK;

		void initColorValues();

};

#endif
