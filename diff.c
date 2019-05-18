#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "diff.h"
#include "pa.h"

// ================================================================ //

int main(int argc, const char* argv[]) {

  init(--argc, ++argv);
  loadfiles(files[0], files[1]);

  if (**argv != '-' || diffnormal == 1)      { standard(files[0], files[1]); }

  if (showsidebyside)     { sideside(files[0], files[1]); }
  if (showbrief)          { quiet(files[0], files[1]); }
  if (report_identical)   { loud(files[0], files[1]); }

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
    setoption(arg, "--help",                    NULL,                         &showhelp);

    if (arg[0] != '-') {
      if (cnt == 2) {
        fprintf(stderr, "Usage: ./diff [options] file1 file2\n");
        exit(TOOMANYFILES_ERROR);
      } else { files[cnt++] = arg; }
    }
    ++argv;
  }

  // ================================= //

  if (showversion)                                       { version();  exit(0); }
  if (showhelp)                                          { help();     exit(0); }

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

  fprintf(stderr, "diff-rcm: Conflicting output style options.\n");
  fprintf(stderr, "diff-rcm: Try `diff --help' for more information.)\n");
  exit(CONFLICTING_OUTPUT_OPTIONS);

}

void loadfiles(const char* filename1, const char* filename2) {

  if (filename2 == NULL) { printf("Usage: ./diff [options] file1 file2\n"); exit(1); }

  memset(buf, 0, sizeof(buf));
  memset(strings1, 0, sizeof(strings1));
  memset(strings2, 0, sizeof(strings2));

  FILE *fin1 = openfile(filename1, "r");
  FILE *fin2 = openfile(filename2, "r");

  while (!feof(fin1) && fgets(buf, BUFLEN, fin1) != NULL) { strings1[count1++] = strdup(buf); }  fclose(fin1);
  while (!feof(fin2) && fgets(buf, BUFLEN, fin2) != NULL) { strings2[count2++] = strdup(buf); }  fclose(fin2);

  p = pa_first(strings1, count1);
  q = pa_first(strings2, count2);

}

void version() {
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
  printf("\tChris Nutter\tWilliam McCarthy    Rasputin\n\n\n");
}
void help() {
  printf("\nUsage: diff-rcm [OPTION]... FILES\n");
  printf("Compare FILES line by line.\n\n");
  printf("Mandatory arguments to long options are mandatory for short options too.\n\n");
  printf("\t    --standard\t\t        output a standard diff (the default)\n");
  printf("\t-q, --brief\t\t        report only when files differ\n");
  printf("\t-s, --report-identical-files    report when two files are the same\n");
  printf("\t-c, -C NUM, --context[=NUM]     output NUM (default 3) lines of copied context\n");
  printf("\t-u, -U NUM, --unified[=NUM]     output NUM (default 3) lines of unified context\n");
  printf("\t-y, --side-by-side\t        output in two columns\n\n");
  printf("\t-i, --ignore-case\t        ignore case differences in file contents\n\n");
  printf("\t    --help\t\t        display this help and exit\n");
  printf("\t-v, --version\t\t        output version information and exit\n\n");

  printf("FILES are 'FILE1 FILE2'\n");
  printf("If --from-file or --to-file is given, there are no restrictions on FILE(s).\n");
  printf("If a FILE is '-', read standard input.\n");
  printf("Exit status is 0 if inputs are the same, 1 if different, 2 if trouble.\n\n");
  printf("Report bugs to: cdnutter@gmail.com\n");
  printf("diff-rcm homepage: <https://www.github.com/cdnutter/diff/>\n\n");
}

int standard(const char* filename1, const char* filename2) {

  identical(filename1, filename2);

  printf("\nTHIS IS NOT standard FOR NOW. THIS IS PLACEHOLDER. MMKAY.\n");
  printf("THIS IS NOT standard FOR NOW. THIS IS PLACEHOLDER. MMKAY.\n");
  printf("THIS IS NOT standard FOR NOW. THIS IS PLACEHOLDER. MMKAY.\n");
  printf("THIS IS NOT standard FOR NOW. THIS IS PLACEHOLDER. MMKAY.\n\n");

    //pa* qlast = q;

  return 0;
}

int sideside(const char* filename1, const char* filename2) {
    
    pa* qlast = q;
    
    while(p != NULL) {
        
        qlast = q;
        foundmatch = 0;
        
        while (q != NULL && (foundmatch = pa_equal(p, q)) == 0) { q = pa_next(q); }
        q = qlast;
        
        if (foundmatch) {
            while ((foundmatch = pa_equal(p, q)) == 0) {
                pa_print(q, NULL, printright);
                q = pa_next(q);
                qlast = q;
            }
            
            if      (showleftcolumn) { pa_print(p, q, printnocommon); }
            else if (suppresscommon) { pa_print(p, q, printleftparen); }
            else                     { pa_print(p, q, printboth); }
            
            p = pa_next(p);
            q = pa_next(q);
        }
        
        else { pa_print(p, NULL, printleft);  p = pa_next(p); }
    }
    
    while(q != NULL) { pa_print(q, NULL, printright);  q = pa_next(q); }
    
    return 0;
    
}

void quiet(const char* filename1, const char* filename2) { if (pa_equal(p, q) == 0) { printf("The files are not the same.\n"); } else { return; } }
void loud(const char* filename1, const char* filename2) {

  if (*filename1 == *filename2 || (pa_equal(p, q) != 0)) { printf("The files are identical.\n"); }
  else { standard(files[0], files[1]); }

}

void identical(const char* filename1, const char* filename2) { if (*filename1 == *filename2) { exit(0); } else return; }
