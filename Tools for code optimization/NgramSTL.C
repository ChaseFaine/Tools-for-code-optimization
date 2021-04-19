/*
 * Rules:
 * 1) No global variables. Any data structure that you need to add must be
 *    added to the class declaration in NgramFast.h
 * 2) You can add one or two new classes if you like. However, it is certainly
 *    possible and easier to just modify this class. Take a look at how a 
 *    data structure is used in NgramSlow.  That's the wrong data structure for
 *    the problem, but it does show how a type can be defined and used in
 *    the class. (If you add new classes, don't forget to modify the makefile.)
 * 3) No functions.  You can add methods to the Ngrams class, but you can
 *    not add functions that are not within the class.
 * 4) No use of the C++ standard template library, except for the WordList class.
 *    You don't need to modify the WordList class so that it doesn't use the
 *    standard template library.
*/

#include <iostream>
#include <string>
#include "WordList.h"
#include "NgramFast.h"
#include <list>
#include <set>
#include <string>
#include <array>
#include <iterator>
#include <tuple>
#include <utility>
#include <map>
#include <unordered_map>
#include <vector>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <algorithm>
#include <functional>

using namespace std;
std::map<std::string,int> hashmap;
vector<pair<string, int>> vec;

/* This implementation cannot used the C++ standard template library. 
 * Thus, you will not need to include any other header files.
 */

/*
 * Ngrams
 *
 * takes as input the size of the ngrams to be built and the list  
 * of words to build the ngrams from and builds a linked list of 
 * ngrams.
 *
 * param: int ngramSz - size of the ngram
 * param: WordList & wl - list of the words use
 */
Ngrams::Ngrams(int ngramSz, WordList & wl)
{
   //ADD any code you need to initialize whatever structure
   /*for(int i = 0; i < SIZE; i++) {
      table[i] = NULL;
   }*/
   //you use for your ngram
   //hashmap = new map();
   this->ngramSz = ngramSz;
   wl.beginIter();
   while (!wl.endIter())
   {
      std::string ngram = wl.getNextNgram(ngramSz);
      wl.incrementIter();
      if (!ngram.empty()) insertNgram(ngram);
   }
/*
   for(int i = 0; i < ARRSIZE; i++) {
      arr[i] = NULL;
   }*/
}

/*
 * Ngrams destructor
 *
 * automatically called when Ngrams object goes out of scope
 * should delete any space dynamically allocated for the ngram
 */
Ngrams::~Ngrams()
{
   
}


/*
 * insertNgram
 *
 * Inserts ngram into whatever structure you choose to hold
 * your ngrams.
 *
 * param: std::string s - ngram to be inserted
 * return: none
 */
void Ngrams::insertNgram(string s)
{
   //ADD code to insert ngram in whatever structure you choose
   if(hashmap.count(s) == 0){
      hashmap.emplace(pair<string, int>(s, 1));
   } else {
      int count = hashmap.at(s);
      count += 1;
      hashmap.erase(hashmap.find(s));
      hashmap.emplace(pair<string,int>(s, count));
   }
}

/*
 * You can ADD any other methods that you need here.
*/

bool sortByVal(const pair<string, int> &x, 
               const pair<string, int> &y) 
{ 
    return (x.second < y.second); 
}

/*
 * sortByCount
 *
 * Performs a bubble sort on the linked list of ngrams, sorting the
 * nodes in the list by the count in increasing or decreasing
 * order of count depending upon the value of reverse.
 *
 * param: reverse - true if sort should be decreasing
 * return: none (modfied private linked list)
 */
void Ngrams::sortByCount(bool reverse)
{
   if(ran == false) {
      map<string, int> :: iterator it2;
      for (it2=hashmap.begin(); it2!=hashmap.end(); it2++) 
      {
         vec.push_back(make_pair(it2->first, it2->second));
      }
      sort(vec.begin(), vec.end(), sortByVal); 
   }
   ran = true;
}

/*
 * printIncreasing
 *
 * prints the list of ngrams in decreasing order
 *
 */
void Ngrams::printIncreasing()
{
   sortByCount(false);
   std::cout << "\nIncreasing list of " << ngramSz << " word ngrams and counts\n";
   std::cout << "-------------------------------------------\n";
   printList();
}

/*
 * printList
 *
 * prints the nodes in the Ngrams
 */
void Ngrams::printList()
{
   /*std::map<std::string, int>::iterator itr = hashmap.begin();
   for(itr = hashmap.begin(); itr != hashmap.end(); itr++) {
      cout << itr->first << ": " << itr->second << endl;
   }*/
   for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i].first << ", " << vec[i].second << endl;
	}
}

void Ngrams::printListDecreasing() {
   for (int i = vec.size()-1; i >= 0; i--)
	{
		cout << vec[i].first << ", " << vec[i].second << endl;
	}
}

/*
 * printDecreasing
 *
 * prints the list of ngrams in decreasing order
 *
 */  
void Ngrams::printDecreasing()
{
   sortByCount(true);
   std::cout << "\nDecreasing list of " << ngramSz << " word ngrams and counts\n";
   std::cout << "-------------------------------------------\n";
   printListDecreasing();
}
