
#include <iostream>
#include "Time.h"
#include "permissions.h"
#include "list.h"

class File
{
  Time time;
protected:
  char *name;
  Permissions permissions;
public:
  File(const char *nam, const Permissions per = Permissions(0, NULL));
  File(const File &rhs);
  File();
  Permissions getPermissions();
  virtual ~File();
  void ls(bool isLongFormat) const;
  void changeName(const char *newName);
  void updateTime();
  virtual void read(istream &is);
  virtual void write(ostream &os) const; 
  bool setPermissions(short newPermissions, char *user);
  bool operator< (const File &rhs) const; 
  bool operator== (const File &rhs) const;
  friend istream& operator>> (istream&, File&);
  friend ostream& operator<< (ostream&, const File&);
}; // class File
