/*
 * CSEN 79 Lab: Poker Statistics
 */
#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include "card.h"
#include "deck.h"
#include "poker.h"

using namespace std;

namespace lab2scajigal {
	const std::string Poker::RankNames[] = {
		"High Card",	// 0
		"Pair",			// 1
		"Two Pairs",	// 2
		"Triple",		// 3
		"Straight",		// 4
		"Flush",		// 5
		"Full House",	// 6
		"Four of a Kind",	// 7
		"Straight Flush"	// 8
		};
	
	Poker::Poker() { deck.shuffle(); }

	// deal 5 cards
	void Poker::dealHand() {
		for (auto i = 0; i < Poker::POKER_HANDCARDS; ++i)
			hand[i] = deck.deal();
		this->sortHand();
	}

	// sort them in nice order
	// fancy way to use "greater", a lambda construct
	void Poker::sortHand() {
		size_t n = sizeof(hand) / sizeof(hand[0]);
		std::sort(hand, hand+n, std::greater<int>());
	}

	// helper funtions for ranking
	// We implemeneted "isStraight" as an example.
	bool Poker::isStraight(uint r[]) {
		uint rankBits = 0;
		for (auto i = 0; i < Card::NRANKS; i++)
			if (r[i] != 0)
				rankBits |= 0x1 << (i+1);
		if (r[12] != 0)
				rankBits |= 0x1;
		while ((rankBits & 0x1) == 0)
			rankBits >>= 1;
		return rankBits == 0x1F;
	}

	// You are to implement these
	bool Poker::isFlush(uint s[]) {
		
	}
	bool Poker::isQuad(uint r[]) {
		uint rank
	}
	bool Poker::isTriple(uint r[]) {

	}
	bool Poker::isPair(uint r[]) {

	}
	bool Poker::is2Pair(uint r[]) {

	}

	bool Poker::countRank(uint r[], int n) {
		for (auto i = 0; i < Card::NRANKS; i++)
			if (r[i] == n)
				return true;
		return false;
	}


	Poker::Rank Poker::rankHand() {
		Poker::Rank rank;	// the return value

		uint rankCount[Card::NRANKS];
		uint suitCount[Card::Suit::CLUB+1];

		memset(rankCount, 0, sizeof(rankCount));
		memset(suitCount, 0, sizeof(suitCount));

		// first count the hand by rank and suit
		for (auto i = 0; i < this->POKER_HANDCARDS; ++i) {
			rankCount[hand[i].getRank()-1]++;
			suitCount[hand[i].getSuit()]++;
		}

		// Poker ranking is a series of if/else's
		if (isFlush(suitCount)) {
			// Flush can be a straight
			if (isStraight(rankCount))
				rank = POKER_STRAIGHT_FLUSH;
			else
				rank = POKER_FLUSH;
		} else if (isQuad(rankCount))	// 4 of a kind
				rank = POKER_QUAD;
		else if (isTriple(rankCount)) {	// 3 of a kind
			if (isPair(rankCount))	// also have a pair?  Then full house
				rank = POKER_FULLHOUSE;
			else
				rank = POKER_TRIPLE;
		} else if (isStraight(rankCount))	// simple straight
			rank = POKER_STRAIGHT;
		else if (is2Pair(rankCount))
			rank = POKER_2_PAIR;
		else if (isPair(rankCount))
			rank = POKER_PAIR;
		else
			rank = POKER_HIGHCARD;	// default
		return rank;
	}

	ostream& operator<<(ostream& os, const Poker &h) {
		for (auto i = 0; i < h.POKER_HANDCARDS; i++)
			cout << h.hand[i];
		return os;
	}
}

