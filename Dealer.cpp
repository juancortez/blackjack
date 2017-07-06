#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <cmath>
#include <cstdlib>
using namespace std;

#include "headers/Dealer.h"
#include "headers/Hand.h"
#include "headers/Card.h"
#include <ctime>

Dealer::Dealer() {
	this->init();
}

/*
	Initializes the deck with 52 cards
*/
void Dealer::init() {
	Deck *deck = new Deck();
	this->deck = deck;
}

/*
	Shuffles the deck using a random number generator
*/
void Dealer::shuffle() {
	this->deck->shuffle();
}

/*
	Prints out the entire deck. Used for testing purposes
*/
void Dealer::showCards() {
	this->deck->print();
}

/*
	Deals out one card from the top of the deck
*/
Card Dealer::deal() {
	Card card = this->deck->getCard();
	return card;
}

/*
	At the beginning of the game, the player is only allowed to see one
	of the dealer's card. The 2nd card is masked with 2 asterick marks.
*/
void Dealer::viewOneCard() {
	list<Card> hand = this->hand->getHand();
	Card card = hand.front();
	card.print();
	cout << " **" << endl;
}


/*
	The simulate function is a function mapped over the function 1/x^2 that will
	determine the probability of the dealer from dealing another card to himself
	based off of his current hand value.

	Rule: If a dealer has less than 17, they must continue drawing cards until they reach 17 or above
*/
void Dealer::simulate() {
	Card card;
	bool done = false;

	do {
		int dealerTotal = this->getHandTotal();
		int distanceFromTwentyOne = 21 - dealerTotal;

		if (dealerTotal >= 21) {
			done = true;
			break;
		}

		float probToHit;
		if (dealerTotal < 17) {
			probToHit = 100; // always hit if value is less than 10
		}
		else {
			probToHit = pow(distanceFromTwentyOne, 2);
		}

		int randomNumber = this->randomNumber();

		//cout << "Dealer has " << dealerTotal << " points with a probability of " << probToHit << "% to deal again.\n" << endl;

		if (probToHit >= randomNumber) {
			card = this->deal();
			this->receiveCard(card);
			cout << "Dealing card...dealer received: ";
			card.print();
			cout << "\n\n";
		}
		else {
			done = true;
		}
	} while (!done);

}

/*
	Returns a random number from 1-100. Used for the simulate algorithm above.
*/
int Dealer::randomNumber() {
	srand(time(NULL));
	return (rand() % 100) + 1;
}
