#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <sstream>
#include "Board.h"
using namespace std;

Board::Board (const string * pLetters) {
	
	cout << "Length: " << pLetters->length() << endl;
	
	// If the string is of the correct length, process it
	if(pLetters->length() == 16){
		
		this->letters = new vector<vector<SChar *> * >();
		vector<SChar *> * tmp;
		
		// Create all the Scramble Characters
		for(int i = 0; i < 4; i++){
			
			tmp = new vector<SChar *>;
			
			for(int j = 0; j < 4; j++){
				tmp->push_back(new SChar(pLetters->at((4 * i) + j), i + 1, j + 1));
			}
			
			this->letters->push_back(tmp);
		}
		
		this->fillAdjacencies();
	}
}

Board::Board (const Board & pBoard) {
	this->letters = new vector<vector<SChar *> *>();
	
	for(vector<vector<SChar *> * >::const_iterator vItr = pBoard.getLetters()->begin(); vItr != pBoard.getLetters()->end(); vItr++){
		
		vector<SChar *> * tmp = new vector<SChar *>();
		
		for(vector<SChar *>::const_iterator cItr = (*vItr)->begin(); cItr != (*vItr)->end(); cItr++) // we have to dereference, because vItr is a pointer to a pointer to a vector
			(*tmp).push_back(new SChar(**cItr)); // we have to double dereference, because cItr is a pointer to a pointer to a SChar
		
		this->letters->push_back(tmp);
	}
	
	this->fillAdjacencies();
}

Board::~Board () {
	// Delete all the SChars
	for(vector<vector<SChar *> * >::const_iterator vItr = this->letters->begin(); vItr != this->letters->end(); vItr++){
		for(vector<SChar *>::const_iterator cItr = (*vItr)->begin(); cItr != (*vItr)->end(); cItr++) // we have to dereference, because vItr is a pointer to a pointer to a vector
			delete *cItr; // we have to dereference, because cItr is a pointer to a pointer to a SChar
		
		delete *vItr;
	}
	
	delete this->letters;
}

void Board::fillAdjacencies () {
	// Set their adjacent letters
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++)
			this->setAdjacentLetters(this->letters->at(i)->at(j), i, j);
	}
}

const vector<const string *> * Board::getWords (const Dictionary * pDic) {
	vector<const string *> * validWords = new vector<const string *>();
	const vector<string> * words = pDic->getWords();
	
	for(vector<string>::const_iterator currWord = words->begin(); currWord != words->end(); currWord++){	
		// For each word, if the word is doable on the board, add it to the set
		if(this->validWord(&(*currWord)))
			validWords->push_back(&(*currWord));
	}
	
	sort(validWords->begin(), validWords->end(), Board::compareStrings);
	
	return validWords;
}

SChar * Board::getLetter (int pRow, int pCol) const {
	if((pRow < 1) || (pRow > 4) || (pCol < 1) || (pCol > 4))
		return 0;
	
	return this->letters->at(pRow - 1)->at(pCol - 1);
}


/**
 * Algorithm:
 * 
 * Find all the characters that are equal to the first letter
 * 
 * For each one:
 *   Create a new board, touch the appropriate letter on that board, and find all the untouched
 *   adjacent letters.
 */
bool Board::validWord (const string * pWord) {
	// recursive method needs:
	// - the current SChar that we're on (specific SChar, since there may be more than one)
	// - the remnants of the string we should be looking for (iterator)
	// 
	// recursive method job:
	// - If there's no string left, return true
	// - If there is part of a string left:
	//   * If no untouched adjacent letters match the next character in the string, return false
	//   * If at least one matches, recurse
	vector<SChar *> * matchingChars = this->getMatchingLetters((*pWord).at(0));
	
	// To get started, go through each letter that matches the first char in the word
	for(vector<SChar *>::const_iterator currLetter = (*matchingChars).begin(); currLetter != (*matchingChars).end(); currLetter++){
		
		if(this->remainingWordSolvable(**currLetter, *pWord, (*pWord).begin())){
			delete matchingChars;
			return true;
		}
		
	}
	
	delete matchingChars;
	return false;
}

bool Board::remainingWordSolvable (SChar & pLetter, const string & pWord,  string::const_iterator pPosition) {
	if((pPosition + 1) == pWord.end())
		return true;
	
	Board * dupBoard  = new Board(*this);
	SChar * dupLetter = (*dupBoard).getLetter(pLetter.getRow(), pLetter.getCol());
	string::const_iterator currPosition = pPosition + 1;
	
	// Touch the letter
	(*dupLetter).touch();
	
	// Get the letters that are adjacent to the current letter, untouched, and match the next character in the word
	vector<SChar *> * adj = (*dupLetter).getUntouchedAdjacentChars(*currPosition);
	
	// If there's at least one matching adjacent untouched letter, recurse
	if((*adj).size() > 0){
		for(vector<SChar *>::iterator currLetter = (*adj).begin(); currLetter != (*adj).end(); currLetter++){
			if((*dupBoard).remainingWordSolvable(**currLetter, pWord, currPosition)){
				delete adj;
				delete dupBoard;
				return true;
			}
		}
	}
	
	// If none of the letters are valid, return false
	delete adj;
	delete dupBoard;
	return false;
}

vector<SChar *> * Board::getMatchingLetters (char pChar = '\0') const {
	vector<SChar *> * matching = new vector<SChar *>();
	
	for(vector<vector<SChar *> * >::const_iterator vItr = this->letters->begin(); vItr != this->letters->end(); vItr++){
		for(vector<SChar *>::const_iterator cItr = (*vItr)->begin(); cItr != (*vItr)->end(); cItr++){ // we have to dereference, because vItr is a pointer to a pointer to a vector
			if((pChar == '\0') || (pChar == (**cItr).getChar()))
				(*matching).push_back(*cItr); // we have to dereference, because cItr is a pointer to a pointer to a SChar
		}
	}
	
	return matching;
}

string * Board::getInput () const {
	string * str = new string("");
	stringstream sout;
	
	for(vector<vector<SChar *> * >::const_iterator vItr = this->letters->begin(); vItr != this->letters->end(); vItr++){
		for(vector<SChar *>::const_iterator cItr = (*vItr)->begin(); cItr != (*vItr)->end(); cItr++)
			sout << (**cItr).getChar() << (**cItr).getRow() << ',' << (**cItr).getCol() << ' ';
	}
	
	(*str).append(sout.str());
	
	return str;
}

SChar * Board::getValidAdjacentLetter (char pChar, SChar * pLastLetter = 0) const {
	
	if(pLastLetter != 0){
		// If a non-null last letter was passed, only look at letters adjacent to it
		
		vector<SChar *> * adj = pLastLetter->getUntouchedAdjacentChars();
		
		// Go through every untouched adjacent letter
		for(vector<SChar *>::iterator currLetter = adj->begin(); currLetter != adj->end(); currLetter++){
			if((*currLetter)->getChar() == pChar)
				return *currLetter; // we have to dereference, because currLetter is a pointer to a pointer to a SChar
		}
	}
	else{
		// Otherwise, look at every letter on the board
		for(vector<vector<SChar *> * >::const_iterator vItr = this->letters->begin(); vItr != this->letters->end(); vItr++){
			for(vector<SChar *>::const_iterator cItr = (*vItr)->begin(); cItr != (*vItr)->end(); cItr++){ // we have to dereference, because vItr is a pointer to a pointer to a vector
				if(((*cItr)->getChar() == pChar) && (!(*cItr)->isTouched())) // If the letter is equal and untouched, return it
				    return *cItr; // we have to dereference, because cItr is a pointer to a pointer to a SChar
			}
		}
	}
	
	return 0;
}

void Board::setAdjacentLetters (SChar * pLetter, int pRow, int pCol) {
	int leftCol  = pCol - 1; // a b c
	int rightCol = pCol + 1; // d E f
	int aboveRow = pRow - 1; // g h i
	int belowRow = pRow + 1;
	
	this->addAdjacentLetter(pLetter, aboveRow, leftCol);  // a
	this->addAdjacentLetter(pLetter, aboveRow, pCol);     // b
	this->addAdjacentLetter(pLetter, aboveRow, rightCol); // c
	
	this->addAdjacentLetter(pLetter, pRow, leftCol);      // d
	// Don't add E, because E is the letter itself
	this->addAdjacentLetter(pLetter, pRow, rightCol);     // f
	
	this->addAdjacentLetter(pLetter, belowRow, leftCol);  // g
	this->addAdjacentLetter(pLetter, belowRow, pCol);     // h
	this->addAdjacentLetter(pLetter, belowRow, rightCol); // i
}

void Board::addAdjacentLetter (SChar * pLetter, int pRow, int pCol) {
	if((pRow > -1) && (pRow < 4) && (pCol > -1) && (pCol < 4))
		pLetter->addAdjacentChar(this->letters->at(pRow)->at(pCol));
}

void Board::clearTouched () {
	
	for(vector<vector<SChar *> * >::iterator vItr = this->letters->begin(); vItr != this->letters->end(); vItr++){
		for(vector<SChar *>::iterator cItr = (*vItr)->begin(); cItr != (*vItr)->end(); cItr++) // we have to dereference, because vItr is a pointer to a pointer to a vector
			(*cItr)->setTouched(false); // we have to dereference, because cItr is a pointer to a pointer to a SChar
	}
}
