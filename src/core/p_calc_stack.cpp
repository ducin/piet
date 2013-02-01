//// includes

// header file
#include "p_calc_stack.h"

// piet core
#include "../debug.h"
#include "p_enums.h"
#include "p_structs.h"

// C++
#include <iostream>

// STL
#include <list>

// Qt
// none

/** \file pcalcstack.cpp
 * \brief Plik z kodem źródłowym klasy PCalcStack
 *
 * Plik zawiera kod źródłowy klasy PCalcStack.
 */

/**
 * Konstruktor stosu. Nie robi nic szczególnego.
 */
PCalcStack::PCalcStack()
{
	debug("CONSTRUCTOR ----- calc stack START\n");
	verbose = false;
	debug("CONSTRUCTOR ----- calc stack END\n");
}

/**
 * Destruktor stosu. Nie robi nic szczególnego.
 */
PCalcStack::~PCalcStack()
{
	debug("DESTRUCTOR ----- calc stack START\n");
	debug("DESTRUCTOR ----- calc stack END\n");
}

/**
 * Ustala tryb gadatliwy.
 * @param verbosity tryb gadatliwy
 */
void PCalcStack::setVerbosity(bool verbosity)
{
	verbose = verbosity;
}

/**
 * Czyści stos - usuwa wszystkie elementy.
 */
void PCalcStack::clear()
{
	values.clear();
}

/**
 * Przygotowuje stos do użycia (czyści go).
 */
void PCalcStack::prepareToExecute()
{
	clear();
}

/**
 * Zwraca rozmiar stosu.
 * @return rozmiar stosu
 */
int PCalcStack::size()
{
	return values.size();
}

std::list<int>::iterator PCalcStack::begin_iterator()
{
	return values.begin();
}

std::list<int>::iterator PCalcStack::end_iterator()
{
	return values.end();
}

/**
 * Sprawdza, czy stos posiada co najmniej zadaną liczbę elementów na stosie. Metoda wykorzystywana np. przed wykonaniem operacji ADD: muszą być na stosie co najmniej dwa elementy, aby udało się wykonać operację.
 * @param elements minimalna liczba elementów stosu
 * @return rozmiar stosu
 */
bool PCalcStack::hasAtLeastNElements(unsigned int elements)
{
	return (values.size() >= elements);
}

//==========================================================================
	// operacje podstawowe:

/**
 * Wykonuje operację PUSH: odkłada element na stosie.
 * @param item element do odłożenia na stosie
 */
void PCalcStack::instrPush(int item)
{
	values.push_front(item);
}

/**
 * Wykonuje operację POP: zdejmuje element ze stosu.
 * @return zdjęty ze stosu element
 */
int PCalcStack::instrPop()
{
	int el = values.front();
	values.pop_front();
	return el;
}

//==========================================================================
	// operacje arytmetyczne:

/**
 * Wykonuje operację ADD: zdejmuje ze szczytu stosu dwa elementy, dodaje ich wartości a wynik odkłada z powrotem na stosie.
 */
void PCalcStack::instrAdd()
{
	int el1 = values.front();
	values.pop_front();
	int el2 = values.front();
	values.pop_front();
	values.push_front(el2 + el1);
}

/**
 * Wykonuje operację SUB: zdejmuje ze szczytu stosu dwa elementy, oblicza różnicę: element pod elementem szczytowym - element szczytowy, a wynik odkłada z powrotem na stosie.
 */
void PCalcStack::instrSubtract()
{
	int el1 = values.front();
	values.pop_front();
	int el2 = values.front();
	values.pop_front();
	values.push_front(el2 - el1);
}

/**
 * Wykonuje operację MUL: zdejmuje ze szczytu stosu dwa elementy, mnoży ich wartości a wynik odkłada z powrotem na stosie.
 */
void PCalcStack::instrMultiply()
{
	int el1 = values.front();
	values.pop_front();
	int el2 = values.front();
	values.pop_front();
	values.push_front(el2 * el1);
}

/**
 * Wykonuje operację DIV: zdejmuje ze szczytu stosu dwa elementy, oblicza iloraz: element pod elementem szczytowym / element szczytowy, a wynik odkłada z powrotem na stosie.
 */
void PCalcStack::instrDivide()
{
	int el1 = values.front();
	values.pop_front();
	int el2 = values.front();
	values.pop_front();
	values.push_front(el2 / el1);
}

/**
 * Wykonuje operację MOD: zdejmuje ze szczytu stosu dwa elementy, oblicza dzielenie modulo: element pod elementem szczytowym % element szczytowy, a wynik odkłada z powrotem na stosie.
 */
void PCalcStack::instrModulo()
{
	int el1 = values.front();
	values.pop_front();
	int el2 = values.front();
	values.pop_front();
	values.push_front(el2 % el1);
}

//==========================================================================
	// operacje logiczne:

/**
 * Wykonuje operację NOT: zdejmuje element ze szczytu stosu i zwraca jego logiczną negację: 1, jeśli element był równy zero lub 0 w przeciwnym razie.
 */
void PCalcStack::instrNot()
{
	int el = values.front();
	values.pop_front();
	values.push_front(el != 0 ? 0 : 1);
}

/**
 * Wykonuje operację GREATER: zdejmuje ze szczytu stosu dwa elementy i sprawdza, czy element pod elementem szczytowym jest większy od elementu szczytowego; jeśli tak - odkłada na stosie wartość 1, jeśli nie - 0.
 */
void PCalcStack::instrGreater()
{
	int el1 = values.front();
	values.pop_front();
	int el2 = values.front();
	values.pop_front();
	values.push_front(el2 > el1 ? 1 : 0);
}

//==========================================================================
	// operacje na stosie:

/**
 * Wykonuje operację DUP: odkłada na stosie kopię elementu szczytowego stosu.
 */
void PCalcStack::instrDuplicate()
{
	int el = values.front();
	values.push_front(el);
}

/**
 * Wykonuje operację ROLL, modyfikującą strukturę stosu. Zdejmuje ze szczytu stosu dwa elementy: element ze szczytu stanowi ilość przesunięć elementów stosu (ozn. C), drugi element (który był pod elementem szczytowym) określa rozmiar fragmentu stosu jaki ulegnie modyfikacji (ozn. S). Po zdjęciu tych elementów następuje przesuwanie elementów: nowy element ze szczytu stosu przesuwa się na sam dół modyfikowanego fragmentu stosu (określanego przez S); operacja powtarza się tyle razy ile wynosi wartość C.
 */
void PCalcStack::instrRoll()
{
	std::list<int> tmp;
	int loop_count = values.front();
	values.pop_front();
	int depth = values.front();
	values.pop_front();
	if (depth > 0) {
		for (int i = 0; i < depth; i++) {
			tmp.push_back(values.front());
			values.pop_front();
		}
		if (loop_count > 0) {
			for (int i = loop_count; i > 0; i--) {
				tmp.push_back(tmp.front());
				tmp.pop_front();
			}
		} else {
			for (int i = loop_count; i < 0; i++) {
				tmp.push_front(tmp.back());
				tmp.pop_back();
			}
		}
		for (int i = 0; i < depth; i++) {
			values.push_front(tmp.back());
			tmp.pop_back();
		}
	}
}

//==========================================================================
	// development:

/**
 * METODA TESTOWA. Wyświetla wartości wszystkich elementów stosu.
 */
void PCalcStack::__dev__printAllStackValues()
{
	std::cout << "rozm:" << values.size() << " elem: ";
	std::list<int>::iterator it;
	for (it = values.begin(); it != values.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

/**
 * METODA TESTOWA. Wyświetla wszystkie informacje o stosie.
 */
void PCalcStack::__dev__printConsole()
{
	std::cout << "STOS/";
	__dev__printAllStackValues();
}


