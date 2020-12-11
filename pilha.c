#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#include "pilha.h"

//funcoes utilizadas em qualquer situacao envolvendo o TAD estacionamento/rua
//Nao podem ser removidas, por�m podem ser utilizadas para novas aplica��es

//criacao do estacionamento
Pilha* pilha_cria (Pilha *p)
{
    int i;

    for (i = 0; i < p->qtd_pilhas; i++)
    {
        p->topo[i] = NULL;
        p->n[i] = 0;
    }

    //pilha apontando para o *elemento criando elementos
    //alocando espa�o para estacionamento
    p->estacionamento = calloc(p->qtd_pilhas, sizeof(Elemento*));

    //verifica aloca��o
    if (p->estacionamento == NULL)
    {
        printf("nao foi possivel alocar");
    }

    //alocando espa�o para estacionamento[i]
    for (i = 0; i < p->qtd_pilhas; i++)
    {

        p->estacionamento[i] = calloc(p->max_carros_pilha,sizeof(Elemento));

    }

    for (i = 0; i < p->qtd_pilhas; i++)
    {
        //verifica aloca��o
        if ( p->estacionamento[i] == NULL)
        {
            printf("nao foi possivel alocar");
        }
    }


    return p;
}
//funcao utilizada para empilhar veiculos no estacionamento
Elemento* insere_carro (Pilha*p, char *placa, int i)
{
    Elemento* novo = malloc(sizeof(Elemento));

    novo->placa_carro = malloc(sizeof(char));//recebe placa

    //empilha e organiza
    novo->placa_carro = placa;
    novo->prox = p->topo[i];
    p->topo[i] = novo;

    return novo;
}

//funcao utilizada para empilhar veiculos na rua
Elemento* insere_rua(Pilha*p, char *placa)
{
    Elemento* novo = malloc(sizeof(Elemento));

    novo->placa_carro = malloc(sizeof(char));

    novo->placa_carro = placa;//recebe a placa

    //empilha e organiza
    novo->prox = p->rua;
    p->rua = novo;

    return novo;
}

//funcao responsavel pela configuracao do estacionamento
//de acordo com as especifica��es do trabalho
Pilha* configura_estacionamento(Pilha* p)
{

    int qtd,i,j;
    char *placa;

    placa = malloc(sizeof(char));

    Elemento* novo = malloc(sizeof(Elemento));


    printf("\n\t--------------TELA DE CONFIGURA��O DO ESTACIONAMENTO--------------\n");

    do//tratando tamanho maximo, podendo ser escolhido alterando o valor da constante TAM
    {
        printf("\n Quantas filas de carro deseja?\n");
        scanf("%d", &qtd);
        p->qtd_pilhas = qtd;
        if(qtd>TAM)
        {
            printf("\nA capacidade do estacionamento � para apenas %d filas de carro\n", TAM);
        }
    }
    while(qtd>TAM);

    do//tratando tamanho maximo, podendo ser escolhido alterando o valor da constante TAM
    {
        printf("\nQual � o n�mero m�ximo de carros em cada fileira?\n");
        scanf("%d", &qtd);
        p->max_carros_pilha = qtd;
        if(qtd>TAM)
        {
            printf("\nA capacidade das filas � no m�ximo para %d carros\n", TAM);
        }
    }
    while(qtd>TAM);

    do//tratando tamanho maximo, podendo ser escolhido alterando o valor da constante TAM
    {
        printf("\nQuantos carros podem ser manobrados na rua?\n");
        scanf("%d", &qtd);
        p->max_carros_rua = qtd;
        if(qtd>TAM)
        {
            printf("\nA capacidade m�xima de carros na rua � %d\n", TAM);
        }
    }
    while(qtd>TAM);

    p = pilha_cria (p);//com as informa��es, cria-se a estrutura do estacionamento

    system("cls");

    printf("\nSeu estacionamento foi configurado com sucesso!\n");//mensagem de confirma��o

    for (i = 0; i < p->qtd_pilhas; i++)
    {
        for (j = 0; j <  p->max_carros_pilha; j++)
        {
            p->topo[i] = malloc(p->max_carros_pilha * sizeof(Elemento));//aloca vetor de pilhas
        }

    }

    for (i = 0; i < p->qtd_pilhas; i++)
    {
        for (j = 0; j <  p->max_carros_pilha; j++)
        {

            placa = "x";//parte da logica do back-end
            novo = insere_carro (p,placa,i);
            p->estacionamento[i] = novo;

        }

    }
    for (i = 0; i < p->max_carros_rua; i++)
    {
        placa = "  ";//parte da logica do back-end
        novo = insere_rua (p,placa);
    }
    p->contador_carro = 0;
    p->contador_rua = 0;
    p->menor_valor = 0;

    printf("\n");
    return p;
}

//funcao responsavel pela inser��o de veiculos no estacionamento
//utiliza como base a funcao insere principal
Pilha* insere_carro_estacionamento(Pilha* p, Elemento* novo)
{

    char *placa;
    int i,pos,j, cont = 0, escolha, resposta;
    placa = malloc(sizeof(char));

    //verifica se estacionamento esta configurado
    if ( p->qtd_pilhas == 0)
    {
        return p;
    }

    // verifica se existe carro na rua
    //se existir, da a op��o de resgate
    if(p->contador_rua > 0)
    {
        printf("\n\tDigite 1 se deseja resgatar um carro da rua\n");
        printf("\n\tDigite 0 se deseja inserir outro carro\n");

        scanf("%d",&escolha);

        if( escolha == 1)
        {

            printf("\n\tDeseja colocar em qual fileira?\n");
            scanf("%d", &resposta);
            do
            {

                if(p->n[resposta] == p->max_carros_pilha)
                {
                    printf("\n\tn�o � possivel inserir, fila cheia\n");

                    printf("\n\tDigite 1 para escolher uma nova fileira\n");
                    printf("\tDigite 0 para voltar ao menu\n\n\n");
                    scanf("%d", &cont);

                    if(cont == 0)
                    {
                        system("pause");
                        return p;
                    }
                    if(cont == 1)
                    {
                        printf("\n\tEm qual fileira deseja inserir?");
                        scanf("%d",&resposta);

                    }
                }
                resposta--;
            }
            while(p->n[resposta] == p->max_carros_pilha);//fim verifica��o para resgate da rua e inser��o no estacionamento

            //inser�ao da rua para o estacionamento
            Elemento*t;
            char *aux;
            //retirada da rua
            t = p->rua;
            aux = t->placa_carro;
            p->rua = t->prox;

            p->contador_rua--;

            //insercao na fila do estacionamento
            novo = insere_carro (p,aux,resposta);
            p->estacionamento[resposta] = novo;
            p->topo[resposta] = novo;
            p->n[resposta]++;

            p->contador_carro++;

            return p;
        }
    }

    //verifica se rua e estacionamento estao cheios
    if((p->contador_carro == p->max_carros_pilha * p->qtd_pilhas) && p->max_carros_rua == p->contador_rua)
    {

        printf("\n\tEstacionamento e rua cheios! N�o � poss�vel inserir e nem manobrar.\n");
        printf("\n\tPor favor, retire um carro na op��o 4 -> op��o 1 (remover veiculo) para continuar.\n");
        system("pause");
        return p;

    }

    //verifica se estacionamento esta cheio
    if((p->contador_carro == p->max_carros_pilha * p->qtd_pilhas))
    {

        printf("\n\tEstacionamento cheio!\n");
        printf("\n\tPor favor, manobre na rua ou retire um carro.\n");
        system("pause");
        return p;

    }



        //-----------------menu de inser��es----------//

    printf("\n\tOl�, sou seu manobrista!\n");
    printf("\n\tDigite 1 - Deseja que eu estacione pra voc�? ( ir� inserir em uma das dicas )\n");
    printf("\n\tDigite 2 - Deseja estacionar sozinho ( voc� escolhe a fileira )\n");

    scanf("%d", &escolha);

    if(escolha == 2)    //-----------------inser��o manual SEM DICAS----------//
    {



        //verifica��o de placas id�nticas//
        Elemento *Aux;
        int cont;
        printf("\n\tEntre com a placa do carro -> ");
        scanf("%s", placa);
        do
        {

            cont = 0;
            for (i = 0; i < p->qtd_pilhas; i++)
            {

                Aux = p->estacionamento[i];

                for (j = 0; j < p->max_carros_pilha; j++)
                {

                    if(strcmp(placa,Aux->placa_carro)==0)
                    {
                        cont++;
                    }

                    Aux = Aux->prox;
                }
            }
            if(cont!=0)
            {
                printf("\n\tCUIDADO, sua placa foi fraudada!\n");
                printf("\n\tJ� existe um ve�culo com essa placa estacionado.\n");
                printf("\n\tEntre com outra placa -> ");
                scanf("%s", placa);
                system("cls");

            }

        }
        while(cont!=0);

        printf("\n\tEm qual fileira deseja inserir?\n");
        scanf("%d",&pos);
        pos--;
        //fim verifica��o de placas id�nticas

        do//verifica��o de fileiras cheias
        {
            if(p->n[pos] == p->max_carros_pilha)
            {
                printf("\n\tn�o � possivel inserir, fila cheia\n");

                printf("\n\tDigite 1 para escolher uma nova fileira\n");
                printf("\tDigite 0 para voltar ao menu\n\n\n");
                scanf("%d", &cont);

                if(cont == 0)
                {
                    system("pause");
                    return p;
                }
                if(cont == 1)
                {

                    printf("\n\tEntre com a placa do carro -> ");
                    scanf("%s", placa);
                    printf("\n\tEm qual fileira deseja inserir?");
                    scanf("%d",&pos);
                    pos--;

                }
            }
        }
        while(p->n[pos] == p->max_carros_pilha);//fim verifica��o de fileiras cheias


        for (i = 0; i < p->qtd_pilhas; i++)//empilhamento - inser��o
        {
            for (j = 0; j <  p->max_carros_pilha; j++)
            {
                if(pos == i && j == p->max_carros_pilha-1)
                {

                    novo = insere_carro (p,placa,pos);
                    p->estacionamento[pos] = novo;
                    p->topo[pos] = novo;
                    p->n[pos]++;
                    p->contador_carro++;

                }

            }

        }
    }//-----------------FIM INSER��O MANUAL SEM DICAS----------//

    //-------------------INSER��O COM DICA----------//
    else
    {

        Elemento *Aux;
        int contador;

        //auxiliar de insercao ----> respeita a heuristica
        system("cls");
        printf("\n\tEstou aqui pra isso!\n");
        printf("\n\tMe informe a placa do seu carro, para eu poder estacion�-lo!\n");

        scanf("%s", placa);
        do
        {
            contador = 0;
            for (i = 0; i < p->qtd_pilhas; i++)
            {

                Aux = p->estacionamento[i];

                for (j = 0; j < p->max_carros_pilha; j++)
                {

                    if(strcmp(placa,Aux->placa_carro)==0)
                    {

                        contador++;
                    }

                    Aux = Aux->prox;
                }
            }
            //-------verifica��o de placas id�nticas -------//

            //se verdadeiro, h� um carro com a mesma placa - programa nao permite
            if(contador!=0)
            {
                printf("\n\tCUIDADO, sua placa foi fraudada!\n");
                printf("\n\tJ� existe um ve�culo com essa placa estacionado.\n");
                printf("\n\tEntre com outra placa -> ");
                scanf("%s", placa);
                system("cls");

            }

        }
        while(contador!=0);

        //-------fim verifica��o de placas id�nticas -------//

        cont = 0;
        p->menor_valor = p->n[0];

        for (j = 0; j < p->qtd_pilhas; j++)
        {
            if(p->n[j] < p->menor_valor)
            {
                p->menor_valor = p->n[j];
                cont = j;
            }

        }


        //insercao de dica, visando a fileira mais vazia
        i = cont;


        if((p->n[i] == p->menor_valor))

        {
            novo = insere_carro (p,placa,i);
            p->estacionamento[i] = novo;
            p->n[i]++;
            p->contador_carro++;


        }

    }//-------------------FIM INSER��O COM DICA----------//

    return p;

}

//funcao responsavel pela remocao de veiculos no estacionamento

//criada de acordo com as especificacoes
//possibilidade de manobrar para a rua
//possibilidade de manobrar no estacionamento
//possibilidade de retirar e sair
void retira_carro_estacionamento (Pilha* p)
{

    Elemento *t;
    int i,cont = 0, escolha, j;
    char *receptor[p->max_carros_pilha+1];

    char *placa;
    placa = malloc(sizeof(char));


    if ( p->qtd_pilhas == 0)
    {

        return;
    }

    //----------------------------------verifica��o estacionamento vazio--------------------------------//
    for(i=0; i<p->qtd_pilhas; i++)
    {
        if(p->n[i] == 0)
        {
            cont++;
        }
    }

    if(cont == p->qtd_pilhas ||  p->contador_carro == 0)
    {
        printf("\n\tN�o � possivel remover, estacionamento vazio\n");
        system("pause");
        return;
    }
    //----------------------------------fim verifica��o estacionamento vazio--------------------------------//


    printf("\n\tDigite 1- Retirar o carro direto\n");
    printf("\n\tDigite 2- Manobrar na rua\n");
    printf("\n\tDigite 3- Manobrar no estacionamento\n");

    scanf("%d", &escolha);

    if(escolha == 1)
    {

        printf("Entre com a placa do carro?");

        scanf("%s",placa);

        Elemento *Aux;

        int indice, cont = 0;

        //-------------------encontrando o indice da pilha do elemento procurado
        for (i = 0; i < p->qtd_pilhas; i++)
        {

            Aux = p->estacionamento[i];

            for (j = 0; j < p->max_carros_pilha; j++)
            {

                if(strcmp(placa,Aux->placa_carro)==0)
                {
                    indice = i;
                    cont++;
                }

                Aux = Aux->prox;
            }
        }
        //------------------- FIM encontrando o indice da pilha do elemento procurado

        //verifica se a placa se encontra no estacionamento atrav�s do la�o anterior
        if(cont == 0)
        {

            printf("\n\tAcho que voc� se enganou... Placa n�o encontrada!\n");
            system("pause");
            return;
        }


        //-------------------POP at� achar o elemento ------------//
        Aux = p->estacionamento[indice];

        for (i = 0; i < p->max_carros_pilha; i++)
        {


            receptor[i] = malloc(sizeof(char));
            receptor[i] = Aux->placa_carro;

            if(i <= p->n[indice]+1)
            {

                t = p->estacionamento[indice];
                p->estacionamento[indice] = t->prox;
                p->topo[indice] = t->prox;
                p->n[indice]--;

                p->contador_carro--;
                cont++;

            }
            Aux = Aux->prox;
        }

        //-------------------FIM POP at� achar o elemento ------------//

        //-------------------Push dos elementos diferentes da placa removida------//
        cont--;
        Elemento *atual;
        atual = malloc(sizeof(Elemento));

        for (i = cont-1; i >= 0; i--)
        {

            if(strcmp(receptor[i],placa)!=0)
            {

                atual = insere_carro(p, receptor[i], indice);
                p->estacionamento[indice] = atual;
                p->topo[indice] = atual;
                p->n[indice]++;
                p->contador_carro++;

            }

        }

         //-------------------Push dos elementos diferentes da placa removida------//


    }//fim escolha 1

    if(escolha == 2)
    {

        //verificando a quantidade de carros que a rua suporta
        if(p->contador_rua == p->max_carros_rua)
        {

            printf("\n\tOps, parece que voc� se confundiu...\n");
            printf("\n\tSegundo sua configura��o, s� � poss�vel %i carro(s) na rua\n",p->max_carros_rua);
            printf("\n\tn�o � possivel manobrar, rua cheia!\n");

            system("pause");
            return;
        }
        //FIM verifica��o da quantidade de carros que a rua suporta


        printf("\n\tEntre com a placa do carro?");

        scanf("%s",placa);

        Elemento *Aux;

        int indice, cont = 0;

        //-------------------encontrando o indice da pilha do elemento procurado
        for (i = 0; i < p->qtd_pilhas; i++)
        {

            Aux = p->estacionamento[i];
            for (j = 0; j < p->max_carros_pilha; j++)
            {

                if(strcmp(placa,Aux->placa_carro)==0)
                {
                    indice = i;
                    cont++;
                }

                Aux = Aux->prox;
            }
        }
         //------------------- FIM encontrando o indice da pilha do elemento procurado


        //verifica se a placa se encontra no estacionamento atrav�s do la�o anterior
        if(cont == 0)
        {

            printf("\n\tAcho que voc� se enganou... Placa n�o encontrada!\n");
            system("pause");
            return;
        }


        //-------------------POP at� achar o elemento
        Aux = p->estacionamento[indice];

        for (i = 0; i < p->max_carros_pilha; i++)
        {


            receptor[i] = malloc(sizeof(char));
            receptor[i] = Aux->placa_carro;

            if(i <= p->n[indice]+1)
            {

                t = p->estacionamento[indice];
                p->estacionamento[indice] = t->prox;
                p->topo[indice] = t->prox;
                p->n[indice]--;

                p->contador_carro--;
                cont++;

            }
            Aux = Aux->prox;
        }
        //-------------------FIM POP at� achar o elemento

        //-------------------Push dos elementos diferentes da placa removida
        cont--;
        Elemento *atual;
        atual = malloc(sizeof(Elemento));

        for (i = cont-1; i >= 0; i--)
        {

            if(strcmp(receptor[i],placa)==0) // se encontrou a placa, joga pra rua
            {

                system("pause");
                atual = insere_rua(p,receptor[i]);
                p->contador_rua++;

            }
            else  //se nao achou, empilha
            {

                atual = insere_carro(p, receptor[i], indice);
                p->estacionamento[indice] = atual;
                p->topo[indice] = atual;
                p->n[indice]++;
                p->contador_carro++;

            }

        }
        //-------------------FIM Push dos elementos diferentes da placa removida

    }//fim escolha 2

    if(escolha == 3) //objetivo: manobrar o carro escolhido respeitando a heuristica das dicas
    {
        //-----------confirmacao ou nao do usuario---------------//
        int dica;

        printf("\n\tOl�, sou seu manobrista!\n");
        printf("\n\tObserve o estacionamento acima...\n");
        printf("\tSeu carro ir� da posi��o que se encontra para o local onde se encontra uma das dicas\n");

        printf("\n\tDigite 1 - Concordar com a manobra.\n");
        printf("\n\tDigite 0 - N�o concordar com a manobra e voltar ao menu.\n");

        scanf("%d", &dica);

        system("cls");

        if(dica == 0)
        {
            return;
        }

        //-----------confirmacao ou nao do usuario---------------//

        //-----------verifica��es iniciais de quantidade de veiculos no estacionamento---------------//

        //verifica se rua e estacionamento estao cheios
        if((p->contador_carro == p->max_carros_pilha * p->qtd_pilhas) && p->max_carros_rua == p->contador_rua)
        {

            printf("\n\tEstacionamento e rua cheios! N�o � poss�vel manobrar.\n");
            printf("\n\tPor favor, retire um carro na op��o 4 -> op��o 1 (remover veiculo) para continuar.\n");
            system("pause");
            return;

        }

        //verifica se estacionamento esta cheio
        if((p->contador_carro == p->max_carros_pilha * p->qtd_pilhas))
        {

            printf("\n\tEstacionamento cheio! N�o � poss�vel manobrar.\n");
            printf("\n\tPor favor, manobre na rua ou retire um carro.\n");
            system("pause");
            return;

        }


        //----------- Fim verifica��es iniciais de quantidade de veiculos no estacionamento---------------//

        printf("\n\tEntre com a placa do carro?");

        scanf("%s",placa);

        Elemento *Aux;

        int indice, cont = 0;

        //-------------------encontrando o indice da pilha do elemento procurado
        for (i = 0; i < p->qtd_pilhas; i++)
        {

            Aux = p->estacionamento[i];

            for (j = 0; j < p->max_carros_pilha; j++)
            {

                if(strcmp(placa,Aux->placa_carro)==0)
                {
                    indice = i;
                    cont++;
                }

                Aux = Aux->prox;
            }
        }
        //------------------- FIM encontrando o indice da pilha do elemento procurado

        //verifica se a placa se encontra no estacionamento atrav�s do la�o anterior
        if(cont == 0)
        {

            printf("\n\tAcho que voc� se enganou... Placa n�o encontrada!\n");
            system("pause");
            return;
        }


        //-------------------POP at� achar o elemento
        Aux = p->estacionamento[indice];

        for (i = 0; i < p->max_carros_pilha; i++)
        {


            receptor[i] = malloc(sizeof(char));
            receptor[i] = Aux->placa_carro;

            if(i <= p->n[indice]+1)
            {

                t = p->estacionamento[indice];
                p->estacionamento[indice] = t->prox;
                p->topo[indice] = t->prox;
                p->n[indice]--;

                p->contador_carro--;
                cont++;

            }
            Aux = Aux->prox;
        }

        //-------------------FIM POP at� achar o elemento

        //-------------------Push dos elementos diferentes da placa removida
        cont--;
        Elemento *atual;
        atual = malloc(sizeof(Elemento));

        for (i = cont-1; i >= 0; i--)
        {

            if(strcmp(receptor[i],placa)!=0)
            {

                atual = insere_carro(p, receptor[i], indice);
                p->estacionamento[indice] = atual;
                p->topo[indice] = atual;
                p->n[indice]++;
                p->contador_carro++;

            }

        }
        //-------------------FIM Push dos elementos diferentes da placa removida

        //-------------------mandando o carro para uma das dicas --------------//
        int c, entrei = 0;
        for (i = cont-1; i >= 0; i--)
        {

            if(strcmp(receptor[i],placa)==0) //achou a placa, entra na procura por dicas
            {
                for (c = 0; c < p->qtd_pilhas; c++)//busca pela fileira mais vazia, onde segundo a heuristica, encontram-se as dicas
                {
                    Aux = p->estacionamento2[c];
                    for (j = 0; j <p->max_carros_pilha; j++)
                    {
                        if((strcmp(Aux->placa_carro,"dica")==0) && entrei ==0)//achou a dica, insere (heuristica ok)
                        {
                            atual = insere_carro(p,placa,c);
                            p->estacionamento[c] = atual;
                            p->topo[c] = atual;
                            p->n[c]++;
                            p->contador_carro++;
                            entrei++; // se entrei == 0, quer dizer que nao entrou no la�o
                                     //logo nao tem dicas...
                                    // se nao tem dicas, � porque o estacionamento est� cheio

                        }

                        Aux = Aux->prox;
                    }

                }

            }

        }


        if(entrei == 0 )//nao tem dicas, estacionamento cheio
        {
            printf("\n\testacionamento cheio\n");
            system("pause");

        }

        //------------------fim mandando o carro para uma das dicas ---------------//

    }

}
//funcao responsavel por criar um estacionamento fake
//possui as mesmas especifica��es que o original
//utilizada pensando na heuristica ( voltada para a criacao de dicas )
Pilha* cria_estacionamento_fake (Pilha *p)
{
    int i;

    for (i = 0; i < p->qtd_pilhas; i++)
    {
        p->topo2[i] = NULL;
        p->n2[i] = 0;
    }

    //pilha apontando para o *elemento criando elementos
    //alocando espacos para estacionamento2
    p->estacionamento2 = calloc(p->qtd_pilhas, sizeof(Elemento*));

    //verifica aloca��o
    if (p->estacionamento2 == NULL)
    {
        printf("nao foi possivel alocar");
    }

    //alocando espaco para estacionamento2[i]
    for (i = 0; i < p->qtd_pilhas; i++)
    {

        p->estacionamento2[i] = calloc(p->max_carros_pilha,sizeof(Elemento));

    }

    //verifica aloca��o
    for (i = 0; i < p->qtd_pilhas; i++)
    {
        if ( p->estacionamento2[i] == NULL)
        {
            printf("nao foi possivel alocar");
        }
    }

    return p;
}

//funcao responsavel por criar uma c�pia do estacionamento principal no estacionamento fake
Pilha* recebe_copia_estacionamento (Pilha *p)
{

    int i;

    //c�pia do estacionamento principal - back-end
    for (i = 0; i < p->qtd_pilhas; i++)
    {
        p->estacionamento2[i] = p->estacionamento[i];

    }
    for (i = 0; i < p->qtd_pilhas; i++)
    {
        p->topo2[i] = p->topo[i];
        p->n2[i] = p->n[i];
    }

    return p;

}

//funcao responsavel por criar criar a heuristica do estacionamento
//funcao mais importante, pois comanda a dinamica do programa

//heur�stica baseada em filas mais vazias
//heur�stica funciona para inser��o e remocao

//insercao: usuario pode escolher uma das dicas ou nao. Caso opte pelo manobrista, ele seguir� todas as dicas

//remocao: a remocao item (manobra no estacionamento), utiliza as dicas para fazer as mudan�as.
//as placas escolhidas nesse item s�o mandadas para as dicas mais proximas (facilitando manobras)
Pilha* heuristica_insercao (Pilha *p, Elemento *novo)
{
    int i,j;

    //heuristica sempre atualiza o estacionamento fake
    p = recebe_copia_estacionamento (p);

    //heuristica recebe tambem o menor valor - fileira mais vazia
    p->menor_valor = p->n[0];

    //captura o menor valor
    for (j = 0; j < p->qtd_pilhas; j++)
    {
        if(p->n[j] < p->menor_valor)
        {
            p-> menor_valor = p->n[j];

        }

    }

    //insercao de dica, visando a fileira mais vazia

    for (i = 0; i < p->qtd_pilhas; i++)
    {

        if(p->n[i] == p->menor_valor && p->max_carros_pilha == p->qtd_pilhas && p->contador_carro < (p->max_carros_pilha * p->qtd_pilhas))//� a menor fileira e matriz quadrada

        {
            //--------------------------- QUADRADA-------------------------------//

            if(p->contador_carro == (p->max_carros_pilha * p->qtd_pilhas))//excedeu limite do estacionamento
            {

                return p;

            }
            if(p->n[i] == 0)
            {

                novo->placa_carro = "dica";
                novo->prox = p->topo2[i];
                p->topo2[i] = novo;
                p->estacionamento2[i] = novo;
                p->n2[i]++;
            }
            else
            {

                novo->placa_carro = "dica";
                novo->prox = p->topo2[i];
                p->topo2[i] = novo;
                p->estacionamento2[i] = novo;
                p->n2[i-1]++;
                break;

            }

        }//fim verifica quadrada


        //---------------------------FIM QUADRADA-------------------------------//

        //---------------------------NAO QUADRADA-------------------------------//

        //� a menor fileira e matriz nao quadrada
        if(p->n[i] == p->menor_valor && p->max_carros_pilha != p->qtd_pilhas && p->contador_carro < (p->max_carros_pilha * p->qtd_pilhas) )
        {

            if(p->n[i] == 0)
            {

                novo->placa_carro = "dica";
                novo->prox = p->topo2[i];
                p->topo2[i] = novo;
                p->estacionamento2[i] = novo;
                p->n2[i]++;
            }
            else
            {

                novo->placa_carro = "dica";
                novo->prox = p->topo2[i];
                p->topo2[i] = novo;
                p->estacionamento2[i] = novo;
                p->n2[i-1]++;
                break;

            }
            //---------------------------FIM NAO QUADRADA-------------------------------//
        }
    }

    return p;
}
