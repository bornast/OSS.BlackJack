#include "pch.h"
#include <string>
#include <algorithm>
#include <iostream>
#include "Player.h"

Player::Player()
{

}

Player::Player(string name, float startMoney)
{
	_name = name;
	money = startMoney;
}

void Player::placeBet()
{
	
	bet = extractFloatValueFromInput("place a bet between 100 and " + to_string((int)money));

	if (bet < 100 || bet > money)
		bet = 100;

	money -= bet;
}

float Player::extractFloatValueFromInput(string message) {
	float returnValue;

	cout << message << endl;
	cin >> returnValue;
	while (!cin.good())
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << message << endl;
		cin >> returnValue;
	}

	return returnValue;
}

string Player::getName()
{
	return _name;
}

bool Player::bankruptcy()
{
	return money <= 100;
}