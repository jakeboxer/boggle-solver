#include "SChar.h"
#include <vector>
using namespace std;

SChar::SChar (char pCh, unsigned int pRow, unsigned int pCol) {
	this->setChar(pCh);
	this->row = pRow;
	this->col = pCol;
	this->initializeAdjacencies();
}

SChar::SChar (const SChar & pChar) {
	this->ch      = pChar.getChar();
	this->row     = pChar.getRow();
	this->col     = pChar.getCol();
	this->touched = pChar.isTouched();
	this->initializeAdjacencies();
}

SChar::~SChar () {
}

void SChar::initializeAdjacencies () {
	for(int i = 0; i < 8; i++)
		this->adjacentChars[i] = 0;  // Start all off as null pointers
}

SChar* SChar::getAdjacentChar (int pIdx) const {
	if((pIdx > 7) || (pIdx < 0))
		return 0;  // If the char index is out of bounds, return a null pointer
	
	return this->adjacentChars[pIdx];
}

vector<SChar *> * SChar::getUntouchedAdjacentChars (char pMatch) const {
	
	vector<SChar *> * adj = new vector<SChar *>();
	
	for(int i = 0; i < 8; i++){
		if((this->adjacentChars[i] != 0) && !this->adjacentChars[i]->isTouched() && ((pMatch == '\0') || (pMatch == this->adjacentChars[i]->getChar())))
			adj->push_back(this->adjacentChars[i]);  // If the character hasn't been touched, add it
	}
	
	return adj;
}

void SChar::addAdjacentChar (SChar * pAdjChar) {
	for(int i = 0; (i < 8); i++){
		if(this->adjacentChars[i] == 0){
			this->adjacentChars[i] = pAdjChar; // If it's a null pointer, make it point at the passed SChar
			break;
		}
	}
}
