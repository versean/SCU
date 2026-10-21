#include <iostream>
#include <iomanip>
#include <string>
#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << "Please type a string of 10 digits (0 to 9) with no space ";

    string input;
    getline(cin, input);

    string inputReveresed = string(input.rbegin(), input.rend());

    for (int i = 0; i < 5; i++) {
        cout << setw(14 + i*2) << input;
        cout << setw(20 + i*2) << inputReveresed << endl;
    }
}