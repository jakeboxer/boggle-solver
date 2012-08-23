#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Dictionary {
private:
	vector<string> words;
public:
	Dictionary(const string);
	virtual ~Dictionary();
	
	const vector<string> * getWords () const { return &this->words; };
	
	static string & cleanWord (string & pWord) {
		
		// ---START TRIM---
		string::size_type pos = pWord.find_last_not_of(' ');
		
		if(pos != string::npos) {
			pWord.erase(pos + 1);
			pos = pWord.find_first_not_of(' ');
			
			if(pos != string::npos)
				pWord.erase(0, pos);
		}
		else
			pWord.erase(pWord.begin(), pWord.end());
		// --- END TRIM ---
		
		// --- START QU -> Q REPLACEMENT ---
		string::size_type idx = 0;
		while(pWord.find("qu", idx) != string::npos){
			idx = pWord.find("qu", idx);
			pWord.replace(idx, 2, "q");
			idx++;
		}
		// --- END QU -> Q REPLACEMENT ---
		
		return pWord;
	};
	
	void printWords () const;
};

#endif /*DICTIONARY_H_*/
