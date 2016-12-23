// Author: Sean Davis

#include <iostream>
#include <cstring>
#include <iomanip>
#include "permissions.h"

using namespace std;

short Permissions::umask = 022;


Permissions::Permissions() : owner(NULL)
{

} // default constructor


Permissions::Permissions(const short perm, const char* owne)
{
  if(owne)
  {
    delete [] owner;
    owner = new char[strlen(owne) + 1];
    strcpy(owner, owne);
  }
  else
    owner = NULL;
  permissions = perm & ~umask;
}  // Permissions()


Permissions::Permissions(const Permissions &rhs) : permissions(rhs.permissions)
{
  if (rhs.owner)
  {
    owner = new char[strlen(rhs.owner) + 1];
    strcpy(owner, rhs.owner);
  }
  else
    owner = NULL;
}  // Permissions copy constructor


Permissions::~Permissions()
{
  if (owner)
    delete [] owner;
} // ~Permissions()


short Permissions::checkOctals(const char *octals)
{
  short newPermissions = 0;
    
  if (strlen(octals) > 4)
    return -1;
  
  for (int i = 0; octals[i] != '\0'; i++ )
    if (octals[i] < '0' || octals[i] > '7')
      return -1;
    else  // valid octal digit
      newPermissions = newPermissions * 8 + octals[i] - '0';
  return newPermissions;
}  // checkOctals())


bool Permissions::chmod(short newPermissions, const char *user)
{
  if (strcmp(user, owner) != 0)  // user is not owner
  {
    cout << "chmod: Permission denied\n";
	return false;
  } // user is not owner
  permissions = newPermissions;
  return true;
}  // chmod())


void Permissions::chown(const char *newOwner)
{
  if (owner)
    delete [] owner;
    
  owner = new char[strlen(newOwner) + 1];
  strcpy(owner, newOwner);
}  // chown()


bool Permissions::isPermitted(short testedPermission, const char *user) const
{
  if (strcmp(owner, user) == 0 )
  {
    if (testedPermission > 0) // purely cheking ownership
      return ((permissions  >> 6) & testedPermission) == testedPermission;
    else
      return true;
  }   // user is owner
  else  // not owner
    return  (permissions & testedPermission) == testedPermission;
}  // isPermitted()


void Permissions::readUmask(istream &is)
{
  is >> umask;
  is.ignore(10, '\n');
}  // read()

void Permissions::set(short originalPermissions, const char *user)
{
  permissions = originalPermissions & ~umask;
  
  if (owner)
    delete [] owner;
  
  if (user)
  {
    owner = new char[strlen(user) + 1];
    strcpy(owner, user);
  }  // if user not NULL 
}  // set())


void Permissions::print() const
{
  for (int i = 6; i >= 0 ; i -= 3)
  {
    if ((permissions >> i) & 4)
      cout << "r";
    else  // no read permissions
      cout << "-";

    if ((permissions >> i) & 2)
      cout << "w";
    else  // no write permissions
      cout << "-";

    if ((permissions >> i) & 1)
      cout << "x";
    else  // no execute permissions
      cout << "-";
  }  // for each set of rwx permissions
  
  cout << " " << setw(8) << owner;
}  // print()


void Permissions::setUmask(int argCount, const char *arguments[])
  // checks "umask" command and executes it if it is proper
{
  short newUmask = 0;
  
  if (argCount == 1)
  {
    cout << oct << umask << dec << endl;
    return;
  }  // if only "umask" on commandline
  
  if (argCount != 2)
  {
    cout << "umask: Too many arguments.\n";
    return;
  }  // if more than 2 arguments
  
  
  if (strlen(arguments[1]) > 3)
  {
    cout << "umask: Improper mask.\n";
    return;
  }  // if umask value too long.
  
  for (int i = 0; arguments[1][i] != '\0'; i++ )
  {
    if (arguments[1][i] < '0' || arguments[1][i] > '7')
    {
      cout << "umask: Improper mask.\n";
      return;
    }  // if incorrect octal
    else  // valid octal digit
      newUmask = newUmask * 8 + arguments[1][i] - '0';
  }   // for each digit in argument
  
  umask = newUmask;
}  // umask()


void Permissions::writeUmask(ostream &os)
{
  os <<  umask << endl;
}  // read()



ostream& operator<< (ostream &os, const Permissions &permissions)
{
  os << permissions.permissions << ' ' << permissions.owner;
  return os;
}  // operator<<


istream& operator>> (istream &is, Permissions &permissions)
{
  char temp[80];
  is >> permissions.permissions  >> temp;
  permissions.owner = new char[strlen(temp) + 1];
  strcpy(permissions.owner, temp);
  return is;
}  // operator>>
