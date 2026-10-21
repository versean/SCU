/*
 * Name: Your Name
 * Email: Your email
 */
#include <iostream>
#include "card.h"
#include "deck.h"

// for shuffling
#include<bits/stdc++.h> 
#include <stdlib.h> 
#include <time.h> 

namespace lab2scajigal {
	void Deck::shuffle(void) {
		next = 0; // go back to top of deck

		srand (time(NULL)); 
		for (int i = nCards - 1; i > 0; i--) 
		{ 
			int j = rand() % (i + 1); 
			
			Card temp = Deck::cards[i]; 
			Deck::cards[i] = Deck::cards[j]; 
			Deck::cards[j] = temp; 
		}
		
	}

	// deal out one card
	const Card &Deck::deal() {
		if (next >= nCards - guard) {
			shuffle();
			
		}
		return cards[next++];
	}
}

