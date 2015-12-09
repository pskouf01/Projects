//////////////////////////////TrigramVector.cpp/////////////////////////////
//	By: Panagiotis Skoufalos
//    Date: 10/20/2015
// Purpose: This file stores all of the functions for the TrigramVectors 
//	    Class.

////////////////////////////////////////////////////////////////////////////
/////////////////ALL CLASS FUNCTIONS FOR TRIGRAM VECTORS////////////////////
////////////////////////////////////////////////////////////////////////////

#include<iostream>
#include<fstream>
using namespace std;
#include "TrigramVector.h"

//TrigramVectors
//	Purp: This is a constructor function that initializes most of the 
//	      private members of the TrigramVectors class
//	Args: None
//	Rets: None
TrigramVectors::TrigramVectors()//_Constructor
{
	createAlphaVec();
	createAllTrigramV();
	used = 0;
	capacity = CAPACITY;
	trigram_array = new string[CAPACITY];
	trigram_count = new int[CAPACITY];
	// initialize the new trigram_array

	for(int i= 0; i < CAPACITY; i++){
		trigram_array[i] = "";
		trigram_count[i] = 0;
	}
}

//read_in()
//	Purp: This function reads in the file name, opens it and initializes
//	      the data variable.
//	Args: On string, fName
//	Rets: None
void TrigramVectors::read_in(string fName, string language)
{
	ifstream finput;
	lang_name = language;
	file_name = fName;
	string data_string = "";
	finput.open(fName.c_str());
	char c;
	//check if file opens
	if(!finput.is_open()){
		cout << "Cannot open" << " doc1" << endl;
	}

	while(finput.get(c)){
		data_string += c;
	}

	data = data_string;
	finput.close();
}

//get_data_info()
//	Purp: This functions pulls a variable used out of the private class
//	      and allows the program to manipulate its information 
//	      throughout
//	Args: None
//	Rets: None
string TrigramVectors::get_data_info()
{
	return data;
}

//data_clearup()
//	Purp: This program initializes the length of the data file and
//	      calls a function to remove capitalized letters and 
//	      punctuation.
// 	Args: one string, data
//	Rets: a string, the new updated data 
string TrigramVectors::data_clearup(string data)
{
	string updatedDataS = "";
	int sLength = data.length();
	updatedDataS = update_DataS(updatedDataS, sLength);
	return updatedDataS;
}

// update_DataS()
//	Purp: This program clears up the data string by checking that the 
//	      characters are in the alphabet and if not turns all extras
//	      into spaces, while also making everything lower case.
//	Args: a string, updatedDataS, and an integer sLength.
//	Rets: a string, updatedDataS.
string TrigramVectors::update_DataS(string updatedDataS, int sLength)
{
	char c;
	for (int k = 0; k < sLength; k++){
		c = data[k];
		if (isalpha(c)){
		       	c = tolower(c);
			updatedDataS += c;
		}
		else if(isspace(c)){
			if(k == sLength-1 || isalpha(data[k+1]))
				updatedDataS += ' ';
     		}
	}
	return updatedDataS;
}
//Trigram_setup()
//	Purp: This function sets up the trigrams themselves, takes in the
//	      length of the data and divides data into threes, while 
//	      incramenting used and expanding the capacity
//	Args: One string, data
//	Rets: None
void TrigramVectors::Trigram_setup(string data)
{
	int sLength = data.length();

	for (int k = 0; k < sLength-2; k++){
		for(int i=0; i < 3; i++){
			trigram_array[k] += data[k+i];
		}
		used++;
		if(used == capacity){
			expand_array();
		}
	}
}

//expand()
//	Purp: This funciton is a typical expand function. It is called when
//	      the program arrays need more space, this function doubles
//	      the space in arrays
//	Args: None
// 	Rets: None
void TrigramVectors::expand_array()
{
	int newCapacity = 1 + capacity*2;
	string *new_array =  new string[newCapacity];
	for (int i = 0; i < capacity; i++){
		new_array[i] = trigram_array[i];
	}
	for (int i = capacity; i< newCapacity; i++){
		new_array[i] = "";
	}
	delete[] trigram_array;
	trigram_array = new_array;

	
	int *n_array = new int[newCapacity];
	for (int i =0; i < capacity; i++){
		n_array[i] = trigram_count[i];
	}
	for (int i = capacity; i < newCapacity; i++){
		n_array[i] = 0;
	}
	delete[] trigram_count;
	trigram_count = n_array;
	
	capacity = newCapacity;

}

//get_file_info()
//	Purp: This functions pulls a variable used out of the private class
//	      and allows the program to manipulate its information 
//	      throughout
//	Args: None
//	Rets: None
string TrigramVectors::get_file_info()
{
	return file_name;
}


//get_capacity_info()
//	Purp: This functions pulls a variable used out of the private class
//	      and allows the program to manipulate its information 
//	      throughout
//	Args: None
//	Rets: None
int TrigramVectors::get_capacity_info()
{
	return used;
}

//get_trigram_info()
//	Purp: This function pulls the trigram_array information out of the
//	      private class and allows this information to be manipulated
//	      in the rest of the program.
//	Args: One integer, get
//	Rets: a string, trigram_array, that is also a pointer
string TrigramVectors::get_trigram_info(int i)
{
	return trigram_array[i];
}

//trigram_count()
// 	Purp:This function counts all of the trigrams in a given file
// 	Args: None
// 	Rets: Void
void TrigramVectors::count_trigrams()
{
	for(int i = 0; i < used; i++){
		for(int k = 0; k < used; k++){
			if(trigram_array[i] == trigram_array[k]){
				trigram_count[i]++;
			}
		}
	}
}
//print_frequency()
//	Purp: This function calculates the frequency of any given trigram 
//	       in a file
//	      file
//	Args: None
// 	Rets: Void
void TrigramVectors::print_freq()
{
	count_trigrams();
	cout << "Frequency for " << file_name << endl;
	for (int i = 0; i < used; i++){
		cout << trigram_count[i] << " " << trigram_array[i] << endl;
	}
	cout << "total trigrams " <<  used << endl;
}

//createAllTrigramV()
//	Purp: This function creates a single, 19863 long vector
//	Args: None
//	Rets: Void
void TrigramVectors::createAllTrigramV()
{
	int counter =0;
	int i,j,k;
	string tristr ="aaa";
	for (i=0;i<27;i++){
		for(j=0;j<27;j++){
			for(k=0;k<27;k++){
				all_trigram_vector[counter]=a_vector[i];
				all_trigram_vector[counter]+=a_vector[j];
				all_trigram_vector[counter]+=a_vector[k];
				counter++;
			}
		}
	}
}

// getAllTrigramV()
//	Purp: This function takes the private variable from the private 
// 	      class and
// 	      allows the program to utilize it publicly
//	Args: integer i
//	Rets: a string, allTrigramVector
string TrigramVectors::getAllTrigramV(int i)
{
	return all_trigram_vector[i];
}

//createAlphaVec()
//	Purp: Creates a vector of a space and then the alphabet
//	Args: Nothing
//	Rets: Void
void TrigramVectors::createAlphaVec()
{
	a_vector[0] = ' ';
	a_vector[1] = 'a';
	for(int i =2; i < 27; i++){
		a_vector[i] = a_vector[i-1] + 1;
	}
}

//setLangName()
//	Purp: passes along a variable value to the private class
//	Args: a string, lName
//	Rets: void
void TrigramVectors::setLangName(string lName)
{
	languageName = lName;
}

//setGramsCount()
//	Purp: passes along a variable value to the private class
//	Args: integer, used
//	Rets: void
void TrigramVectors::setGramsCount(int used)
{
	usedTrigrams = used;
}

//getLanguageName()
//	Purp: Getter function for languageName
//	Args: Nothing
//	Rets: one string, languageName
string TrigramVectors:: getLanguageName()
{
	return languageName;
}

//countAllGrams
//	Purp: counts the frequency of an individual trigram compared to the
//	      rest
//	      of the inputed file
//	Args: one TrigramVectors variable, i
//	Rets: Void
void TrigramVectors:: countAllGrams(TrigramVectors i)
{
	int k,j;
	for(k=0;k<TRIMAX;k++){
 		for(j=0;j<i.getUsed();j++){
			if(all_trigram_vector[k] ==i.get_trigram_info(j)){
				count_all_trigrams[k]++;
			}
		}
	}
}

//setUsedLanguages
//	Purp: increments the value of the used variable for a given trigram 
//	      vctr
//	Args: One TrigramVectors instance, i
//	Rets: void
void TrigramVectors::setUsedLanguages(TrigramVectors i)
{
	used += i.getUsed();
}

//getAllTrigramFrequencies
//	Purp: getter function for count_all_trigrams[i]
//	Args: an integer i
//	Rets: an integer count_all_trigrams
int TrigramVectors::getAllTrigramFrequencies(int i)
{
	return count_all_trigrams[i];
}

//getUsed()
//	Purp: getter function for used variable
//	Args: none
//	Rets: an integer, used
int TrigramVectors::getUsed()
{
	return used;
}
