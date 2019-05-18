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
  char* firstline;   // DEBUG only
  char* secondline;
};

pa* p;
pa* q;

pa* pa_make(char* base[], int size, int start, int stop);
pa* pa_first(char* base[], int size);
pa* pa_next(pa* p);
void pa_destroy(pa* p);
size_t pa_filesize(pa* p);
size_t pa_size(pa* p);
char** pa_base(pa* p);
char* pa_info(pa* p);
int pa_equal(pa* p, pa* q);
void sideside_type(const char* left, const char* right, int nocommon, int leftparen, char symbol);
void print_first(pa* p, void (*fp)(const char*));
void print_second(pa* p, pa* q, void (*fp)(const char*, const char*));
void pa_print(pa* p, pa* q, void (*fp)(const char*, const char*));
void printleftparen(const char* left, const char* right);
void printnocommon(const char* left, const char* right);
void pa_printfile(char* base[], int count, void(*fp)(const char*, const char*));
char* yesorno(int condition);
FILE* openfile(const char* filename, const char* openflags);
void pa_printline(void);
void printleft(const char* left, const char*);
void printright(const char* right, const char*);
void printboth(const char* left_right, const char* n);

#endif
