//// includes

// header file
#include "p_color_manager.h"

// piet core
#include "../debug.h"
#include "p_enums.h"
#include "p_structs.h"

//C
#include <cstdlib>

// C++
#include <sstream>

// STL
// none

// Qt
#include <QRgb>

/** \file pcolormanager.cpp
 * \brief Plik z kodem źródłowym klasy PColorManager
 *
 * Plik zawiera kod źródłowy klasy PColorManager.
 */

PColorManager::PColorManager(std::stringstream &str) : stream(str)
{
	debug("CONSTRUCTOR ----- color-manager START\n");
	verbose = false;
	initColorValues();
	debug("CONSTRUCTOR ----- color-manager END\n");
}

PColorManager::~PColorManager()
{
	debug("DESTRUCTOR ----- color-manager START\n");

	debug("DESTRUCTOR ----- color-manager END\n");
}

/**
 * Ustala tryb gadatliwy.
 * @param verbosity tryb gadatliwy
 */
void PColorManager::setVerbosity(bool verbosity)
{
	verbose = verbosity;
}

/**
 * Inicjuje wartości zmiennych typu QRgb reprezentujących wszystkie 20 kolorów standardowych Pieta. Są one potem wykorzystywane praktycznie cały czas: do wyznaczania instrukcji które powinny być wykonane, do sprawdzania białych lub czarnych bloków.
 */
void PColorManager::initColorValues()
{
	// red
	LIGHT_RED = qRgb(255, 192, 192);
	NORMAL_RED = qRgb(255, 0, 0);
	DARK_RED = qRgb(192, 0, 0);
	// yellow
	LIGHT_YELLOW = qRgb(255, 255, 192);
	NORMAL_YELLOW = qRgb(255, 255, 0);
	DARK_YELLOW = qRgb(192, 192, 0);
	// green
	LIGHT_GREEN = qRgb(192, 255, 192);
	NORMAL_GREEN = qRgb(0, 255, 0);
	DARK_GREEN = qRgb(0, 192, 0);
	// cyan
	LIGHT_CYAN = qRgb(192, 255, 255);
	NORMAL_CYAN = qRgb(0, 255, 255);
	DARK_CYAN = qRgb(0, 192, 192);
	// blue
	LIGHT_BLUE = qRgb(192, 192, 255);
	NORMAL_BLUE = qRgb(0, 0, 255);
	DARK_BLUE = qRgb(0, 0, 192);
	// magenta
	LIGHT_MAGENTA = qRgb(255, 192, 255);
	NORMAL_MAGENTA = qRgb(255, 0, 255);
	DARK_MAGENTA = qRgb(192, 0, 192);
	// black, white
	WHITE = qRgb(255, 255, 255);
	BLACK = qRgb(0, 0, 0);
}

/**
 * Zwraca kolor jako element enumeracji dla zadanej wartości koloru typu QRgb.
 * @param color zadany kolor (wartość)
 * @return kolor (element enumeracji)
 */
PStdColors PColorManager::getColorName(QRgb color)
{
	if (color == LIGHT_RED) {
		return color_light_red;
	} else if (color == NORMAL_RED) {
		return color_normal_red;
	} else if (color == DARK_RED) {
		return color_dark_red;
	} else if (color == LIGHT_YELLOW) {
		return color_light_yellow;
	} else if (color == NORMAL_YELLOW) {
		return color_normal_yellow;
	} else if (color == DARK_YELLOW) {
		return color_dark_yellow;
	} else if (color == LIGHT_GREEN) {
		return color_light_green;
	} else if (color == NORMAL_GREEN) {
		return color_normal_green;
	} else if (color == DARK_GREEN) {
		return color_dark_green;
	} else if (color == LIGHT_CYAN) {
		return color_light_cyan;
	} else if (color == NORMAL_CYAN) {
		return color_normal_cyan;
	} else if (color == DARK_CYAN) {
		return color_dark_cyan;
	} else if (color == LIGHT_BLUE) {
		return color_light_blue;
	} else if (color == NORMAL_BLUE) {
		return color_normal_blue;
	} else if (color == DARK_BLUE) {
		return color_dark_blue;
	} else if (color == LIGHT_MAGENTA) {
		return color_light_magenta;
	} else if (color == NORMAL_MAGENTA) {
		return color_normal_magenta;
	} else if (color == DARK_MAGENTA) {
		return color_dark_magenta;
	} else if (color == WHITE) {
		return color_white;
	} else if (color == BLACK) {
		return color_black;
	} else {
		stream << "ERROR: PStdColors PColorManager::getColorName(QRgb color)" << std::endl;
		stream << "R:" << qRed(color) << " G:" << qGreen(color) << " B:" << qBlue(color) << std::endl;
		exit(1);
	}
}

int PColorManager::lightnessCycleDifference(PStdColors c1, PStdColors c2)
{
	int c1code = (int) c1, c2code = (int) c2;
	return ((c1code - c2code + 21) % 3);
}

int PColorManager::saturationCycleDifference(PStdColors c1, PStdColors c2)
{
	int c1code = (int) c1, c2code = (int) c2;
	return ( ( (c1code / 3) - (c2code / 3) + 6) % 6);
}

/**
 * Wyznacza instrukcję Pieat jaka ma zostać wykonana na podstawie dwóch kolorów bloków: pierwszy - który głowica opuściła i drugi - do którego głowica weszła. Metoda implementuje algorytm wyznaczania instrukcji opisany w tabeli 1.2 w rozdziale 1 pracy magisterskiej.
 * @param old_color kolor bloku który głowica opuściła
 * @param new_color kolor bloku do którego głowica weszła
 * @return indeks instrukcji która powinna zostać wykonana
 */
int PColorManager::getInstructionIndex(QRgb old_color, QRgb new_color)
{
	PStdColors p_old_color = getColorName(old_color);
	PStdColors p_new_color = getColorName(new_color);

	if (verbose) {
		stream << PEnums::stdColor(p_old_color) << "(" << ( (int) p_old_color ) << ")";
		stream << " -> ";
		stream << PEnums::stdColor(p_new_color) << "(" << ( (int) p_new_color ) << ")" << "; ";
	}

	int lightness_diff = lightnessCycleDifference(p_new_color, p_old_color);
	int saturation_diff = saturationCycleDifference(p_new_color, p_old_color);

	return ( 3 * saturation_diff + lightness_diff );
}
