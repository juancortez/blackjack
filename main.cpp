#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#include "headers/Game.h"


int main() {
	Game *game = new Game();

	while (game->continuePlaying()) {
		game->startNewRound();
	}

	cout << "Game ended" << endl;

	return 1;
}