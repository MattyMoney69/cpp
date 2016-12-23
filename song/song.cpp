
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include "song.h"

using namespace std;

int Song::searchType = 1;


Song::Song(string titl, string artis, string albu):
           title(titl), artist(artis), album(albu)
{
  //cout << title;
} //Song constructor


Song::Song(string query, int cmd) 
{
  switch (cmd)
  {
    case 1 : artist = query; break;
    case 2 : title = query; break;
    case 3 : album = query; break;
    case 4 : title = query; break;
  } //comment
} //comment


Song::~Song()
{
  
} //Song destructor


bool Song::isLessThan(Song &rhs, int comparisonType)
{
  string compareLhs;
  string compareRhs;

  if (comparisonType == 1 || comparisonType == 4)
  {
    compareLhs = artist;
    compareRhs = rhs.artist;
  } //comment

  if (comparisonType == 2 || comparisonType == 3)
  {
    compareLhs = title;
    compareRhs = rhs.title;
  } //comment

  int cmp = compareLhs < compareRhs;
  return (cmp != 0);
  
} // compares songs


bool isEqual(const Song &lhs, const Song &rhs, int comparisonType)
{
  if (comparisonType == 4)
    return (lhs.title.find(rhs.title) + 1);
  
  if (comparisonType == 1)
    return !lhs.artist.compare(rhs.artist);
  
  if (comparisonType == 2)
    return !lhs.title.compare(rhs.title);
  
  if (comparisonType == 3)
    return !lhs.album.compare(rhs.album);
  
    return !lhs.artist.compare(rhs.artist);
} //comment

void Song::modify(Song &s)
{
  int ch = 1;

  for (string::iterator it = s.artist.begin(); it != s.artist.end(); ++it)
  {
    if (*it == 32)
    {
      ch = 1;
      it++;
    } // Checking for space.

    if (*it > 64 && *it < 91)
      if (!ch)
      {
        *it = *it + 32;
      } //If the letter is lowercase.

    ch = 0;
  } //modifying Artist name.

  int f = (s.title.find("A ") + 1);
  int t = (s.title.find("THE ") + 1);

  if (t == 1 || f == 1)
  {
    s.title = s.title.substr(s.title.find(" ") + 1, s.title.length());

    if (t)
      s.title += ", THE";
    else //else
      s.title += ", A";
  } //comment
} //comment


void swapSongs(Song &song1, Song& song2)
{
  song1.title.swap(song2.title);
  song1.artist.swap(song2.artist);
  song1.album.swap(song2.album);
} // swaps song data


ostream& operator<< (ostream &os, Song const &rhs)
{
  os << rhs.title << ":" << rhs.artist << ":" << rhs.album << endl;
  return os;
} //writes

istream& operator>> (istream &is, Song &rhs)
{
  string temp;

  if (!getline(is, temp))
    return is;

  rhs.title = temp.substr(0, temp.find("___"));
  temp = temp.substr(temp.find("___") + 3);
  rhs.artist = temp.substr(0, temp.find("___"));
  temp = temp.substr(temp.find("___") + 3);
  rhs.album = temp.substr(temp.find("___") + 3);
  rhs.modify(rhs);
  int f = (rhs.album.find("CD+G") + 1);

  if (f)
    rhs.album.erase(f - 2);

  return is;
} //reads

