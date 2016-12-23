
#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "permission.h"

#define MAX_SUBDIR 3

typedef struct Dir 
{
  int mod; 
  struct Dir *subDirectories[MAX_SUBDIR];  
  int subCount; 
  struct Dir *parent;
  char *name; 
  Permission *p; 
} Directory; // the directory data structure

void pwd(Directory *currentDirectory);

Directory *createDirectory(Directory *parent, Permission *p, int mod, 
                           char *name);

#endif
