//// includes

// header file
#include "pcodepointer.h"

// piet core
#include "../debug.h"
#include "penums.h"
#include "pstructs.h"

// C++
#include <iostream>

// STL
// none

// Qt
// none

/** \file pcodepointer.cpp
 * \brief Plik z kodem źródłowym klasy PCodePointer
 *
 * Plik zawiera kod źródłowy klasy PCodePointer.
 */

/**
 * Konstruktor głowicy obrazu kodu. Nie robi nic szczególnego.
 */
PCodePointer::PCodePointer(QImage *code_image, PPoint initial)
{
	debug("CONSTRUCTOR ----- code-pointer START\n");
	verbose = false;
	initial_coords = initial;
	image = code_image; // referencja do obiektu obrazu kodu
	debug("CONSTRUCTOR ----- code-pointer END\n");
}

/**
 * Destruktor głowicy obrazu kodu. Nie robi nic szczególnego.
 */
PCodePointer::~PCodePointer()
{
	debug("DESTRUCTOR ----- code-pointer START\n");

	debug("DESTRUCTOR ----- code-pointer END\n");
}

/**
 * Ustala tryb gadatliwy.
 * @param verbosity tryb gadatliwy
 */
void PCodePointer::setVerbosity(bool verbosity)
{
	verbose = verbosity;
}

/**
 * Ustawia atrybuty głowicy (współrzędne oraz DP i CC) na wartości domyślne.
 */
void PCodePointer::clear()
{
	coords.x = initial_coords.x;
	coords.y = initial_coords.y;
	codel_chooser = INIT_cc;
	direction_pointer = INIT_dp;
}

//==================================================================

/**
 * Zwraca piksel wskazywany przez głowicę.
 * @return piksel wskazywany przez głowicę
 */
QRgb PCodePointer::getPointedPixel()
{
	return image->pixel(coords.x, coords.y);
}

/**
 * Zwraca piksel o zadanych współrzędnych.
 * @param point współrzędne punktu
 * @return piksel o wskazanych współrzędnych
 */
QRgb PCodePointer::getPixel(PPoint point)
{
	return image->pixel(point.x, point.y);
}

//==================================================================

/**
 * Ustala wartość DP.
 * @param dp wartość DP
 */
void PCodePointer::setDirectionPointer(PDirectionPointerValues dp)
{
	direction_pointer = dp;
}

/**
 * Zwraca wartość DP.
 * @return wartość DP
 */
PDirectionPointerValues PCodePointer::getDirectionPointerValue()
{
	return direction_pointer;
}

//==================================================================

/**
 * Ustala wartość CC.
 * @param cc wartość CC
 */
void PCodePointer::setCodelChooser(PCodelChooserValues cc)
{
	codel_chooser = cc;
}

/**
 * Zwraca wartość DP.
 * @return wartość DP
 */
PCodelChooserValues PCodePointer::getCodelChooserValue()
{
	return codel_chooser;
}

//==================================================================

/**
 * Obraca DP zgodnie z ruchem wskazówek zegara raz.
 */
void PCodePointer::turnDirectionPointerClockwise()
{
	switch (direction_pointer) {
		case dp_right:
			direction_pointer = dp_down;
			break;
		case dp_down:
			direction_pointer = dp_left;
			break;
		case dp_left:
			direction_pointer = dp_up;
			break;
		case dp_up:
			direction_pointer = dp_right;
			break;
	}
}

/**
 * Obraca DP przeciwnie do ruchu wskazówek zegara raz.
 */
void PCodePointer::turnDirectionPointerAnticlockwise()
{
	switch (direction_pointer) {
		case dp_right:
			direction_pointer = dp_up;
			break;
		case dp_down:
			direction_pointer = dp_right;
			break;
		case dp_left:
			direction_pointer = dp_down;
			break;
		case dp_up:
			direction_pointer = dp_left;
			break;
	}
}

/**
 * Zmienia wartość CC w sytuacji, gdy głowica nie mogła iść dalej w dotychczasowym kierunku. Używane wewnątrz metody toggle().
 */
void PCodePointer::toggleCodelChooser()
{
	switch (codel_chooser) {
		case cc_left:
			codel_chooser = cc_right;
			break;
		case cc_right:
			codel_chooser = cc_left;
			break;
	}
}

/**
 * Zmienia wartość DP w sytuacji, gdy głowica nie mogła iść dalej w dotychczasowym kierunku. Używane wewnątrz metody toggle().
 */
void PCodePointer::toggleDirectionPointer()
{
	turnDirectionPointerClockwise();
}

/**
 * Zmienia wartość CC oraz DP w sytuacji, gdy głowica nie mogła iść dalej w dotychczasowym kierunku.
 */
void PCodePointer::toggle()
{
	if (codel_chooser == cc_left) {
		toggleCodelChooser();
	} else {
		toggleCodelChooser();
		turnDirectionPointerClockwise();
	}
}

//==================================================================

/**
 * Zwraca współrzędne głowicy.
 * @return współrzędne głowicy
 */
PPoint PCodePointer::getCoordinates()
{
	return coords;
}

/**
 * Ustala współrzędną X głowicy.
 * @param newX nowa wartość współrzędnej X
 */
void PCodePointer::setCoordinateX(int newX)
{
	coords.x = newX;
}

/**
 * Inkrementuje współrzędną X głowicy.
 */
void PCodePointer::incCoordinateX()
{
	coords.x++;
}

/**
 * Dekrementuje współrzędną X głowicy.
 */
void PCodePointer::decCoordinateX()
{
	coords.x--;
}

/**
 * Ustala współrzędną Y głowicy.
 * @param newY nowa wartość współrzędnej Y
 */
void PCodePointer::setCoordinateY(int newY)
{
	coords.y = newY;
}

/**
 * Inkrementuje współrzędną Y głowicy.
 */
void PCodePointer::incCoordinateY()
{
	coords.y++;
}

/**
 * Dekrementuje współrzędną Y głowicy.
 */
void PCodePointer::decCoordinateY()
{
	coords.y--;
}

/**
 * Ustala współrzędne głowicy.
 * @param new_point punkt (nowe współrzędne)
 */
void PCodePointer::setCoordinates(PPoint new_point)
{
	coords = new_point;
}

/**
 * Determinuje, czy punkt o zadanych współrzędnych mieści się w obrazie kodu.
 * @param point wskazany punkt
 * @return czy mieści się w obrazie kodu
 */
bool PCodePointer::pointOutsideImage(PPoint point)
{
	return (point.x < 0 || point.x >= image->width() || point.y < 0 || point.y >= image->height());
}

//==================================================================
 // development
//==================================================================

/**
 * METODA TESTOWA. Wyświetla na konsoli informacje o współrzędnych głowicy.
 */
void PCodePointer::__dev__printCoordinates()
{
	std::cout << "[" << coords.x << "," << coords.y << "]";
}

/**
 * METODA TESTOWA. Wyświetla na konsoli informacje o DP.
 */
void PCodePointer::__dev__printDirectionPointer()
{
	std::cout << "DP:";
	switch (direction_pointer) {
		case dp_right:
			std::cout << "right";
			break;
		case dp_down:
			std::cout << "down";
			break;
		case dp_left:
			std::cout << "left";
			break;
		case dp_up:
			std::cout << "up";
			break;
	}
	std::cout << "(" << (int) direction_pointer << ")";
}

/**
 * METODA TESTOWA. Wyświetla na konsoli informacje o CC.
 */
void PCodePointer::__dev__printCodelChooser()
{
	std::cout << "CC:";
	switch (codel_chooser) {
		case cc_left:
			std::cout << "left";
			break;
		case cc_right:
			std::cout << "right";
			break;
	}
	std::cout << "(" << (int) codel_chooser << ")";
}

/**
 * METODA TESTOWA. Wyświetla na konsoli wszystkie informacje o głowicy.
 */
void PCodePointer::__dev__printConsole()
{
	std::cout << "GŁOWICA/";
	__dev__printCoordinates();
	std::cout << ",";
	__dev__printDirectionPointer();
	std::cout << ",";
	__dev__printCodelChooser();
	std::cout << "; ";
}
