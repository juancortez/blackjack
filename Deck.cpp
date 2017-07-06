#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <ctime>

using namespace std;

#include "headers/Deck.h"
#include "headers/Card.h"

Deck::Deck() {
	// cout << "Initializing deck..." << endl;
	this->init();
	srand(time(NULL));
}

/*
	Initializes a complete deck of cards, including suites
*/
void Deck::init() {
	this->deck = new Card[52];
	this->counter = 1;
	int j = 0;
	for (Card::Suit curSuit = Card::Diamonds; curSuit <= Card::Spades; curSuit++) {
		for (int i = 1; i <= NUM_CARDS + 1; i++) {
			Card *card = new Card(i, curSuit);
			this->deck[j++] = *card;
		}
	}
}

/*
	Prints out the entire deck. Used mainly for testing purposes.
*/
void Deck::print() {
	for (int i = 0; i < DECK_SIZE; i++) {
		Card card = this->deck[i];
		card.print();
	}
}

/*
	Shuffles the complete deck using a random number generator
*/
void Deck::shuffle() {
	this->counter = 0;
	for (int i = 0; i < DECK_SIZE; i++) {
		this->swap(this->randomNumber(), this->randomNumber());
	}
}

/*
	Retrieves the top-most card of the deck
*/
Card Deck::getCard() {
	return this->deck[this->counter++];
}

int Deck::randomNumber() {
	return rand() % 52;
}

/*
	Given 2 index values of an array, it swaps the cards in the deck
*/
void Deck::swap(int x, int y) {
	Card tmp;
	tmp = this->deck[x];
	this->deck[x] = this->deck[y];
	this->deck[y] = tmp;
}