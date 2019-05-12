#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "diff.h"

// ========================================================================== //

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
//char* yesorno(int condition);

void init(int argc, const char* argv[]);
void setoption(const char* arg, const char* s, const char* t, int* value);
void diff_output_conflict_error(void);

void loadfiles(const char* filename1, const char* filename2);

void version();
void todo();

void quiet(const char* argv[]);
void loud(const char* argv[]);
int sideside(const char* argv[]);
int normal(const char* filename1, const char* filename2);

// ================================================================= //

int main(int argc, const char* argv[]) {

  init(--argc, ++argv);
  loadfiles(files[0], files[1]);
  if (!showcontext && !showunified && !showsidebyside && !showleftcolumn) { normal(files[0], files[1]); }

  return 0;
}

// =============================================================== //

void init(int argc, const char* argv[]) {
  int count = 0;
  const char* files[2] = { NULL, NULL };

  while (argc-- > 0) {
    const char* arg = *argv;

    setoption(arg, "-v",                        "--version",                  &showversion);
    setoption(arg, "-q",                        "--brief",                    &showbrief);
    setoption(arg, "-i",                        "--ignore-case",              &ignorecase);
    setoption(arg, "-s",                        "--report-identical-files",   &report_identical);
    setoption(arg, "--normal",                  NULL,                         &diffnormal);
    setoption(arg, "-y",                        "--side-by-side",             &showsidebyside);
    setoption(arg, "--left-column",             NULL,                         &showleftcolumn);
    setoption(arg, "--suppress-common-lines",   NULL,                         &suppresscommon);
    setoption(arg, "-c",                        "--context",                  &showcontext);
    setoption(arg, "-u",                        "showunified",                &showunified);
    setoption(arg, "-h",                        "--help",                     &showhelp);

    if (arg[0] != '-') {
      if (cnt == 2) {
        fprintf(stderr, "apologies, this version of diff only handles two files\n");
        fprintf(stderr, "Usage: ./diff [options] file1 file2\n");
        exit(TOOMANYFILES_ERROR);
      } else { files[cnt++] = arg; }
    }
    ++argv;
  }

  if (showversion)                                       { version();  exit(0); }

  if (!showcontext && !showunified &&
      !showsidebyside && !showleftcolumn)                { diffnormal = 1; }

  if (((showsidebyside || showleftcolumn) &&
        (diffnormal || showcontext || showunified)) ||
        (showcontext && showunified) || (diffnormal &&
        (showcontext || showunified)))                   { diff_output_conflict_error(); }
}

void setoption(const char* arg, const char* s, const char* t, int* value) {
  if ((strcmp(arg, s) == 0) || ((t != NULL && strcmp(arg, t) == 0))) { *value = 1; }
}
void diff_output_conflict_error(void) {

  fprintf(stderr, "diff: conflicting output style options\n");
  fprintf(stderr, "diff: Try `diff --help' for more information.)\n");
  exit(CONFLICTING_OUTPUT_OPTIONS);

}

void loadfiles(const char* filename1, const char* filename2) {
  memset(buf, 0, sizeof(buf));
  memset(strings1, 0, sizeof(strings1));
  memset(strings2, 0, sizeof(strings2));

  FILE *fin1 = openfile(filename1, "r");
  FILE *fin2 = openfile(filename2, "r");

  while (!feof(fin1) && fgets(buf, BUFLEN, fin1) != NULL) { strings1[count1++] = strdup(buf); }  fclose(fin1);
  while (!feof(fin2) && fgets(buf, BUFLEN, fin2) != NULL) { strings2[count2++] = strdup(buf); }  fclose(fin2);

  p = pa_first(strings1, count1);
  q = pa_first(strings2, count2);

  int foundmatch = 0;
}

void version() {
  printf("\n     _ _  __  __                            \n");
  printf("  __| (_)/ _|/ _|      _ __ ___ _ __ ___    \n");
  printf(" / _` | | |_| |_ _____| '__/ __| '_ ` _ \\   \n");
  printf("| (_| | |  _|  _|_____| | | (__| | | | | |  \n");
  printf(" \\__,_|_|_| |_|       |_|  \\___|_| |_| |_|  \n\n");
  printf("------------------------------------------\n\n");
  printf("v0.4 alpha | Quoth the anti-Raven. Alwaysmore.\n\n");
  printf("Copyright (C) 2019 | All Rights Reserved.\n");
  printf("Any unauthorized use or re-distribution (before May 19, 2019) of this code is STRICTLY prohibited.\n\n");
  printf("Written by: Chris Nutter; William McCarthy; Rasputin\n\n");
}
void todo() {
  printf("\nTODO: check line by line in a pagraph, using '|' for differences");
  printf("\nTODO: this starter code does not yet handle printing all of fin1's pagraphs.");
  printf("\nTODO: handle the rest of diff's options");
  printf("\nTODO: fix standard printing with no pameters");
  printf("\nTODO: implement multiple types of pameters\n");
}

int normal(const char* filename1, const char* filename2) {

  printf("\nTHIS IS NOT NORMAL FOR NOW. THIS IS PLACEHOLDER. MMKAY.\n");
  printf("THIS IS NOT NORMAL FOR NOW. THIS IS PLACEHOLDER. MMKAY.\n\n\n");

  pa_print(p, printleft);
  pa_print(q, printright);

  printf("\nTHIS IS NOT NORMAL FOR NOW. THIS IS PLACEHOLDER. MMKAY.\n");
  printf("THIS IS NOT NORMAL FOR NOW. THIS IS PLACEHOLDER. MMKAY.\n\n\n");

  return 0;
}
int sideside(const char* argv[]) {

  if (pa_equal(p, q)) { pa_print(p, printboth); return 0; }
  pa_print(q, printright);
  while ((q = pa_next(q)) != NULL && !equal) { equal = pa_equal(p, q); pa_print(q, equal ? printboth : printright); }
  pa_print((p = pa_next(p)), printleft);

  return 0;
}
void quiet(const char* argv[]) { if (pa_equal(p, q) == 0) { printf("The files are not equal.\n"); } }
void loud(const char* argv[]) { if (pa_equal(p, q) == 1) { printf("The files are equal.\n"); } }

int hash(const char* s) {
    unsigned long code = 0;
    while (*s != '\0') { code = code *31 + *s++; }
    return code % HASHLEN;
}

// ====================================================== //

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
//char* yesorno(int condition) { return condition == 0 ? "no" : "YES"; }
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
