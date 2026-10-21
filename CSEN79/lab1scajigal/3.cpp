#include <iostream>
#include <fstream>
#include <ctype.h>
#include <assert.h>
using namespace std; 

int main(int argc, char* argv[]) {
    // cout << "You have entered " << argc << " arguments:" << endl;
    assert(argc==2);

    // Create and open a text file
    ifstream MyFile(argv[1]);

    string word;
    while (MyFile >> word) {
        string newWord = "";
        for (int i = 0; i < word.length(); i++) {
            if (isalnum(word.at(i))) {
                newWord += (char)toupper(word.at(i));
            }
        }
        if (newWord.length() >= 10) {
            cout << newWord << endl;
        }
    }

    //// Close the file
    MyFile.close();
}