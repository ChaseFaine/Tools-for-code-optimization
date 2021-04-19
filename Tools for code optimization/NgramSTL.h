/*
 * Here are includes for lots of STL header files.
 * You shouldn't need to add more.
*/
#include <iostream>
#include <set>
#include <string>
#include <array>
#include <iterator>
#include <list>
#include <tuple>
#include <utility>
#include <map>
#include <unordered_map>
#include <vector>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <algorithm>
#include <functional>

/* You can add more to this header class declaration. For example,
 * you can add a data member for the stl data structure that you use. 
 * You can also method declarations for the methods you add to the
 * class.
 */
#define SIZE 911

#define ARRSIZE 3000

class Ngrams 
{
   struct Ngram
   {
      std::string ngram;
      int count;
      struct Ngram * next;
      struct Ngram * sortedNext;
   };

   typedef struct Ngram Ngram_t;

   private:
      bool ran = false;
      //Ngram * first;
      //Ngram *table[SIZE];
      //std::map<std::string,int> name;
      std::array<Ngram, ARRSIZE> arr;
      int counter[ARRSIZE];
      int ngramSz;
      void insertNgram(std::string s);
      void printList();
      void printListDecreasing();
      bool sortByCount(const std::pair<std::string, int> &x, const std::pair<std::string, int> &y);
   public:
      Ngrams(int ngramSz, WordList & wl);
      ~Ngrams();
      void sortByCount(bool reverse);
      void printIncreasing();
      void printDecreasing();
      //void createMap();
      //int hash(std::string s);
};

