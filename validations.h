//
// Created by vitor on 22/07/23.
//

#ifndef CALCULADORA_TABELA_VERDADE_VALIDATIONS_H
#define CALCULADORA_TABELA_VERDADE_VALIDATIONS_H

#include <string>
#include <iostream>

bool verify_token(char *operation, char token_init, char token_end);
bool verify_token_after(char *operation, char what_token, int (*is_function) (int), int (*segundary_function)(int)= nullptr);

#endif //CALCULADORA_TABELA_VERDADE_VALIDATIONS_H
