#pragma once
#include <string>

using namespace std;

namespace games {

	class Card
	{
	private:
		string _type;		
		string _name;
		int _value;
	public:
		Card();
		Card(string name, string type, int value);
		string getName() const;
		string getType() const;
		int getValue() const;		
	};
}