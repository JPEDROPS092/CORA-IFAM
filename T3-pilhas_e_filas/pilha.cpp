#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <iostream>
#include <new>
#include <windows.h>

using namespace std;

//ESTRUTURAS
struct Numero {
    float num;
    struct Fruta *pAnt_num, *pProx_num;
} Num1, Num2, Soma, *pAux, *pUlt_num1, *pUlt_num2, *pUlt_soma;

//*************************OPERAÇÕES*******************************
//clear() limpa a lista
void limpar(Numero pilha) {
    pilha.pProx_num = NULL;
}

//isEmpty() verifica se a pilha esta vazia
int estaVazio(Numero pilha) {
    if(pilha.pProx_num == NULL){
        return 1;
    } else {
        return 0;
    }
}

//push(el) empilha no topo da lista
void empilhar(Numero *ultimo, float elemento) {
    ultimo->pProx_num = new Numero;
    ultimo->pProx_num->pAnt_num = ultimo;
    ultimo = ultimo->pProx_num;
    ultimo->num = elemento;
    ultimo->pProx_num = NULL;
}

//pop() retira e retorna o mais alto
Numero desempilhar (Numero *ultimo) {

}

//topEl() retorna o mais alto sem removê-lo
Numero ultimo(Numero *ultimo) {

}

int main() {
    setlocale(LC_ALL, "Portuguese");

    return 0;
}
