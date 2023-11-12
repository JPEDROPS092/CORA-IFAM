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
    int num;
    struct Numero *pProx_num;
} numero;

struct Pilha {
    Numero *topo;
    int tamanho;
} pilha;

void criarPilhar(Pilha *p) {
    p->topo = NULL;
    p->tamanho = 0;
}

//********************************************OPERAÇÕES******************************************


//isEmpty() verifica se a pilha esta vazia
int estaVazio(Pilha *p) {
    if(p->tamanho > 0)
        return 0;
    else
        return 1;
}

//push(el) empilha no topo da lista
void empilhar(Pilha *p, int num) {
    Numero *novo = new Numero;
    if(novo){
        novo->num = num;
        novo->pProx_num = p->topo;
        p->topo = novo;
        p->tamanho++;
    } else
        cout << "\nErro ao alocar memória\n";
}

//pop() retira e retorna o mais alto
Numero* desempilhar(Pilha *p) {
    if(p->topo) {
        Numero *removido = p->topo;
        p->topo = removido->pProx_num;
        p->tamanho--;
        return removido;
    } else
        cout << "\nPilha vazia!\n";
    return NULL;
}

//clear() limpa a lista
void limpar(Pilha *p) {
    while(p->topo) {
        desempilhar(p);
    }
}

//topEl() retorna o mais alto sem removê-lo
Numero* topo(Pilha *p) {
    return p->topo;
}

//Receber número
int receberNumero() {
    int numero;
    cout << "Número: ";
    scanf("%d", &numero);
    return numero;
}

//Listar pilha
void listarPilha(Pilha *p) {
    Numero *exibir = p->topo;
    while(exibir) {
        cout << exibir->num << " ";
        exibir = exibir->pProx_num;
    }
}

//Menu Principal
void menu() {
    int op = 1, novo;
    Pilha pilha;
    criarPilhar(&pilha);
    do{
       system("cls");
       cout << "\t\tO QUE DESEJA FAZER?\n";
       cout << "SAIR-0\nEMPILHAR-1\nDESEMPILHAR-2\nLIMPAR-3\nESTA VAZIA-4\nTOPO-5\nLISTAR PILHA-6\n:";
       cin >> op;
       switch(op){
           case 0:
               system("cls");
               cout<<"PROGRAMA FINALIZADO";
           break;
           case 1:
                system("cls");
                novo = receberNumero();
                empilhar(&pilha, novo);
                system("pause");
           break;
           case 2:
               system("cls");
               desempilhar(&pilha);
               system("pause");
           break;
           case 3:
               system("cls");
               limpar(&pilha);
               system("pause");
           break;
           case 4:
               system("cls");
               if(estaVazio(&pilha))
                    cout << "Pilha vazia";
                else
                    cout << "Pilha não está vazia";
               system("pause");
           break;
           case 5:
               system("cls");
               cout << topo(&pilha)->num;
               system("pause");
           break;
           case 6:
               system("cls");
               listarPilha(&pilha);
               system("pause");
           break;
           default:
            cout<<"\nOpção inválida, tente novamente!\n";
            system("pause");
           break;
       }
    }while(op!=0);

}

int main() {
    setlocale(LC_ALL, "Portuguese");
    menu();
    return 0;
}
