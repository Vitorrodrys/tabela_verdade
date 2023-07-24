//
// Created by vitor on 22/07/23.
//

#include "validations.h"

bool verify_token(char *operation, char token, char end_token){
    int count = 0;
    while (*operation){
        if(*operation == token){
            count++;
        }else if(*operation == end_token){
            count--;
        }
        if(count < 0){
            return false;
        }
        operation++;
    }
    return count == 0;
}

bool verify_token_after(char *operation, char what_token, int (*is_function) (int), int (*segundary_function)(int)){


    for(operation; *operation; operation++){
        if(*operation == what_token){
            if(not is_function(*(operation+1))){
                if(not segundary_function or not segundary_function(*(operation+1)))
                    return  false;
            }
        }
    }
    return true;
}


