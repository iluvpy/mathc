#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "cstr.h"

// manipulators

// appends src to dest
void cstr_append(cstr *dest, char *src) {
    if (dest != NULL && src != NULL) {
        dest->size += strlen(src);
        if (dest->free_str) {dest->str = realloc(dest->str, dest->size);}
		else {dest->str = malloc(dest->size);}
        strcat(dest->str, src);
        dest->free_str = true;
    }
}

// appends src to dest
void cstr_appendcs(cstr *dest, cstr *src) {
    if (dest != NULL && src != NULL) {
        cstr_append(dest, src->str);
    }
}

void cstr_appendc(cstr *dest, char c) {
	dest->size++;
	if (dest->free_str) {
		dest->str = realloc(dest->str, dest->size);
	}
	else {
		dest->str = malloc(dest->size);
	}

	strncat(dest->str, &c, 1);
}

// removes char at index
void cstr_remove(cstr *s, size_t index) {
    if (s != NULL) {
		memmove(&(s->str[index]), &(s->str[index+1]), s->size - index);
		s->size--;
    }
}

// delets all occurencies of c in str
void cstr_delc(cstr *s, char c) {
	size_t occurencies = 0;
	char *str = s->str;
	size_t len = strlen(str);
	for (int i = 0; i < len; i++) {
		if (str[i] == c) occurencies++;
	}
	char *new_str = malloc(len-occurencies+1);
	int i = 0;
	int j = 0;
	while (new_str[i] != '\0') {
		if (str[j] != c) {
			new_str[i] = c;
			i++;
		}
		j++;
	}
	free_cstr_str(s);
	s->str = new_str;
	s->free_str = true;
}

// deletes whole cstring and not only the string pointer
void del_cstr(cstr *s) {
    if (s != NULL) {
        free_cstr_str(s);
        free(s); 
        s = NULL;
    }
}

// frees the underlying char * of s
// when free_str is true
void free_cstr_str(cstr *s) {
    if (s != NULL) {
       if (s->free_str && s->str != NULL) {
            free(s->str);
            s->free_str = false;
        }
    }
}



// getters


// returns the char * of s
char *cstr_str(cstr *s) {
    if (s != NULL) {
        return (s->str != NULL) ? s->str : NULL;
    }
	return NULL;
}

// returns char at index or null if index is invalid 
char cstr_getc(cstr *s, size_t index) {
	if (index >= 0 && index < s->size && s != NULL) {
		return s->str[index];
	}
	return '\0';
}

// returns number of chars in cstr (without including null termination)
size_t cstr_len(cstr *s) {
	return s->size-1;
}
// return number of chars including null termination
size_t cstr_size(cstr *s) {
	return s->size;
}

// creates a cstr from an allocated char *
// deallocates the used char * when needed instead of just overwriting it
cstr *cstr_from_allocstr(char *src) {
    if (src == NULL) {return NULL;}
    cstr *cs = malloc(CSTR_SIZE_);
	cs->size = strlen(src)+1;
	cs->str = src;
	cs->free_str = true;
    return cs;
}   


// generates a new cstr from a char *
cstr *get_cstr(char *src) {
    cstr *s = malloc(CSTR_SIZE_);
    s->size = strlen(src)+1;
    s->str = malloc(s->size);
    strcpy(s->str, src);
    s->free_str = true;
    return s;  
}


// adds 2 cstrings together creating a new one
cstr *add_cstr(cstr *x, cstr *y) {
    if (x != NULL && y != NULL) {
        char res[x->size+x->size];
        strcpy(res, x->str);
        strcat(res, y->str);
        return get_cstr(res); 
    }

    return NULL;
}

// returns copy of src
cstr *cstr_cpy(cstr *src) {
	if (src != NULL) {
		char *cpy = malloc(src->size+1);
		strcpy(cpy, src->str);
		return cstr_from_allocstr(cpy);
	}
	return NULL;
}



int str_sum(char *s) {
    size_t sum = 0;
    for (int i = 0; i < strlen(s); i++) {
        sum += s[i];
    }
    return sum;
}

// returns the sum of ascii values 
int cstr_sum(cstr *s) {
    return str_sum(s->str);
}

size_t cstr_last(cstr *s) {
	return s->size-1;
}



bool cstr_eq_str(cstr *cs, char *s) {
    return (cstr_sum(cs) - str_sum(s) == 0);
}

bool cstr_is_in(cstr *cs, char c) {
	for (int i = 0; i < cs->size; i++) {
		if (cstr_getc(cs, i) == c) {return true;}
	}
	return false;
}

// returns int of cstr if is int and 0 if not int
int cstr_toi(cstr *str) {
	return atoi(str->str);
}

float cstr_tof(cstr *str) {
	return atof(str->str);
}