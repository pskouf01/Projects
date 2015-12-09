#ifndef TRIGRAMVECTOR_H
#define TRIGRAMVECTOR_H

//////////////////////////////////TrigramVector.h////////////////////////////
//	By: Panos Skoufalos
//    Date: 10/20/2015
/////////////////////////////////////////////////////////////////////////////

const int CAPACITY = 1000;
const int TRIMAX = 19683;
const int AMAX = 27;

class TrigramVectors
{
public:
	TrigramVectors();
	void Trigram_setup(std::string data);
	void read_in(std::string fName, std::string language);
	std::string data_clearup(std::string data);
	std::string update_DataS(std::string updatedDataS, int sLength);

	std::string get_trigram_info(int i);
	int get_capacity_info();
	std::string get_data_info();
	std::string get_file_info();
	int getAllTrigramFrequencies(int i);
	std::string getAllTrigramV(int i);
	std::string getLanguageName();
	int getUsed();	

	void count_trigrams();
	void print_freq();
	void countAllGrams(TrigramVectors i);

	void setLangName(std::string lName);
	void setGramsCount(int used);
	void setUsedLanguages(TrigramVectors i);

	void createAllTrigramV();
	int count_all_trigrams[TRIMAX];
   	
private:
	int used;
	std::string file_name;
	std::string lang_name;
	std::string *trigram_array;
	std::string data;
	std::string languageName;
	int capacity;
	int *trigram_count;
	int usedTrigrams;

	void createAlphaVec();
	void expand_array();

	std::string all_trigram_vector[TRIMAX];
	char a_vector[AMAX];
};

#endif
