#pragma once
#include <vector>
#include "Card.h"

using namespace std;


namespace games {

	class BlackJack
	{
	private:
		vector<Card> _deck;
		vector<Card> _playerCards;
		vector<Card> _computerCards;
		int _computerPts;
		int _playerPts;
		float _playerMoney;
		float _playerBet;
		bool _playerWon;
		bool _computerWon;
		Card _computerFirstCard;
		void fillDeck();
		void fillClubs();
		void fillHearts();
		void fillDiamonds();
		void fillSpades();
		void shuffle();
		void pullCards();		
		void computerTurn();
		void playerTurn();
		void printResult() const;
		void printTurn(string player, Card card) const;
		void printTurn(string player, Card card, int playerPts) const;
		void printTurn(string player) const;
		void sortCards(vector<Card> &cards);		
		void giveTwoCards();
		void printComputerFirstCard() const;
		void placeBet();
		void handleBet();
		void getResults();
		void resetRound();
		void prepareDeck();
		bool turnOver(int pts);
		bool hit() const;
		bool stopGame();
		Card pullCard(vector<Card> &toDeck);
		int calculatePts(vector<Card> cards);		
		float extractFloatValueFromInput(string message);
	public:
		BlackJack(float playerMoney);
		void start();
	};

}



