
#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include "string.h"


String::String():
        data(0), length((size_t)NULL) {
}


String::String(const String &str) {
    char *new_data = new char[strlen(str.data)+1];
    strcpy(new_data,str.data);
    new_data[strlen(str.data)] = '\0';
    this->data = new_data;
    this->length = str.length;
}


String::String(const char *str){

    char *new_data = new char[strlen(str)+1];

    strcpy(new_data,str);
    new_data[strlen(str)] = '\0';

    this->data = new_data;
    this->length = strlen(str);
}

String::~String(){
    delete[] this->data;
}

String& String::operator=(const String &rhs){

    char *new_data = new char[strlen(rhs.data)+1];

    strcpy(new_data,rhs.data);
    new_data[strlen(rhs.data)] = '\0';

    delete[] this->data;

    this->data = new_data;
    this->length = rhs.length;
    return *this;
}

String& String::operator=(const char *str){

    char *new_data = new char[strlen(str)+1];

    strcpy(new_data,str);
    new_data[strlen(str)] = '\0';

    delete[] this->data;

    this->data = new_data;
    this->length = strlen(str);
    return *this;
}

bool String::equals(const String &rhs) const{
    return (!strcmp((const char*)(this->data),
           (const char*)(rhs.data)) && this->length == rhs.length);
}

bool String::equals(const char *str) const{
    return !strcmp((const char*)(this->data),(const char*)str);
}


int String::to_integer() const {
    return atoi(this->data);
}

void String::split(const char *delimiters, String **output, size_t *size)
                   const {

    *size = 0;
    String temp(*this);
    char* split;

    split = strtok(temp.data,delimiters);

    /*counting number of splits*/
    while (split) {
       *size = *size + 1;
        split = strtok(NULL,delimiters);
    }

    if(*size == 0){
        *output = NULL;
        return;
    }
    if(output == NULL){
        return;
    }

    *output = new String[*size];

    String temp_1(*this);

    /*splitting*/
    split = strtok(temp_1.data,delimiters);
    int chunk = 0;
    while (split) {
        (*output)[chunk] = split;
        chunk++;
        split = strtok(NULL,delimiters);
    }
    delete[] split;
    return;
}


String String::trim() const {


    String to_trim(*this);

    int start = 0;
    int end = length - 1;

    /*getting the start and the end of the text*/
    while(to_trim.data[start] == ' ') {
        start++;
    }

    if(start == (int)(this->length)){
        return to_trim;
    }

    String trimmed;

    while (to_trim.data[end] == ' '){
        end--;
    }

    to_trim.data[end +1] = '\0';

    trimmed = &(to_trim.data[start]);

    return trimmed;

}



