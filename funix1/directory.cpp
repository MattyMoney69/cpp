
#include "directory.h"
#include <stdlib.h>
#include <stdio.h>

void pwd(Directory *dir)
{
  if (dir->parent != NULL)
  {
    pwd(dir->parent);
    printf("%s", dir->name);
  } // checks if parent dir is null

  else // prints last "/" for the path name
    printf("/");
} // returns a char pointer with the current path name to dir

Directory *createDirectory(Directory *parent, Permission *p, 
                           int mod, char *name)
{
  Directory *newDirectory = (Directory*) malloc(sizeof(Directory));
  int i = 0;

  while (i < MAX_SUBDIR)
  {
    newDirectory->subDirectories[i] = 
    (struct Dir*) malloc(sizeof(struct Dir) * MAX_SUBDIR);
    newDirectory->subDirectories[i] = NULL;
    i++;
  } // creates memory for the subdirectories
 
  newDirectory->name = name; 
  newDirectory->mod = mod; 
  newDirectory->p = p; 
  newDirectory->parent = parent; 
  newDirectory->subCount = 0;  
  
  return newDirectory;
} // initiaslizes a Directory and returns the address

