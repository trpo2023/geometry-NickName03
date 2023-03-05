#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 25

enum Errors {
    ER_NAME,       // название
    ER_NOT_POINT,  // вершина (центр у окружности)
    ER_NOT_NUMBER, // радиус у окружности
    ER_NOT_PARENTHESIS_LEFT, // круглая скобка
    ER_NOT_PARENTHESIS_RIGHT,
    ER_NOT_BRACE_LEFT, //фигурная скобка
    ER_NOT_BRACE_RIGHT,
    ER_EXP_COMMA,
};

void print_error(int pos, int err)
{
    pos += 1;
    switch (err) {
    case ER_NAME:
        printf("\e[1;31mError\e[0m at column 1: \e[1;31mexpected 'circle' or "
               "'triangle' or 'poligon'\e[0m\n");
        break;
    case ER_NOT_POINT:
        printf("\e[1;31mError\e[0m at column %d: \e[1;31mexpected Point\e[0m\n",
               pos);
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
    }
}

int parser(FILE* file)
{
    char figure[size];
    int position = 0;
    char sym;
    const char* mask = "circletrianglepolygon0123456789.,(){}";
    while ((sym = getc(file)) != EOF) {
        if (sym == 'q') {
            break;
        }
        if (sym == '\n') {
            if (figure[0] == 'c') {
                for (int i = 1; i < 14; i++) {
                    if (i < 6 && figure[i] != mask[i]) {
                        printf("\e[1;31mError\e[0m at column %d: "
                               "\e[1;31mexpected %c\e[0m\n",
                               i + 1,
                               mask[i]);
                        break;
                    }
                    if (i == 6 && figure[i] != '(') {
                        print_error(i, ER_NOT_BRACE_LEFT);
                        break;
                    }
                    if (i > 6 && i < 13 && i != 9 && i != 11
                        && strchr("0123456789", figure[i]) == NULL) {
                        print_error(i, ER_NOT_POINT);
                        break;
                    }
                    if (i == 9 && figure[i] != ',') {
                        print_error(i, ER_EXP_COMMA);
                        break;
                    }
                    if (i == 11 && figure[i] != '.') {
                        print_error(i, ER_NOT_NUMBER);
                        break;
                    }
                    if (i == 14 && figure[i] != ')') {
                        print_error(i, ER_NOT_BRACE_RIGHT);
                        break;
                    }
                }
            } else {
                if (figure[0] == 't') {
                    puts(figure);
                } else {
                    if (figure[0] == 'p') {
                        puts(figure);
                    } else {
                        print_error(0, ER_NAME);
                    }
                }
            }
            memset(&figure[0], 0, size);
            position = 0;
        }
        if (strchr(mask, tolower(sym)) != 0) {
            figure[position] = tolower(sym);
            position++;
        }
    }
    return 0;
}

int main(int argc, char* argv[])
{
    FILE* file = NULL;
    if (argc < 2) {
        parser(stdin);
    } else if (argc == 2) {
        if ((file = fopen(argv[1], "r")) == NULL) {
            printf("\e[1;31mError\e[0m: can't open file \e[1;35m\"%s\"\e[0m\n",
                   argv[1]);
            return 1;
        } else {
            parser(file);
            fclose(file);
        }
    } else {
        printf("\e[1;35mUsage\e[0m: %s <filename>\n", argv[0]);
    }
    return 0;
}