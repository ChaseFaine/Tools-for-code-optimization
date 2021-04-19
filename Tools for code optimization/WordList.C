
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include "WordList.h"

/*
 * WordList
 * constructor has no work to do
 */
WordList::WordList() { }

/*
 * beginIter
 * Initialize a private iterator to use to go through the WordList.
 *
 * return: none
 */
void WordList::beginIter() 
{
   lstIter = wl.begin();
}

/*
 * endIter
 * Returns true if the private iterator has reach the end of the WordList.
 *
 * return: none
 */
bool WordList::endIter()
{
    return lstIter == wl.end();
}

/*
 * incrementIter
 * Increment the private iterator to point to the next word in the WordList.
 *
 * return: none
 */
void WordList::incrementIter() 
{
   lstIter++;
}

/*
 * getWord
 * Return the word pointed to by the private iterator.
 *
 * return: string within the WordList
 */
std::string WordList::getWord() 
{
   return (*lstIter);
}

/*
 * getNextNgram
 * Get the next ngram of size ngramSz starting from the current location
 * of the private iterator. Also increments the private iterator.
 *
 * param: size of the ngram to build and return
 * return: string that is an ngram or "" if no ngram starting from the
 *         point of the private iterator 
 *
 */
std::string WordList::getNextNgram(int ngramSz)
{
   int i, len;
   std::string ngram = "";
   std::vector<std::string>::iterator startI = lstIter;
   std::vector<std::string>::iterator endI = wl.end();
   for (i = 0; i < ngramSz && startI != endI; i++)
   {
      std::string word = (*startI);
      //see if the string ends with punctuation
      //don't create ngrams that continue after punctuation
      if (!isalpha(word[word.length()-1]) && i < ngramSz - 1) return "";
      
      //take off all ending punctuation
      len = word.length() - 1;
      while (len >= 0 && !isalpha(word[len]))
      {
         //remove last character
         word = word.substr(0, word.length() - 1);
         len--;
      }
      if (len < 0) return "";  //give up

      //is the first word in the ngram?
      if (ngram == "") ngram = word;
      else ngram = ngram + " " + word;
 
      startI++;
   }

   if (i < ngramSz) return "";

   //take off beginning punctuation
   while (ngram.length() > 0 && !isalpha(ngram[0]))
      ngram = ngram.substr(1, ngram.length());
   return ngram;
}

/*
 * addWord 
 *
 * lower case the alphabetic characters in the string
 * and add it to the WordListvector
 *
 * param: std:string s - string to add to vector
 * return: none
 */
void WordList::addWord(std::string s)
{
   int len = s.length();
   for (int i = 0; i < len; i++)
      if (isalpha(s[i])) s[i] = tolower(s[i]);
   wl.push_back(s);
}

/*
 * operator<<
 *
 * outputs the WordList vector to the output stream
 *
 * param: std::ostream & os - output stream
 * param: const WordList & ws - WordList vector
 * return: ostream & os - output stream
 */   
std::ostream& operator<<(std::ostream& os, WordList & wl)
{
   wl.beginIter();
   while (!wl.endIter())
   {
      std::cout << wl.getWord() << std::endl;
      wl.incrementIter();
   }
   return os;
}
