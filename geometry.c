#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 50

struct Circle {
    int id;
    float x, y, radius, perimetr, square;
};

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

int check_number(char* number, int pos)
{
    int dot_flag = 0;
    for (int i = 0; i < strlen(number); i++) {
        if (number[i] == '.')
            dot_flag++;
        if (dot_flag > 1
            || (isdigit(number[i]) == 0 && number[i] != '.'
                && number[i] != ' ')) {
            print_error(pos + i, ER_NOT_NUMBER);
            return 1;
        }
    }
    return 0;
}

int write_struct(struct Circle* circle, char* inputed_string)
{
    char* cont = NULL;
    char* str_x = strtok_r(inputed_string, "(", &cont);
    str_x = strtok_r(NULL, " ", &cont);
    char* str_y = strtok_r(NULL, ",", &cont);
    char* str_r = strtok_r(NULL, ")", &cont);
    int pos = strlen(inputed_string) + 1;
    if (check_number(str_x, pos) == 1)
        return 1;
    if (check_number(str_y, pos + strlen(str_x)) == 1)
        return 1;
    if (check_number(str_r, pos + strlen(str_x) + strlen(str_y) + 1) == 1)
        return 1;
    circle->x = atof(str_x);
    circle->y = atof(str_y);
    circle->radius = atof(str_r);
    circle->perimetr = 2 * 3.1415 * circle->radius;
    circle->square = 2 * 3.1415 * circle->radius * circle->radius;
    return 0;
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