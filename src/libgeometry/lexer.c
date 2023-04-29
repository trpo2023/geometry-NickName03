#include <ctype.h>
#include <string.h>

#include <informer.h>

enum Errors {
    ER_NOT_NUMBER,
};

struct Circle {
    int id;
    float x, y, radius, perimetr, square;
};

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