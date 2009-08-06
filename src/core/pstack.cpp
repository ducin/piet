//// includes

// header file
#include "pstack.h"

// piet core
#include "../debug.h"
#include "penums.h"

// C++
#include <iostream>

// STL
#include <list>

// Qt
// none

PStack::PStack()
{
	debug("CONSTRUCTOR ----- stack START\n");
	debug("CONSTRUCTOR ----- stack END\n");
}

PStack::~PStack()
{
	debug("DESTRUCTOR ----- stack START\n");
	debug("DESTRUCTOR ----- stack END\n");
}

void PStack::clear()
{
	values.clear();
}

void PStack::prepareToExecute()
{
	clear();
}

//==========================================================================
	// operacje podstawowe:

void PStack::instrPush(int item)
{
	values.push_front(item);
}

void PStack::instrPop()
{
	values.pop_front();
}

//==========================================================================
	// operacje arytmetyczne:

void PStack::instrAdd()
{
	int el1 = values.front();
	values.pop_front();
	int el2 = values.front();
	values.pop_front();
	values.push_front(el2 + el1);
}

void PStack::instrSubtract()
{
	int el1 = values.front();
	values.pop_front();
	int el2 = values.front();
	values.pop_front();
	values.push_front(el2 - el1);
}

void PStack::instrMultiply()
{
	int el1 = values.front();
	values.pop_front();
	int el2 = values.front();
	values.pop_front();
	values.push_front(el2 * el1);
}

void PStack::instrDivide()
{
	int el1 = values.front();
	values.pop_front();
	int el2 = values.front();
	values.pop_front();
	values.push_front(el2 / el1);
}

void PStack::instrModulo()
{
	int el1 = values.front();
	values.pop_front();
	int el2 = values.front();
	values.pop_front();
	values.push_front(el2 % el1);
}

//==========================================================================
	// operacje logiczne:

void PStack::instrNot()
{
	int el = values.front();
	values.pop_front();
	values.push_front(el != 0 ? 0 : 1);
}

void PStack::instrGreater()
{
	int el1 = values.front();
	values.pop_front();
	int el2 = values.front();
	values.pop_front();
	values.push_front(el2 > el1 ? 1 : 0);
}

//==========================================================================
	// operacje na głowicy maszyny:

int PStack::instrPointer()
{

}

int PStack::instrSwitch()
{

}

//==========================================================================
	// operacje na stosie:

void PStack::instrDuplicate()
{

}

void PStack::instrRoll()
{

}

//==========================================================================
	// operacje I/O:

void PStack::instrInNumber()
{

}

void PStack::instrInChar()
{

}

void PStack::instrOutNumber()
{

}

void PStack::instrOutChar()
{

}

//==========================================================================
	// development:

void PStack::__dev__printAllStackValues()
{
	std::cout << "size: " << values.size() << " values: ";
	std::list<int>::iterator it;
	for (it = values.begin(); it != values.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void PStack::__dev__printConsole()
{
	std::cout << "stack" << std::endl;
	__dev__printAllStackValues();
	std::cout << std::endl;
}


