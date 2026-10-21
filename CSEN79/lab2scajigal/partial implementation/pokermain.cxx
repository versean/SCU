/*
 * CSEN 79 Lab: Poker Statistics
 */
#include <ctime>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <cmath>
#include "card.h"
#include "deck.h"
#include "poker.h"
#include <cassert>

using namespace std;
using namespace lab2scajigal;

// Generate one sample hand for each rank
void pokerHands(Poker &poker) {
	/*
	 * Loop until you have found one of each rank.
	 * Print that "sample hand"
	 */
	int rankFound[Poker::POKER_ARRAY_SIZE] = {0,0,0,0,0,0,0,0,0};
	while (rankFound[0] == false || rankFound[1] == false || rankFound[2] == false || rankFound[3] == false || rankFound[4] == false || rankFound[5] == false || rankFound[6] == false || rankFound[7] == false || rankFound[8] == false) {
		poker.dealHand();
		Poker::Rank r = poker.rankHand();
		if (rankFound[r] == false) {
			rankFound[r] = true;
			cout << setw(15) << poker << " " << Poker::RankNames[r] << endl;
		}
	}
}

// Collect statistics for each rank of Poker
void pokerStats(Poker &poker, int n) {
	time_t tmark = clock();			// ready, get set, go!
	/*
	 * Do your thing here.
	 * This is supposed to be big loop that deal many many poker hands and collect the
	 * statistics for each rank.
	 * Once you believe the statistics are good.  Exit the loop.
	 * "tmark" then computes the number of "clock ticks" in your loop.
	 * You should convert that to human friendly units, such as "seconds"
	 * 
	 * Output your stats then, with the amount of time it took you collect the stats.
	 */

	int nDeals = n; // lab pdf used 8795000
	int nRank[Poker::POKER_ARRAY_SIZE] = {0,0,0,0,0,0,0,0,0};
	for (int i = 0; i < nDeals; i++) {
		poker.dealHand();
		nRank[poker.rankHand()]++;
	}

	tmark = clock() - tmark;	// stop the clock
	double secs = (double)tmark/CLOCKS_PER_SEC;

	cout << "Dealt " << nDeals << " hands. Elapsed Time: " << secs << " seconds." << endl;
	cout << "Average " << (secs/nDeals)*50000 << " seconds per 50k hands" << endl;

	for (int i = Poker::POKER_ARRAY_SIZE - 1; i >= 0; i--) {
		cout << setw(15) << Poker::RankNames[i] << ": " << setw(9) << nRank[i] << setw(7) << fixed << setprecision(2) << nRank[i] / (double)nDeals * 100 << "%" << endl;
	}
}

int main(int argc, char* argv[]) {
	assert(argc==2); // using args for nDeals in pokerStats.

	Poker poker;
	cout << "Sample hand for each Rank:" << endl;
	pokerHands(poker);
	cout << endl << "Statistics:" << endl;
	pokerStats(poker,stoi(argv[1]));

	return EXIT_SUCCESS;
}
