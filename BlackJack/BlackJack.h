#pragma once
#include <vector>
#include "Card.h"
#include "Player.h"
#include "Deck.h"


using namespace std; // triba li u h file-u?


namespace games {

	class BlackJack
	{
	private:
		Deck _deck;
		bool _playerWon;
		bool _computerWon;
		void pullCards();
		void computerTurn();
		void playerTurn();
		void printResult() const;
		void printTurn(string player, Card card) const;
		void printTurn(string player, Card card, int playerPts) const;
		void printTurn(string player) const;
		void giveTwoCards();
		void printComputerFirstCard() const;
		void handleBet();
		void getResults();
		void resetRound();
		bool turnOver(int pts);
		bool hit() const;
		bool stopGame();
		Player *_player;
		Player _computer;
	public:
		BlackJack(Player player);
		void start();
	};

}



