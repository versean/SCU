/*
 * CSEN 79 Lab Sample Code
 */
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <exception>
#include "person.h"
#include "roster.h"
#include "rosterptr.h"

namespace csen79 {
	// write code for all these
	RosterPtr::RosterPtr() {
		int capacity = 2; 

		T *roster = new T[capacity];
		int idx = 0;	
		int last = 0;
	}
	RosterPtr::~RosterPtr() {
		delete [] roster;
	}
	bool RosterPtr::insert(const T &rec) {
		if (last >= capacity) {
			//std::cout << "Roster iterator exceeded range: " << CAPACITY << std::endl;
			// new array, copy, delete old array stuff yeah
			T *newRoster = new T[capacity+1];
			for (int i = 0; i < capacity; i++) {
				newRoster[i] = roster[i];
			}
			capacity++;
			delete [] roster; 
			roster = newRoster;
		}

		roster[last] = rec;
		last++;
		return true;
	}
	void RosterPtr::erase(Person::ID_t id) {
		for (int i = 0; i < last; i++) {
			if (roster[i].getID() == id) {
				roster[i] = roster[last-1];
				last--;
			}
		}
	}
	Roster::T* RosterPtr::begin(void) {
		idx=0;
		return &roster[0];
	}
	Roster::T* RosterPtr::end(void) {
		return &roster[last];
	}
	Roster::T* RosterPtr::next(void) {
		idx++;
		if (idx > capacity) {
			throw std::out_of_range("You're already at the end!!");
			idx--;
		}
		return &roster[idx]; 
	}

	
}	// namespace
