/*
 * CSEN 79 Lab Sample Code
 */
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "person.h"
#include "roster.h"


namespace csen79 {

	// STUDENT WORK
	Roster::Roster() {
		T roster[CAPACITY+1] = {}; // the extra one at the end for the rostermain.cxx loop, so it knows when to stop
		int idx = 0;
		int last = 0;
	}
	// insert into the roster
	void Roster::insert(const T &rec) {
		// STUDENT WORK
		if (last < CAPACITY) {
			roster[last] = rec;
			last++;
		} else {
			std::cout << "Roster iterator exceeded range: " << CAPACITY << std::endl;
		}
		
	}

	// simply mark the slot empty
	void Roster::erase(Person::ID_t id) {
		// STUDENT WORK
		for (int i = 0; i < last; i++) {
			if (roster[i].getID() == id) {
				roster[i] = roster[last-1];
				last--;
			}
		}
	}

	// rudimentary iterator
	// in the future, this will return an object of iterator type
	Roster::T* Roster::begin(void) {
		// STUDENT WORK
		idx=0;
		return &roster[0];
	}

	Roster::T* Roster::end(void) {
		// STUDENT WORK
		return &roster[last];
	}

	// The next element for interation
	// if already reached the end, throw exception
	Roster::T* Roster::next(void) {
		// STUDENT WORK
		idx++;
		if (idx > CAPACITY) {
			throw std::out_of_range("You're already at the end!!");
			idx--;
		}
		return &roster[idx]; 

	}
}
