/*Faça uma lista simplesmente encadeada porem com 2 elementos*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define INICIO "------------INICIO------------" 
#define RESULTADO "------------RESULTADO------------"
#define CORTE "------------------------"

struct TElemento{
    int valor;
    struct TElemento *prox; 
};
typedef struct TElemento TElemento;

struct TLista{
    TElemento *inicio;
    TElemento *fim;
    int total;    
};
typedef struct TLista Tlista;

void inicializa(Tlista *lista){
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->total = 0;
}

void inserir(Tlista *lista, int valor){
    int inseriu = 0;
    TElemento *novo = (TElemento *)malloc(sizeof(TElemento));
    novo->valor = valor;
    novo->prox = NULL;
    if (lista->inicio == NULL){
        //Lista encontra-se vazia.
        //Inserir o primeiro e unico elemento da lista ate agora
        lista->inicio = novo;
        lista->fim = novo;
        lista->total = 1;
        inseriu = 1;
    }else{
        //Lista ja possui pelo menos 1 elemento
        TElemento *atual = lista->inicio;
        TElemento *anterior = NULL;
        while (atual != NULL){
            if (atual->valor >= novo->valor){
                if (anterior == NULL){
                    //Inserir novo antes do primeiro da lista
                    novo->prox = atual;
                    lista->inicio = novo;
                }else{
                    //Inserir no meio da lista
                    novo->prox = atual;
                    anterior->prox = novo;
                }
                inseriu = 1;
                lista->total++;
                break;
            }
            anterior = atual;
            atual = atual->prox; //move para o próximo elemento
        }
    }
    if (!inseriu){
        //Inserir elemento no fim da lista
        lista->fim->prox = novo;
        lista->fim = novo;
        lista->total++;
    }
    
}

void exibeLista(Tlista lista){
    TElemento *atual = lista.inicio;
    int cont = 0;
    printf("\n\n\n\t\t===| EXIBE LISTA COMPLETA |===\n\n");
    while (atual != NULL){
        printf("\n%s\n", RESULTADO);
        printf("Numero do %d da lista e: (%d)\n", ++cont, atual->valor);
        atual = atual->prox;
    }
    printf("%s\n", CORTE);

}

void excluirLista(Tlista *lista, int valor){
    TElemento *atual = lista->inicio;
    int cont = 0;
    TElemento *anterior = NULL;
    while (atual != NULL){
        if (cont == 0){
            printf("\n\n\tA lista esta vazia\n");
            printf("\n\n\tExcluindo o ELEMENTO %d ...\n", atual->valor);
            cont++;
        }else if (atual->valor == valor){
            //Encontra o elemento a ser excluido
            if (lista->inicio == lista->fim){
                //Exclusao do unico elemento da lista
                printf("\n\n\tExcluindo o ELEMENTO %d ...\n", atual->valor);
                lista->inicio = NULL;
                lista->fim = NULL;
            }else if (atual == lista->inicio){
                //Esclui o primeiro elemento da lista
                printf("\n\n\tExcluindo o ELEMENTO %d ...\n", atual->valor);
                lista->inicio = atual->prox; //lista->inicio = lista->inicio->prox;
            }else if (atual == lista->fim){
                //Excluindo o ultimo cara da lista
                printf("\n\n\tExcluindo o ELEMENTO %d ...\n", atual->valor);
                lista->fim = anterior;
                lista->fim->prox = NULL;
            }else if ((atual != lista->inicio)&&(atual != lista->fim)){
                //Excluindo alguem que nao esta nem no fim e nem no inicio
                printf("\n\n\tExcluindo o ELEMENTO %d ...\n", atual->valor);
                anterior->prox = atual->prox;
            }
            free(atual);
            lista->total--;
            break;
        }
        anterior = atual;
        atual = atual->prox;// move para o proximo elemento
    }
}

int pedirOpcao(){
    int op;
    printf("\n%s\n", INICIO);
    do{
        printf("1 - Inserir na Lista\n");
        printf("2 - Exibe Lista\n");
        printf("3 - Excluir da Lista\n");
        printf("4 - Sair\n");
        printf("Digite a opção: ");
        scanf("%d", &op);
        printf("%s\n", CORTE);
    } while ((op < 1)||(op > 4));
    return op;
}

int pedirNum(){
    int num;
    do{
        printf("Digite um numero para ser inserido: ");
        scanf("%d", &num);
    } while (num < 0);
    return num;
}

int pedirNum2(){
    int num;
    do{
        printf("Digite um numero para ser excluido: ");
        scanf("%d", &num);
    } while (num < 0);
    return num;
}

Tlista lista; //variavel global

//=================================================
int main(){
    int op, numInseri;
    int repete = 0;
    inicializa(&lista);
    do{
        op = pedirOpcao();
        switch (op){
        case 1:
            numInseri = pedirNum();
            inserir(&lista,numInseri);
            break;
        case 2:
            exibeLista(lista);
            break;
        case 3:
            numInseri = pedirNum2();
            excluirLista(&lista,numInseri);
            break;
        case 4:
            repete = 1;
            break;
        default:
            break;
        }
    } while (repete == 0);
    return 0;
}

//=========================================