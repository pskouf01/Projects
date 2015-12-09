//language.cpp
// By Panos Skoufalos
// Date: December 1, 2015
// Purpose: This file holds all of the functions for the language Class
#include<iostream>
#include<fstream>
#include "language.h"
using namespace std;

//Language()
//	Purp: This is a constructor function that initializes private 
//	      variables
//	Args: none
//	Rets: none
Language::Language()
{
	capacity = 10;
	num_languages = 0;
	used=0;
	language_vector = new TrigramVectors[capacity];

}

//addTrigramVecs()
//	Purp: This function breaks down each language into its trigrams and 
//	      increments the number of languages.
//	Args: One TrigramVectors variable i, one string language
//	Rets: Void
void Language::addTrigramVecs(TrigramVectors i, string language)
{
	bool languageMatch =false;

	for(int k = 0; k < num_languages; k++){
	      if((language==language_vector[k].getLanguageName())){
		        language_vector[k].countAllGrams(i);
			language_vector[k].setUsedLanguages(i);
			languageMatch = true;
		      }
	}
	if (!languageMatch){
		expand_array();
		language_vector[num_languages].setLangName(language);
		language_vector[num_languages].countAllGrams(i);
		language_vector[num_languages].setUsedLanguages(i);
		num_languages++;
	}
}

//expand()
//	Purp: This funciton is a typical expand function. It is called when
//	      the program arrays need more space, this function doubles
//	      the space in arrays
//	Args: None
// 	Rets: None
void Language::expand_array()
{
	int newCapacity = 1 + capacity*2;
	TrigramVectors *new_array =  new TrigramVectors[newCapacity];
	for (int i = 0; i < capacity; i++){
		new_array[i] = language_vector[i];
	}
	delete[] language_vector;
	language_vector = new_array;
	capacity = newCapacity;

}

//get_num_languages()
//	Purp: A getter function for the number of languages in the private class
//	Args: None
//	Rets: a integer, num_languages
int Language::get_num_languages()
{
	return num_languages;
}

//get_num_languages()
//	Purp: a getter function for the languages vector
//	Args: an integer, i
//	Rets: the language vector of type TrigramVectors.
TrigramVectors Language::get_languages(int i)
{
	return language_vector[i];
}
    
