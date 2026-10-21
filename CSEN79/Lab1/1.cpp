#include <iostream>
#include <string>
#include <ctype.h>
#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << "Please type something: ";

    string input;
    getline(cin, input);

    int numAlNum = 0;
    int numNonAlNum = 0;
    for (int i = 0; i < input.length(); i++) {
        if (isalnum(input.at(i))) {
            numAlNum++;
        } else if (!isblank(input.at(i))) {
            numNonAlNum++;
        }
    }
    cout << "\"" << input << "\"" << " has " << numAlNum << " alphanumeric characters and " << numNonAlNum << " non-alphanumeric characters.";
}