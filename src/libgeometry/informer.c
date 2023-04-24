#include <stdio.h>
#include <stdlib.h>

enum Errors {
    ER_NAME,
    ER_NOT_NUMBER,
    ER_NOT_PARENTHESIS_LEFT, // круглая скобка
    ER_NOT_PARENTHESIS_RIGHT,
    ER_NOT_BRACE_LEFT, //фигурная скобка
    ER_NOT_BRACE_RIGHT,
    ER_EXP_COMMA,
    ER_EXP_SPACE,
};

int print_error(int pos, int err)
{
    pos += 1;
    switch (err) {
    case ER_NAME:
        printf("\e[1;31mError\e[0m at column 1: \e[1;31mexpected 'circle' or "
               "'triangle' or 'poligon'\e[0m\n");
        break;
    case ER_NOT_NUMBER:
        printf("\e[1;31mError\e[0m at column %d: \e[1;31mexpected "
               "Number\e[0m\n",
               pos);
        break;
    case ER_NOT_PARENTHESIS_LEFT:
        printf("\e[1;31mError\e[0m at column %d: \e[1;31mexpected '('\e[0m\n",
               pos);
        break;
    case ER_NOT_PARENTHESIS_RIGHT:
        printf("\e[1;31mError\e[0m at column %d: \e[1;31mexpected ')'\e[0m\n",
               pos);
        break;
    case ER_NOT_BRACE_LEFT:
        printf("\e[1;31mError\e[0m at column %d: \e[1;31mexpected '{'\e[0m\n",
               pos);
        break;
    case ER_NOT_BRACE_RIGHT:
        printf("\e[1;31mError\e[0m at column %d: \e[1;31mexpected '}'\e[0m\n",
               pos);
        break;
    case ER_EXP_COMMA:
        printf("\e[1;31mError\e[0m at column %d: \e[1;31mexpected ','\e[0m\n",
               pos);
        break;
    case ER_EXP_SPACE:
        printf("\e[1;31mError\e[0m at column %d: \e[1;31mexpected SPACE "
               "between "
               "points\e[0m\n",
               pos);
        break;
    }
    return 1;
}