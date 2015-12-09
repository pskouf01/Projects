d////////////////////////////////////////////////////////////////////////////
////////////////////////////////////Trigram Vectors Project /////////////////
/////////////////////////////////////////////////////////////////////////////
//	By: Panagiotis Skoufalos
//    Date: 10/20/2015
/////////////////////////////////////////////////////////////////////////////
///////////////////////////////////The Design////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
-The program begins by reading in multiple text files and immediately breaks
the file down into two categories: 

-A known language or an unknown. If unknown the program compares that file
with the known languages and calculates the probability of what language this
file can be. 

-The program then reads in the given text, removes all none alphabetic chara-
cters with spaces, breaks down this altered text into trigram, and compares
each trigram to the file to find out the frequency of each trigram.

-if the file is a language, each trigram is compared to the text file and in-
cremented to a count in a parallel vector. Then the program saves the lang-
uage name, the count for each trigram, and the total number of trigrams.

-if the file is unknown, each trigram is compared to the text file of a poss-
ible trigram file, increments how often a match is found, compares this vec-
tor to a parralel vector stored in languages, through cosine similarity, and
computes the highest probability of what language this file can be. It then 
prints out the name of the file and from highest to lowest the probability
of what language this file is.

/////////////////////////////////////////////////////////////////////////////
///////////////////////////////////Instructions//////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// - The user must input the language file that contains an upercase first
// letter and a space followed by a lowercase text_file. 
// e.g. English texts/english_short.txt
//
//- Compiling goes as follows
// clang++ -Wall -Wextra -g -o TrigramVector TrigramVector.cpp
 main_TrigramVectors.cpp language.cpp 
//
