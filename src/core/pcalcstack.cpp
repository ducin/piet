//// includes

// header file
#include "pcalcstack.h"

// piet core
#include "../debug.h"
#include "penums.h"
#include "pstructs.h"

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

PCalcStack::PCalcStack()
{
	debug("CONSTRUCTOR ----- calc stack START\n");
	verbose = false;
	debug("CONSTRUCTOR ----- calc stack END\n");
}

PCalcStack::~PCalcStack()
{
	debug("DESTRUCTOR ----- calc stack START\n");
	debug("DESTRUCTOR ----- calc stack END\n");
}

void PCalcStack::setVerbosity(bool verbosity)
{
	verbose = verbosity;
}

void PCalcStack::clear()
{
	values.clear();
}

void PCalcStack::prepareToExecute()
{
	clear();
}

int PCalcStack::size()
{
	return values.size();
}

bool PCalcStack::hasAtLeastNElements(unsigned int elements)
{
	return (values.size() >= elements);
}

//==========================================================================
	// operacje podstawowe:

void PCalcStack::instrPush(int item)
{
	values.push_front(item);
}

int PCalcStack::instrPop()
{
	int el = values.front();
	values.pop_front();
	return el;
}

//==========================================================================
	// operacje arytmetyczne:

void PCalcStack::instrAdd()
{
	int el1 = values.front();
	values.pop_front();
	int el2 = values.front();
	values.pop_front();
	values.push_front(el2 + el1);
}

void PCalcStack::instrSubtract()
{
	int el1 = values.front();
	values.pop_front();
	int el2 = values.front();
	values.pop_front();
	values.push_front(el2 - el1);
}

void PCalcStack::instrMultiply()
{
	int el1 = values.front();
	values.pop_front();
	int el2 = values.front();
	values.pop_front();
	values.push_front(el2 * el1);
}

void PCalcStack::instrDivide()
{
	int el1 = values.front();
	values.pop_front();
	int el2 = values.front();
	values.pop_front();
	values.push_front(el2 / el1);
}

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

void PCalcStack::instrNot()
{
	int el = values.front();
	values.pop_front();
	values.push_front(el != 0 ? 0 : 1);
}

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

void PCalcStack::instrDuplicate()
{
	int el = values.front();
	values.push_front(el);
}

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

void PCalcStack::__dev__printAllStackValues()
{
	std::cout << "rozm:" << values.size() << " elem: ";
	std::list<int>::iterator it;
	for (it = values.begin(); it != values.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void PCalcStack::__dev__printConsole()
{
	std::cout << "STOS/";
	__dev__printAllStackValues();
}


