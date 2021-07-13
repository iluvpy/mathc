#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define CSTR_SIZE_ sizeof(cstr)
#define CSTR_PTR_SIZE sizeof(cstr*)
typedef struct cstr 
{
    size_t size; // characters
    char *str;
    bool free_str; // if string needs to be freed on deletion of cstr
} cstr;

// manipulators


// appends src to dest
void append_str(cstr *dest, char *src);
// appends src to dest
void append_cstr(cstr *dest, cstr *src);

// removes char at index
void cstr_remove(cstr *str, size_t index);
// delets all occurencies of c in str
void cstr_delc(cstr *str, char c);

// frees s
void del_cstr(cstr *s); 

// frees the underlying char * of s
// when free_str is true
void free_cstr_str(cstr *s);

// getters

// creates a cstr from an allocated char *
// deallocates the used char * when needed
// instead of just overwriting it
cstr *cstr_from_allocstr(char *src);

// returns the char * of s
char *getstr(cstr *s);

// change cstr value to new value
// uses get_cstr to create new cstr
cstr *getnew_cstr(cstr *cs, char *src);
cstr *allocnew_cstr(cstr *cs, char *src);
cstr *get_cstr(char *src);
cstr *allocate_cstr(char *src);
// returns copy of src
cstr *cstr_cpy(cstr *src);

// adds 2 cstrings together creating a new one
cstr *add_cstr(cstr *x, cstr *y);
// returns the sum of ascii values 
int str_sum(char *s);
// returns the sum of ascii values 
int cstr_sum(cstr *s);

// other
void stdout_cstr(cstr *s, bool endl);

bool cstr_eq_str(cstr *cs, char *s);


