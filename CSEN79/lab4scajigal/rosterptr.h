/*
 * CSEN 79 Lab4
 * Roster with pointers as data structure
 *
 * Use Inheriatance which is not yet covered in lecture
 * Derive from "Roster" which was part of Lab3
 * 
 * "T" was defined in "roster.h" which is an alias to "Student".
 * We use this name as a hint this can be a future template.
 */
#ifndef ROSTERPTR_H
#define ROSTERPTR_H

// Class declaration for roster
namespace csen79 {
	class RosterPtr : public Roster {
	public:
		RosterPtr();
		~RosterPtr();
		bool insert(const T &);
		void erase(Person::ID_t);
		T* begin(void);
		T* end(void);
		T* next(void);

		void testRoster();

	private:
		T *roster;
		int capacity; // current capacity
		int idx;	// for the iterator
		int last;	// for insertion
	};
}
#endif // ROSTERPTR_H
