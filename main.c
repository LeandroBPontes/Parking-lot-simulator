#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#include "pilha.h"


//funcoes utilizadas para melhoria na exibicao e impressão

void pilha_imprime (Pilha* p);
void rua_imprime (Pilha* p);
void imprime_estacionamento_fake (Pilha* p);
Pilha* rearruma_fake (Pilha *p);

int item_menu(void);
void print_bonito (Pilha* p);

//aplicação principal
int main()
{
    setlocale(LC_ALL, "");

    Pilha *p = malloc(sizeof(Pilha));
    Elemento *e = malloc(sizeof(Elemento*));
    int item;

    //inicializando inteiros com zero
    p->qtd_pilhas = 0;
    p->max_carros_pilha = 0;
    p->max_carros_rua = 0;

    for(;;)
    {
        system("cls");
        item = item_menu();
        switch(item)
        {
        case 1:

            system("cls");
            p = configura_estacionamento(p);
            p = cria_estacionamento_fake (p);
            system("pause");

            break;
        case 2:
            system("cls");
            p = heuristica_insercao (p,e);
            imprime_estacionamento_fake (p);
            rua_imprime (p);
            system("pause");

            break;
        case 3:
            system("cls");
            p = heuristica_insercao (p,e);
            imprime_estacionamento_fake (p);
            rua_imprime (p);
            p =  insere_carro_estacionamento(p,e);
            p = heuristica_insercao (p,e);
            imprime_estacionamento_fake (p);
            rua_imprime (p);
            system("pause");
            break;
        case 4:
            system("cls");
            p = heuristica_insercao (p,e);
            imprime_estacionamento_fake (p);
            rua_imprime (p);
            retira_carro_estacionamento (p);
            system("cls");
            p = heuristica_insercao (p,e);
            imprime_estacionamento_fake (p);
            rua_imprime (p);
            system("pause");
            break;
        case 5:
            system("cls");
            p = rearruma_fake (p);
            system("pause");
            break;

        case 6:
            exit(0);
            break;
        }
    }
}

//funcoes utilizadas para a aplicação das questoes propostas no trabalho
//Podem ser recriadas de acordo com a adaptação do autor do código

//funcao responsavel pela criacao do menu
int item_menu(void)
{
    char s[80];
    int c;

    printf("\n");
    printf("Menu:\n");
    printf("1. Configurar estacionamento\n");
    printf("2. Mostrar estacionamento\n");
    printf("3. Estacionar veículo\n");
    printf("4. Sair com um veículo\n");
    printf("5. Rearrumação (cenário ideal)\n");
    printf("6. Sair\n");

    do
    {
        printf("\nEntre com sua escolha: ");
        gets(s);
        c = atoi(s);
    }
    while(c<0 || c>6);

    return c;
}

//funcao responsavel por "responder" aos diversos tamanhos possiveis que o estacionamento pode assumir
void print_bonito (Pilha* p)
{
    if(p->max_carros_pilha == 1)
    {
        printf("\t-----\n");
    }
    if(p->max_carros_pilha == 2)
    {
        printf("\t----------\n");
    }
    if(p->max_carros_pilha == 3)
    {
        printf("\t----------------\n");
    }
    if(p->max_carros_pilha == 4)
    {
        printf("\t-------------------------\n");
    }
    if(p->max_carros_pilha == 5)
    {
        printf("\t--------------------------------\n");
    }
    if(p->max_carros_pilha == 6)
    {
        printf("\t----------------------------------------\n");
    }
    if(p->max_carros_pilha == 7)
    {
        printf("\t---------------------------------------------\n");
    }
    if(p->max_carros_pilha == 8)
    {
        printf("\t----------------------------------------------------\n");
    }
    if(p->max_carros_pilha == 9)
    {
        printf("\t------------------------------------------------------------\n");
    }
    if(p->max_carros_pilha == 10)
    {
        printf("\t-------------------------------------------------------------------\n");
    }

}

//funciona como o front-end para aplicações e testes
//essa funcao é capaz de mostrar como está a situação do estacionamento fake (o que será exposto ao usuário)
//com a participação da heuristica (dicas adicionadas ao estacionamento fake)
void imprime_estacionamento_fake (Pilha* p)
{
    Elemento* Aux;
    int i,j;

    //-------------testa se o estacionamento foi configurado
    if ( p->qtd_pilhas == 0)
    {
        printf("\nÉ necessário configurar o estacionamento primeiro!\n");
        return;
    }
    //------------- fim testa se o estacionamento foi configurado


    char *mat[p->qtd_pilhas][p->max_carros_pilha];

    for (i = 0; i < p->qtd_pilhas; i++)
    {
        Aux = p->estacionamento2[i];
        int contador = 0;

        for (j = 0; j < p->max_carros_pilha; j++)
        {
            if(strcmp("x",Aux->placa_carro))
            {
                contador++;
            }

            Aux = Aux->prox;
        }
        for(j = 0; j < p->max_carros_pilha - contador; j++)
        {
            mat[i][j] = " ";
        }
        Aux = p->estacionamento2[i];
        for(; j < p->max_carros_pilha; j++ )
        {
            mat[i][j] = Aux->placa_carro;
            Aux = Aux->prox;
        }
    }

    printf("\nSaídas\n");
    for(i = 0; i < p->qtd_pilhas; i++)
    {
        print_bonito (p);
        printf("%i-",i+1);
        for (j = 0; j< p->max_carros_pilha; j++)
        {
            printf("%7s", mat[i][j]);
        }
        printf("\n");

    }
    print_bonito (p);
}

//funcao responsavel por rearrumar uma exibição para o estacionamento fake

//recebe as heuristicas como previsao de vagas ideais
//a cada insercao de vagas e geracao de novas dicas, essa funcao insere no:
//lugar de insercao principal e nas dicas trazidas pela heuristica
//formando o estacionamento ideal
Pilha* rearruma_fake (Pilha *p)
{
    int i;

    Elemento* Aux;
    int j;
    char *mat[p->qtd_pilhas][p->max_carros_pilha];

    //-------------testa se o estacionamento foi configurado
    if ( p->qtd_pilhas == 0)
    {
        printf("\nÉ necessário configurar o estacionamento primeiro!\n");
        return p;
    }
    //------------- fim testa se o estacionamento foi configurado


    //cria uma estrutura identica e recebe a copia da principal
    p = cria_estacionamento_fake (p);
    p = recebe_copia_estacionamento (p);

    //cria um estacionamento ideal, neste
    //dicas e veículos já inseridos são levados em consideracao
    printf("\nDe acordo com as características da sua configuração de estacionamento e das dicas dadas");
    printf("\nO estacionamento ideal:\n");

    p->menor_valor = p->n[0];

    for (j = 0; j < p->max_carros_pilha; j++)
    {
        if(p->n[j] < p->menor_valor)
        {
           p-> menor_valor = p->n[j];
        }

    }

    //insercao de dica, visando a fileira mais vazia
    for (i = 0; i < p->qtd_pilhas; i++)
    {

        if(p->n2[i] ==  p->menor_valor)

        {
            Elemento *novo=malloc(sizeof(Elemento));

            novo->placa_carro = malloc(sizeof(char));
            novo->placa_carro = "carro";

            novo->prox = p->topo2[i];
            p->topo2[i] = novo;
            p->estacionamento2[i] = novo;
            p->n2[i]++;

        }

    }

    for (i = 0; i < p->qtd_pilhas; i++)
    {
        Aux = p->estacionamento2[i];
        int contador = 0;

        for (j = 0; j < p->max_carros_pilha; j++)
        {
            if(strcmp("x",Aux->placa_carro))
            {
                contador++;
            }

            Aux = Aux->prox;

        }
        for(j = 0; j < p->max_carros_pilha - contador; j++)
        {
            mat[i][j] = " ";
        }

        Aux = p->estacionamento2[i];
        for(; j < p->max_carros_pilha; j++ )
        {
            mat[i][j] = Aux->placa_carro;
            Aux = Aux->prox;
        }

    }

    printf("\nSaídas\n");
    for(i = 0; i < p->qtd_pilhas; i++)
    {
        print_bonito (p);
        printf("%i-",i+1);
        for (j = 0; j< p->max_carros_pilha; j++)
        {
            if((strcmp(mat[i][j], "carro")!=0) && (strcmp(mat[i][j], " ")!=0) && (strcmp(mat[i][j], "x")!=0 ))
            {
                mat[i][j] = "carro";
            }
            printf("%7s", mat[i][j]);
        }
        printf("\n");

    }
    print_bonito (p);
    p = recebe_copia_estacionamento (p);
    return p;
}
//funciona como o back-end para aplicações e testes
//essa funcao é capaz de mostrar como está a situação do estacionamento principal
//sem a participação da heuristica (dicas adicionadas ao estacionamento fake)
void pilha_imprime (Pilha* p)
{
    Elemento* Aux;
    int i,j;

    char *mat[p->qtd_pilhas][p->max_carros_pilha];


    for (i = 0; i < p->qtd_pilhas; i++)
    {
        Aux = p->estacionamento[i];
        int contador = 0;

        for (j = 0; j < p->max_carros_pilha; j++)
        {

            if(strcmp("-",Aux->placa_carro))
            {
                contador++;
            }

            Aux = Aux->prox;

        }
        for(j = 0; j < p->max_carros_pilha - contador; j++)
        {
            mat[i][j] = " ";
        }
        Aux = p->estacionamento[i];
        for(; j < p->max_carros_pilha; j++ )
        {
            mat[i][j] = Aux->placa_carro;
            Aux = Aux->prox;
        }

    }

    printf("\nSaídas\n");
    for(i = 0; i < p->qtd_pilhas; i++)
    {


        print_bonito (p);
        printf("%i-",i+1);
        for (j = 0; j< p->max_carros_pilha; j++)
        {
            printf("%7s", mat[i][j]);
        }
        printf("\n");

    }
    print_bonito (p);


}
//funcao utilizada para imprimir veiculos na rua
void rua_imprime (Pilha* p)
{
    Elemento* Aux;
    int j;

    if ( p->qtd_pilhas == 0)
    {

        return;
    }

    Aux = p->rua;

    printf ("\n\tRua:");

    printf ("\n\t-------------------------\n");
    for (j = 0; j < p->max_carros_rua; j++)
    {
        printf ("  %7s",Aux->placa_carro);
        Aux = Aux->prox;
    }
    printf ("\n\t-------------------------\n");
}
