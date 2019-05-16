#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARGC_ERROR 1
#define TOOMANYFILES_ERROR 2
#define CONFLICTING_OUTPUT_OPTIONS 3

#define MAXSTRINGS 1024
#define MAXPARAS 4096

#define HASHLEN 200
#define BUFLEN 256

// ================================================================ //

/*
    TODO: check line by line in a pagraph, using '|' for differences");
    TODO: this starter code does not yet handle printing all of fin1's pagraphs.");
    TODO: handle the rest of diff's options");
    TODO: fix standard printing with no pameters");
    TODO: implement multiple types of pameters\n");
*/

// ================================================================= //

FILE *fin1, *fin2;
const char* files[2] = { NULL, NULL };

char buf[BUFLEN];
char *strings1[MAXSTRINGS], *strings2[MAXSTRINGS];

int showversion = 0, showbrief = 0, ignorecase = 0, report_identical = 0, showsidebyside = 0;
int showleftcolumn = 0, showunified = 0, showcontext = 0, suppresscommon = 0, diffnormal = 0;
int showhelp = 0, foundmatch = 0;

int equal = 0, cnt = 0, count = 0;

int count1 = 0, count2 = 0;

// ================================================================ //

void init(int argc, const char* argv[]);
void setoption(const char* arg, const char* s, const char* t, int* value);
void diff_output_conflict_error(void);

void loadfiles(const char* filename1, const char* filename2);

void version();
void help();

int normal(const char* filename1, const char* filename2);
int sideside(const char* filename1, const char* filename2);
void quiet(const char* filename1, const char* filename2);
void loud(const char* filename1, const char* filename2);

void identical(const char* filename1, const char* filename2);
