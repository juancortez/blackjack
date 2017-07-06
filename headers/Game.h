// Game.h
#include "Dealer.h"
#include "Player.h"
#ifndef game_h
#define game_h

class Game {
public:
	Game();
	void startNewRound();
	bool continuePlaying();
private:
	Dealer *dealer;
	Player *player;
	void printWelcome();
	bool contPlaying;
	string promptUser(string);
	void stopPlaying();
	void dealHands();
	void beginGame();
	void dealOrNoDeal();
	void showHands(bool);
	bool simulateDealer();
	bool determineLoss(string);
	void determineWinner();
	void restartGame();
	void busted(bool);
	void playAgainQuestion();
};

#endif