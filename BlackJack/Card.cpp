#include "pch.h"
#include "Card.h"
#include <string>

using namespace std;
using namespace games;

Card::Card() {}

Card::Card(string name, string type, int value)
{
	_name = name;
	_type = type;
	_value = value;
}

string Card::getName() const
{
	return _name;
}

string Card::getType() const
{
	return _type;
}

int Card::getValue() const
{
	return _value;
}

