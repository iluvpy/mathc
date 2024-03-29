
/*
	NOTE: this file is just used for testing purposes and can be removed from the build file if needed
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "console.h"
#include "strvec.h"
#include "cstr.h"
#include "lexer.h"
#include "strvec.h"
#include "tokens.h"
#include "numbers.h"
#include "ast.h"
#include "debug.h"

void print_section(char *name);



int main(void) {
	print_section("test");
	
	print_section("finished test");
	return 0;
}

// prints ------- name -------
void print_section(char *name) {
	print_color(FgGreen, "------- ");
	print_color(FgGreen, "%s", name);
	print_color(FgGreen, " -------\n");
}