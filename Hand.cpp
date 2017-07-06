#include <iostream>
#include <string>
#include <sstream>
#include <list>
using namespace std;

#include "headers/Card.h"
#include "headers/Hand.h"

/*
	Represents the hand that both the dealer and the player have at all times
*/
Hand::Hand() {
	this->aceInHand = false;
}

/*
	Adds a particular card to a player's hand
*/
void Hand::add(Card card) {
	int cardinalValue = card.getCardinal(true);
	if (cardinalValue == 1) this->aceInHand = true;
	this->hand.push_back(card);
}

/*
	Gets the total cardinal value of the hand
*/
int Hand::getTotal() {
	int total = 0;
	for (list<Card>::iterator it = this->hand.begin(); it != this->hand.end(); it++) {
		total += it->getCardinal(true);
	}
	return total;
}

/*
	Prints the player's hand to the console
*/
void Hand::viewHand() {
	for (list<Card>::iterator it = this->hand.begin(); it != this->hand.end(); it++) {
		it->print();
		cout << " ";
	}
}

/*
	Retrieves the entire hand of the user
*/
list<Card> Hand::getHand() {
	return this->hand;
}

/*
	Clears the hand of the user
*/
void Hand::clearHand() {
	this->hand.clear();
	this->aceInHand = false;
}

/*
	Determines whether or not the current hand contains an Ace. If it does, an ace
	can stand for both a 1 or 11
*/
bool Hand::aceExists() {
	return this->aceInHand;
}