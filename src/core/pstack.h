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
 * Plik nagłówkowy zawiera definicję klasy PStack.
 */

/** \brief stos
 *
 * Klasa pełniąca funkcję stosu wykorzystywanego do interpretowania kodu Pieta. Wszystkie jej funkcjonalności są dokładnie określone przez instrukcje dozwolone w języku Piet - począwszy od podstawowych (kładzenie/zdejmowanie elementów), poprzez arytmetyczne i logiczne (zmieniające elementy na szczycie stosu w zależności od ich wartości) a skończywszy na operacjach sterujących głowicą (przestawianie 'codel chooser' i 'direction pointer' - patrz: specyfikacja Piet), operacjach modyfikujących strukturę elementów stosu oraz operacjach I/O.

Stanowi jeden z dwóch obiektów potrzebnych do pełnej interpretacji kodu, używanych przez tzw. "wirtualną maszynę Pieta", najwyższy w hierarchi obiekt.
 */
class PStack {

	protected:

		std::list<int> values;

	public:

		PStack();
		~PStack();

		void clear();
		void prepareToExecute();

	// operacje podstawowe:

		void instrPush(int);
		void instrPop();

	// operacje arytmetyczne:

		void instrAdd();
		void instrSubtract();
		void instrMultiply();
		void instrDivide();
		void instrModulo();

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
		void __dev__printConsole();

};

#endif
