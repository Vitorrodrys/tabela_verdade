//
// Created by vitor on 15/07/23.
//

#ifndef CALCULADORA_TABELA_VERDADE_NO_TABELA_VERDADE_H
#define CALCULADORA_TABELA_VERDADE_NO_TABELA_VERDADE_H
#include <map>
#include <iostream>
#include <string.h>
#include <exception>
#include "funcoes_memoria.h"
#include "vars_map_table.h"
#include <algorithm>
#include <ranges>
class vectorChar{
public:
    char *vector;
    int tamanho;
    vectorChar(){
        this->tamanho=1;
        this->vector = (char *)aloca_memoria(nullptr, sizeof(char));
        this->vector[0] = '\0';
    }
    bool add(char element){
        this->tamanho++;
        this->vector = (char *)aloca_memoria(this->vector, this->tamanho);
        this->vector[this->tamanho-2] = element;
        return true;
    }
    bool in_list(char element){
        return strchr(this->vector, element);
    }
    int operator[](char element){

        if(not this->in_list(element)){
            this->add(element);
            return 1;
        }
        return 0;
    }
};

typedef enum operacao{

    THEN,
    AND,
    OR,
    SOMETHING_THEN,
    VAR

}operacao;
//a |
//c | e) ) ^
//b- d)
// (a | (c | e) )^ (b - d)
class no_tabela_verdade {
private:

    std::map <char, int> *dict_dist = new std::map<char, int>;
    std::map<char, operacao > dict_op = {

            {'^', AND},
            {'|', OR},
            {'>', THEN},
            {'=', SOMETHING_THEN}

    };

    static bool verify_remove_parentheses(char *operation);
    char *operacao_or;
    operacao op;
    bool __not;
    bool *__valores__;
    int tam_values;
    no_tabela_verdade* esq;
    no_tabela_verdade* dir;

public:
    no_tabela_verdade(char *operation, int tamanho_tabela, bool negacao, map_vars *vars);
    no_tabela_verdade(int tamanho_tabela, char var, map_vars *vars_map, bool negacao);
    bool *pre_ordem_resolving();
    ~no_tabela_verdade();
    void resolving();

    bool is_something_one_char(const char* op) {
        return std::ranges::all_of(dict_op, [op](const auto& key) { return strchr(op, key.first) == nullptr; });
    }
    void resolve_and(){
        for(int i = 0; i<this->tam_values; i++){
            this->__valores__[i] = this->esq->__valores__[i] and this->dir->__valores__[i];
        }
    }
    void resolve_or(){
        for(int i = 0; i<this->tam_values; i++){
            this->__valores__[i] = this->esq->__valores__[i] or this->dir->__valores__[i];
        }
    }
    void resolve_then(){
        for(int i = 0; i<this->tam_values; i++){
            this->__valores__[i] = not this->esq->__valores__[i] or this->dir->__valores__[i];
        }
    }
    void resolve_something_then(){
        for(int i = 0; i<this->tam_values; i++){
            this->__valores__[i] = this->esq->__valores__[i] == this->dir->__valores__[i];
        }
    }

    void resolve_not(){
        for(int i = 0; i<this->tam_values; i++){
            this->__valores__[i] = not this->__valores__[i];
        }
    }
    void show_result(){
        //static int descloc = 0;

        printf("solucao %s:\n", this->operacao_or);
        for(int i = 0; i<this->tam_values; i++){
            printf(this->__valores__[i]?"V":"F");
        }
        printf("\n");
        /*printf("\033[%d;0%s|", descloc, this->operacao_or);
        int size_str = strlen(this->operacao_or);
        descloc+= size_str/2;

        for(int i = 0; i<this->tam_values; i++){
            printf("\033[%d;%d", descloc, i+1);
            printf(this->__valores__[i]?"V":"F");
        }
        printf("\n");

        descloc+= size_str/2 + size_str%2?1:0;
        for(int i = 0; i<this->tam_values; i++){
            printf("\033[%d;%d|", descloc, i+1);
        }
         */
    }



};

class dist_values_finish:public std::exception{
public:
    const char *mensagem_;
    dist_values_finish(const char *msg_err){
        this->mensagem_ = msg_err;
    }
    const char* what() const noexcept override {
        return mensagem_;
    }
};




#endif //CALCULADORA_TABELA_VERDADE_NO_TABELA_VERDADE_H
