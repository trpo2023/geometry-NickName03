#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "informer.h"
#include "lexer.h"

enum Errors;

void delete_space(char* inputed_string);
void str_to_lower(char* inputed_string);
int parser(FILE* file);