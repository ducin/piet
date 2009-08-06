//// includes

// header file
#include "pstack.h"

// piet core
#include "../debug.h"
#include "penums.h"

// C++
// none

// STL
#include <list>

// Qt
// none

PStack::PStack()
{
	debug("CONSTRUCTOR ----- stack START\n");
	clear();
	debug("CONSTRUCTOR ----- stack END\n");
}

PStack::~PStack()
{

}

void PStack::clear()
{
/*	while( !values.empty() ) {
		values.pop();
	}
*/	values.clear();
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

void PStack::instrSub()
{
	int el1 = values.front();
	values.pop_front();
	int el2 = values.front();
	values.pop_front();
	values.push_front(el2 - el1);
}

void PStack::instrMul()
{
	int el1 = values.front();
	values.pop_front();
	int el2 = values.front();
	values.pop_front();
	values.push_front(el2 * el1);
}

void PStack::instrDiv()
{
	int el1 = values.front();
	values.pop_front();
	int el2 = values.front();
	values.pop_front();
	values.push_front(el2 / el1);
}

void PStack::instrMod()
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

}

