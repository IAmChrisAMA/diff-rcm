#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pa.h"

// ======================================================================= //

pa* pa_make(char* base[], int filesize, int start, int stop) {
  pa* p = (pa*) malloc(sizeof(pa));
  p->base = base;
  p->filesize = filesize;
  p->start = start;
  p->stop = stop;

  return p;
}
pa* pa_first(char* base[], int size) {
  pa* p = pa_make(base, size, 0, -1);
  return pa_next(p);
}
pa* pa_next(pa* p) {
  if (p->stop == p->filesize) { return NULL; }

  int i;
  pa* pnew = pa_make(p->base, p->filesize, p->stop + 1, p->stop + 1);
  for (i = pnew->start; i < p->filesize && strcmp(p->base[i], "\n") != 0; ++i) { }
  pnew->stop = i;

  return pnew;
}

void pa_print(pa* p, void (*fp)(const char*)) {
  if (p == NULL) { return; }
  for (int i = p->start; i <= p->stop && i != p->filesize; ++i) { fp(p->base[i]); }
}
void pa_destroy(pa* p) { free(p); }
void printleft(const char* left) {
  char buf[BUFLEN];

  strcpy(buf, left);
  int j = 0, len = (int)strlen(buf) - 1;
  for (j = 0; j <= 48 - len ; ++j) { buf[len + j] = ' '; }
  buf[len + j++] = '<';
  buf[len + j++] = '\0';
  printf("%s\n", buf);
}
void printright(const char* right) {
  if (right == NULL) { return; }
  printf("%50s %s", ">", right);
}
void printboth(const char* left_right) {
  char buf[BUFLEN];
  size_t len = strlen(left_right);
  if (len > 0) { strncpy(buf, left_right, len); }
  buf[len - 1] = '\0';
  printf("%-50s %s", buf, left_right);
}

size_t pa_filesize(pa* p) { return p == NULL ? 0 : p->filesize; }
size_t pa_size(pa* p) { return p == NULL || p->stop < p->start ? 0 : p->stop - p->start + 1; }

char** pa_base(pa* p) { return p->base; }
char* yesorno(int condition) { return condition == 0 ? "no" : "YES"; }
char* pa_info(pa* p) {
  static char buf[BUFLEN];   // static for a reason
  snprintf(buf, sizeof(buf), "base: %p, filesize: %d, start: %d, stop: %d\n",
    p->base, p->filesize, p->start, p->stop);
  return buf;  // buf MUST be static
}

int pa_equal(pa* p, pa* q) {
  if (p == NULL || q == NULL) { return 0; }
  if (pa_size(p) != pa_size(q)) { return 0; }
  int i = p->start, j = q->start, equal = 0;
  while ((equal = strcmp(p->base[i], q->base[i])) == 0) { ++i; ++j; }
  return equal;
}

FILE* openfile(const char* filename, const char* openflags) {
  FILE* f;
  if ((f = fopen(filename, openflags)) == NULL) {  printf("can't open '%s'\n", filename);  exit(1); }
  return f;
}
