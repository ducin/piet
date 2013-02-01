//// includes

// header file
#include "pguivirtualmachine.h"

// piet core
#include "../debug.h"

// C++
#include <iostream>

// STL
// none

// Qt
#include <QtGui>
#include <QString>

/** \file pconsolevirtualmachine.cpp
 * \brief Plik z kodem źródłowym klasy PConsoleVirtualMachine
 *
 * Plik zawiera kod źródłowy klasy PConsoleVirtualMachine.
 */

PGuiVirtualMachine::PGuiVirtualMachine(QString filename, std::stringstream &str)
: PVirtualMachine(filename, str)
{
    std::cout << "GUI VM" << std::endl;
}

bool PGuiVirtualMachine::validateNumber(int value)
{
    return true;
}

void PGuiVirtualMachine::readNumber()
{
    std::cout << "GUI readNumber" << std::endl;
    int read;
    do {
      read = QInputDialog::getInteger(
        0, "Piet input reading", "Enter a number:", 1);
    } while (!validateNumber(read));
    stack->instrPush(read);
}

bool PGuiVirtualMachine::validateChar(QString value)
{
    return value.size() == 1;
}

void PGuiVirtualMachine::readChar()
{
    std::cout << "GUI readNumber" << std::endl;
    QString read;
    do {
      read = QInputDialog::getText(
        0, "Piet input reading", "Enter a character:");
    } while (!validateChar(read));
    stack->instrPush(read.toInt());
}
