#include "pch.h"
#include "Deck.h"
#include <string>
#include <map>

Deck::Deck()
{
}

void Deck::fillDeck()
{

	string cardNames[13] = { "ace", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "jack", "queen", "king"};
	
	int j = 0;
	int cardValue = 1;

	for (int i = 1; i < 53; i++) {
		
		if (j > 12) {
			j = 0;
			cardValue = 1;
		}
		if (j > 9) cardValue = 10;

		string cardType = "diamonds";
		if (i > 13 && i < 27) cardType = "hearts";
		else if (i >= 27 && i < 40) cardType = "spades";
		else if (i >= 40 && i < 54) cardType = "clubs";
		
		_deck.push_back(Card(cardNames[j], cardType, cardValue));
		j++;
		cardValue++;
	}
	

}

void Deck::clear() 
{
	_deck.clear();
}

void Deck::add(Card card)
{
	_deck.push_back(card);
}

Card Deck::getCard(Deck& toDeck)
{
	Card card = _deck.back();
	_deck.pop_back();

	toDeck.add(card);
	toDeck.sortDeck();

	return card;
}

void Deck::sortDeck()
{
	for (int i = 0; i < _deck.size() - 1; i++)
	{
		for (int j = i + 1; j < _deck.size(); j++)
		{
			if (_deck[i].getValue() < _deck[j].getValue())
			{
				Card temp = _deck[i];
				_deck[i] = _deck[j];
				_deck[j] = temp;
			}
		}
	}
}

int Deck::calculatePts()
{
	vector<Card>::iterator it;
	int pts = 0;

	for (int i = 0; i < _deck.size(); i++) 
	{		
		int ptsToAdd = _deck[i].getName() == "ace" && pts + 11 <= 21 ? 11 : _deck[i].getValue();
		pts += ptsToAdd;
	}

	return pts;
}

void Deck::shuffle()
{
	for (int i = _deck.size() - 1; i > 0; --i) {
		int j = rand() % (i + 1);
		Card temp = _deck[i];
		_deck[i] = _deck[j];
		_deck[j] = temp;
	}
}

void Deck::prepareDeck()
{
	fillDeck();
	shuffle();
}