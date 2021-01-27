
#include <iostream>
#include <stdlib.h>
#include <stddef.h>
#include <cstring>
#include "field.h"
#include "string.h"
#include "input.h"

int main(int argc, char **argv) {

    /*making sure the arguments are legal*/
    if (check_args(argc, argv)){
        return -1;
    }

    /*getting the rule from the user*/
    String rule(argv[1]);

    /*translating the rule for the program*/
    Field parsing_field(rule);
    parsing_field.set_value(rule);

    /*check if the packet fits the rule*/
    parse_input(parsing_field);

    return 0;
}


