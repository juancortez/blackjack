#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "headers/Card.h"

Card::Card() {}

Card::Card(int cardInit, Suit suitInit) {
	this->suit = suitInit;
	this->cardinalValue = cardInit;
}

/*
	Gets the cardinal number of the card.
	Jack, Queen, and King are assigned the value of 10
	Ace is assigned the value 1 and 11
*/
int Card::getCardinal(bool getValue) {
	if (getValue && this->cardinalValue > 10) return 10;
	return this->cardinalValue;
}

/*
	Returns the suit of the card.

	Suites are Diamond, Hearts, Clubs, or Spades, all in one alphabetical value.
*/
Card::Suit Card::getSuit() {
	return this->suit;
}

/*
	Prints out the value of the card as follows:
	-> 4D
	
	The first number corresponds to the cardinal value, and the second value corresponds
	to the suit.
*/
string Card::print() {
	string result = "";

	int cardinal = this->getCardinal(false);
	Card::Suit suit = this->getSuit();

	result = this->_convertCardinal(cardinal);
	//result += " of ";
	result += this->_convertSuit(suit);

	cout << result;

	return result;
}

/*
	Helper function that converts face cards into their appropriate cardinal values
*/
string Card::_convertCardinal(int cardinal) {
	string result = "";
	if (cardinal > 10) {
		switch (cardinal) {
		case 11: result += "J";
			break;
		case 12: result += "Q";
			break;
		case 13: result += "K";
			break;
		default: break;
		}
	}
	else if (cardinal == 1) {
		result += "A";
	}
	else {
		ostringstream convert;
		convert << cardinal;
		result += convert.str();
	}
	return result;
}

/*
	Given a Suit, it will convert it from a Suit to a string representation
*/
string Card::_convertSuit(Suit suit) {
	static string Suits[4] = {
	  "D", "H", "C", "S"
	};

	return Suits[suit];
}