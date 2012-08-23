#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "SChar.h"
#include "Board.h"
#include "Dictionary.h"

using namespace std;

string getAdjacentLetters (const SChar * pLetter) {
	string lets = "";
	
	for(int i = 0; i < 8; i++){
		const SChar * adj = pLetter->getAdjacentChar(i);
		
		if(adj != 0){
			lets.append(1, adj->getChar());
			lets.append(", ");
		}
	}
	
	return lets;
}

void printWords (const vector<const string *> & pWords) {
	char usrIn[16];
	unsigned int i = 0;
	
	// print them out
	for(vector<const string *>::const_iterator currWord = pWords.begin(); currWord != pWords.end(); currWord++, i++){
		cout << **currWord << endl;
		
		if((i % 20) == 0)
			cin.getline(usrIn, 16);
	}
}

int main () {
	
	
	cout << "Please enter the string of letters" << endl;
	cout << "(Do one row, left to right, then the next row, etc)" << endl;
	
	string userIn;
	cin >> userIn;
	cout << endl;
	
	// Create the board
	Board * b = new Board(&userIn);
	
	
	// Create the dictionary
	Dictionary * d = new Dictionary(string("words.txt"));
	
	// Get the words
	const vector<const string *> * words = b->getWords(d);
	
	// print them out
	printWords(*words);
	
	
	/*
	// The letter at 0,0 should be adjacent to 3 letters
	const SChar * s00 = b->getLetter(0,0);
	cout << "Letters adjacent to 0,0: " << getAdjacentLetters(s00) << endl;
	
	// The letter at 1,1 should be adjacent to 9 letters
	const SChar * s11 = b->getLetter(1,1);
	cout << "Letters adjacent to 1,1: " << getAdjacentLetters(s11) << endl;
	
	// The letter at 0,1 should be adjacent to 6 letters
	const SChar * s01 = b->getLetter(0,1);
	cout << "Letters adjacent to 0,1: " << getAdjacentLetters(s01) << endl;*/
	
	delete b;
	delete d;
	return 0;
}
