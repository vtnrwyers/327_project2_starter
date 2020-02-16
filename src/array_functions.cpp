/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 */

//============================================================================
//	TODO add necessary includes here
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "array_functions.h"
#include "constants.h"
#include "utilities.h"
using namespace std;
using namespace constants;
//============================================================================
//	stuff you will need
//============================================================================

//TODO define a structure to track words and number of times they occur
struct trackwords {
	int times;
	string word;
};

//TODO add a global array of entry structs (global to this file)
struct trackwords v[MAX_WORDS];
//TODO add variable to keep track of next available slot in array
int nextavail;

//zero out array that tracks words and their occurrences
void clearArray() {
	for (int i = 0; i < MAX_WORDS; i++) {
		v[i].word = "";
		v[i].times = 0;
	}
	nextavail = 0;
}
//how many unique words are in array
int getArraySize(){
return nextavail;
}
//get data at a particular location
std::string getArrayWordAt(int i){
return v[i].word;
}
//get data at a particular location
int getArrayWord_NumbOccur_At(int i){
return v[i].times;
}
/*loop through whole file, one line at a time
 * call processLine on each line
 * returns false: myfstream is not open
 *         true: otherwise*/
bool processFile(std::fstream &myfstream){
	string line;
		if (myfstream.is_open()) {
			while (getline(myfstream, line)) {
				processLine(line);
			}
			return true;
		}
		else {
			return false;
		}
}
/*take 1 line and extract all the tokens from it
feed each token to processToken for recording*/
void processLine(std::string &myString){
		std::stringstream ss(myString);
		std::string temptoken;

		while (std::getline(ss, temptoken, CHAR_TO_SEARCH_FOR)) {
			processToken(temptoken);
		}
}
/*Keep track of how many times each token seen*/
void processToken(std::string &token){
	strip_unwanted_chars(token);

		if (token == ""){
			return;
		}

		for (int i = 0; i < nextavail; i++) {
			std::string a = token;
			std::string b = v[i].word;
			toUpper(a);
			toUpper(b);

			if (a == b) {
				v[i].times++;
				return;
			}
		}

		v[nextavail].word = token;
			v[nextavail].times = 1;
			nextavail++;
}
/*if you are debugging the file must be in the project parent directory
 in this case Project2 with the .project and .cProject files*/
bool openFile(std::fstream& myfile, const std::string& myFileName,
	std::ios_base::openmode mode = std::ios_base::in){
	myfile.open(myFileName, mode);

		if (myfile.is_open()){
			return true;
		}
		else{
		return false;
		}
    }
/*if myfile is open then close it*/
void closeFile(std::fstream& myfile){
	if (myfile.is_open()) {
			myfile.close();
		}
}
/* serializes all content in myEntryArray to file outputfilename
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in myEntryArray
 * 			SUCCESS if all data is written and outputfilename closes OK
 * */
int writeArraytoFile(const std::string &outputfilename){
	ofstream out;
		out.open(outputfilename.c_str(), ios::out);
		if (!out.is_open()) {
			return FAIL_FILE_DID_NOT_OPEN;
		}
		else if (nextavail == 0) {
			out.close();
			return FAIL_NO_ARRAY_DATA;
		}
		else {
			for (int i = 0; i < nextavail; i++) {
				out << v[i].word << CHAR_TO_SEARCH_FOR << v[i].times
						<< endl;
			}
			out.close();
			return SUCCESS;
		}
}
/*
 * Sort myEntryArray based on so enum value.
 * The presence of the enum implies a switch statement
 */
void sortArray(constants::sortOrder so){
	switch(so) {
		case sortOrder::ASCENDING: {
			for (int i = 0; i < nextavail - 1; i++) {
				for (int j = 0; j < nextavail - i - 1; j++) {
					std::string a = v[j].word;
					std::string b = v[j + 1].word;
					toUpper(a);
					toUpper(b);
					if (a > b) {
						trackwords temp = v[j];
						v[j] = v[j+1];
						v[j+1] = temp;
					}
				}
			}
			break;
		}
		case sortOrder::DESCENDING: {
			for (int i = 0; i < nextavail - 1; i++) {
				for (int j = 0; j < nextavail - i - 1; j++) {
					std::string a = v[j].word;
					std::string b = v[j+1].word;
					toUpper(a);
					toUpper(b);
					if (a < b) {
						trackwords temp = v[j];
						v[j] = v[j+1];
						v[j+1] = temp;
					}
				}
			}
			break;
		}
		case sortOrder::NUMBER_OCCURRENCES: {
			for (int i = 1; i < nextavail; i++) {
				for (int j = 1; j < nextavail; j++) {
					if (v[j - 1].times < v[j].times) {
						trackwords a;
						a.word = v[j - 1].word;
						a.times = v[j - 1].times;
						v[j - 1] = v[j];
						v[j] = a;
					}
				}
			}
		}
			break;
		case sortOrder::NONE:
			break;
	}
}
