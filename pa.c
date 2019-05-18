#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pa.h"

// ======================================================================= //

pa* pa_make(char* base[], int filesize, int start, int stop) {
    
    pa* p = (pa*)malloc(sizeof(pa));
    
    p->base = base;
    p->filesize = filesize;
    p->start = start;
    p->stop = stop;
    p->firstline = (p == NULL || start < 0) ? NULL : p->base[start];
    p->secondline = (p == NULL || start < 0 || filesize < 2) ? NULL : p->base[start + 1];
    
    return p;
    
}

pa* pa_next(pa* p) {
    
    int i;
    
    if (p->stop == p->filesize) { return NULL; }
    pa* pnew = pa_make(p->base, p->filesize, p->stop + 1, p->stop + 1);
    
    for (i = pnew->start; i < p->filesize && strcmp(p->base[i], "\n") != 0; ++i);
    pnew->stop = i;
    if (pnew->start >= p->filesize) { free(pnew); pnew = NULL; }
    
    return pnew;
    
}

pa* pa_first(char* base[], int size) {
    
    pa* p = pa_make(base, size, 0, -1);
    return pa_next(p);
    
}

void pa_destroy(pa* p)    { free(p); }

size_t pa_filesize(pa* p) { return p == NULL ? 0 : p->filesize; }
size_t pa_size(pa* p)     { return p == NULL || p->stop < p->start ? 0 : p->stop - p->start + 1; }
char** pa_base(pa* p)     { return p->base; }

char* pa_info(pa* p) {
    
    static char buf[BUFLEN];
    snprintf(buf, sizeof(buf), "base: %p, filesize: %d, start: %d, stop: %d\n", p->base, p->filesize, p->start, p->stop);
    return buf;
    
}

int pa_equal(pa* p, pa* q) {
    
    if (p == NULL || q == NULL)   { return 0; }
    if (pa_size(p) != pa_size(q)) { return 0; }
    if(p->start >= p->filesize || q->start >= q->filesize) { return 0; }
    
    int i = p->start, j = q->start, equal = 0;
    while ((equal = strcmp(p->base[i], q->base[i])) == 0) { ++i; ++j; }
    
    return 1;
    
}

// ======================================================================================================= //

void sideside_type(const char* left, const char* right, int nocommon, int leftparen, char symbol) {
    
    char buf[BUFLEN];
    
    symbol = ((strcmp(left, right) == 0) ? symbol : '|');
    size_t len = strlen(left);
    
    if(len > 0) { strncpy(buf, left, len); }
    buf[len - 1] = '\0';
    
    if(symbol != '|' && nocommon == 1) { return; }
    
    printf("%-48s %c ", buf, symbol);
    if (symbol == '|') { printf("%s", right); }
    else               { printf("%s", (leftparen ? "\n" : right)); }
    
}

// ======================================================================================================= //

void print_left_paren(const char* left, const char* right)  { sideside_type(left, right, 0, 1, '('); }
void print_no_common(const char* left, const char* right)   { sideside_type(left, right, 1, 0, ' '); }
void print_side_normal(const char* left, const char* right) { sideside_type(left, right, 0, 0, ' '); }

FILE* openfile(const char* filename, const char* openflags) {
    
    FILE* f;
    if ((f = fopen(filename, openflags)) == NULL) {  printf("can't open '%s'\n", filename);  exit(1); }
    return f;
    
}

void print_left(const char* left, const char* n) {
    
    char buf[BUFLEN];
    strcpy(buf, left);
    
    int j = 0, len = (int)strlen(buf) - 1;
    for (j = 0; j <= 48 - len ; ++j) { buf[len + j] = ' '; }
    
    buf[len + j++] = '<';
    buf[len + j++] = '\0';
    
    printf("%s\n", buf);
    
}

void print_right(const char* right, const char* _) {
    
    if (right == NULL) { return; }
    printf("%50s %s", ">", right);
    
}

void print_both(const char* left_right, const char* _) {
    
    char buf[BUFLEN];
    size_t len = strlen(left_right);
    
    if (len > 0) { strncpy(buf, left_right, len); }
    
    buf[len - 1] = '\0';
    printf("%-50s %s", buf, left_right);
    
}

void print_check(pa* p, pa* q, void (*fp)(const char*, const char*)) {
    
    if (q == NULL) { print_first(p, (void (*)(const char*)) fp); }
    else           { print_second(p, q, fp); }
    
}

void print_first(pa* p, void (*fp)(const char*)) {
    
    if (p == NULL) { return; }
    for (int i = p->start; i <= p->stop && i != p->filesize; ++i) { fp(p->base[i]); }
    
}

void print_second(pa* p, pa* q, void (*fp)(const char*, const char*)) {
    
    if(p == NULL || q == NULL) { return; }
    for(int i = p->start, j = q->start;
        i <= p->stop && i != p->filesize &&
        j <= q->stop && j != q->filesize; ++i, ++j) {
        fp(p->base[i], q->base[j]);
    }
    
}
