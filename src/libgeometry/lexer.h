#pragma once

#include <ctype.h>
#include <string.h>

struct Circle;

enum Errors;
int check_number(char* number, int pos);
int write_struct(struct Circle* circle, char* inputed_string);
