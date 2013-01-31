#ifndef P_CALC_STACK
#define P_CALC_STACK

//// includes

// piet core
#include "penums.h"
#include "pstructs.h"

// C++
// none

// STL
#include <list> // lista użyta celowo (a nie stos <stack>), aby ułatwić wyświetlanie zawartości stosu

// Qt
// none

/** \file pcalcstack.h
 * \brief plik nagłówkowy klasy PCalcStack
 *
 * Plik nagłówkowy zawiera definicję klasy PCalcStack.
 */

/** \brief Stos
 *
 * Klasa pełniąca funkcję stosu wykorzystywanego do interpretowania kodu Pieta. Wszystkie jej funkcjonalności są dokładnie określone przez instrukcje dozwolone w języku Piet - począwszy od podstawowych (kładzenie/zdejmowanie elementów), poprzez arytmetyczne i logiczne (zmieniające elementy na szczycie stosu w zależności od ich wartości) a skończywszy na operacjach sterujących głowicą (przestawianie 'codel chooser' i 'direction pointer' - patrz: specyfikacja Piet), operacjach modyfikujących strukturę elementów stosu oraz operacjach I/O.

Stanowi jeden z dwóch obiektów potrzebnych do pełnej interpretacji kodu, używanych przez tzw. "wirtualną maszynę Pieta", najwyższy w hierarchi obiekt.
 */
class PCalcStack {

	private:

		/**
		 * Pole logiczne definiujące tryb gadatliwy.
		 */
		bool verbose;

	protected:

		/**
		 * Struktura przechowująca wszystkie wartości stosu. Jest nią lista a nie stos - celowo - aby ułatwić implementację niektórych operacji: operacji Pieta ROLL. wyświetlanie wszystkich elementów stosu itd. Użycie zwykłego stosu skomplikowałoby zakodowanie tych metod bardzo znacznie - i niepotrzebnie.
		 */
		std::list<int> values;

	public:

		PCalcStack();
		~PCalcStack();

		void setVerbosity(bool);

		void clear();
		void prepareToExecute();

		int size();
		std::list<int>::iterator begin_iterator();
		std::list<int>::iterator end_iterator();
		bool hasAtLeastNElements(unsigned int);

	// operacje podstawowe:

		void instrPush(int);
		int instrPop();

	// operacje arytmetyczne:

		void instrAdd();
		void instrSubtract();
		void instrMultiply();
		void instrDivide();
		void instrModulo();

	// operacje logiczne:

		void instrNot();
		void instrGreater();

	// operacje na strukturze elementów:

		void instrDuplicate();
		void instrRoll();

	// development:

		void __dev__printAllStackValues();
		void __dev__printConsole();

};

#endif
