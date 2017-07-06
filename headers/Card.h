// Card.h
#ifndef card_h
#define card_h
#define DECK_SIZE 52

class Card {
public:
	enum Suit {
		Diamonds,
		Hearts,
		Clubs,
		Spades
	};
	Card();

	Card(int cardInit, Suit suitInit);

	int getCardinal(bool);
	Suit getSuit();
	string print();
	void init();
private:
	Suit suit;
	int cardinalValue;
	string _convertCardinal(int cardinal);
	string _convertSuit(Suit suit);
};

inline Card::Suit operator++(Card::Suit &rs, int) {
	Card::Suit oldSuit = rs;
	rs = (Card::Suit)(rs + 1);
	return oldSuit;
}

#endif
