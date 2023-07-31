//
// Created by vitor on 22/07/23.
//

#include "vars_map_table.h"


int map_vars::include(char var) {

    this->vars[var] = new bool[this->tamanho];

    bool var_init = true;

    if(isdigit(var)){
        char *tmp = new char[2];
        tmp[0] = var;
        tmp[1] = '\0';
        char *err = nullptr;
        for(int i = 0; i<this->tamanho; i++){
            this->vars[var][i] = strtol(tmp, &err, 10);
            if(*err != '\0'){
                printf("ERRO AO CONVERTER UM CARACTER PARA NUMERO: %s", err);
                exit(1);
            }
        }
        delete[] tmp;
        return 0;
    }

    for(int i = 0; i<this->tamanho; i+=this->dist){
        for(int j = i; j<(i+this->dist); j++){
            this->vars[var][j] = var_init;
        }
        var_init = not var_init;
    }
    return 1;

}

map_vars::map_vars(int tamanho, char *operacao) {

    this->dist = tamanho/2;
    this->tamanho = tamanho;
    for(char *aux = operacao; *aux; aux++){

        if(isalpha(*aux) or isdigit(*aux)){
            auto it = this->vars.find(*aux);

            if(it == this->vars.end()){
                if (this->include(*aux))
                    this->dist/=2;
            }
        }
    }
}
map_vars::~map_vars() {

    std::vector<char> keys;
    for(auto &key_value:this->vars){

        delete[] this->vars[key_value.first];
        keys.push_back(key_value.first);


    }
    for(const auto& key:keys){
        this->vars.erase(key);
    }
    this->tamanho = 0;
    this->dist = 0;
}
