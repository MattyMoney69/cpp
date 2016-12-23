
#include <cstring>
#include <typeinfo>
#include <iostream>
#include "file.h"


using namespace std;

File::File(const char *nam, Permissions per)
{
  name = new char[strlen(nam) + 1];
  strcpy(name, nam);

  permissions = per;

} // File constructor


File::File(const File &rhs)
{
  permissions = rhs.permissions;
  name = new char[strlen(rhs.name) + 1];
  strcpy(name, rhs.name);
} // File copy constructor


File::File()
{
  name = NULL;
} // File()


File::~File()
{
  delete [] name;
} // File destructor


void File::changeName(const char *newName)
{
  delete [] name;
  name = new char[strlen(newName) + 1];
  strcpy(name, newName);
}


Permissions File::getPermissions()
{
  return permissions;
} // getPermissions()


void File::ls(bool isLongFormat) const
{
  if (isLongFormat){
    permissions.print();
    cout << ' ';
    time.print();
    cout << name << endl;
  }  // print long format

  else
  {
    cout << name << ' ';
  }  // short ls

} // ls()


void File::updateTime()
{
  time.update();
} // updateTime()


bool File::setPermissions(short newPermissions, char *user)
{
  if (permissions.isPermitted(-1, user))
  {
    permissions.chmod(newPermissions, user);
    return true;
  }
  else
    return false;
} // setPermissions()


void File::read(istream &is)
{
  is >> name >> time >> permissions;
  // cout << name << ' ' << time << ' ' << permissions << endl;
}  // read() from directories.txt


void File::write(ostream &os) const
{
  os << 'F' << ' ' << name << ' ' << time << ' ' << permissions << ' ' << endl;
}  // write() to directories.txt


bool File::operator== (const File &rhs) const
{
  return strcmp(name, rhs.name) == 0;
}  // operator==


bool File::operator< (const File &rhs) const
{
  return strcmp(name, rhs.name) < 0;
}  // operator<


ostream &operator<<(ostream &os, const File &rhs)
{
  rhs.write(os);
  return os;
}  // operator<<


istream &operator>>(istream &is, File &rhs)
{
  cout << typeid(rhs).name() << endl;
  rhs.read(is);
  return is;
} // operator<<













