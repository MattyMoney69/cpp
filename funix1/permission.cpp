
#include "permission.h"
#include <stdio.h>
#include <stdlib.h>

Permission *initPermission(short octal)
{
  Permission *per = (Permission*) malloc(sizeof(Permission));
  per->octal = octal;
  return per;
} // initializes a permission struct

char *toString(int oct)
{
  char *rwx = (char*) malloc(sizeof(char) * 3); 
  
  switch (oct) 
  {
    case 0: 
      rwx = (char*) "rwx"; 
      break; 
    case 1: 
      rwx = (char*) "rw-"; 
      break; 
    case 2:
      rwx = (char*) "r-x"; 
      break; 
    case 3: 
      rwx = (char*) "r--"; 
      break; 
    case 4: 
      rwx = (char*) "-wx"; 
      break; 
    case 5: 
      rwx = (char*) "-w-"; 
      break; 
    case 6: 
      rwx = (char*) "--x"; 
      break; 
    case 7: 
      rwx = (char*) "---"; 
      break; 
  } // analyzes oct for what permission it gives

  return rwx; 
} // toString of a Permission in the form of rwx permissions

