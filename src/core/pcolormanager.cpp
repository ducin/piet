//// includes

// header file
#include "pcolormanager.h"

// piet core
#include "../debug.h"
#include "penums.h"

// C++
// none

// STL
// none

// Qt
// none

PColorManager::PColorManager()
{
	debug("CONSTRUCTOR ----- color-manager START\n");
	initColorValues();
	debug("CONSTRUCTOR ----- color-manager END\n");
}

PColorManager::~PColorManager()
{
	debug("DESTRUCTOR ----- color-manager START\n");

	debug("DESTRUCTOR ----- color-manager END\n");
}

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

