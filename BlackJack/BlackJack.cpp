#include "pch.h"
#include "BlackJack.h"
#include "Card.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace games;

BlackJack::BlackJack(float playerMoney)
{
	_playerMoney = playerMoney;
}

void BlackJack::start()
{
	while (!stopGame())
	{
		prepareDeck();
		placeBet();
		pullCards();
		getResults();
		handleBet();
		printResult();
		if (_playerMoney < 100) break;
		resetRound();
	}

	cout << "game done, player money is " << _playerMoney << endl;
		
}

bool BlackJack::stopGame()
{
	string res;
	cout << "play [y]/[n]" << endl;
	cin >> res;
	return res == "n";

}

void BlackJack::prepareDeck()
{
	fillDeck();
	shuffle();
}

void BlackJack::fillDeck()
{
	fillDiamonds();
	fillHearts();
	fillSpades();
	fillClubs();
}

void BlackJack::fillDiamonds()
{
	_deck.push_back(Card("ace", "diamonds", 1));
	_deck.push_back(Card("two", "diamonds", 2));
	_deck.push_back(Card("three", "diamonds", 3));
	_deck.push_back(Card("four", "diamonds", 4));
	_deck.push_back(Card("five", "diamonds", 5));
	_deck.push_back(Card("six", "diamonds", 6));
	_deck.push_back(Card("seven", "diamonds", 7));
	_deck.push_back(Card("eight", "diamonds", 8));
	_deck.push_back(Card("nine", "diamonds", 9));
	_deck.push_back(Card("jack", "diamonds", 10));
	_deck.push_back(Card("queen", "diamonds", 10));
	_deck.push_back(Card("king", "diamonds", 10));
}

void BlackJack::fillHearts()
{
	_deck.push_back(Card("ace", "hearts", 1));
	_deck.push_back(Card("two", "hearts", 2));
	_deck.push_back(Card("three", "hearts", 3));
	_deck.push_back(Card("four", "hearts", 4));
	_deck.push_back(Card("five", "hearts", 5));
	_deck.push_back(Card("six", "hearts", 6));
	_deck.push_back(Card("seven", "hearts", 7));
	_deck.push_back(Card("eight", "hearts", 8));
	_deck.push_back(Card("nine", "hearts", 9));
	_deck.push_back(Card("jack", "hearts", 10));
	_deck.push_back(Card("queen", "hearts", 10));
	_deck.push_back(Card("king", "hearts", 10));
}

void BlackJack::fillSpades()
{
	_deck.push_back(Card("ace", "spades", 1));
	_deck.push_back(Card("two", "spades", 2));
	_deck.push_back(Card("three", "spades", 3));
	_deck.push_back(Card("four", "spades", 4));
	_deck.push_back(Card("five", "spades", 5));
	_deck.push_back(Card("six", "spades", 6));
	_deck.push_back(Card("seven", "spades", 7));
	_deck.push_back(Card("eight", "spades", 8));
	_deck.push_back(Card("nine", "spades", 9));
	_deck.push_back(Card("jack", "spades", 10));
	_deck.push_back(Card("queen", "spades", 10));
	_deck.push_back(Card("king", "spades", 10));
}

void BlackJack::fillClubs()
{
	_deck.push_back(Card("ace", "clubs", 1));
	_deck.push_back(Card("two", "clubs", 2));
	_deck.push_back(Card("three", "clubs", 3));
	_deck.push_back(Card("four", "clubs", 4));
	_deck.push_back(Card("five", "clubs", 5));
	_deck.push_back(Card("six", "clubs", 6));
	_deck.push_back(Card("seven", "clubs", 7));
	_deck.push_back(Card("eight", "clubs", 8));
	_deck.push_back(Card("nine", "clubs", 9));
	_deck.push_back(Card("jack", "clubs", 10));
	_deck.push_back(Card("queen", "clubs", 10));
	_deck.push_back(Card("king", "clubs", 10));
}

void BlackJack::shuffle()
{
	for (int i = _deck.size() - 1; i > 0; --i) {
		int j = rand() % (i + 1);
		Card temp = _deck[i];
		_deck[i] = _deck[j];
		_deck[j] = temp;
	}

}

void BlackJack::placeBet()
{
	_playerBet = extractFloatValueFromInput("place a bet between 100 and " + to_string(_playerMoney));

	if (_playerBet < 100 || _playerBet > _playerMoney)
		_playerBet = 100;

	_playerMoney -= _playerBet;
}

float BlackJack::extractFloatValueFromInput(string message) {

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

void BlackJack::pullCards()
{
	giveTwoCards();
	playerTurn();
	computerTurn();
}

void BlackJack::giveTwoCards()
{
	printTurn("player", pullCard(_playerCards));
	Card card = pullCard(_playerCards);
	_playerPts = calculatePts(_playerCards);
	printTurn("player", card, _playerPts);

	_computerFirstCard = pullCard(_computerCards);
	printTurn("computer");
	printTurn("computer", pullCard(_computerCards));

}

void BlackJack::printTurn(string player, Card card) const
{
	cout << player << " takes " << card.getName() << " of " << card.getType() << endl << endl;
}

Card BlackJack::pullCard(vector<Card> &toDeck)
{
	Card card = _deck.back();
	_deck.pop_back();

	toDeck.push_back(card);
	sortCards(toDeck);

	return card;
}

void BlackJack::sortCards(vector<Card> &cards)
{
	for (int i = 0; i < cards.size() - 1; i++)
	{
		for (int j = i + 1; j < cards.size(); j++)
		{
			if (cards[i].getValue() < cards[j].getValue())
			{
				Card temp = cards[i];
				cards[i] = cards[j];
				cards[j] = temp;
			}
		}
	}
}

void BlackJack::printTurn(string player, Card card, int playerPts) const
{
	cout << player << " takes " << card.getName() << " of " << card.getType() << endl;
	cout << player << " has " << playerPts << " points" << endl << endl;
}

void BlackJack::printTurn(string player) const
{
	cout << player << " took a card" << endl << endl;
}

void BlackJack::playerTurn()
{
	_playerPts = calculatePts(_playerCards);
	while (!turnOver(_playerPts))
	{
		if (hit())
		{
			Card card = pullCard(_playerCards);
			_playerPts = calculatePts(_playerCards);
			printTurn("player", card, _playerPts);

		}
		else break;
	}
}

int BlackJack::calculatePts(vector<Card> çards)
{
	vector<Card>::iterator it;
	int pts = 0;
	for (it = çards.begin(); it < çards.end(); ++it)
	{
		int ptsToAdd = (*it).getName() == "ace" && pts + 11 <= 21 ? 11 : (*it).getValue();
		pts += ptsToAdd;
	}
	return pts;
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
	printComputerFirstCard();
	_computerPts = calculatePts(_computerCards);

	while (_computerPts < 17 && _playerPts <= 21)
	{
		Card card = pullCard(_computerCards);
		_computerPts = calculatePts(_computerCards);
		printTurn("computer", card, _computerPts);

	}
}

void BlackJack::printComputerFirstCard() const
{
	cout << "computer first card was " << _computerFirstCard.getName() << " of " << _computerFirstCard.getType() << endl << endl;
}

void BlackJack::getResults()
{

	if (_playerPts > _computerPts && _playerPts <= 21)
		_playerWon = true;
	else if (_computerPts > _playerPts && _computerPts <= 21)
		_computerWon = true;
	else if (_playerPts > _computerPts)
		_computerWon = true;
	else if (_computerPts > _playerPts)
		_playerWon = true;
}

void BlackJack::handleBet()
{
	if (_playerWon)
		_playerMoney += _playerBet * 2;
	else if (!_playerWon && !_computerWon)
		_playerMoney += _playerBet;
}

void BlackJack::printResult() const
{
	cout << endl << endl;
	cout << "----------------- RESULTS -----------------" << endl;
	if (!_computerWon && !_playerWon)
		cout << "TIE";
	else if (_playerWon)
		cout << "player wins";
	else if (_computerWon)
		cout << "computer wins";
	cout << endl;
	cout << " player money: " << _playerMoney << endl;
	cout << endl << endl;
}

void BlackJack::resetRound()
{
	_deck.clear();
	_playerCards.clear();
	_computerCards.clear();
	_playerWon = false;
	_computerWon = false;
}

