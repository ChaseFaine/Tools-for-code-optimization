
#include <iostream>
#include <string>
#include "WordList.h"
#include "NgramSlow.h"

/*
 * Ngrams
 *
 * takes as input the size of the ngrams to be built and the list  
 * of words to build the ngrams from and builds a linked list of 
 * ngrams.
 *
 * param: int ngramSz - size of the ngram
 * param: const WordList & wl - list of the words use
 */
Ngrams::Ngrams(int ngramSz, WordList & wl)
{
   this->ngramSz = ngramSz;
   first = NULL;
   wl.beginIter();
   while (!wl.endIter())
   {
      std::string ngram = wl.getNextNgram(ngramSz);
      wl.incrementIter();
      if (!ngram.empty()) insertNgram(ngram);
   }
}

/*
 * Ngrams destructor
 *
 * automatically called when Ngrams object goes out of scope
 * deletes the linked list
 */
Ngrams::~Ngrams()
{
   Ngram_t * nextNgram;
   while (first != NULL)
   {
      nextNgram = first->next;
      delete(first);  
      first = nextNgram;
   }
}

/*
 * insertNgram
 *
 * looks for the ngram to be inserted. If it is already in
 * the linked list,  it increments the count. If not, it 
 * inserts it into the linked list.
 *
 * param: std::string s - ngram to be inserted
 * return: none
 */
void Ngrams::insertNgram(std::string s)
{
   Ngram_t * ptr = first;
   Ngram_t * newNode = new Ngram_t();
   //delete(newNode);
   newNode->ngram = s;
   newNode->count = 1;

   while (ptr != NULL)
   {
      //s already in list
      if (ptr->ngram == s) 
      {
         ptr->count++;
         delete(newNode);
         return;
      }
      ptr = ptr->next;
      //delete(newNode);
   }
   //insert in front of list
   newNode->next = first;
   first = newNode;
   //delete(newNode);
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
   Ngram_t * ptr = first;
   Ngram_t * ptr1;
   Ngram_t * ptr2;
   int tcount;
   bool switchNodes;
   std::string tngram;

   while (ptr != NULL)
   {
      ptr1 = first; 
      ptr2 = ptr1->next;
      while (ptr2 != NULL) 
      {
         switchNodes = (reverse == true && ptr2->count > ptr1->count) ||
                       (reverse == false && ptr2->count < ptr1->count);
         if (switchNodes)
         {
            tcount = ptr1->count;
            tngram = ptr1->ngram;
            ptr1->count = ptr2->count;
            ptr1->ngram = ptr2->ngram; 
            ptr2->count = tcount;
            ptr2->ngram = tngram;
         }
         ptr1 = ptr2; 
         ptr2 = ptr2->next;
      }
      ptr = ptr->next;
   }
}

/*
 * printIncreasing
 *
 * prints the list of ngrams in increasing order
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
   Ngrams::Ngram_t * ptr = first;
   while (ptr != NULL)
   {
      std::cout << ptr->ngram << ", " << ptr->count << std::endl;
      ptr = ptr->next;
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
   printList();
}
