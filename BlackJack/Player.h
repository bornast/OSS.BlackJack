#pragma once
#include <string>
#include <iostream>
#include "Deck.h"

using namespace std;

class Player
{
private:
	string _name;
public:
	Player();
	Player(string name, float money);
	void placeBet();
	float extractFloatValueFromInput(string message);
	float money;
	float bet;
	int pts;
	Deck deck;
	Card firstCard;
	string getName();
	bool bankruptcy();
	friend istream & operator >> (istream & is, Player& player) {
		cout << "name: " << endl;
		is >> player._name;
		cout << "buy in:" << endl;
		is >> player.money;
		return is;
	}
};

