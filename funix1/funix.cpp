
#include "funix.h"
#include "directory.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define COMMAND_LENGTH 80
#define NUM_COMMANDS 5

void cd(Funix *funix, int argCount, const char *arguments[])
{
  if (argCount == 2)
  {
    arguments[1] = strcat((char*) arguments[1], "/"); 
    Directory *c = funix->currentDirectory; 
    int i = 0;
    int b = 0;

    if (strcmp(arguments[1], "../") == 0 && strcmp(c->name, "/") != 0) 
    {
      funix->currentDirectory = c->parent;
      b = -1;
    } // checks for parent dir notation    
    
    while (i < MAX_SUBDIR && c->subDirectories[i] != NULL)
    {
      if (strcmp(c->subDirectories[i]->name, arguments[1]) == 0)
      {
        funix->currentDirectory = (Directory*) c->subDirectories[i]; 
        b = -1;
        break;
      } // if the directory is found 
 
      i++;
    }//transverses subdirs to find arg[1]
 
    if (strcmp(c->name, "/") == 0 && strcmp(arguments[1], "../") == 0)
      b = -1;
    
    if (b != -1)
      printf("cd: %s: No such file or directory\n", 
      strtok((char*) arguments[1], "/"));
  } // checks for the proper number of parameters
 
  else // priints error message if command in the wrong format
    printf("usage: cd directoryName\n");
} // moves the woking directory to the specified directory

int eXit(Funix *funix, int argCount, const char *arguments[])
{ 
  if (argCount == 1)
    return 0;
  else // returns 1 when exit has not been called correctly
    return 1;
} // checks "exit" command, returns 0 on proper exit

void getCommand(Funix *funix, char *command)
{
  writePrompt(funix); 
  
  fgets(command, COMMAND_LENGTH, stdin);
  command = strtok(command, "\n");
} // writes prompt and reads command

void init(Funix *funix)
{
  char *name = (char*) malloc(sizeof("/"));
  *name = '/'; 
  Permission *per;
  funix->umask = 0; 
  funix->time = 0; 
  per = initPermission(funix->umask);
  funix->currentDirectory = createDirectory(NULL, per, 0, name);
} // creates currentDirectory, and sets umask and time

void ls(Funix *funix, int argCount, const char *arguments[])
{
  if (argCount == 1)
  {
    Directory *c = funix->currentDirectory;
    int i = 0;
    
    while (i < MAX_SUBDIR && c->subDirectories[i] != NULL)
    { 
      printf("%s ", strtok(c->subDirectories[i]->name, "/"));
      strcat(c->subDirectories[i]->name, "/");
      i++;
    } // prints the contents of the surrent dir

    printf("\n");
  } // displays the directories on a single line

  else // argcount is not just 1
  if (strcmp(arguments[1], "-l") == 0 && argCount == 2) // if true 
  // prints the long format of ls
  {
    Directory *c = funix->currentDirectory;
    int i = 0;

    while (i < MAX_SUBDIR && c->subDirectories[i] != NULL)
    {
      printf("%s %d %s\n", toString(c->subDirectories[i]->p->octal), 
      c->subDirectories[i]->mod, strtok(c->subDirectories[i]->name, "/"));
      strcat(c->subDirectories[i]->name, "/");
      i++;
    } // prints long format
 
  } // checks if in long format
  
  else // prints proper usage of ls
    printf("usage: ls [-l]\n");
} // calls ls() with currentDirectory as one of its parameters

void mkdir(Funix *funix, int argCount, const char *arguments[])
{ 
  int b = 0;

  if (argCount == 2)
  {
    arguments[1] = strcat((char*) arguments[1], "/"); 
    Directory *c = funix->currentDirectory;
    int i = 0;
    
    while (i < MAX_SUBDIR && c->subDirectories[i] != NULL)
    {
      
      if (strcmp(c->subDirectories[i]->name, arguments[1]) == 0) 
        b = 1;
      i++;
    } // finds the first null location
 
    if (i < MAX_SUBDIR && !b)
    { 
      Permission *p = initPermission(funix->umask);
      c->subDirectories[i] = createDirectory(c, p, funix->time, 
      (char*) arguments[1]);
    } // checks if there can be more subdirectories
 
    else // there cant be more subdirs
    if (b == 0)
    {
      printf("mkdir: %s already contains the maximum number of directories\n", 
      c->name);
      b = 0;
    } // prints error message showing that the max has been hit
 
    else // checks if the name has already been taken
      printf("mkdir: cannot create directory '%s': File exists\n", 
      strtok((char*) arguments[1], "/")); 
  } // checks if the command is in the right format
 
  else // prints error message that comman is in the wrong format
    printf("usage: mkdir directory_name\n");

} // calls mkdir() with currentDirectory as one of its parameters

int processCommand(Funix *funix, char *command)
{ 
  char *arguments[2];
  int i = 0; 
  char *currentArg = strtok(command, " "); 
  
  for (i = 0; currentArg != NULL; i++)
  {
    arguments[i] = (char*) malloc(sizeof(*currentArg)); 
    strcpy(arguments[i], currentArg);
    currentArg = strtok(NULL, " "); 
  } // allocates memory for arguments and places args in proper address

  int argCount = i; 
  char *firstWord = arguments[0]; 

  if (strcmp(firstWord, "cd") == 0)
    cd(funix, argCount, (const char**) arguments); 

  else // not cd
  if (strcmp(firstWord, "ls") == 0)
    ls(funix, argCount, (const char**) arguments); 

  else // not ls or cd
  if (strcmp(firstWord, "umask") == 0)
    umask(funix, argCount, (const char**) arguments); 

  else // not umask ls or cd
  if (strcmp(firstWord, "mkdir") == 0)
    mkdir(funix, argCount, (const char**) arguments); 

  else // not mkdir umask ls or cd
  if (strcmp(firstWord, "exit") == 0)
    return eXit(funix, argCount, (const char**) arguments);
  
  else // not exit mkdir umask ls or cd
  if (strcmp((const char*) command, "\n") == 0)
    return 1;
  
  else // not anything
    printf("%s: Command not found.\n", firstWord); 
  
  return 1;
} // returns 0 on proper exit

void run(Funix *funix) 
{
  char command[COMMAND_LENGTH];
  init(funix);
  
  do 
  {
    getCommand(funix, command);
    funix->time++;
  } // runs the loop til the user exit the OS

  while (processCommand(funix, command) == 1);
} // reads and processes commands in a loop until proper exit

void umask(Funix *funix, int argCount, const char *arguments[])
{
  if (argCount == 2)
  {
    if (arguments[1][0] >= 48 && arguments[1][0] <= 55)
    {
      funix->umask = arguments[1][0] - 48; 
    } // checks if its the correct number range and assigns value

    else // prints proper usage
      printf("umask: octal must be between 0 and 7\n");
  } // checks if in the correct format

  else // prints the proper usage
    printf("usage: umask octal\n");
} // checks "umask" command and executes it if it is proper

void writePrompt(Funix *funix)
{
  pwd(funix->currentDirectory);
  printf(" # ");
} // shows path and '#'






















