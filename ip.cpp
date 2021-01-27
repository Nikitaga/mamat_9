#include <iostream>
#include <cstring>
#include "string.h"
#include "field.h"
#include "ip.h"

Ip::Ip(String pattern):Field(pattern){
	 this->high = 0;
	 this->low = 0;
}


bool Ip::set_value(String val) {

    size_t size_val;

    String *chunks;

    val.split("=./", &chunks, &size_val);

    int mask = (chunks[5].trim()).to_integer();

    unsigned int ip_holder = ((chunks[1].trim()).to_integer()<<24)|
                             ((chunks[2].trim()).to_integer()<<16)|
                             ((chunks[3].trim()).to_integer()<<8)|
                             ((chunks[4].trim()).to_integer());

    this->high = ip_holder;
    this->low = ip_holder;

    for (int i = 0; i < (32 - mask) ; i++){
        this->high |= (1u << i);
        this->low &= ~(1u << i);
    }
    delete[] chunks;

    return true;
}

bool Ip::match_value(String val) const{
    size_t size_val;
    String *chunks;
    val.split("=.", &chunks, &size_val);

    unsigned int ip_holder = ((chunks[1].trim()).to_integer()<<24)|
                             ((chunks[2].trim()).to_integer()<<16)|
                             ((chunks[3].trim()).to_integer()<<8)|
                             ((chunks[4].trim()).to_integer());

    if(ip_holder >= this->low && ip_holder <= this->high){
        delete[] chunks;
        return true;
    } else {
        delete[] chunks;
        return false;
    }
}
