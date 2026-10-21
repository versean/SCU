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
	Roster::Roster() {}
	// insert into the roster
	void Roster::insert(const T &rec) {
		// STUDENT WORK
	}

	// simply mark the slot empty
	void Roster::erase(Person::ID_t id) {
		// STUDENT WORK
	}

	// rudimentary iterator
	// in the future, this will return an object of iterator type
	Roster::T* Roster::begin(void) {
		// STUDENT WORK
		return nullptr;
	}

	Roster::T* Roster::end(void) {
		// STUDENT WORK
		return nullptr;
	}

	// The next element for interation
	// if already reached the end, throw exception
	Roster::T* Roster::next(void) {
		// STUDENT WORK
		return nullptr;
	}
}
