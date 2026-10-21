/*
 * CSEN 79 Lab Sample Code
 */
#include <cstddef>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "person.h"
#include "roster.h"

using namespace std;
using namespace csen79;

// Test code for class roster
// Input file: <CMD> [ID] [FIRST LAST]
// CMD : A | X | L
// ID: 7-digit unsigned integer
// FIRST, LAST: string
int main() {
	Roster r;
	Person st;
	Person::ID_t id;
	string cmd, first, last;

	// Read cmd first, then branch accordingly
	while (cin >> cmd) {
		switch (cmd[0]) {
		case Command::Add:
			// Insert a record
			// STUDENT WORK
			break;
		case Command::Erase:
			// remove a record, given the ID
			// STUDENT WORK
			break;
		case Command::Print:
			// listing the entire roster with a rudimentary iterator
			cout << "---- Current Roster ----"  << endl;
			int i = 1;
			for (auto st = r.begin(); st != r.end(); st = r.next(), i++)
				cout << i << ": " << *st << endl;
			break;
		} 
	}
	
	return EXIT_SUCCESS;
}

