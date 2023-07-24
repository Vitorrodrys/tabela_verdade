//
// Created by vitor on 15/07/23.
//


#include "arvore_operacoes.h"

int tamanho_tabela(char *operation){

    vectorChar ocorrency;
    int tamanho = 0;
    while (*operation){
        if(isalpha(*operation) and ocorrency[*operation]) {
            tamanho++;
        }
        operation++;
    }
    return tamanho?2<<(tamanho-1):1;
}
arv_operacoes::arv_operacoes(char *operation) {
    int size_table = tamanho_tabela(operation);
    this->vars = new map_vars(size_table, operation);
    if(*operation == '!' and *(operation+1) == '('){
        this->raiz = new no_tabela_verdade(operation+1, size_table, true, this->vars);
    }else
        this->raiz = new no_tabela_verdade(operation, size_table, false, this->vars);

    this->raiz->resolving();



}
arv_operacoes::~arv_operacoes() {
    delete this->raiz;
    delete this->vars;

}