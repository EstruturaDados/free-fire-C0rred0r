#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_N 30
#define MAX_STR_T 20
#define TAM_MAX 10


typedef struct {
    char nome[MAX_STR_N];
    char tipo[MAX_STR_T];
    int quantidade;
    int prioridade;

} Item;

typedef struct {
    Item itens[TAM_MAX];
    int total;
} Backpack;


//chamando as funções
void inserir(Backpack *mochilha, const char* nome, const char* tipo, int total, int prio);
void iniciar(Backpack *mochila);
void remover(Backpack *mochilha, const char* nome);
void limpar(Backpack *mochilha);
void listar(Backpack *mochilha);
void busca(Backpack *mochila, const char* nome);
void buscaBinaria(Backpack *mochila, const char* nome);
void menuOrdenar(Backpack *mochila, int* ord);
void OrdernarAlfa(Backpack *mochila);
void OrdernarTipo(Backpack *mochila);
void ordenarPrioridade(Backpack *mochila);
void troca(Item *x, Item *y);



int main(){
    //alocando  memoria para as structs
    Item *itens;
    Backpack *mochila;
    mochila= (Backpack*) malloc(sizeof(Backpack));

    char obj[MAX_STR_N];
    char tipo[MAX_STR_T];
    int total, opc, prio;
    int ord=0;
    char stts[MAX_STR_N]= "Não Ordenado";
    char sOrd[MAX_STR_N]= "ORDENADO";
    iniciar(mochila);
    do{
        printf("============================================\n");
        if(ord!=0){
            strcpy(stts, sOrd);
        }
        printf("-- mochila(%d/%d) --\n",mochila->total, TAM_MAX);
        printf("STATUS DA ORDENAÇÃO POR NOME: %s", &stts);
        printf("\n---Selecione uma das opções a seguir---\n");
        printf("1- Inserir item na mochila \n");
        printf("2- Remover item da mochila \n");
        printf("3- mostrar items da mochila \n");
        printf("4- busca item na mochila \n");
        printf("5- Ordernar Mochila \n");
        printf("0- sair \n");
        printf("Sua escolha: ");
        scanf("%d", &opc);
        printf("============================================\n");
        switch (opc)
        {
        case 1:
            printf("---ADICIONAR NOVO ITEM---\n");
            printf("qual o nome do item: ");
            scanf("%s", &obj);
            printf("qual o tipo? (Estrutural, Eletronico, Energia) : ");
            scanf("%s", &tipo);
            printf("quantos items serão adicionados? ");
            scanf("%d", &total);
            printf("Qual a prioriade do item? (1/5): ");
            scanf("%d", &prio);
            inserir(mochila, obj, tipo, total, prio);
            break;
        case 2:
            if(mochila->total==0){
                printf("a mochila esta vazia!!!");
                break;
            }else{
                printf("---REMOVER ITEM---\n");
                printf("qual o nome do item: ");
                scanf("%s", &obj);
                remover(mochila, obj);
            }
            break;
        case 3:
            listar(mochila);
            break;
        case 4:
            if(mochila->total==0){
                printf("a mochila esta vazia!!!");
                break;
            }else if(ord==0){
                printf("ALERTA!! Para a busca funcionar é necessario que a mochila esteja ordenada em ordem alfabetica pelo Nome, por favor selecione a opção 5 para ordenar!!\n");
            }else{
                printf("qual o nome do item: ");
                scanf("%s", &obj);
                busca(mochila, obj);
            }
            break;
        case 5:
            menuOrdenar(mochila, &ord);
            break;
        case 0:
            printf("Saindo do programa...\n");
            limpar(mochila);
            break;
        default:
            printf("opção invalida, tente novamente!");
            break;
        }
    } while (opc !=0);



}

void menuOrdenar(Backpack *mochila, int* ord){
    int sel;
    printf("============================================\n");
            printf("escolha o tipo de ordenção: \n");
            printf("1- Por Nome (ordem alfabetica) \n");
            printf("2- Por Tipo \n");
            printf("3- Por Prioridade \n");
            printf("0- Cancelar\n");
            printf("Sua escolha: ");
            scanf("%d", &sel);
            printf("============================================\n");
            switch (sel)
            {
            case 1:
                *ord=1;
                OrdernarAlfa(mochila);
                break;
            case 2:
                OrdernarTipo(mochila);
                break;
            case 3:
                ordenarPrioridade(mochila);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            
            default:
            printf("opção invalida tente novamente!\n");
                break;
            }
}

void iniciar(Backpack *mochila){
    mochila->total = 0;
}

void inserir(Backpack *mochilha, const char* nome, const char* tipo, int total, int prio){
    if(mochilha == NULL){
        printf("você não tem uma mochila (ela não foi iniciada)\n");
        return;
    }
    if(mochilha->total==TAM_MAX){
        printf("não há mais espaço na mochila\n");
    }else{
        strcpy(mochilha->itens[mochilha->total].nome, nome);
        strcpy(mochilha->itens[mochilha->total].tipo, tipo);
        mochilha->itens[mochilha->total].quantidade = total;
        mochilha->itens[mochilha->total].prioridade = prio;
        mochilha->total++;
        printf("Item adicionado com sucesso!\n");
    }
}

void remover(Backpack *mochilha, const char* nome){
    int i=0, pos= -1;
    if(mochilha->total==0){
        printf("a mochila esta vazia\n");
        return;
    }


    for(i;i<mochilha->total;i++){
        if(strcmp(mochilha->itens[i].nome, nome)==0){
            pos= i;
            break;
        }
    }

    if (pos== -1){
        printf("o item não esta na mochila!!\n");
        return;
    }

    for(i=pos; i<mochilha->total-1;i++){
        strcpy(mochilha->itens[i].nome, mochilha->itens[i+1].nome);
        strcpy(mochilha->itens[i].tipo, mochilha->itens[i+1].tipo);
        mochilha->itens[i].quantidade = mochilha->itens[i+1].quantidade;
    }

    mochilha->total--;
    printf("você retirou o \"%s\" da mochila\n", nome);

    
}

void limpar(Backpack *mochilha){
    free(mochilha);
}

void listar(Backpack *mochilha){

    if (mochilha->total==0)
    {
        printf("A mochila esta vazia\n");
        return;
    }
    

    printf("mochila (%d/%d)\n", mochilha->total, TAM_MAX);
    printf("|%-20s|%-20s|%-12s|%-12s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    for(int i=0;i< mochilha->total;i++){
    printf("|%-20s|%-20s|%-12d|%-12d\n", mochilha->itens[i].nome, mochilha->itens[i].tipo, mochilha->itens[i].quantidade, mochilha->itens[i].prioridade);
}
}

void buscaBinaria(Backpack *mochila, const char* nome){
    int inicio= 0, fim= mochila->total-1, vezes=0;

    while(inicio<= fim){
        int meio= (inicio + fim) / 2;
        if(strcmp(mochila->itens[meio].nome, nome)==0){
            printf("o item \"%s\" está na mochila\n", nome);
            printf("-------------\n");
            printf("Nome: %s\n",mochila->itens[meio].nome);
            printf("Tipo: %s\n",mochila->itens[meio].tipo);
            printf("Quantidade: %d\n",mochila->itens[meio].quantidade);
            printf("-------------\n");
            return;
        }
        if(strcmp(mochila->itens[meio].nome, nome)< 0){
            inicio = meio + 1;
            vezes++;
        } else if(strcmp(mochila->itens[meio].nome, nome)> 0){
            fim= meio -1;
            vezes++;
        }
    }

    printf("o item \"%s\" não esta na mochila\n", nome);
}

void troca(Item *x, Item *y){
    Item temp= *x;
    *x= *y;
    *y= temp;
}

void OrdernarAlfa(Backpack *mochila){
    Backpack *temp= mochila;
    int vezes=0;
    for( int i=0; i<mochila->total-1; i++){
        int menorI= i;
        for(int j=i+1; j<mochila->total; j++ ){
            if(strcmp(mochila->itens[j].nome, mochila->itens[menorI].nome)<0){
                menorI= j;
                vezes++;
            }
        }
        if(menorI != i){
            troca(&mochila->itens[i], &mochila->itens[menorI]);
        }
    }
    printf("a mochila foi ordenada por NOME!\n");
    printf("\n foram necessarias %d comparaçoes\n", vezes);
}

void OrdernarTipo(Backpack *mochila){
    Backpack *temp= mochila;
    int vezes=0;
    for( int i=0; i<mochila->total-1; i++){
        int menorI= i;
        for(int j=i+1; j<mochila->total; j++ ){
            if(strcmp(mochila->itens[j].tipo, mochila->itens[menorI].tipo)<0){
                menorI= j;
                vezes++;
            }
        }
        if(menorI != i){
            troca(&mochila->itens[i], &mochila->itens[menorI]);
        }
    }
    printf("a mochila foi ordenada por TIPO!\n");
    printf("\n foram necessarias %d comparaçoes\n", vezes);
}

void ordenarPrioridade(Backpack *mochila){
    Backpack *temp= mochila;
    int i=0, j;
    int vezes=0;
    for(i;i<mochila->total-1;i++){
        int maior=i;
        for(j=i+1;j<mochila->total;j++){
            if(mochila->itens[j].prioridade > mochila->itens[maior].prioridade){
                maior= j;
                vezes++;
            }
        }
        if(maior !=i){
            troca(&mochila->itens[i], &mochila->itens[maior]);
        }
    }
    printf("a mochila foi ordenada por PRIORIDADE!\n");
    printf("\n foram necessarias %d comparaçoes\n", vezes);
}

void busca(Backpack *mochila, const char* nome){
    int i=0;
    if(mochila->total==0){
        printf("a mochila esta vazia\n");
        return;
    }
    for(i=0; i<mochila->total;i++){
        if(strcmp(mochila->itens[i].nome, nome)==0){
            printf("o item \"%s\" está na mochila\n", nome);
            printf("-------------\n");
            printf("Nome: %s\n",mochila->itens[i].nome);
            printf("Tipo: %s\n",mochila->itens[i].tipo);
            printf("Quantidade: %d\n",mochila->itens[i].quantidade);
            printf("-------------\n");
            return;
        }
    }
        printf("o item \"%s\" não está na mochila!\n", nome);
}