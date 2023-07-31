# Tabela Verdade
O programa consiste em calcular todos os resultados possíveis de um conjunto de proposições e operações segundo as regras de lógica proposicional.

- Nenhum operador tem precedência em outro, sendo todos resolvidos na mesma ordem. Se quiser uma precedência, será necessário adicionar parênteses. É possível aninhar parênteses em qualquer nível de aninhamento, dependendo somente da necessidade do usuário.
- Por enquanto, estão sendo usados símbolos não tão convencionais para algumas operações, como implica e bi implica. No futuro, pretendo criar formas de inserir o símbolo que o usuário achar mais convincente para cada aplicação isolada.

## Operadores aceitos atualmente:
Os seguintes operadores são aceitos no programa:
- `!`: negação de uma variável ou proposição. Para negar uma operação, é necessário colocar a operação entre parênteses, por exemplo, `!(a|b)`. Para negar uma variável, basta usar `!a`.
- `^`: operador AND.
- `|`: operador OR.
- `>`: operador de implicação.
- `=`: operador de bi implicação.
- `()`: parênteses para adicionar precedência em alguma operação.

## Funcionalidades:
Ao rodar a aplicação na CLI, podem ser passados os seguintes argumentos:
- `-e`: expressão longa "--expression='a|b'", pode ser usada para passar a expressão booleana a ser calculada por parâmetros da CLI.
- `-o`: expressão longa "--output=resultadosaida.txt", pode ser usada para salvar o resultado da saída em um arquivo.
