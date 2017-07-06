# Introdução
O governo federal lançou uma licitação bilionária para o desenvolvimento da última geração em
sistemas de votação para as eleições. Após um acirrado processo, a consultoria multinacional Tps
S.A. venceu essa licitação e promoveu seu promissor engenheiro, você, para realizar uma etapa
fundamental na implementação de seu audacioso projeto.
Em sua carta de promoção consta: “Caso decida por aceitar o desafio, caro engenheiro, sua tarefa
será:
1. Implementar o sistema de registro dos votos e apuração das eleições;
2. Levar em conta os possíveis milhões de votantes;
3. O resultado da apuração dever ser computado o mais rápido possível;
4. Não permitir que um eleitor vote com o mesmo título mais de uma vez;
5. O sistema deve permitir excluir votos suspeitos: pessoas que votam no lugar de votantes que
faltam.

# O que deve ser feito
Um sistema para realização das eleições, onde serão computados os votos das pessoas, juntamente
com instruções externas de outro sistema(detecção de voto fantasma) e apuração dos resultados.
Tendo em vista a regra 2 e 4 de sua carta que foi auto-destruída, você deverá utilizar uma estrutura
de dados que possibilite checar se o voto de um determinado título já foi computado ou não, num
tempo muito curto. Adicionalmente, caso o voto não tenha ainda sido computado, a estrutura deverá
possibilitar a inserção desse voto no sistema em um tempo muito curto. Por fim, pela regra 5, a
estrutura deverá possibilitar remoção de um voto corrupto em tempo novamente baixíssimo.
Mas que estruturas fantásticas são essas, que permitem inserção, remoção, contagem de elementos e
checagem de elementos numa velocidade bastante alta? Com bom aluno de EDII, você identifica
imediatamente que estamos nos referindo a tabelas hash e árvores de pesquisa.
OBS.: Nesse TP, será realizado um campeonato entre os algoritmos que contará pontos extra! Leia
maisna seção 4 - Campeonato.

# Algoritmos e Estruturas
Primeiramente, implemente o TAD cédula de eleição, com campos pra votos para presidente e
senador(inteiros) e título de eleitor(string).
Em seguida, implemente as seguintes estruturas que serão utilizadas no processo de contabilização
dos votos:
1. Tabela hash (com resolução de colisão por hashing duplo).
2. Tabela hash (com resolução de colisão por árvore binária de pesquisa).
3. Árvore AVL.
Todas estruturas devem permitir inserção, remoção e checagem da existência de elementos.
Por fim, implemente duas tabela hash(com resolução de colisão por endereçamento aberto) para
servir de apuração dos votos a qualquer momento da eleição(uma pra presidente e outra para
senador).

# Restrições
1. O código deve ser escrito em C.
2. A documentação do TP deve conter no máximo 8 páginas.
3. O seu código deve compilar usando C padrão ANSI. Basta evitar utilizar funções específicas
do Windows ou Linux.
4. O seu código deve compilar sem nenhuma warning! Você pode verificar se seu código
compila sem warnings com o seguinte comando no Linux
gcc -Werror <arquivos.c>

# Entrada
Seu programa irá ler da entrada padrão (usando scanf normal).
A primeira linha irá conter um identificador de execução: “0” para modo simulação e “1” para
modo campeonato.
A segunda linha irá conter o identificador de estrutura: “1” para tabela hash (com resolução de
colisão por hashing duplo); “2” para tabela hash (com resolução de colisão por árvore binária de
pesquisa) , e “3” para árvore AVL.
A terceira linha irá conter o número de candidatos a senador, presidente e número de eleitores. As
linhas seguintes irão conter um dos códigos das ações com seus possíveis argumentos, de acordo
com a tabela a seguir:



Assim, o programa deve ficar lendo continuamente e processando as ações, até que leia a entrada
'3', correspondendo ao comando encerra.
Dicas:
1. Ao computar um voto, deve-se checar se o título já votou antes para o cargo em questão.
2. Ao remover um título, deve-se remover os votos aos quais ele estava vinculado.
3. Não necessariamente todos os eleitores vão votar, nem todos candidatos receberão pelo
menos um voto.

# Saída
Os resultados da saída devem ser impressos na saída padrão(usando o printf normalmente). Cada
comando de entrada deve exibir uma saída diferente, conforme as regras a seguir:
Ação votar: imprimir “<voto computado, candidato X tem Y voto(s) | voto não computado>”
Exemplo:
0 0 abbf3 40
voto computado, candidato 40 tem 132 voto(s).
0 0 abbf3 30
voto não computado.
Aqui, o voto não foi computado, desde que o eleitor “abbf3” já tinha votado para presidente.
Ação remover: imprimir meliante <removido|nãoremovido>, X voto(s) válidos no sistema.”
Exemplo:
1 133calote
meliante removido, 456 voto(s) válidos no sistema.
1 3honesto
meliante não removido, 567 voto(s) válido(s) no sistema.
Aqui, o cidadão não foi removido, pois ele ainda não tinha votado.
Ação apurar: imprimir “<numero do candidato , X voto(s)>” para os Y primeiros candidatos(de
acordo com o parâmeto da ação), ordene-os pelo número de votos, um por linha. Em caso de
empate, ordenar pelo número do candidato em ordem crescente, Exemplo:
2 0 4
13 3241 voto(s).
25 2301 voto(s)
40 1056 voto(s).
45 0 voto(s).
Encerra: apenas fecha o programa
