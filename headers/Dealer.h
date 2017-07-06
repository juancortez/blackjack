// Dealer.h
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#ifndef dealer_h
#define dealer_h

class Dealer : public Player {
public:
	Dealer();
	void init();
	void shuffle();
	void showCards();
	Card deal();
	void viewOneCard();
	void simulate();
private:
	Deck *deck;
	int randomNumber();
};

#endif