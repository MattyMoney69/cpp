#ifndef SONG_H
  #define SONG_H

#include <string>
#include <iostream>
using namespace std;

class Song
{
  string title;
  string artist;
  string album;
public:
  static int searchType;
  Song(string titl, string artis, string albu);
  Song(string element, int cmd);
  ~Song();
  bool isLessThan(Song &s, int t);
  void modify(Song &s);
  friend void swapSongs(Song &song1, Song& song2);
  friend bool isEqual(const Song &lhs, const Song &rhs, int comparisonType);
  friend ostream& operator<< (ostream &os, Song const &rhs); //write
  friend istream& operator>> (istream &is, Song &rhs); //read
}; //class Song
#endif
