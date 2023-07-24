//
// Created by vitor on 15/07/23.
//



#include "no_tabela_verdade.h"
#include <vector>
#include <functional>
#include <unistd.h>
#include "validations.h"


bool is_something_one_char(const char *op){

    return (isalpha(*op) or isdigit(*op)) and *(op+1) == '\0';
}

bool no_tabela_verdade::verify_remove_parentheses(char *operation) {
    if(*operation != '('){
        return false;
    }
    char *aux = new char[strlen(operation)];
    strncpy(aux, operation+1, strlen(operation)-2);
    aux[strlen(operation)-2] = '\0';

    bool result = verify_token(aux, '(', ')');
    delete[] aux;
    return result;


}
no_tabela_verdade::no_tabela_verdade(int tamanho_tabela, char op, map_vars *vars_map, bool negacao) {
    this->operacao_or = nullptr;
    this->dir = nullptr;
    this->op = VAR;
    this->esq = nullptr;
    this->__not = false;
    this->__valores__ = new bool[tamanho_tabela];

    memmove(this->__valores__, (*vars_map)[op], tamanho_tabela);
    this->tam_values = tamanho_tabela;
    if (negacao){
        this->resolve_not();
    }
}

char *find_last_operator(char *op, std::map<char, operacao> *dict){

    char *pos_last_operator;
    int count_parentheses = 0;
    while (*op){
        if(*op == '(' ){
           count_parentheses++;
        }else if(*op == ')'){
            count_parentheses--;
        }else
            if(dict->count(*op) > 0 && not count_parentheses){
                pos_last_operator = op;
            }
        op++;
    }
    return pos_last_operator;
}

no_tabela_verdade::no_tabela_verdade(char *operation, int tamanho_tabela, bool negacao, map_vars *vars) {




    this->operacao_or = new char[strlen(operation)+1];
    strcpy(this->operacao_or, operation);

    while(*operation == '!' and (*(operation+1) == '(' or *(operation+1) == '!') ) {
        negacao = not negacao;
        operation++;
    }
    while(this->verify_remove_parentheses(operation)){
        operation++;
        *(strchr(operation, '\0')-1) = '\0';

        while(*operation == '!' and (*(operation+1) == '(' or *(operation+1) == '!') ) {
            negacao = not negacao;
            operation++;
        }
    }

    this->tam_values = tamanho_tabela;
    this->__valores__ = new bool[tamanho_tabela];
    this->__not = negacao;
    char *in = operation;
    char *last_op = find_last_operator(operation, &this->dict_op);
    this->op = this->dict_op[*last_op];
    if(*(last_op+1) == '!') {

        if( not is_something_one_char(last_op+2)){
            this->dir = new no_tabela_verdade(last_op+2, tamanho_tabela, true, vars);
        }else{
            this->dir = new no_tabela_verdade(tamanho_tabela, *(last_op+2),vars, true);

        }

    }else{
        if( not is_something_one_char(last_op+1)){
            this->dir = new no_tabela_verdade(last_op+1, tamanho_tabela, false, vars);
        }else{
            this->dir = new no_tabela_verdade(tamanho_tabela, *(last_op+1), vars, false);
        }
    }

    *last_op = '\0';
    if(*in == '!'){

        if (not is_something_one_char(in+1)){
            this->esq = new no_tabela_verdade(in+1, tamanho_tabela, true, vars);
        }else{
            this->esq = new no_tabela_verdade(tamanho_tabela, *(in+1), vars, true);
        }

    }else{
        if(not is_something_one_char(in)){
            this->esq = new no_tabela_verdade(in, tamanho_tabela, false, vars);

        }else{
            this->esq = new no_tabela_verdade(tamanho_tabela, *in, vars, false);
        }

    }



}

void no_tabela_verdade::resolving() {



    if(this->dir != nullptr){
        this->dir->resolving();
    }
    if(this->esq!= nullptr){
        this->esq->resolving();
    }
    std::vector<std::function<void()>> lambdaVector = {
                [this](){this->resolve_then();},
                [this](){this->resolve_and();},
                [this](){this->resolve_or();},
                [this](){this->resolve_something_then();}
    };
    if(this->esq != nullptr and this->dir != nullptr) {

        //sleep(0.2);
        lambdaVector[this->op]();
        if(this->__not) {
            this->resolve_not();
        }
        this->show_result();
    }

}
no_tabela_verdade::~no_tabela_verdade() {
    delete[] this->operacao_or;
    delete[] this->__valores__;
    this->op = VAR;
    this->tam_values = 0;
    delete this->esq;
    delete this->dir;
}
