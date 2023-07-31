//
// Created by vitor on 22/07/23.
//

#ifndef CALCULADORA_TABELA_VERDADE_VARS_MAP_TABLE_H
#define CALCULADORA_TABELA_VERDADE_VARS_MAP_TABLE_H

#include <map>
#include <string.h>
#include <vector>
#include <iostream>
class map_vars{
private:
    std::map<char, bool*> vars;
    int tamanho;
    int dist;
public:
    map_vars(int tamanho, char *operacao);
    ~map_vars();
    int include(char var);

    bool* operator[](char var){
        return this->vars[var];
    }

    void show_vars(){
        for(auto &key_value:this->vars){
            printf("%c:\n", key_value.first);
            for(int i = 0; i<this->tamanho; i++){
                printf(key_value.second[i]? "V":"F");
            }
            printf("\n");
        }
    }
};


#endif //CALCULADORA_TABELA_VERDADE_VARS_MAP_TABLE_H
