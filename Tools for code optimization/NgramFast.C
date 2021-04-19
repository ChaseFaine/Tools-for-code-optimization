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

//need to do in order traversal to see if string (node.ngram) matches any nodes already created

/* 
insert (node)
{
   if(node.ngram == node.left.ngram) {
      node.left.count += 1;
      reorder();
   } 
}
*/
#include <iostream>
#include <string>
#include "WordList.h"
#include "NgramFast.h"

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
   for(int i = 0; i < SIZE; i++) {
      table[i] = NULL;
   }

   //This code to get the next ngram will stay the same. 
   this->ngramSz = ngramSz;
   wl.beginIter();
   while (!wl.endIter())
   {
      std::string ngram = wl.getNextNgram(ngramSz);
      wl.incrementIter();
      if (!ngram.empty()) insertNgram(ngram);
   }

   for(int i = 0; i < ARRSIZE; i++) {
      arr[i] = NULL;
   }
}

/*
 * Ngrams destructor
 *
 * automatically called when Ngrams object goes out of scope
 * should delete any space dynamically allocated for the ngram
 */
Ngrams::~Ngrams()
{
   Ngram * temp;
   Ngram * temp2;
   for(int i = 0; i < SIZE; i ++) {
      temp = table[i];
      while(temp != NULL) {
         temp2 = temp->next;
         delete(temp);
         temp = temp2;
      }
   }
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
void Ngrams::insertNgram(std::string s)
{
   //ADD code to insert ngram in whatever structure you choose
   int index = hash(s);
   Ngram * newNode = new Ngram();
   Ngram * node = new Ngram();
   delete(node);
   newNode->ngram = s;
   newNode->count = 1;
   newNode->next = NULL;
   newNode->sortedNext = NULL;
   bool done = false;
   
   if(table[index] == NULL) {
      table[index] = newNode;
   } else {
      node = table[index];
      while (node != NULL) {
         if (node->ngram == s) {
            node->count = node->count + 1;
            done = true;
            delete(newNode);
            break;
         }
         node = node->next;
      }
      if(!done) {
         newNode->next = table[index];
         table[index] = newNode;
      }
   }
}

/*
 * You can ADD any other methods that you need here.
*/

int Ngrams::hash(std::string s) {
   unsigned int hash = SIZE;
   char c = s[0];
   for(int i = 0; i < s.length(); i++) {
      hash += (((s[i] << 5) + s[i]) + s[i]);
   }
   return hash % SIZE;
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
      Ngram * temp;
      Ngram * temp2;
      for(int i = 0; i < SIZE; i++) {
         if(table[i] != NULL) {
            temp = table[i];
            while(temp != NULL) {
               if(arr[temp->count] != NULL) {
                  temp2 = arr[temp->count];
                  arr[temp->count] = temp;
                  temp->sortedNext = temp2;
                  temp = temp->next;
               } else {
                  arr[temp->count] = temp;
                  temp = temp->next;
               }
            }
         }
      }
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
   Ngram * temp = new Ngram();
   delete(temp);
   for(int i = 0; i < ARRSIZE; i++) {
      if(arr[i] != NULL) {
         temp = arr[i];
         while(temp != NULL) {
            std::cout << temp->ngram << ", " << temp->count << std::endl;
            temp = temp->sortedNext;
         }
      }
   }
}

void Ngrams::printListDecreasing() {
   Ngram * temp = new Ngram();
   delete(temp);
   for(int i = ARRSIZE-1; i >= 0; i--) {
      if(arr[i] != NULL) {
         temp = arr[i];
         while(temp != NULL) {
            std::cout << temp->ngram << ", " << temp->count << std::endl;
            temp = temp->sortedNext;
         }
      } else {
         continue;
      }
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
