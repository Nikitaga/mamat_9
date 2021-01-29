
#include <iostream>
#include <stdlib.h>
#include <stddef.h>
#include <cstring>
#include "field.h"
#include "string.h"
#include "input.h"
#include "ip.h"
#include "port.h"

int main(int argc, char **argv) {

    /*making sure the arguments are legal*/
    if (check_args(argc, argv)){
        return -1;
    }

    /*getting the rule from the user*/
    String rule(argv[1]);


    Field parsing_field(rule);


    /*check if the packet fits the rule, different per type*/
    if (parsing_field.get_type() == IP){
    	Ip ip_rule(rule);
    	ip_rule.set_value(rule);
    	parse_input(ip_rule);
    } else if (parsing_field.get_type() == PORT){
    	Port port_rule(rule);
    	port_rule.set_value(rule);
    	parse_input(port_rule);
    }



    return -1;
}


