//
// Created by vitor on 15/07/23.
//



#include "no_tabela_verdade.h"
#include <vector>
#include <functional>
#include <unistd.h>
#include "validations.h"


int count_ocorrency(char *str, char caracter){
    int ocorruncy = 0;
    while((str = strchr(str, caracter))) {
        ocorruncy++;
        str++;
    }
    return ocorruncy;
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

    char *pos_last_operator = nullptr;
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

bool not_follow_parentheses(char *op){

    while(not isalpha(*op)){
        if(*op == '('){
            return true;
        }
        op++;
    }
    return false;
}
no_tabela_verdade::no_tabela_verdade(char *operation, int tamanho_tabela, bool negacao, map_vars *vars) {




    this->operacao_or = new char[strlen(operation)+1];
    strcpy(this->operacao_or, operation);
    this->tam_values = tamanho_tabela;
    this->__valores__ = new bool[tamanho_tabela];
    this->__not = negacao;
    char *last_op = find_last_operator(operation, &this->dict_op);
    while ( not last_op) {



        while(*operation != '('){
            if(*operation == '!'){
                this->__not = not this->__not;
            }
            operation++;
        }
        operation++;
        *(strchr(operation, '\0')-1) = '\0';
        last_op =  find_last_operator(operation, &this->dict_op);

    }
    char *in = operation;
    this->op = this->dict_op[*last_op];
    bool negation_new = false;
    char *aux = last_op+1;

    if( not this->is_something_one_char(aux)){
        this->dir = new no_tabela_verdade(aux, tamanho_tabela, negation_new, vars);
    }else{
        char *aux2= aux;
        while(*aux2== '!')
            aux2++;
        this->dir = new no_tabela_verdade(tamanho_tabela, *aux2,vars, (count_ocorrency(aux, '!')%2));

    }


    *last_op = '\0';
    aux = in;
    if (not is_something_one_char(aux)){
        this->esq = new no_tabela_verdade(aux, tamanho_tabela, negation_new, vars);
    }else{
        char *aux2 = aux;
        while (*aux2 == '!')
            aux2++;
        this->esq = new no_tabela_verdade(tamanho_tabela, *aux2, vars,  (count_ocorrency(aux, '!') %2));
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
