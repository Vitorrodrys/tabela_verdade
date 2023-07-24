//
// Created by vitor on 16/07/23.
//


#include "funcoes_memoria.h"



void swap(void *ptr, void *ptr1, size_t tam){

    char aux[tam];
    memmove(aux, ptr, tam);
    memmove(ptr, ptr1, tam);
    memmove(ptr1, aux, tam);

}



void *aloca_memoria(void *ptr, size_t tam) {

    void *ptrReall = realloc(ptr, tam);
    if(!ptrReall){
        printf("erro, memoria indisponivel!");
        exit(1);
    }

    return ptrReall;

}
void limpa_memoria(void **ptr) {
    free(*ptr);
    *ptr = nullptr;
    ptr = nullptr;
}