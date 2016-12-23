
#ifndef PERMISSION_H
#define PERMISSION_H

typedef struct Per 
{
  short octal; // the octal format permission for the user
} Permission; // Permssion datastructure

Permission *initPermission(short octal);

char *toString(int oct);

#endif
