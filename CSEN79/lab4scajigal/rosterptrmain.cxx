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
#include "rosterptr.h"

using namespace std;
using namespace csen79;


int main() {
	RosterPtr r;
    r.testRoster();
    return EXIT_SUCCESS;
}
