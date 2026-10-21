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

using namespace std;
using namespace lab2scajigal;

// Generate one sample hand for each rank
void pokerHands(Poker &poker) {
	/*
	 * Loop until you have found one of each rank.
	 * Print that "sample hand"
	 */
}

// Collect statistics for each rank of Poker
void pokerStats(Poker &poker) {
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
	tmark = clock() - tmark;	// stop the clock
}

int main(void) {
	Poker poker;
	cout << "Sample hand for each Rank:" << endl;
	pokerHands(poker);
	cout << endl << "Statistics:" << endl;
	pokerStats(poker);

	return EXIT_SUCCESS;
}
