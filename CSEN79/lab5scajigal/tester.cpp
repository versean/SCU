// FILE: main.cpp
// To test string class
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//

#include <iostream>
#include "mystring.h"
#include <cassert>

using std::cout;
using std::cin;
using std::endl;
using coen79_lab5::string;

std::string boolString(bool b) {
	return (b) ? "true" : "false";
}

static int testCount = 0;
static int passCount = 0;

class VerboseStream {
	private:
		bool verbose = false;
	public:
		void setVerbose(bool v) { verbose = v; }
		// Overload << for any type T
		template <typename T>
		VerboseStream& operator<<(const T& data) {
			if (verbose) {
				std::cout << data;
			}
			return *this;
		}

		// Handle manipulators like std::endl (function pointers)
		VerboseStream& operator<<(std::ostream& (*manip)(std::ostream&)) {
			if (verbose) {
				std::cout << manip;
			}
			return *this;
		}
};

void countAssert(bool b) {
	++testCount;
	if (b) ++passCount;
	else cout << "Test #" << testCount << " failed!" << endl;
}

int main(int argc, char const *argv[]) {
	VerboseStream vout;
	if (argc > 1) {
		if (std::string(argv[1]) == "-v") vout.setVerbose(true);
		else cout << "Run with -v option for verbose" << endl;
	}

	 vout << "*** Constructor tests ***" << endl;
	string s1, s2("Hello, World!"), s3(s2);
     vout << "s1: " << s1 << endl;
     vout << "s2: " << s2 << endl;
     vout << "s3: " << s3 << endl;
	 countAssert(s1 == string(""));
	 countAssert(s2 == "Hello, World!");
	 countAssert(s3 == s2);
    
     vout << "*** += operator tests ***" << endl;
     vout << "s1 length: " << s1.length() << endl;
	 countAssert(s1.length() == 0);
     s1 += string("A");
     vout << "s1: " << s1 << endl;
     vout << "s1 length: " << s1.length() << endl;
	 countAssert(s1.length() == 1);
     s1 += "B";
     vout << "s1: " << s1 << endl;
     vout << "s1 length: " << s1.length() << endl;
	 countAssert(s1.length() == 2);
     s1 += 'C';
     vout << "s1: " << s1 << endl;
     vout << "s1 length: " << s1.length() << endl;
	 countAssert(s1.length() == 3);
    
     vout << "*** [] operator test ***" << endl;
     vout << "s1[0]: " << s1[0] << endl;
     vout << "s1[1]: " << s1[1] << endl;
     vout << "s1[2]: " << s1[2] << endl;
	 countAssert(s1[0] == 'A');
	 countAssert(s1[1] == 'B');
	 countAssert(s1[2] == 'C');
    
     vout << "*** = operator test ***" << endl;
     s2 = string("= Test 1 Success");
     vout << "s2: " << s2 << endl;
	 countAssert(s2 == string("= Test 1 Success"));
     vout << "s2: " << (s2 = string("= Test 2 Success")) << endl;
	 countAssert(s2 == "= Test 2 Success");
    
     string A("A"), B("B");
     vout << "*** logical operator tests ***" << endl;
     vout << "A == A: " << boolString(A == A) << endl;
	 countAssert(A == A);
     vout << "A == B: " << boolString(A == B) << endl;
	 countAssert(!(A == B));
     vout << "A != A: " << boolString(A != A) << endl;
	 countAssert(!(A != A));
     vout << "A != B: " << boolString(A != B) << endl;
	 countAssert(A != B);
     vout << "A > A: " << boolString(A > A) << endl;
	 countAssert(!(A > A));
     vout << "A > B: " << boolString(A > B) << endl;
	 countAssert(!(A > B));
     vout << "B > A: " << boolString(B > A) << endl;
	 countAssert(B > A);
     vout << "A >= A: " << boolString(A >= A) << endl;
	 countAssert(A >= A);
     vout << "A >= B: " << boolString(A >= B) << endl;
	 countAssert(!(A >= B));
     vout << "B >= A: " << boolString(B >= A) << endl;
	 countAssert(B >= A);
     vout << "A < A: " << boolString(A < A) << endl;
	 countAssert(!(A < A));
     vout << "A < B: " << boolString(A < B) << endl;
	 countAssert(A < B);
     vout << "B < A: " << boolString(B < A) << endl;
	 countAssert(!(B < A));
     vout << "A <= A: " << boolString(A <= A) << endl;
	 countAssert(A <= A);
     vout << "A <= B: " << boolString(A <= B) << endl;
	 countAssert(A <= B);
     vout << "B <= A: " << boolString(B <= A) << endl;
	 countAssert(!(B <= A));
    
     vout << "*** + operator tests ***" << endl;
     vout << "A + B: " << (A + B) << endl;
	 countAssert((A + B) == "AB");
     vout << "A + C: " << (A + "C") << endl;
	 countAssert((A + "C") == "AC");
     vout << "B + A: " << (B + A) << endl;
	 countAssert((B + A) == "BA");

     vout << "*** >> operator test ***" << endl;
     cout << "Please enter a word: ";
     cin >> s1;
     vout << "You entered: " << s1 << endl;

	// Testing new functions.

	// Character constructor test.
	vout << "*** Single character constructor test ***" << endl;
	string C('C');
	vout << "C: " << C << endl;
	countAssert(C == "C");
	// Insertion tests.
	vout << "*** insert tests ***" << endl;
	s1 = "ABCD";
	vout << "s1: " << s1 << endl;
	countAssert(s1 == "ABCD");
	s1.insert("-",0);
	vout << "s1: " << s1 << endl;
	countAssert(s1 == "-ABCD");
	s1.insert("*",3);
	vout << "s1: " << s1 << endl;
	countAssert(s1 == "-AB*CD");
	s1.insert(".",s1.length());
	vout << "s1: " << s1 << endl;
	countAssert(s1 == "-AB*CD.");
	// Deleteion tests.
	vout << "*** dlt tests ***" << endl;
	s1 = "1112233445555";
	vout << "s1: " << s1 << endl;
	countAssert(s1 == "1112233445555");
	s1.dlt(0,3);
	vout << "s1: " << s1 << endl;
	countAssert(s1 == "2233445555");
	s1.dlt(2,2);
	vout << "s1: " << s1 << endl;
	countAssert(s1 == "22445555");
	s1.dlt(s1.length()-4,4);
	vout << "s1: " << s1 << endl;
	countAssert(s1 == "2244");
	// Replace test
	vout << "*** replace tests ***" << endl;
	s1 = "abc";
	vout << "s1: " << s1 << endl;
	countAssert(s1 == "abc");
	s1.replace('z',0);
	vout << "s1: " << s1 << endl;
	countAssert(s1 == "zbc");
	s1.replace('y',1);
	vout << "s1: " << s1 << endl;
	countAssert(s1 == "zyc");
	s1.replace('x',2);
	vout << "s1: " << s1 << endl;
	countAssert(s1 == "zyx");
	s1 = "ABCDEFGHIJKLMNOP";
	s2 = "123";
	s1.replace(s2, 0);
	vout << "s1: " << s1 << endl;
	countAssert(s1 == "123DEFGHIJKLMNOP");
	s1.replace(s2, 5);
	vout << "s1: " << s1 << endl;
	countAssert(s1 == "123DE123IJKLMNOP");
	s1.replace(s2, s1.length() - s2.length());
	vout << "s1: " << s1 << endl;
	countAssert(s1 == "123DE123IJKLM123");

	vout << "*** count tests ***" << endl;
	s1 = "ABBCCCDDDD";
	vout << "s1: " << s1 << endl;
	countAssert(s1 == "ABBCCCDDDD");
	vout << "Num A's: " << s1.count('A') << endl;
	countAssert(s1.count('A') == 1);
	vout << "Num B's: " << s1.count('B') << endl;
	countAssert(s1.count('B') == 2);
	vout << "Num C's: " << s1.count('C') << endl;
	countAssert(s1.count('C') == 3);
	vout << "Num D's: " << s1.count('D') << endl;
	countAssert(s1.count('D') == 4);
	vout << "Num E's: " << s1.count('E') << endl;
	countAssert(s1.count('E') == 0);

	vout << "*** search tests ***" << endl;
	vout << "s1: " << s1 << endl;
	countAssert(s1 == "ABBCCCDDDD");
	vout << "First A: " << s1.search('A') << endl;
	countAssert(s1.search('A') == 0);
	vout << "First B: " << s1.search('B') << endl;
	countAssert(s1.search('B') == 1);
	vout << "First C: " << s1.search('C') << endl;
	countAssert(s1.search('C') == 3);
	vout << "First D: " << s1.search('D') << endl;
	countAssert(s1.search('D') == 6);
	vout << "First E: " << s1.search('E') << endl;
	countAssert(s1.search('E') == -1);
	s1 = "ABCDEFGHIJKLMNOP";
	vout << "s1: " << s1 << endl;
	countAssert(s1 == "ABCDEFGHIJKLMNOP");
	vout << "Location of \"ABC\": " << s1.search(string("ABC")) << endl;
	countAssert(s1.search(string("ABC")) == 0);
	vout << "Location of \"GHI\": " << s1.search(string("GHI")) << endl;
	countAssert(s1.search(string("GHI")) == 6);
	vout << "Location of \"NOP\": " << s1.search(string("NOP")) << endl;
	countAssert(s1.search(string("NOP")) == 13);
	vout << "Location of \"XYZ\": " << s1.search(string("XYZ")) << endl;
	countAssert(s1.search(string("XYZ")) == -1);
	cout << "Tests passed: " << passCount << " out of " << testCount << " - " << (double) passCount / testCount * 100 << "%" << endl;

	return 0;
}
