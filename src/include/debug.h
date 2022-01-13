#pragma once
#include "stdio.h"
#include "stdarg.h"
#include "console.h"

/*
    DEBUG should be defined by the compiler flag -DDEBUG in the build file,
    remove it or run another build file if there is any that is flagged as the release build file
*/


#ifdef DEBUG
    #define DEBUG_MESSAGE_VAR(fmt, var, ...) \
        print_color(FgGreen, "DEBUG:\n");\
        printf("\t%s line: %d,\n\tvar name: %s,\n\tmessage: ", __FILE__, __LINE__, #var);\
        printf(fmt, var, ##__VA_ARGS__);
    
    #define DEBUG_MESSAGE(string) \
        print_color(FgGreen, "DEBUG:\n");\
        printf("%s line: %d,\n\tmessage: %s", __FILE__, __LINE__, string);
#else
    #define DEBUG_MESSAGE(string)
    #define DEBUG_MESSAGE_VAR(...)
#endif

