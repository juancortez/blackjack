// Hand.h
#include "Card.h"
#include <list>
#ifndef hand_h
#define hand_h

class Hand {
public:
	Hand();
	void add(Card);
	void viewHand();
	int getTotal();
	list<Card> getHand();
	void clearHand();
	bool aceExists();
private:
	list<Card> hand;
	bool aceInHand;
};

#endif