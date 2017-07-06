// Game.h
#ifndef player_h
#define player_h

#include "Card.h"
#include "Hand.h"

class Player {
public:
	Player();
	void receiveCard(Card);
	void viewHand();
	int getHandTotal();
	void clearHand();
	bool hasAceCard();
protected:
	Hand *hand;
};

#endif