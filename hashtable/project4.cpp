#include <iostream>
#include <fstream>
#include "hashTable.h"
#include <string>
#include <time.h>
#include <ctime>

using namespace std;

int main(int argc, char* argv[])
{
  clock_t start, end;
  double duration;

  start = clock();

  ifstream input(argv[1]);

  string operation;
  string SSN;
  string firstName;
  string lastName;

  string insertion = "i";
  int insertionCount = 0;
  string deletion = "d";
  int deletionCount = 0;
  string retrieval = "r";
  int retrievalCount = 0;

  HashTable<string>* infoList = new HashTable<string>(10007);

  while(input >> operation >> SSN >> firstName >> lastName)
  {
    string name = firstName + " " + lastName;
    if(insertion.compare(operation) == 0)
    {
      if(infoList->insert(SSN, name))
      {
        insertionCount++;
      }
    }
    if(deletion.compare(operation) == 0)
    {
      if(infoList->erase(SSN))
      {
        deletionCount++;
      }
    }
    if(retrieval.compare(operation) == 0)
    {
      if(infoList->find(SSN))
      {
        retrievalCount++;
      } 
    }
  }
  input.close();

  cout << "The Number of Valid Insertion(s): " << insertionCount << endl;
  cout << "The Number of Valid Deletion(s): " << deletionCount << endl;
  cout << "The Number of Valid Retrieval(s): " << retrievalCount << endl;
  cout << "Item numbers in the list: " << (insertionCount-deletionCount) << endl;

  end = clock();
  duration = ( end - start ) / (double) CLOCKS_PER_SEC;

  cout << "Time Elapsed: " << duration << '\n';
}
