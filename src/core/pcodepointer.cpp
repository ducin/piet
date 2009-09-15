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

PCodePointer::PCodePointer(QImage *code_image, PPoint initial)
{
	debug("CONSTRUCTOR ----- code-pointer START\n");
	verbose = false;
	initial_coords = initial;
	image = code_image; // referencja do obiektu obrazu kodu
	debug("CONSTRUCTOR ----- code-pointer END\n");
}

PCodePointer::~PCodePointer()
{
	debug("DESTRUCTOR ----- code-pointer START\n");

	debug("DESTRUCTOR ----- code-pointer END\n");
}

void PCodePointer::setVerbosity(bool verbosity)
{
	verbose = verbosity;
}

void PCodePointer::clear()
{
	coords.x = initial_coords.x;
	coords.y = initial_coords.y;
	codel_chooser = INIT_cc;
	direction_pointer = INIT_dp;
}

//==================================================================

QRgb PCodePointer::getPointedPixel()
{
	return image->pixel(coords.x, coords.y);
}

QRgb PCodePointer::getPixel(PPoint point)
{
	return image->pixel(point.x, point.y);
}

//==================================================================

void PCodePointer::setDirectionPointer(PDirectionPointerValues dp)
{
	direction_pointer = dp;
}

PDirectionPointerValues PCodePointer::getDirectionPointerValue()
{
	return direction_pointer;
}

//==================================================================

void PCodePointer::setCodelChooser(PCodelChooserValues cc)
{
	codel_chooser = cc;
}

PCodelChooserValues PCodePointer::getCodelChooserValue()
{
	return codel_chooser;
}

//==================================================================

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

void PCodePointer::toggleDirectionPointer()
{
	turnDirectionPointerClockwise();
}

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

PPoint PCodePointer::getCoordinates()
{
	return coords;
}

void PCodePointer::setCoordinateX(int newX)
{
	coords.x = newX;
}

void PCodePointer::incCoordinateX()
{
	coords.x++;
}

void PCodePointer::decCoordinateX()
{
	coords.x--;
}

void PCodePointer::setCoordinateY(int newY)
{
	coords.y = newY;
}

void PCodePointer::incCoordinateY()
{
	coords.y++;
}

void PCodePointer::decCoordinateY()
{
	coords.y--;
}

void PCodePointer::setCoordinates(PPoint new_point)
{
	coords = new_point;
}

// Metoda determinuje, czy punkt o zadanych współrzędnych mieści się w obrazie kodu.
bool PCodePointer::pointOutsideImage(PPoint point)
{
	return (point.x < 0 || point.x >= image->width() || point.y < 0 || point.y >= image->height());
}

//==================================================================
 // development
//==================================================================

void PCodePointer::__dev__printCoordinates()
{
	std::cout << "[" << coords.x << "," << coords.y << "]";
}

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
