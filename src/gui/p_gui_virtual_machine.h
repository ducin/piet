#ifndef P_GUI_VIRTUAL_MACHINE
#define P_GUI_VIRTUAL_MACHINE

#include <QString>

#include "p_virtual_machine.h"

/** \file p_gui_virtual_machine.h
 * \brief plik nagłówkowy klasy PGuiVirtualMachine
 *
 * Plik nagłówkowy zawiera definicję klasy PGuiVirtualMachine.
 */

/** \brief Wirtualna maszyna Pieta dla aplikacji desktopowych
 *
 * Implementacja "wirtualnej maszyny Pieta" dla aplikacji desktopowych.
 */
class PGuiVirtualMachine : public PVirtualMachine {

public:
    PGuiVirtualMachine(const char *, std::stringstream& );

protected:
    bool validateNumber(int);
    virtual void readNumber();

    bool validateChar(QString);
    virtual void readChar();

public slots:
    void inputSubmitted();
};

#endif
