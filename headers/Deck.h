// Dealer.h
#include "Card.h"
#ifndef deck_h
#define deck_h
#define DECK_SIZE 52
#define NUM_CARDS 12

class Deck {
public:
	int counter;
	Deck();
	void shuffle();
	void print();
	Card getCard();
private:
	Card *deck;
	void init();
	int randomNumber();
	void swap(int, int);
};

#endif
