#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"

Field::Field(String pattern){

    this->pattern = pattern;
    /*IP or PORT*/
    this->type = this->get_type();
}

Field::~Field(){

}

field_type Field::get_type() const{
	/*check if the rule applies to IP or PORT*/
    size_t size_val;
    String *chunks;

    this->pattern.split("=", &chunks, &size_val);

    if ((chunks[0].trim()).equals("src-ip") || (chunks[0].trim()).equals("dst-ip")){
        delete[] chunks;
        return IP;
    } else {
        delete[] chunks;
        return PORT;
    }
}

bool Field::set_value(String val){
    /*should be done in Port/Ip*/
	return false;
}

bool Field::match_value(String val) const {
	/*should be done in Port/Ip*/
	return false;
}

bool Field::match(String packet) {

    String trimmed_packet(packet);

    size_t rule_size;
    String* rule_chunk;

    /*find the argument type the rule applies to*/
    this->pattern.split("=", &rule_chunk, &rule_size);
    String rule_id(rule_chunk[0].trim());
    delete[] rule_chunk;

    size_t packet_size;
    String* packet_chunk;

    /*find the exact argument type the rule applies to*/
    trimmed_packet.split(",", &packet_chunk, &packet_size);

    int required_string = -1;

    for (size_t i = 0; i < packet_size; i = i + 1){

        String *val_chunk;
        size_t val_size;

        (packet_chunk[i].trim()).split("=", &val_chunk, &val_size);

        if ((val_chunk[0].trim()).equals(rule_id)){

            required_string = (int)i;

        }
        delete[] val_chunk;
    }
    /*in case none exists*/
    if (required_string == -1){
        return false;
    }

    /*match the rule with the correct argument*/
    String input(packet_chunk[required_string].trim());

    delete[] packet_chunk;

    if (this->type == IP){
        Ip my_ip(this->pattern);
        my_ip.set_value(this->pattern);
        return	my_ip.match_value(input);
    } else if (this->type == PORT){
        Port my_port(this->pattern);
        my_port.set_value(this->pattern);
        return	my_port.match_value(input);
    }
    return false;
}

