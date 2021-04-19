
/* You can add more to this header class declaration. For example,
 * you can add typedefs and data members for the data structure that you use. 
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
      Ngram * first;
      Ngram *table[SIZE];
      Ngram * arr[ARRSIZE];
      int counter[ARRSIZE];
      int ngramSz;
      void insertNgram(std::string s);
      void printList();
      void printListDecreasing();
   public:
      Ngrams(int ngramSz, WordList & wl);
      ~Ngrams();
      void sortByCount(bool reverse);
      void printIncreasing();
      void printDecreasing();
      //void createMap();
      int hash(std::string s);
};

