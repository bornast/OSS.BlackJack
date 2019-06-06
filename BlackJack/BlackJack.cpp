#include "pch.h"
#include "BlackJack.h"
#include "Card.h"
#include "Deck.h"
#include <vector>
#include <iostream>
#include <algorithm>


using namespace std;
using namespace games;


BlackJack::BlackJack(Player player)
{
	_player = &player;
	Player _computer("house", 10000000);
}

void BlackJack::start()
{
	while (!stopGame())
	{
		_deck.prepareDeck();
		_player->placeBet();
		pullCards();
		getResults();
		handleBet();
		printResult();
		if (_player->bankruptcy()) break;
		resetRound();
	}

	cout << "game done, player money: " << _player->money << endl;
		
}

bool BlackJack::stopGame()
{
	string res;
	cout << "play [y]/[n]" << endl;
	cin >> res;
	return res == "n";

}

void BlackJack::pullCards()
{
	giveTwoCards();
	playerTurn();
	computerTurn();
}

void BlackJack::giveTwoCards()
{
		
	printTurn("player", _deck.getCard(_player->deck));
	Card card = _deck.getCard(_player->deck);
	_player->pts = _player->deck.calculatePts();

	printTurn("player", card, _player->pts);
		
	_computer.firstCard = _deck.getCard(_computer.deck);
	printTurn("house");
	printTurn("house", _deck.getCard(_computer.deck));

}

void BlackJack::printTurn(string player, Card card) const
{		
	cout << player << " takes " << card.getName() << " of " << card.getType() << endl << endl;
}

void BlackJack::printTurn(string player, Card card, int playerPts) const
{
	cout << player << " takes " << card.getName() << " of " << card.getType() << endl << endl;
	cout << player << " has " << playerPts << " points" << endl << endl;
}

void BlackJack::printTurn(string player) const
{
	cout << player << " took a card" << endl << endl;
}

void BlackJack::playerTurn()
{	
	_player->pts = _player->deck.calculatePts();
	
	while (!turnOver(_player->pts))
	{
		if (hit())
		{
			Card card = _deck.getCard(_player->deck);
			_player->pts = _player->deck.calculatePts();
			printTurn("player", card, _player->pts);

		}
		else break;
	}
}

bool BlackJack::turnOver(int pts)
{
	return pts >= 21;
}

bool BlackJack::hit() const
{
	string playAgain;

	cout << "HIT? [y]/[n]" << endl;
	cin >> playAgain;

	return playAgain == "y";
}

void BlackJack::computerTurn()
{
	_computer.pts = _computer.deck.calculatePts();
	printComputerFirstCard();

	while (_computer.pts < 17 && _player->pts <= 21)
	{		
		Card card = _deck.getCard(_computer.deck);
		_computer.pts = _computer.deck.calculatePts();
		printTurn("house", card, _computer.pts);

	}
}

void BlackJack::printComputerFirstCard() const
{
	cout << "computer first card was " << _computer.firstCard.getName() << " of " << _computer.firstCard.getType() << endl << endl;
	cout << "computer has " << _computer.pts << " points" << endl << endl;
}

void BlackJack::getResults()
{

	if (_player->pts > _computer.pts && _player->pts <= 21)
		_playerWon = true;
	else if (_computer.pts > _player->pts && _computer.pts <= 21)
		_computerWon = true;
	else if (_player->pts > _computer.pts)
		_computerWon = true;
	else if (_computer.pts > _player->pts)
		_playerWon = true;
}

void BlackJack::handleBet()
{
	if (_playerWon)
		_player->money += _player->bet * 2;
	
	else if (!_playerWon && !_computerWon)
		_player->money += _player->bet;
}

void BlackJack::printResult() const
{
	cout << endl << endl;
	cout << "----------------- RESULTS -----------------" << endl;
	if (!_computerWon && !_playerWon)
		cout << "TIE";
	else if (_playerWon)
		cout << "player won";
	else if (_computerWon)
		cout << "house won";
	cout << endl;
	cout << "player money: " << _player->money << endl;
	cout << endl << endl;
}

void BlackJack::resetRound()
{	
	_deck.clear();	
	_player->deck.clear();
	_computer.deck.clear();
	_playerWon = false;
	_computerWon = false;
}
