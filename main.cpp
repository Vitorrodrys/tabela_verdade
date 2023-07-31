#include <iostream>
#include "arvore_operacoes.h"
#include "funcoes_memoria.h"
#include "validations.h"
#include <getopt.h>
#include <unistd.h>
#include <fcntl.h>
#define herdastruct(nome, maisopcoes) \

char *dig_text(FILE *f, char parar){


    char *text =(char *)aloca_memoria(nullptr, sizeof (char));
    int tamanho = 0;
    do {
        text[tamanho] = fgetc(f);
        if(text[tamanho] != parar){
            tamanho++;
            text = (char *)aloca_memoria((void *)text, sizeof(char)*(tamanho+1));
        }

    } while (text[tamanho]!= parar);
    text[tamanho] = '\0';

    return text;
}

char *copy_str(char *str){
    char *new_str = new char [strlen(str)+1];
    strcpy(new_str, str);
    return new_str;
}
char *remove_spaces(char *string){
    char *aux = strchr(string, ' ');
    char *aux2;
    while (aux){

        aux2 = strchr(string, '\0');
        for(aux; aux != aux2; aux++){
            swap(aux, aux+1, sizeof(char));
        }

        aux = strchr(string, ' ');
    }
    return string;
}
int igual_parenteses(int token){
    return token == '(' or isdigit(token) or token == '!';
}
int main(int argc, char **argv) {






    const char *const short_options = "e:o";
    const option long_options[] = {
            {"expression", optional_argument, nullptr, 'e'},
            {"output", optional_argument, nullptr, 'o'},
            {nullptr, 0, nullptr, '\0'}
    };

    int opt;
    int index;
    char *expression = nullptr;
    while((opt = getopt_long(argc, argv, short_options, long_options,&index)) != -1){
        switch (opt) {
            case 'e':
                expression = copy_str(optarg?optarg:argv[2]);
                break;
            case 'o': {
                int fd = open(optarg?optarg:argv[4], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                dup2(fd, STDOUT_FILENO);
                close(fd);
                break;

            }
            case '?':
                fprintf(stderr, "opção não reconhecida %s.\n", argv[optind-1]);
                exit(1);

        }

    }


    if(not expression) {
        printf("digite a expressao boleana: ");
        expression = dig_text(stdin, '\n');

    }
    if(not verify_token(expression, '(', ')')){
        printf("Parenteses errados!\n");
        return 1;
    }
    if(not verify_token_after(expression, '!', isalpha, igual_parenteses)){
        printf("erro");
        return 0;
    }
    arv_operacoes arv(remove_spaces(expression));

    return 0;
}
