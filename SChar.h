#ifndef SCHAR_H_
#define SCHAR_H_

#include <vector>
using namespace std;

class SChar {
private:
	char ch;
	bool touched;
	unsigned int row;
	unsigned int col;
	SChar * adjacentChars[8];
	void initializeAdjacencies ();
public:
	SChar(char, unsigned int, unsigned int);
	SChar(const SChar &);
	virtual ~SChar();
	
	char getChar () const { return this->ch; };
	bool isTouched () const { return this->touched; };
	unsigned int getRow () const { return this->row; };
	unsigned int getCol () const { return this->col; }
	SChar * getAdjacentChar (int) const;
	vector<SChar *> * getUntouchedAdjacentChars () const { return this->getUntouchedAdjacentChars('\0'); };
	vector<SChar *> * getUntouchedAdjacentChars (char) const;
	
	void setChar (char pCh) { this->ch = pCh; };
	void setTouched (bool pTouched) { this->touched = pTouched; };
	void touch () { this->setTouched(true); };
	void addAdjacentChar (SChar *);
};

#endif /*SCHAR_H_*/
