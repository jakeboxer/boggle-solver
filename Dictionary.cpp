#include <fstream>
#include <string>
#include <iterator>
#include <vector>
#include "Dictionary.h"
using namespace std;

Dictionary::Dictionary (const string pFileName) {
	
	string currLine;
	ifstream dicFile;
	dicFile.open(pFileName.data());
	
	if(dicFile.is_open()){
		while(!dicFile.eof()){
			getline(dicFile, currLine);
			Dictionary::cleanWord(currLine);
			
			if((currLine.length() >= 3) && (currLine.length() <= 16)) // Only add words between sizes 3 and 16
				this->words.push_back(currLine);
		}
	}
	else
		cout << "Unable to open file." << endl;
}


Dictionary::~Dictionary () {
	//delete this->words;
}

void Dictionary::printWords () const {
	for(vector<string>::const_iterator itr = this->words.begin(); itr != this->words.end(); itr++)
		cout << *itr << endl;
	//cout << "Number of words: " << this->words.size() << endl;
}
