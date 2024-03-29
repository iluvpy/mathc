#pragma once
#include "stdio.h"
#include "stdarg.h"
#include "console.h"

/*
    DEBUG should be defined by the compiler flag -DDEBUG in the build file,
    remove it or run another build file if there is any that is flagged as the release build file
*/


#ifdef DEBUG
    #define DEBUG_MESSAGE_VAR(fmt, ...) \
        print_color(FgGreen, "DEBUG:\n");\
        printf("\t%s line: %d\n\tmessage: ", __FILE__, __LINE__);\
        printf(fmt, ##__VA_ARGS__);
    
    #define DEBUG_MESSAGE(string) \
        print_color(FgGreen, "DEBUG:\n");\
        printf("%s line: %d,\n\tmessage: %s", __FILE__, __LINE__, string);
    
    #define ON_DEBUG(code)  \
        code\
    
#else
    #define DEBUG_MESSAGE(string)
    #define DEBUG_MESSAGE_VAR(...)
    #define ON_DEBUG(code)
#endif

