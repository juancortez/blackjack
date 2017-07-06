#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

#include "headers/Game.h"
#include "headers/Card.h"
#include "headers/Hand.h"
#include "headers/Player.h"

Game::Game() {
	this->dealer = new Dealer();
	this->player = new Player();
	this->printWelcome();
	this->contPlaying = true;
}

/*
	Reusable function that starts each round, including the shuffling,
	initial dealing of hands, and prompting on whether or not the player
	wants to deal or stay with their hand.
*/
void Game::startNewRound() {
	cout << "Shuffling...\n";
	this->dealer->shuffle();
	this->dealHands();
	this->beginGame();
}

/*
	Deals cards to both the player and dealer
*/
void Game::dealHands() {
	cout << "Dealing cards...\n\n";

	Card card;
	for (int count = 0; count < 2; count++) {
		card = this->dealer->deal();
		this->player->receiveCard(card);

		card = this->dealer->deal();
		this->dealer->receiveCard(card);
	}
	showHands(false);
}

/*
	Begins the game of blackjack
*/
void Game::beginGame() {
	this->dealOrNoDeal();
	this->simulateDealer();
}

/*
	This function drives the interaction between the player and the dealer. Relies on
	appropriate input feedback from the user.
*/
void Game::dealOrNoDeal() {
	bool playerHasAce = this->player->hasAceCard();
	string answer = this->promptUser("Cards dealt are shown above. Deal or Stand? (d/s) ");
	while (answer.compare("s") != 0 && this->continuePlaying()) {
		system("CLS");
		Card card = this->dealer->deal();
		this->player->receiveCard(card);
		cout << "Dealing card...received: ";
		card.print();
		cout << "\n\n";
		showHands(false);
		bool overDealPlayer = determineLoss("p");
		if (overDealPlayer) {
			this->busted(true);
			this->playAgainQuestion();
			continue;
		}
		answer = this->promptUser("Cards dealt are shown above. Deal or Stand? (d/s) ");
	}
	if (answer.compare("s") == 0) {
		bool overDealDealer = simulateDealer();
		if (overDealDealer) {
			this->showHands(true);
			this->busted(false);
		}
		else {
			this->determineWinner();
		}
		this->playAgainQuestion();
	}
}

void Game::playAgainQuestion() {
	string result = this->promptUser("Would you like to play again? (y/n)");
	if (result.compare("y") == 0) this->restartGame();
	else this->stopPlaying();
}

/*
	Goes through a path if either the player or the dealer busted

	@param{bool} player		If true, it is player, else it is the dealer
*/
void Game::busted(bool player) {
	if (player) {
		int playerTotal = this->player->getHandTotal();
		cout << "You busted! Your hand hit " << playerTotal << " points.\n\n";
	}
	else {
		cout << "The dealer busted! You win!\n\n";
	}
}

/*
	Simulates the dealer playing the game
*/
bool Game::simulateDealer() {
	system("CLS");
	this->dealer->simulate();
	return determineLoss("d");
}


/*
	Determines who won between the dealer and the player. Result will be outputted
	to the screen.
*/
void Game::determineWinner() {
	system("CLS");
	cout << "Determining winner...\n";
	this->showHands(true);

	int playerTotal = this->player->getHandTotal();
	int dealerTotal = this->dealer->getHandTotal();

	if (playerTotal == 21 && dealerTotal != 21) {
		cout << "You hit blackjack! Congratulations, you win!" << endl;
	}
	else if (playerTotal != 21 && dealerTotal == 21) {
		cout << "Bummer, the dealer hit blackjack. You lose." << endl;
	}
	else if (playerTotal == 21 && dealerTotal != 21) {
		cout << "Wow, you and the dealer both hit blackjack. Tie game!" << endl;
	}
	else if (playerTotal == dealerTotal) {
		cout << "Tie game!" << endl;
	}
	else if (playerTotal > dealerTotal) {
		cout << "Congratulations, you win!" << endl;
	}
	else {
		cout << "Sorry, you lose." << endl;
	}
	cout << endl;
}

/*
	Determines whether or not each player "busted". 
	(i.e. if they hit over 21 points)
*/
bool Game::determineLoss(string playerType) {
	if (playerType.compare("p") == 0) {
		int playerTotal = this->player->getHandTotal();
		if (playerTotal > 21) {
			return true;
		}
		return false;
	}
	else if (playerType.compare("d") == 0) {
		int dealerTotal = this->dealer->getHandTotal();
		if (dealerTotal > 21) {
			return true;
		}
		return false;
	}
	return false;
}

/*
	Function is called upon starting of the new round. It shows the player
	their own cards, as well as one of the two cards the dealer has.
*/
void Game::showHands(bool final) {
	cout << "Player's hand: " << endl;
	this->player->viewHand();
	int playerTotal = this->player->getHandTotal();
	cout << " -> " << playerTotal << endl;
	cout << "\n";
	cout << "Dealer's hand: " << endl;

	if (final == true) {
		this->dealer->viewHand();
		int dealerTotal = this->dealer->getHandTotal();
		cout << " -> " << dealerTotal << endl;
	}
	else {
		this->dealer->viewOneCard();
	}
	cout << endl;
}

/*
	Boolean flag that will kill the current game of blackjack
*/
void Game::stopPlaying() {
	this->contPlaying = false;
}

bool Game::continuePlaying() {
	return this->contPlaying;
}

/*
	Helper function that prompts the user with a message, as well as a parser
	for the user input.
*/
string Game::promptUser(string msg) {
	string result;
	bool validInput = false;
	do {
		cout << msg << endl;
		getline(cin, result);
		transform(result.begin(), result.end(), result.begin(), ::tolower);
		if (result.compare("q") == 0 || result.compare("quit") == 0) {
			cout << "Exiting game" << endl;
			this->stopPlaying();
			validInput = true;
		}
		else if (result.compare("d") == 0 || result.compare("s") == 0) {
			validInput = true;
		}
		else if (result.compare("y") == 0) {
			validInput = true;
		}
		else if (result.compare("n") == 0) {
			validInput = true;
			this->stopPlaying();
		}
		else {
			cout << "Invalid input, please enter a valid selection." << endl;
		}
	} while (!validInput);

	return result;
}

/*
	Clears the current state of the players and starts a new round
*/
void Game::restartGame() {
	system("CLS");
	this->player->clearHand();
	this->dealer->clearHand();
	this->startNewRound();
}

/*
Prints the welcoming screen, as well as details about the game of Blackjack.
*/
void Game::printWelcome() {
	cout << "\n*********************************************************************\n" << endl;
	cout << "\t\t\tBLACKJACK" << endl;
	cout << "Description of how to play: http://www.blackjack.org/blackjack-rules/\n" << endl;
	cout << "Map of Cards:\n";
	cout << "\t**Suites**\tD=Diamond, H=Hearts, S=Spades, C=Clubs\n";
	cout << "\t**Face Cards**  J=Jack, Q=Queen, K=King, A=Ace\n";
	cout << "\nIf at any time you would like to exit, you can type q, or quit." << endl;
	cout << "\n\n*********************************************************************" << endl;
}
