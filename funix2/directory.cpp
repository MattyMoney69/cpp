// Author: Sean Davis
#include <cstring>
#include <iostream>
#include "directory.h"

using namespace std;


Directory::Directory(const char *nam, Directory *paren, const char *owner)
  : subDirectoryCount(0) 
 {
  parent = paren;
  name = new char[strlen(nam) + 1];
  strcpy(name, nam);
  permissions.set(0777, owner);
 }  // Directory())


Directory::Directory(const Directory &rhs) : 
  subDirectoryCount(rhs.subDirectoryCount),  
  parent(rhs.parent)
{
  permissions = rhs.permissions;
  name = new char[strlen(rhs.name) + 1];
  strcpy(name, rhs.name);
  
  for (int i = 0; i < subDirectoryCount; i++)
  {
    Directory *directory = dynamic_cast<Directory*> (subDirectories[i]);
    if (directory)
      directory->parent = this;
  } // sets parent 

  if(rhs.subDirectoryCount)
  {
    for( int i = 0; i < rhs.subDirectoryCount; i++)
    // add each subDirectory to newly constructed list
      subDirectories += (File *) rhs.subDirectories[i];

  }  // if there are subDirectories in rhs

}  // Directory copy constructor


Directory* Directory::cd(int argCount, const char *arguments[], 
                         const char *user)
{
  if (argCount != 2)
  {
    cout << "usage: cd directoryName\n";
    return this;
  }  // if two many arguments

  if (strcmp(arguments[1], "..") == 0)
  {
    if (parent)
      return parent;
    else  // this is root
      return this;
  }  // if cd ..

  for (int i = 0; i < subDirectoryCount; i++)
  {
    Directory *directory = dynamic_cast<Directory*> (subDirectories[i]);
    
	if (!directory)
	{
        cout << arguments[1] << ": Not a directory.\n";
        return this;
    } // error if attempting to cd into a file
	  
    if (*directory == Directory(arguments[1]))
    {
      if (directory->getPermissions().isPermitted(EXECUTE_PERMISSIONS, user))
        return directory;

      else  // subdirectory doesn't have execute permissions
      {
        cout << arguments[1] << ": Permission denied.\n";
        return this;
      }   // else no execute permissions for the specified directory
    }  // if found the named directory 
  }  // for each subdirectory
 
  cout << "cd: " << arguments[1] << ": No such file or directory\n";
  return this;
}  // cd()


void Directory::chmod(int argCount, const char *arguments[], const char *user)
 // changes the permissions of the arguments
{
  if (argCount < 3)
  {
    if (argCount == 1)
      cout << "chmod: missing operand\n";
    else   // argCount == 2
      cout << "chmod: missing operand after ‘" << arguments[1] << "’\n";

    cout << "Try 'chmod --help' for more information.\n";
    return;
  }   // if wrong number of arguments
  
  short newPermissions = Permissions::checkOctals(arguments[1]);
  int j;
  
  if (newPermissions < 0)
  {
    cout << "chmod: invalid mode: ‘" << arguments[1] << "’\n";
    cout << "Try 'chmod --help' for more information.\n";
    return;
  }  // if invalid permissions
  
  for (int i = 2; i < argCount; i++)
  {
    for (j = 0; j < subDirectoryCount; j++)
      if (File(arguments[i]) == *subDirectories[j])
      {
	    Directory *dir = dynamic_cast<Directory*> (subDirectories[j]);
		if (!dir)
		// updates time if it is a file
		  subDirectories[j]->updateTime();
		  
        if (subDirectories[j]->setPermissions(newPermissions, (char*) user))
		// successfully changed permissions
          break;
        else
        {
          cout << "chmod: changing of '" << arguments[i] 
               << "': Operation not permitted" << endl;
          break;
        } // unsuccessfully set permissions

      } // if matched name of directory with argument
    
    if (j == subDirectoryCount)
      cout << "chmod: cannot access ‘" << arguments[i]
           << "’: No such file or directory\n";
  }  // for each filename

}  // chmod()


void Directory::chown(int argCount, const char *arguments[])
{
  int j;
  
  if (argCount != 3)
  {
    if (argCount == 1)
      cout << "chown: missing operand\n";
    else  // 2 or more than 3 arguments
      if (argCount == 2)
        cout << "chown: missing operand after ‘" << arguments[1] << "’\n";
      else  // more than 3 arguments
        cout << "chown: Too many arguments.\n";

    cout << "Try 'chown --help' for more information.\n";
    return;
  }  // if wrong number of arguments
  
  for (j = 0; j < subDirectoryCount; j++)
     if (Directory(arguments[2]) == *subDirectories[j])
      {
        subDirectories[j]->getPermissions().chown(arguments[1]);
        break;
      }  // if matched name of directory with argument
    
  if (j == subDirectoryCount)
    cout << "chown: cannot access ‘" << arguments[2] 
         << "’: No such file or directory\n";
}  // chown()


bool Directory:: iscpCorrectFormat(int argCount, const char *arguments[])
{
  if (argCount != 3)
  {
    if (argCount == 1)
      cout << "cp: missing file operand\n";
    else   // more than one argument, but not 3
      if (argCount == 2)
        cout << "cp: missing destination file operand after ‘" << arguments[1]
             << "’\n";
      else  // more than 3 arguments
        cout << "Too many operands\n";

    cout << "Try 'cp --help' for more information.\n";
    return false;
  }  // if incorrect number of operands

  if (strcmp(arguments[1], arguments[2]) == 0)
  {
    cout << "cp: ‘" << arguments[1] << "’ and ‘" << arguments[2]
      << "’ are the same file\n";
    return false;
  }  // if source and destination have the same name

  for (int i = 0; i < subDirectoryCount; i++)
    if (*subDirectories[i] == Directory(arguments[2]))
    {
      cout << "cp: '" << arguments[2] << "' already exists.\n";
      return false;
    }  // if the destination directory already exists

  return true;
}  //  iscpCorrectFormat()


void Directory::cp(int argCount, const char *arguments[], const char *user)
{
  if (!iscpCorrectFormat(argCount, arguments))
    return;
  for (int i = 0; i < subDirectoryCount; i++)
  {
    if (*subDirectories[i] == File(arguments[1]))
    {
      if (!subDirectories[i]->getPermissions().isPermitted(READ_PERMISSIONS, user ))
      {
        cout << "cp: cannot open ‘" << arguments[1] 
             << "’ for reading: Permission denied\n";
        return;
      }  // if not allowed to read
      
	  Directory *directory = dynamic_cast<Directory*> (subDirectories[i]);
	  
      if (directory)
      {
        Directory *destinationDirectory = new Directory(*directory);
        delete [] destinationDirectory->name;
        destinationDirectory->name = new char[strlen(arguments[2]) + 1];
        strcpy(destinationDirectory->name, arguments[2]);
        subDirectories += destinationDirectory;
        subDirectoryCount++;
        return;
      }  // if found source subdirectory

      else
      {
        File *file = new File(arguments[2], subDirectories[i]->getPermissions());
        subDirectories += file;
        subDirectoryCount++;
		return;
      } // not a directory

    } // file found

  } // loops through all potential elements

  cout << "cp: cannot stat ‘" << arguments[1] 
       << "’: No such file or directory\n";
  cout << "Try 'cp --help' for more information.\n";
}  // cp())


void Directory::ls(int argCount, const char *arguments[], const char *user)const
{
  if (argCount > 2 || (argCount == 2 && strcmp(arguments[1], "-l") != 0))
    cout << "usage: ls [-l]\n";
  else  // correct number of arguments
  {
    if (permissions.isPermitted(READ_PERMISSIONS, user))
    {
      if (argCount == 1)  // simple ls
      {
        for (int i = 0; i < subDirectoryCount; i++)
        {
          const Directory *directory = dynamic_cast<const Directory*> (subDirectories[i]);
          if (!directory)
            subDirectories[i]->ls(false);
          else
            cout << directory->name << " ";
        }   // ls
        cout << "\n";
      }  // if simple ls
      else  // must be ls -l
      {
        for (int i = 0; i < subDirectoryCount; i++)
        {
          const File *data = subDirectories[i];
          data->ls(true);
        } // prints stuff out 

       }  // if have read permissions

     } // has permissions
    
    else // don't have read permissions
      cout << "ls: cannot open directory .: Permission denied\n";
  }  // else correct arguments

}  // ls()


void Directory::mkdir(int argCount, const char *arguments[], const char *user)
{
  int i;
  
  if (argCount == 1)
  {
    cout << "mkdir: missing operand\n";
    cout << "Try 'mkdir --help' for more information.\n";
    return;
  }  // if too many arguments
   
  for (int argPos = 1; argPos < argCount; argPos++)
  {
    for (i = 0; i < subDirectoryCount; i++)
      if (*subDirectories[i] == Directory(arguments[argPos]))
      {
        cout << "mkdir: cannot create directory ‘" << arguments[argPos] 
             << "’: File exists\n"; 
        break;
      }  // if subdirectory already exists.
    
    if (i == subDirectoryCount)
    {
      if (permissions.isPermitted(WRITE_PERMISSIONS, user))
      {
        subDirectories += new Directory(arguments[argPos], this, user);
        subDirectoryCount++;
      }  // if have write permissions
      else // no write permissions
        cout << "mkdir: cannot create directory ‘" << arguments[argPos] 
             <<  "’: Permission denied\n";
    }  // if name not found

  }  // for each filename

}  // mkdir()


void Directory::touch(int argCount, const char *arguments[], const char *user)
{
  int i;
  if (argCount == 1)
  {
    cout << "touch: missing operand" << endl;
    cout << "Try 'touch --help' for more information" << endl;
  } // is not enough args
  
  for (int argPos = 1; argPos < argCount; argPos++)
  {
    for (i = 0; i <subDirectoryCount; i++)
    {
      if (*subDirectories[i] == File(arguments[argPos]))
      {
        cout << "touch: cannot create directory '" << arguments[argPos]
             << "': File exists" << endl;
        break;
      } // if the file already exists

    } // for each subdir
    
    if (i == subDirectoryCount)
    {
      if (permissions.isPermitted(WRITE_PERMISSIONS, user))
      {
        File *temp = new File(arguments[argPos], Permissions(0666, user));
        temp->updateTime();
        subDirectories += temp;
        subDirectoryCount++;
      } // if the user is give write permissiins
    } // if name is not found
  } // for each file name
} // touch()


void Directory::showPath() const
{
  if (parent == NULL)
  {
    cout << "/";
    return;
  }  // at root
  
  parent->showPath();
  cout << name << "/";
} // showPath())


void Directory::read(istream &is)
{
  
  File::read(is);
  is >> subDirectoryCount;
    
  for (int i = 0; i < subDirectoryCount; i++)
  {
    char type[2];
    is >> type;
    int isDir = 0;
    if (type[0] == 'D')
    isDir = 1;
    File *sub = NULL;
    if (isDir)
      sub = new Directory("dir", this);
    else 
      sub = new File("file");
    is >> *sub;
    subDirectories += sub;
  } // collects subdirs

}  // read() directory from file


void Directory::write(ostream &os) const
{
  os << 'D';
  File::write(os);
  os << subDirectoryCount << endl;
  for (int i = 0; i < subDirectoryCount; i++)
    os << *subDirectories[i];

}  // write() directory to file



















