
#include <iostream>
#include <cstring>
#include "string.h"
#include "field.h"
#include "port.h"


Port::Port(String pattern):Field(pattern){
}

 bool Port::set_value(String val) {

    size_t size_val;
    String *chunks;

    val.split("-=", &chunks, &size_val);

    this->range[0] = (chunks[2].trim()).to_integer();
    this->range[1] = (chunks[3].trim()).to_integer();

    delete[] chunks;

    return true;
}

bool Port::match_value(String val) const{
    size_t size_val;
    String *chunks;

    val.split("=", &chunks, &size_val);

    if((chunks[1].trim()).to_integer() >= this->range[0] && (chunks[1].trim()).to_integer() <= this->range[1]){
        delete[] chunks;
        return true;
    } else {
        delete[] chunks;
        return false;
    }
}
