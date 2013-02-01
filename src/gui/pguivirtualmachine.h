#ifndef P_GUI_VIRTUAL_MACHINE
#define P_GUI_VIRTUAL_MACHINE

//// includes

// piet core
#include "pvirtualmachine.h"

// C++
// none

// STL
// none

// Qt
#include <QString>

/** \file pguivirtualmachine.h
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

        PGuiVirtualMachine(QString , std::stringstream& );
  
    protected:

        bool validateNumber(int);
        virtual void readNumber();

        bool validateChar(QString);
        virtual void readChar();

public slots:
    void inputSubmitted();
};

#endif
