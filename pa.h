#ifndef pa_h
#define pa_h

#include <stdio.h>
#include <stdlib.h>

#define MAXSTRINGS 1024
#define BUFLEN 256

typedef struct pa pa;
struct pa {
  char** base;
  int filesize;
  int start;
  int stop;
};

pa* p;
pa* q;

pa* pa_make(char* base[], int size, int start, int stop);
pa* pa_first(char* base[], int size);
pa* pa_next(pa* p);
size_t pa_filesize(pa* p);
size_t pa_size(pa* p);
char** pa_base(pa* p);
char* pa_info(pa* p);
int   pa_equal(pa* p, pa* q);
void pa_print(pa* p, void (*fp)(const char*));
void printboth(const char* left_right);
void printleft(const char* left);
void printright(const char* right);
FILE* openfile(const char* filename, const char* openflags);
char* yesorno(int condition);

#endif
