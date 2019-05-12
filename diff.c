#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "diff.h"
#include "pa.h"

// ================================================================ //

void init(int argc, const char* argv[]);
void setoption(const char* arg, const char* s, const char* t, int* value);
void diff_output_conflict_error(void);

void loadfiles(const char* filename1, const char* filename2);

void version();
void todo();

int normal(const char* filename1, const char* filename2);
int sideside(const char* filename1, const char* filename2);
void quiet(const char* filename1, const char* filename2);
void loud(const char* filename1, const char* filename2);

// ================================================================ //

int main(int argc, const char* argv[]) {

  init(--argc, ++argv);
  loadfiles(files[0], files[1]);

  if (**argv != '-')      { normal(files[0], files[1]); }
  if (argc < 3)           { printf("Usage: ./diff [options] file1 file2\n"); }

  //if (!diffnormal)         { normal(files[0], files[1]); printf("\n"); }
  if (showsidebyside)     { sideside(files[0], files[1]); }
  if (showbrief)          { quiet(files[0], files[1]); }
  if (report_identical)   { loud(files[0], files[1]); }
  if (!showversion && !showbrief && !ignorecase && !report_identical &&
      !diffnormal && !showsidebyside && !showleftcolumn && !suppresscommon &&
      !showcontext && !showunified && !showhelp) { printf("Usage: ./diff [options] file1 file2\n"); }
  return 0;

}

// ================================================================ //

void init(int argc, const char* argv[]) {

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
  // printf("\n     _ _  __  __                            \n");
  // printf("  __| (_)/ _|/ _|      _ __ ___ _ __ ___    \n");
  // printf(" / _` | | |_| |_ _____| '__/ __| '_ ` _ \\   \n");
  // printf("| (_| | |  _|  _|_____| | | (__| | | | | |  \n");
  // printf(" \\__,_|_|_| |_|       |_|  \\___|_| |_| |_|  \n\n");
  printf("\n\n       ██ ██   ████   ████                                     \n");
  printf("      ░██░░   ░██░   ░██░                                        \n");
  printf("      ░██ ██ ██████ ██████        ██████  █████  ██████████     \n");
  printf("   ██████░██░░░██░ ░░░██░  █████░ ░██░░█ ██░░░██░░██░░██░░██   \n");
  printf("  ██░░░██░██  ░██    ░██  ░░░░░   ░██ ░ ░██  ░░  ░██ ░██ ░██    \n");
  printf(" ░██  ░██░██  ░██    ░██          ░██   ░██   ██ ░██ ░██ ░██     \n");
  printf(" ░░██████░██  ░██    ░██         ░███   ░░█████  ███ ░██ ░██    \n");
  printf("  ░░░░░░ ░░   ░░     ░░          ░░░     ░░░░░  ░░░  ░░  ░░      \n\n");
  printf("\n");
  printf("\tv0.5 alpha | Smoking is bad for your health.\n\n");
  printf("Copyright (C) 2019 | All Rights Reserved.\n");
  printf("Any unauthorized use or re-distribution of this code is permitted.\n\n");
  printf("\tChris Nutter\tWilliam McCarthy     Rasputin\n\n\n");
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
int sideside(const char* filename1, const char* filename2) {

  if (pa_equal(p, q)) { pa_print(p, printboth); return 0; }
  pa_print(q, printright);
  while ((q = pa_next(q)) != NULL && !equal) { equal = pa_equal(p, q); pa_print(q, equal ? printboth : printright); }
  pa_print((p = pa_next(p)), printleft);

  return 0;
}
void quiet(const char* filename1, const char* filename2) { if (pa_equal(p, q) == 0) { printf("The files are not the same.\n"); } }
void loud(const char* filename1, const char* filename2) {

  if (pa_equal(p, q) != 0) { printf("The files are equal.\n"); }
  else { normal(files[0], files[1]); }

}

// ================================================================ //
