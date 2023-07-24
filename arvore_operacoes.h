//
// Created by vitor on 15/07/23.
//

#ifndef CALCULADORA_TABELA_VERDADE_ARVORE_OPERACOES_H
#define CALCULADORA_TABELA_VERDADE_ARVORE_OPERACOES_H
#include "no_tabela_verdade.h"
#include <vector>
#include "funcoes_memoria.h"
#include "vars_map_table.h"
class arv_operacoes{
private:
    no_tabela_verdade *raiz;
    map_vars *vars;
public:
    arv_operacoes(char *operation);
    ~arv_operacoes();


};



#endif //CALCULADORA_TABELA_VERDADE_ARVORE_OPERACOES_H
