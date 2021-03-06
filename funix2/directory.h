#ifndef DIRECTORY_H
  #define DIRECTORY_H

#include <iostream>
#include "permissions.h"
#include "Time.h"
#include "list.h"
#include "file.h"

using namespace std;


class Directory: public File
{
  List<File> subDirectories;
  int subDirectoryCount;
  Directory *parent;
  bool iscpCorrectFormat(int argCount, const char *arguments[]);
public:
  Directory(const char *nam, Directory *paren = NULL, const char *owner = NULL);
  Directory(const Directory &rhs);
  Directory* cd(int argCount, const char *arguments[], const char *user);
  void chmod(int argCount, const char *arguments[], const char *user);
    // changes the permissions of the arguments
  void chown(int argCount, const char *arguments[]);
  void cp(int argCount, const char *arguments[], const char *user);
  void ls(int argCount, const char *arguments[], const char *user) const;
  void mkdir(int argCount, const char *arguments[], const char *user);
  void touch(int argCount, const char *arguments[], const char *user);
  void showPath() const;
  void read(istream &is);
  void write(ostream &os) const;
};  // class Directory
#endif  // DIRECTORY_H

