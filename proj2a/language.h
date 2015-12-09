#ifndef LANGUAGE_H
#define LANGUAGE_H

/////////////////// language.h
// By: Panos Skoufalos
// Date: December 4, 2015

//Purp: Holds all of the class specification for functions in the Language
//      class
#include "TrigramVector.h"

class Language
{
	public:
		Language();
		void addTrigramVecs(TrigramVectors i,std::string language);
		int get_num_languages();
		TrigramVectors get_languages(int i);
	private:
		int capacity;
		int used;
		void expand_array();
		int num_languages;
		TrigramVectors *language_vector;
		
};

#endif
