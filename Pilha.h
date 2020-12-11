//Autor: Leandro Barros Pontes
//Matricula: 1713332040
//Matéria: Estrutura de dados 1


#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

#define TAM 10  //tamanho maximo de filas/carros por filas

typedef struct elemento
{
    char *placa_carro;         //responsavel pelo armazenamento de placas
    struct elemento *prox;     //responsavel por apontar para o proximo

} Elemento;

/*estrutura da pilha (cabeçalho) */
typedef struct pilha
{

    //variaveis responsaveis pelo estacionamento/rua principais

    int contador_rua;          //utilizada para contar os carros inseridos na rua
    int menor_valor;           //utilizada para criacao da heuristica
    int contador_carro;        //utilizada para contar os carros inseridos na rua
    int qtd_pilhas;            //responsavel pela quantidade maxima de fileiras do estacionamento
    int max_carros_pilha;      //responsavel pela quantidade maxima de carros em cada fileira
    int max_carros_rua;        //responsavel pela quantidade maxima de carros na rua
    int n[TAM];                //responsavel pela contagem de carros em cada fileira
    Elemento **estacionamento; //responsavel pelo armazenamento de pilhas no estacionamento
    Elemento *topo[TAM];       //responsavel pelo armazenamento de pilhas em cada indice
    Elemento *rua;             //responsavel pelo armazenamento de pilhas em cada indice

    //variaveis responsaveis pelo estacionamento fake/auxiliar
    Elemento **estacionamento2;
    Elemento *topo2[TAM];
    int n2[TAM]; //responsavel pela contagem de carros em cada fileira

} Pilha;


//criacao do estacionamento
Pilha* pilha_cria (Pilha *p);

//funcao utilizada para empilhar veiculos no estacionamento
Elemento* insere_carro (Pilha*p, char *placa, int i);

//funcao utilizada para empilhar veiculos na rua
Elemento* insere_rua(Pilha*p, char *placa);

//funcao responsavel pela configuracao do estacionamento
//de acordo com as especificações do trabalho
Pilha* configura_estacionamento(Pilha* p);

//funcao responsavel pela inserção de veiculos no estacionamento
//utiliza como base a funcao insere principal
Pilha* insere_carro_estacionamento(Pilha* p, Elemento* Novo);

//funcao responsavel pela remocao de veiculos no estacionamento
//criada de acordo com as especificacoes
//possibilidade de manobrar para a rua
//possibilidade de manobrar no estacionamento
//possibilidade de retirar e sair
void retira_carro_estacionamento (Pilha* p);

//funcao responsavel por criar um estacionamento fake
//possui as mesmas especificações que o original
//utilizada pensando na heuristica ( voltada para a criacao de dicas )
Pilha* cria_estacionamento_fake (Pilha *p);

//funcao responsavel por criar uma cópia do estacionamento principal no estacionamento fake
Pilha* recebe_copia_estacionamento (Pilha *p);

//funcao responsavel por criar criar a heuristica do estacionamento
//funcao mais importante, pois comanda a dinamica do programa

//heurística baseada em filas mais vazias
//heurística funciona para inserção e remocao

//insercao: usuario pode escolher uma das dicas ou nao. Caso opte pelo manobrista, ele seguirá todas as dicas

//remocao: a remocao item (manobra no estacionamento), utiliza as dicas para fazer as mudanças.
//as placas escolhidas nesse item são mandadas para as dicas mais proximas (facilitando manobras)
Pilha* heuristica_insercao (Pilha *p, Elemento *novo);

#endif // PILHA_H_INCLUDED
