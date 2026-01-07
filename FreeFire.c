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

} Item;

typedef struct {
    Item itens[TAM_MAX];
    int total;
} Backpack;

typedef struct No {
   Item* dados;
   struct No* proximo;
} No;

typedef No* MochilaEncadeada;



void inserirSequencial(Backpack *mochilha, const char* nome, const char* tipo, int total);
void iniciarSequencial(Backpack *mochila);
void removerSequencial(Backpack *mochilha, const char* nome);
void limparSequencial(Backpack *mochilha);
void listarSequencial(Backpack *mochilha);
void buscaSequencial(Backpack *mochila, const char* nome);
void menuSequencial();
void OrdernarSequencia(Backpack *mochila);
void buscaBinaria(Backpack *mochila, const char* nome);
//MochilaEncadeada
void menuEncadeada();
void iniciarEncadeada(MochilaEncadeada *mochila);
void inserirEncadeada(MochilaEncadeada *mochila, const char* nome, const char* tipo, int total);
void RemoverEncadeada(MochilaEncadeada *mochila, const char* nome);
void listarEncadeada(MochilaEncadeada *mochila);
void BuscaSeqEncadeada(MochilaEncadeada *mochila, const char* nome);
void limparEncadeada(MochilaEncadeada *mochila);


int main(){
    int opc;
    do{
        printf("---fortinatis tipis---\n");
        printf("---Selecione uma das opções a seguir---\n");
        printf("1- Mochila Sequencial\n");
        printf("2- Mochila Ordenada \n");
        printf("0- sair\n");
        printf("Sua escolha: ");
        scanf("%d", &opc);
        

        switch (opc)
        {
        case 1:
            menuSequencial();
            break;
        case 2:
            menuEncadeada();
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
        printf("Opção invalida, tente novamente\n");
            break;
        }
    } while (opc !=0);
}


void menuSequencial(){
    Item *itens;
    Backpack *mochila;
    mochila= (Backpack*) malloc(sizeof(Backpack));

    
    iniciarSequencial(mochila);
    
    char obj[MAX_STR_N];
    char tipo[MAX_STR_T];
    int total;
    int opc;
    do{
        OrdernarSequencia(mochila);
        printf("-- mochila(%d/%d) --\n",mochila->total, TAM_MAX);
        printf("\n---Selecione uma das opções a seguir---\n");
        printf("1- Inserir item na mochila \n");
        printf("2- Remover item da mochila \n");
        printf("3- mostrar items da mochila \n");
        printf("4- busca item na mochila \n");
        printf("5- busca Binaria na mochila \n");
        printf("0- sair \n");
        printf("Sua escolha: ");
        scanf("%d", &opc);
        switch (opc)
        {
        case 1:
            printf("---ADICIONAR NOVO ITEM---\n");
            printf("qual o nome do item: ");
            scanf("%s", &obj);
            printf("qual o tipo do item: ");
            scanf("%s", &tipo);
            printf("quantos items serão adicionados? ");
            scanf("%d", &total);
            inserirSequencial(mochila, obj, tipo, total);
            break;
        case 2:
            if(mochila->total==0){
                printf("a mochila esta vazia!!!");
                break;
            }else{
                printf("---REMOVER ITEM---\n");
                printf("qual o nome do item: ");
                scanf("%s", &obj);
                removerSequencial(mochila, obj);
            }
            break;
        case 3:
            listarSequencial(mochila);
            break;
        case 4:
            if(mochila->total==0){
                printf("a mochila esta vazia!!!\n");
                break;
            }else{
                printf("qual o nome do item: ");
                scanf("%s", &obj);
                buscaSequencial(mochila, obj);
            }
            break;
        case 5:
            if(mochila->total==0){
                printf("a mochila esta vazia!!!\n");
                break;
            }else{
                printf("qual o nome do item: ");
                scanf("%s", &obj);
                buscaBinaria(mochila, obj);
            }
            break;
        case 0:
            printf("Saindo do programa...\n");
            limparSequencial(mochila);
            break;
        default:
            printf("opção invalida, tente novamente!\n");
            break;
        }
    } while (opc !=0);
}

void iniciarSequencial(Backpack *mochila){
    mochila->total = 0;
}

void inserirSequencial(Backpack *mochilha, const char* nome, const char* tipo, int total){
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
        mochilha->total++;
        printf("Item adicionado com sucesso!\n");
    }
}

void removerSequencial(Backpack *mochilha, const char* nome){
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

void limparSequencial(Backpack *mochilha){
    free(mochilha);
}

void listarSequencial(Backpack *mochilha){

    if (mochilha->total==0)
    {
        printf("A mochila esta vazia\n");
        return;
    }
    

    printf("mochila (%d/%d)\n", mochilha->total, TAM_MAX);
    printf("|NOME                | Tipo                | Quantidade\n");
    for(int i=0;i< mochilha->total;i++){
    printf("|%s               |%s                 |%d              \n", mochilha->itens[i].nome, mochilha->itens[i].tipo, mochilha->itens[i].quantidade);
}
}

void buscaSequencial(Backpack *mochila, const char* nome){
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

void troca(Item *x, Item *y){
    Item temp= *x;
    *x= *y;
    *y= temp;
}

void OrdernarSequencia(Backpack *mochila){
    Backpack *temp= mochila;

    for( int i=0; i<mochila->total-1; i++){
        int menorI= i;
        for(int j=i+1; j<mochila->total; j++ ){
            if(strcmp(mochila->itens[j].nome, mochila->itens[menorI].nome)<0){
                menorI= j;
            }
        }
        if(menorI != i){
            troca(&mochila->itens[i], &mochila->itens[menorI]);
        }
    }
}

void buscaBinaria(Backpack *mochila, const char* nome){
    int inicio= 0, fim= mochila->total-1, vezes=0;

    while(inicio<= fim){
        int meio= (inicio + fim) / 2;
        if(strcmp(mochila->itens[meio].nome, nome)==0){
            vezes++;
            printf("o Item \"%s\" está no indice: %d\n", nome, meio);
            printf("foram necessarias %d comparações\n", vezes);
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

//ENCADEAMENTO

void menuEncadeada(){

    MochilaEncadeada *mochila;
    mochila= (MochilaEncadeada*) malloc(sizeof(MochilaEncadeada));

    iniciarEncadeada(mochila);
    char obj[MAX_STR_N];
    char tipo[MAX_STR_T];
    int total;
    int opc;
    do{
        printf("\n---Selecione uma das opções a seguir---\n");
        printf("1- Inserir item na mochila \n");
        printf("2- Remover item da mochila \n");
        printf("3- mostrar items da mochila \n");
        printf("4- busca item na mochila \n");
        printf("0- sair \n");
        printf("Sua escolha: ");
        scanf("%d", &opc);
        switch (opc)
        {
        case 1:
            printf("---ADICIONAR NOVO ITEM---\n");
            printf("qual o nome do item: ");
            scanf("%s", &obj);
            printf("qual o tipo do item: ");
            scanf("%s", &tipo);
            printf("quantos items serão adicionados? ");
            scanf("%d", &total);
            inserirEncadeada(mochila, obj, tipo, total);
            break;
        case 2:
            if(mochila==NULL){
                printf("a mochila esta vazia!!!\n");
                break;
            }else{
                printf("---REMOVER ITEM---\n");
                printf("qual o nome do item: ");
                scanf("%s", &obj);
                RemoverEncadeada(mochila, obj);
            }
            break;
        case 3:
            listarEncadeada(mochila);
            break;
        case 4:
            if(mochila==NULL){
                printf("a mochila esta vazia!!!\n");
                break;
            }else{
                printf("qual o nome do item: ");
                scanf("%s", &obj);
                BuscaSeqEncadeada(mochila, obj);
            }
            break;
        case 0:
            printf("Saindo do programa...\n");
            limparEncadeada(mochila);
            break;
        default:
            printf("opção invalida, tente novamente!\n");
            break;
        }
    } while (opc !=0);

}

void iniciarEncadeada(MochilaEncadeada *mochila){
    *mochila= NULL;
}

void inserirEncadeada(MochilaEncadeada *mochila, const char* nome, const char* tipo, int total){


    No* novoNo = (No*)malloc(sizeof(No));

    if(novoNo== NULL){
        printf("o nó não pode ser criado\n");
        return;
    }

    novoNo->dados= (Item*) malloc(sizeof(Item));
    if(novoNo->dados==NULL){
        printf("Não foi possivel alocar a memoria!!");
        return;
    }

    strcpy(novoNo->dados->nome, nome);
    strcpy(novoNo->dados->tipo, tipo);
    novoNo->dados->quantidade= total;

    novoNo->proximo= *mochila;
    *mochila= novoNo;
}

void RemoverEncadeada(MochilaEncadeada *mochila, const char* nome){

    No* atual= *mochila;
    No* anterior= NULL;

    if (mochila==NULL)
    {
        printf("a mochila esta vazia!\n");
        return;
    }
    
    while( atual !=NULL && strcmp(atual->dados->nome, nome)!=0){
        anterior= atual;
        atual= atual->proximo;
    }

    if(atual==NULL){
        printf("o texto não está na lista!!\n");
        return;
    }

    if(anterior==NULL){
        *mochila= atual->proximo;
    }else{
        anterior->proximo= atual->proximo;
        free(atual->dados);
        free(atual);
        printf("item excluido com sucesso!!\n");
    }
}

void listarEncadeada(MochilaEncadeada *mochila){
   No* temp= *mochila;

   if(temp==NULL){
    printf("a mochila está vazia!!\n");
    return;
   }

    printf("|NOME                | Tipo                | Quantidade\n");
    while(temp!=NULL){
    printf("|%s               | %s                 | %d              \n", temp->dados->nome, temp->dados->tipo, temp->dados->quantidade);
    temp= temp->proximo;
   }
}

void BuscaSeqEncadeada(MochilaEncadeada *mochila, const char* nome){
    No* atual= *mochila;
    No* anterior= NULL;

    if (atual==NULL)
    {
        printf("a mochila esta vazia!\n");
        return;
    }
    
    while( atual !=NULL && strcmp(atual->dados->nome, nome)!=0){
        anterior= atual;
        atual= atual->proximo;
    }

    if(strcmp(atual->dados->nome, nome)==0){
        printf("o item \"%s\" está na mochila\n", nome);
        printf("-------------\n");
        printf("Nome: %s\n",atual->dados->nome);
        printf("Tipo: %s\n",atual->dados->tipo);
        printf("Quantidade: %d\n",atual->dados->quantidade);
        printf("-------------\n");
        return;
    }
    printf("o item \"%s\" não está na mochila!\n", nome);
}

void limparEncadeada(MochilaEncadeada *mochila){
    No *atual= *mochila;
    No *proximo;

    while(atual!=NULL){
        proximo= atual->proximo;
        free(atual->dados);
        free(atual);
        atual=proximo;
    }

    printf("MEMORIA LIMPA!!\n");
}

