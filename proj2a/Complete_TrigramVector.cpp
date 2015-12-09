////////////////////////////////TrigramVector.cpp////////////////////////////
#include<iostream> 
#include<fstream>
//#include "TrigramVector.h"
//#include "Language.h"

using namespace std;

class TrigramVectors
{
public:
//	TrigramVector_Construct();
//	~Trigram_Vector_Deconstruct();
	TrigramVectors();
	~TrigramVectors();
	void Trigram_setup(string data);
	void read_in(string fName);
	string data_clearup(string data);

	string get_trigram_info(int get);
	int get_capacity_info();
	string get_data_info();
	string get_file_info();

private:
	string *trigram_array;
	string data;
	int capacity;
	void expand();
	int used;
	string file_name;
};
 
void print_out(TrigramVectors *);
const int CAPACITY = 1000;

int main()
{
	string fName;
	string Language;
	string data;

	while (cin >> Language >> fName){
		TrigramVectors(i);
		i.read_in(fName);
		data = i.get_data_info();
		data = i.data_clearup(data);
		i.Trigram_setup(data);
		print_out(&i);
	}
}

////////////////////////////////////////////////////////////////////////////
/////////////////ALL CLASS FUNCTIONS FOR TRIGRAM VECTORS////////////////////
////////////////////////////////////////////////////////////////////////////

//TrigramVectors
//	Purp: This is a constructor function that initializes most of the 
//	      private members of the TrigramVectors class
//	Args: None
//	Rets: None
TrigramVectors::TrigramVectors()//_Constructor
{
	used = 0;
	capacity = CAPACITY;
	trigram_array = new string[CAPACITY];

	for(int i= 0; i < CAPACITY; i++){
		trigram_array[i] = "";
	}
}

//~TrigramVectors
//	Purp: This is the Deconstructor function that deletes the trigram
//	      array
//	Args: None
//	Rets: None
TrigramVectors::~TrigramVectors()//_Deconstruct
{
	delete[] trigram_array;
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
		if(used == capacity)
			expand();
	}
}

//read_in()
//	Purp: This function reads in the file name, opens it and initializes
//	      the data variable.
//	Args: On string, fName
//	Rets: None
void TrigramVectors::read_in(string fName)
{
	ifstream finput;
	file_name = fName;
	string data_string = "";
	finput.open(fName.c_str());
	char c;
	if(!finput.is_open()){
		cout << "Cannot open" << " doc1" << endl;
	}
	while(finput.get(c)){
		data_string += c;
	}
	data = data_string;
	finput.close();
}

//data_clearup()
//	Purp: This program clears up the data string by checking that the 
//	      characters are in the alphabet and if not turns all extras
//	      into spaces, while also making everything lower case.
// 	Args: one string, data
//	Rets: a string, the new updated data 
string TrigramVectors::data_clearup(string data)
{
	string updatedDataS = "";
	int sLength = data.length();
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

//get_trigram_info()
//	Purp: This function pulls the trigram_array information out of the
//	      private class and allows this information to be manipulated
//	      in the rest of the program.
//	Args: One integer, get
//	Rets: a string, trigram_array, that is also a pointer
string TrigramVectors::get_trigram_info(int get)
{
	return trigram_array[get];
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

//expand()
//	Purp: This funciton is a typical expand function. It is called when
//	      the program arrays need more space, this function doubles
//	      the space in arrays
//	Args: None
// 	Rets: None
void TrigramVectors::expand()
{
	string *new_array =  new string[capacity*2];
	for (int i = 0; i < capacity; i++){
		new_array[i] = trigram_array[i];
	}
	delete[] trigram_array;
	trigram_array = new_array;
	capacity = capacity*2;
}

////////////////////////////////////////////////////////////////////////////
///////////////////////////ALL OTHER FUNCTIONS//////////////////////////////
////////////////////////////////////////////////////////////////////////////
//print_out
//	Purp: This function prints out the file name and trigrams for any
//	      given file name.
//	Args: A class, TrigramVectors
//	Rets: Nothings
void print_out(TrigramVectors *i)
{
	int finalCapacity;

	cout << i -> get_file_info() << endl;
	finalCapacity = i -> get_capacity_info();

	for(int k= 0; k < finalCapacity; k++){
		cout << i -> get_trigram_info(k) << endl;
	}
}
