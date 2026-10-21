/*
 * CSEN 79 Lab Sample Code
 */
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "person.h"
#include "roster.h"

using namespace std;
using namespace csen79;

int main() {
    Roster roster;
    Person person;
    roster.insert(person);
    for (auto a = roster.begin(); a <= roster.end(); a = roster.next()) {
        cout << a;
    }
}