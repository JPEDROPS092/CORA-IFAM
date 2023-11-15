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

void criarPilha(Pilha *p) {
    p->topo = NULL;
    p->tamanho = 0;
}

//********************************************OPERAÇÕES******************************************


//isEmpty() verifica se a pilha esta vazia
int estaVazio(Pilha *p) {
    if(p->topo) {
        cout << "Pilha não está vazia\n";
        return 0;
    } else {
        cout << "Pilha vazia\n";
        return 1;
    }
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
        //cout << "\nPilha vazia!\n";
    return NULL;
}

//clear() limpa a lista
void limpar(Pilha *p) {
    while(p->topo) {
        desempilhar(p);
    }
    cout << "Pilha vazia\n";
}

//topEl() retorna o mais alto sem removê-lo
Numero* topo(Pilha *p) {
    if(p->topo)
        return p->topo;
    else
        return NULL;
}



//Listar pilha
void listarPilha(Pilha *p) {
    Numero *exibir = p->topo;
    while(exibir) {
        cout << exibir->num << " ";
        exibir = exibir->pProx_num;
    }
}

/*
int receberValor() {
    int numero;
    cout << "Número: ";
    scanf("%d", &numero);
    return numero;
}
*/

//Retorna o número no topo
int topoPilha(Pilha *p) {
    if(p->topo) {
        return p->topo->num;
    } else
        return 0;
}

//Menu Principal
void menu() {
    int op = 1, novo;
    Pilha pilha;
    criarPilha(&pilha);
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
                //novo = receberValor();
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
               estaVazio(&pilha);
               system("pause");
           break;
           case 5:
               system("cls");
               cout << topoPilha(&pilha);
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

//Receber número
void receberNumero(Pilha *pilha) {
    char numeroStr[15];
    int num;
    cout << "Número: ";
    scanf("%s", numeroStr);
    //cout << numeroStr;
    for(int i = 0; i < strlen(numeroStr); i++) {
        //cout << numeroStr[i];
        num =  numeroStr[i] - '0';
        //cout << num;
        empilhar(pilha, num);
        pilha->tamanho++;
    }
    //listarPilha(pilha);
}

//Soma pilhar
void somar_pilhas(Pilha *pilha1, Pilha *pilha2, Pilha *soma) {
    int num1, num2, somado;
    Numero *aux1, *aux2, *ultimo;
    //soma->topo->num = desempilhar(pilha1)->num + desempilhar(pilha2)->num;
    while(pilha1->topo || pilha2->topo) { //Enquanto alguma pilha tiver valor desempilhar e somar
        if(aux1 = desempilhar(pilha1)) {
            num1 = aux1->num;
            //cout <<"\ntira 1 ";
        } else {
            //cout <<"\nzera 1 ";
            num1 = 0;
        }
        //cout << "\nnum1 " << num1;
        if(aux2 = desempilhar(pilha2)) {
            num2 = aux2->num;
            //cout <<"\ntira 2 ";
        } else {
            //cout <<"\nzera 2 ";
            num2 = 0;
        }
        //cout << "\nnum2 " << num2;
        somado = num1 + num2;
        if(somado > 9){ //Soma sobe resto
            somado -= 10;
            //Adicionar 1 ao proximo
            if(pilha1->topo) { //Pilha 1 tem numero
                ultimo = topo(pilha1);
                ultimo->num++;
            } else { //acrescenta 1 a pilha1
                empilhar(pilha1, 1);
                ultimo = topo(pilha1);
            }

        }
        //cout << "\nsoma " << somado;
        empilhar(soma, somado); //Empilha o topo das pilhas em soma
        //cout << "ultimo " << ultimo->num;
    }
    cout <<"\nResultado da soma = ";
    listarPilha(soma);
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    Pilha pilhaNum1;
    criarPilha(&pilhaNum1);
    Pilha pilhaNum2;
    criarPilha(&pilhaNum2);
    //menu();
    receberNumero(&pilhaNum1);
    receberNumero(&pilhaNum2);
    Pilha soma;
    criarPilha(&soma);
    somar_pilhas(&pilhaNum1, &pilhaNum2, &soma);

    return 0;
}
