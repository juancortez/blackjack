#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "headers/Player.h"
#include "headers/Hand.h"

/*
	Player is the parent of a Dealer, since a Dealer is also a player
*/
Player::Player() {
	this->hand = new Hand();
}

/*
	Puts the provided input card into the player's hand
*/
void Player::receiveCard(Card card) {
	this->hand->add(card);
}

/*
	Prints out the players hand to the console
*/
void Player::viewHand() {
	this->hand->viewHand();
}

/*
	Returns the cardinal value of the players hand
*/
int Player::getHandTotal() {
	return this->hand->getTotal();
}

/*
	Clears the players hand of any cards
*/
void Player::clearHand() {
	this->hand->clearHand();
}

/*
	Returns a flag indicating whether or not the player has an ace in their hand
*/
bool Player::hasAceCard() {
	return this->hand->aceExists();
}
