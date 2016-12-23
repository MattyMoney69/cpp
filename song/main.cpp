// main.cpp

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include "song.h"

using namespace std;

void printPrompt()
{
  cout << "\nSong Menu\n0. Done.\n1. Search for Artist.\n";
  cout << "2. Search for Title.\n3. Search for Album.\n";
  cout << "4. Search for title phrase.\n";
} // printPrompt()

bool isType(int comparisonType)
{
  bool isOkay = comparisonType > 0 && comparisonType <= 4;

  if (isOkay)
  {
    cout << "Please enter the ";

    switch (comparisonType)
    {
      case (1) : cout << "artist's name: "; break;
      case (2) : cout << "title: "; break;
      case (3) : cout << "album: "; break;
      case (4) : cout << "phrase: "; break;
    } // checks 

  } // comment

  else // else
  {
    cout << "Your choice must be between 0 and 4." << endl 
         << "Please try again." << endl << endl;
  } // comment

  return isOkay;
} // comment

void sort(vector<Song> &son, int comparisonType)
{
  vector<Song>::iterator i, j;

  for (i = ++son.begin(); i != son.end(); ++i)
  {
    vector<Song>::iterator saveI = i;

    for (j = --saveI; j != son.begin() 
         && i->isLessThan(*j, comparisonType); --j)
    {
      swapSongs(*i, *j);
      --i;
    } // comment
    
    saveI++;

    if (j == son.begin() && i->isLessThan(*j, comparisonType))
      swapSongs(*i, *j);

    i = saveI;
  } // comment 

} //using iterators, and the string::swap()


void search(vector<Song> &son, int cmd, string query)
{
  vector<Song> found;

  for (vector<Song>::iterator it = son.begin(); it != son.end(); ++it)

    if (isEqual(*it, Song(query, cmd), cmd))
      found.push_back(*it);
  sort(found, cmd);

  for (vector<Song>::iterator it = found.begin(); it != found.end(); ++it)
    cout << *it;
  
} // comment


void run(vector<Song> &song)
{
  while (true)
  {
    printPrompt();
    cout << endl << "Your choice: ";
    int comparisonType;
    cin >> comparisonType;
    Song::searchType = comparisonType;

    if (comparisonType == 0)
      return;

    if (!isType(comparisonType))
      continue;
    string query;
    cin.ignore();
    getline(cin, query);
    search(song, comparisonType, query);
  } // loops prompt

} // comment

int main()
{ 
  //Reading in songs
  vector<Song> song;
  ifstream inf("songs.txt");

  if (inf)
  {
    string temp;

    while (inf.good())
    {
      Song *son = new Song("title", "artist", "album");
      inf >> *son;

      if (!isEqual(*son, Song("title", "artist", "album"), 0))
        song.push_back(*son);
    } // comment

    inf.close(); 
  } // If songs.txt exists. 
 
  run(song); 

  return 0;
} // comment

