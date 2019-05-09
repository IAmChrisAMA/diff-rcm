#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARGC_ERROR 1
#define BUFLEN 256
#define MAXSTRINGS 1024

#define HASHLEN 256

typedef struct pa pa;
struct pa {
  char** base;
  int filesize;
  int start;
  int stop;
};

FILE *fin1, *fin2;

int count1 = 0, count2 = 0, equal = 0;
char buf[BUFLEN];
char *strings1[MAXSTRINGS], *strings2[MAXSTRINGS];

pa* p;
pa* q;
