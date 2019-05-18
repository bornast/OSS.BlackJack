#include "pch.h"
#include <iostream>
#include "BlackJack.h"
#include <time.h> 

using namespace games;

int main()
{
	srand(time(NULL));
	BlackJack blackJack(1000);
	blackJack.start();
}

