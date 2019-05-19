#ifndef pa_h
#define pa_h

#include <stdio.h>
#include <stdlib.h>

#define MAXSTRINGS 1024
#define BUFLEN 256

// ================================================== //

typedef struct pa pa;
struct pa {
  char** base;
  int filesize;
  int start;
  int stop;
  char* firstline;   // DEBUG only
  char* secondline;
};

FILE* openfile(const char* filename, const char* openflags);

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

void print_check(pa* p, pa* q, void (*fp)(const char*, const char*));

void print_first (pa* p, void (*fp)(const char*));
void print_second(pa* p, pa* q, void (*fp)(const char*, const char*));

void print_left_paren (const char* left, const char* right);
void print_no_common  (const char* left, const char* right);
void print_side_normal(const char* left, const char* right);

void print_left (const char* left, const char*);
void print_right(const char* right, const char*);
void print_both (const char* left_right, const char*);

void print_normal_left (const char* left, const char*);
void print_normal_right(const char* right, const char*);
void print_normal_both (const char* left, const char* right, const char*);

void line_check(const char* right, const char*);
int  line_number(const char* left, const char* right);


#endif
