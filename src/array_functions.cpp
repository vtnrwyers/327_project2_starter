/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 */

//============================================================================
//	TODO add necessary includes here
//============================================================================

//============================================================================
//	stuff you will need
//============================================================================
//TODO define a structure to track words and number of times they occur

//TODO add a global array of entry structs (global to this file)

//TODO add variable to keep track of next available slot in array

//TODO define all functions in header file

//TODO look in utilities.h for useful funvoid clearArray();ctions, particularly strip_unwanted_chars!
string v[0] = {};
void clearArray(){
v.clear();
}

int getArraySize(){
return v.size();
}

std::string getArrayWordAt(int i){
return v[i];
}

int getArrayWord_NumbOccur_At(int i){
return i;
}

bool processFile(std::fstream &myfstream){
return true;
}

void processLine(std::string &myString){

}

void processToken(std::string &token){

}

bool openFile(std::fstream& myfile, const std::string& myFileName,
	std::ios_base::openmode mode = std::ios_base::in){
return true;
    }

void closeFile(std::fstream& myfile){

}

int writeArraytoFile(const std::string &outputfilename){
return 1;
}

void sortArray(constants::sortOrder so){

}