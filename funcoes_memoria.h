//
// Created by vitor on 16/07/23.
//

#ifndef CALCULADORA_TABELA_VERDADE_FUNCOES_MEMORIA_H
#define CALCULADORA_TABELA_VERDADE_FUNCOES_MEMORIA_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void swap(void *ptr, void *ptr1, size_t tam);
void *aloca_memoria(void *ptr, size_t tam);
void limpa_memoria(void **ptr);


#endif //CALCULADORA_TABELA_VERDADE_FUNCOES_MEMORIA_H
