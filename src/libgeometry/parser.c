#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "informer.h"
#include "lexer.h"
#define size 50

enum Errors {
    ER_NAME,
    ER_NOT_PARENTHESIS_LEFT, // круглая скобка
    ER_NOT_PARENTHESIS_RIGHT,
    ER_EXP_COMMA,
    ER_EXP_SPACE,
};

struct Circle {
    int id;
    float x, y, radius, perimetr, square;
};

int check_circle(char* inputed_string)
{
    const char* mask = "circle";
    int i = 0;
    while (inputed_string[i] != '(') {
        if (inputed_string[i] != mask[i]) {
            if (i <= strlen(mask) - 1) {
                printf("\e[1;31mError\e[0m at column %d: \e[1;31mexpected "
                       "%c\e[0m\n",
                       i + 1,
                       mask[i]);
                return 1;
            } else {
                if (inputed_string[i] != ' ') {
                    printf("\e[1;31mError\e[0m at column %d: \e[1;31mexpected "
                           "%c or "
                           "space\e[0m\n",
                           i + 1,
                           '(');
                    return 1;
                }
            }
        }
        i++;
    }
    // сейчас inputed_string[i] == '('
    i++; // теперь следущий символ
    int flag_for_space = 0;
    while (inputed_string[i] != ',') {
        if ((inputed_string[i - 1] != '(' && inputed_string[i] == ' ')
            && (inputed_string[i + 1] != ',' && inputed_string[i] == ' ')) {
            flag_for_space++;
        }
        if (flag_for_space > 1) {
            print_error(i, ER_EXP_COMMA);
            return 2;
        }
        i++;
    }
    if (flag_for_space == 0) {
        print_error(i - 4, ER_EXP_SPACE);
        return 3;
    }
    // сейчас inputed_string[i] == ','
    i++; // теперь следущий символ
    while (inputed_string[i] != ')') {
        if (i == strlen(inputed_string) - 1) {
            print_error(i + 1, ER_NOT_PARENTHESIS_RIGHT);
            return 5;
        }
        i++;
    }
    return 0;
}

void delete_space(char* inputed_string)
{
    int pos = 0;
    while (inputed_string[pos] != '\0') {
        if ((inputed_string[pos] == ' ' && inputed_string[pos + 1] == ' ')
            || (inputed_string[pos] == ' ' && inputed_string[pos - 1] == ' ')
            || (inputed_string[pos] == ' ' && inputed_string[pos - 1] == '(')) {
            for (int i = pos; i < strlen(inputed_string); i++) {
                inputed_string[i] = inputed_string[i + 1];
            }
            pos--;
        }
        pos++;
    }
    // удаление пробела в начале
    if (inputed_string[0] == ' ') {
        for (int i = 0; i < strlen(inputed_string); i++) {
            inputed_string[i] = inputed_string[i + 1];
        }
    }
}

void str_to_lower(char* inputed_string)
{
    delete_space(inputed_string);
    for (int i = 0; i < strlen(inputed_string) - 1; i++) {
        if (islower(inputed_string[i]) == 0)
            inputed_string[i] = tolower(inputed_string[i]);
    }
}

int parser(FILE* file)
{
    char figure[size];
    struct Circle circle[size];
    int counter_figure = 1;
    while (fgets(figure, size, file) != NULL && figure[0] != 'q') {
        str_to_lower(figure);
        puts(figure);
        if (figure[0] != 'c' || figure[0] != 'c' || figure[0] != 'c') {
            print_error(0, ER_NAME);
        }
        if (figure[0] == 'c') {
            if (check_circle(figure) == 0) {
                if (write_struct(&circle[counter_figure], figure) == 0) {
                    printf("Inputed!\n");
                    circle[counter_figure].id = counter_figure;
                    printf("P = %f\nS = %f\n",
                           circle[counter_figure].perimetr,
                           circle[counter_figure].square);
                    counter_figure++;
                }
            }
        }
        if (figure[0] == 't') {
            check_circle(figure);
        }
        if (figure[0] == 'p') {
            check_circle(figure);
        }
        memset(&figure[0], 0, strlen(figure));
    }
    return 10;
}