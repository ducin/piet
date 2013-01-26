#ifndef P_COLOR_MANAGER
#define P_COLOR_MANAGER

//// includes

// piet core
#include "penums.h"
#include "pstructs.h"

// C++
// none

// STL
// none

// Qt
#include <QRgb>

/** \file pcolormanager.h
 * \brief plik nagłówkowy klasy PColorManager
 *
 * Plik nagłówkowy zawiera definicję klasy PColorManager.
 */

/** \brief Maszyna kodu
 *
 * Klasa odpowiedzialna za właściwe interpretowanie kolorów, determinowanie czy kolor jest standardowy, jeśli niestandardowy - przydziela go do odpowiedniego koloru standardowego wg odpowiedniego algorytmu.
 */
class PColorManager {

	private:

		int lightnessCycleDifference(PStdColors, PStdColors);
		int saturationCycleDifference(PStdColors, PStdColors);

		/**
		 * Pole logiczne definiujące tryb gadatliwy.
		 */
		bool verbose;

	public:

		PColorManager();
		~PColorManager();

		void setVerbosity(bool);

		int getInstructionIndex(QRgb, QRgb);

	QRgb /** kolor jasny czerwony */ LIGHT_RED, /** kolor czerwony */ NORMAL_RED, /** kolor ciemny czerwony */ DARK_RED;
	QRgb /** kolor jasny żółty */ LIGHT_YELLOW, /** kolor żółty */ NORMAL_YELLOW, /** kolor ciemny żółty */ DARK_YELLOW;
	QRgb /** kolor jasny zielony */ LIGHT_GREEN, /** kolor zielony */ NORMAL_GREEN, /** kolor ziemny zielony */ DARK_GREEN;
	QRgb /** kolor jasny błękitny */ LIGHT_CYAN, /** kolor błękitny */ NORMAL_CYAN, /** kolor ciemny błękitny */ DARK_CYAN;
	QRgb /** kolor jasny niebieski */ LIGHT_BLUE, /** kolor niebieski */ NORMAL_BLUE, /** kolor ciemny niebieski */ DARK_BLUE;
	QRgb /** kolor jasny magenta */ LIGHT_MAGENTA, /** kolor magenta */ NORMAL_MAGENTA, /** kolor ciemny magenta */ DARK_MAGENTA;
	QRgb /** kolor biały */ WHITE, /** kolor czarny */ BLACK;

		PStdColors getColorName(QRgb);

		void initColorValues();

	// development:

		void __dev__printColor(PStdColors);

};

#endif
