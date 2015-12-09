////////////////////////////////////main_TrigramVector.cpp//////////////////
//	 By: Panos Skoufalos
//     Date: 10/20/2015
//  Purpose: This program was designed to analyze a text file and detect the 
//	     language in which it is written in. It utilizes the concept of 
//	     trigrams to break down the text file into phrases of three, and 
//	     analyzed from there.

#include<iostream> 
#include<fstream>
using namespace std;
#include "language.h"
#include<math.h>

void cosineSimilarity(TrigramVectors i, Language l);

int main()
{
	string fName;
	string language;
	string data;
	Language l;
	while (cin >> language >> fName){

			TrigramVectors i;
			i.read_in(fName, language);
			data = i.get_data_info();
			data = i.data_clearup(data);
			i.Trigram_setup(data);	
//			i.print_freq();
			if(language != "Unknown"){
				l.addTrigramVecs(i, language);
			} else {
				i.countAllGrams(i);
			       	cosineSimilarity(i, l);
			}
	}
}
//cosineSimilarit()
//	Purp: This function does the mathematical aspect of the project as 
//	      as prints out the highest to lowest language probability.
//	Args: a TrigramVectors variable, i and a variable l of type Language.
//	Rets: void
void cosineSimilarity(TrigramVectors i, Language l)
{
	int numLang = l.get_num_languages();
	int usedLanguages;
	float similarityVec[numLang];
	TrigramVectors *Language;
	Language = new TrigramVectors[numLang];
	for (int a=0; a < numLang; a++){
		Language[a] = l.get_languages(a);
	}
	int used_text = i.getUsed();
	for( int j = 0; j < numLang; j++){
	  	usedLanguages = Language[j].getUsed();		
		float numerator= 0.0;
		float language_denom= 0.0;
		float text_denom = 0.0;
		for(int p=0;p<TRIMAX;p++){
			numerator +=((float)i.getAllTrigramFrequencies(p) /
				     (float)used_text)
			   *((float)Language[j].getAllTrigramFrequencies(p)/
			      (float)usedLanguages);
       		text_denom += pow(((float)i.getAllTrigramFrequencies(p)
					   /(float)used_text), 2);
       		language_denom+=
		pow(((float)Language[j].getAllTrigramFrequencies(p)
				     /(float)usedLanguages),2);
		}
		text_denom = sqrt(text_denom);
		language_denom = sqrt(language_denom);
		similarityVec[j] = numerator/(text_denom * language_denom);
	}
	float temp1;
       	TrigramVectors temp2;
       	for(int k = 0;(k< numLang); k++){
       		for (int j=0; j < (numLang-1);j++){
       			if(similarityVec[j+1] > similarityVec[j]){
       				temp1 = similarityVec[j];
       				temp2 = Language[j];   	
       			   	 similarityVec[j] = similarityVec[j+1];
       				Language[j] = Language[j+1];
		       		similarityVec[j+1] = temp1;
		       		Language[j+1] = temp2;
		       	}
	       	}
       	}
       	cout<< i.get_file_info() << endl;
       	for( int h=0; h< numLang;h++){
       	cout << Language[h].getLanguageName() << ": "<< similarityVec[h]
	     << endl ;
       	}
}




