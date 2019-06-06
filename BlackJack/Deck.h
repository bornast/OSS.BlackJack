#pragma once
#include <vector>
#include "Card.h"

using namespace std;
using namespace games;

class Deck
{
private:
	vector<Card> _deck;
	void fillDeck();
	void shuffle();
public:
	Deck();	
	void clear();
	void add(Card card);
	Card getCard(Deck& toDeck);
	void sortDeck();
	int calculatePts();	
	void prepareDeck();
};

