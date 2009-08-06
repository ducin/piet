#ifndef P_STACK
#define P_STACK

//// includes

// piet core
#include "penums.h"

// C++
// none

// STL
#include <list> // lista użyta celowo, aby ułatwić wyświetlanie zawartości stosu

// Qt
// none

/** \file pstack.h
 * \brief plik nagłówkowy klasy PStack
 *
 * Klasa pełniąca funkcję stosu wykorzystywanego do interpretowania kodu Pieta.
 */

class PStack {

	protected:

		std::list<int> values;

	public:

		PStack();
		~PStack();

		void clear();

	// operacje podstawowe:

		void instrPush(int);
		void instrPop();

	// operacje arytmetyczne:

		void instrAdd();
		void instrSub();
		void instrMul();
		void instrDiv();
		void instrMod();

	// operacje logiczne:

		void instrNot();
		void instrGreater();

	// operacje na głowicy maszyny:

		int instrPointer(); // zwraca liczbę obrotów DP (co dalej jest wykonywane przez maszynę kodu)
		int instrSwitch();

	// operacje na stosie:

		void instrDuplicate();
		void instrRoll();

	// operacje I/O:

		void instrInNumber();
		void instrInChar();
		void instrOutNumber();
		void instrOutChar();

	// development:

		void __dev__printAllStackValues();

};

#endif
