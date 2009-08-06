//// includes

// header file
#include "pcodemachine.h"

// piet core
#include "../debug.h"
#include "penums.h"
#include "pblockmanager.h"
#include "pcolormanager.h"
#include "pcodepointer.h"
#include "pconsole.h"

// C++
#include <iostream>

// STL
// none

// Qt
#include <QString>

PCodeMachine::PCodeMachine(PConsole *given_console, QString given_filename)
{
	debug("CONSTRUCTOR ----- code-machine START\n");
	console = given_console;
	image = new QImage(given_filename);
	pointer = new PCodePointer(image);
	block_manager = new PBlockManager(image, pointer);
	color_manager = new PColorManager();
	debug("CONSTRUCTOR ----- code-machine END\n");
}

PCodeMachine::~PCodeMachine()
{
	debug("DESTRUCTOR ----- code-machine START\n");
	image->~QImage();
	debug("DESTRUCTOR ----- code-machine END\n");
}

void PCodeMachine::prepareToExecute()
{
	pointer->clear();
}

//==================================================================

int PCodeMachine::getCodelBlockCount()
{
	return block_manager->getCodelBlockCount();
}

PInstructions PCodeMachine::movePointerAndGetInstructionToExecute()
{
	block_manager->searchAndFillCodels(); // oblicz liczbe kodeli bloku kolorów w którym sie znajduje kodel wskazywany przez głowicę

	std::cout << block_manager->getCodelBlockCount() << std::endl;
}

//==================================================================

void PCodeMachine::__dev__printImageInfo()
{
	std::cout << std::endl;
	QRgb tmp = image->pixel(28, 0);
	std::cout << "R: " << qRed(tmp) << std::endl;
	std::cout << "G: " << qGreen(tmp) << std::endl;
	std::cout << "B: " << qBlue(tmp) << std::endl;
	std::cout << std::endl;
}

void PCodeMachine::__dev__printConsole()
{
	pointer->__dev__printConsole();
	std::cout << "image size: height= " << image->height() << " width= " << image->width() << std::endl;
	std::cout << std::endl;
}

