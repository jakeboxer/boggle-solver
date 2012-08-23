#ifndef BOARD_H_
#define BOARD_H_

#include <set>
#include <vector>
#include "SChar.h"
#include "Dictionary.h"
using namespace std;

class Board {
private:
	vector<vector<SChar *> * > * letters;
	void fillAdjacencies ();
public:
	Board(const string *);
	Board(const Board &);
	virtual ~Board();
	
	const vector<const string *> * getWords (const Dictionary *);
	SChar * getLetter (int, int) const;
	void touchLetter (int r, int c) { this->letters->at(r)->at(c)->setTouched(true); };
	vector<vector<SChar *> * > * getLetters () const { return this->letters; };  // This is a pointer to a pointer to SChars, because it's a pointer to an array of them
	bool validWord (const string *);
	bool remainingWordSolvable (SChar &, const string &, string::const_iterator);
	vector<SChar *> * getMatchingLetters (char) const;
	string * getInput () const;
	
	SChar * getValidAdjacentLetter (char, SChar *) const;
	
	void setAdjacentLetters (SChar *, int, int);
	void addAdjacentLetter (SChar *, int, int);
	void clearTouched ();
	
	static bool compareStrings (const string * i, const string * j) {
		return (i->length() != j->length()) ? i->length() > j->length() : i->compare(*j) < 0;
	};
};

#endif /*BOARD_H_*/
