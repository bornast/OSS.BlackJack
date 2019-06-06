#include "pch.h"
#include <iostream>
#include <string>
#include "BlackJack.h"
#include "Player.h"
#include <time.h> 

using namespace games;

int main()
{
	srand(time(NULL));
	
	Player player;
	cin >> player;	

	BlackJack blackJack(player);
	blackJack.start();
}

