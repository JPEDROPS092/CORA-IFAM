#include <iostream>
#include <stdio.h>
#include <new>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>
#include <cstdlib>
using namespace std;
struct Fruta {
     char nome[40], descricao[500];
     struct Fruta *pProx;
     int relevancia;
} frutas, *pAux_fruta, *pLer_fruta, *pProx_fruta, *pbuscarFruta, *pAux_fruta_temp, *pAnt_fruta, *tempFruta = new Fruta;

struct Dicionario {
     char inicial;
     int quant, pos;
     struct Dicionario *pProx;
     struct Dicionario *pAnt;
     Fruta inicio_fruta;
} inicio_dicio, *pAux_dicio, *pSal, *pAnt_dicio, *pbuscarLetra, dicio_temp;

//************************Variáveis globais
char palavra[40], letra,elemento[40];
int cont_linha = 2, cont_fruta;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y){
 CursorPosition.X = x; // Locates column
 CursorPosition.Y = y; // Locates Row
 SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed
}

/****************** FUNCAO VERIFICAR NODO ******************/
int inicial_existe(char let){//verificação da inicial para inserir
    pAux_dicio = &inicio_dicio;
    while((pAux_dicio->pProx) && (toupper(pAux_dicio->inicial) != toupper(let))){
        pAnt_dicio = pAux_dicio;
        pAux_dicio = pAux_dicio->pProx;
    }
    if(toupper(pAux_dicio->inicial) == toupper(let)) { //Inicial existe
        return 1;
    } else {
        return 0;
    }
}

/****************** FUNCAO CONTADOR DE OCORRÊNCIA ******************/
int existe(char *str1, char *str2, int id) { //Passa a string que pode conter a substring, a substring e a posição em que começa a verificação
    int i, j = 0;
    for(i = id; i < strlen(str1); i++){ //Percorre a string da posição id até o final
        if(str1[i] == str2[j]) //Se a letra atual é igual a letra da sobstring j++
            j++;
        else //Senão é uma palavra diferente e j = 0
            j = 0;
        if(j == strlen(str2)) //retorna a posição em que termina a substring na string
            return i;
    }
    return -1; //Não encontrou substring na string
}

/****************** FUNCAO SALVAR ******************/
void gravar(){
    FILE *pont_arq;
    pont_arq = fopen("dicionario.txt", "w");
    if(pont_arq) {
        if(inicio_dicio.pProx != NULL) {
            pSal = inicio_dicio.pProx; /* aponta para o inicio do dicionario */
             while(pSal){
                 pAux_fruta = pSal->inicio_fruta.pProx;/* aponta para o inicio da lista de frutas */
                 while(pAux_fruta) {
                    fprintf(pont_arq, "%s\n", pAux_fruta->nome);
                    fprintf(pont_arq, "%s\n", pAux_fruta->descricao);
                    pAux_fruta = pAux_fruta->pProx; //Passa para a próxima fruta
             }
            pSal = pSal->pProx; //Passa para a próxima letra
        }
        fclose(pont_arq);
    }
  } else {
        cout << "Erro ao gravar arquivo!";
        system("pause");
    }
  pAux_dicio = NULL;
  pAux_fruta = NULL;
}

/****************** FUNCAO LER ******************/
void ler(){
    char lido[500];
    int etapa=0;
    FILE *pont_arq;
    pont_arq = fopen("dicionario.txt", "r");
    if(pont_arq) {
      pAux_dicio = &inicio_dicio;
      while(!feof(pont_arq)) {
          if(fgets(lido, 500, pont_arq)) {
            lido[strlen(lido)-1] = '\0';
            switch(etapa) {
            case 0:
                pAux_dicio = &inicio_dicio;
                while((pAux_dicio->pProx) && (toupper(pAux_dicio->inicial) != toupper(lido[0]))){
                    pAnt_dicio = pAux_dicio;
                    pAux_dicio = pAux_dicio->pProx;
                }
                if(toupper(pAux_dicio->inicial) != toupper(lido[0])) { //Inicial não existe
                    pAux_dicio->pProx = new Dicionario;
                    pAux_dicio = pAux_dicio->pProx;
                    pAux_dicio->pProx = NULL;
                    pAux_dicio->inicial = lido[0];
                    pLer_fruta = &pAux_dicio->inicio_fruta;
                    pLer_fruta->pProx = new Fruta;
                    pAux_fruta = pLer_fruta->pProx;
                    strcpy(pAux_fruta->nome, lido);
                } else {
                    pLer_fruta = &pAux_dicio->inicio_fruta;
                    while(pLer_fruta->pProx){
                        pLer_fruta = pLer_fruta->pProx;
                    }
                    pAux_fruta->pProx = new Fruta;
                    pAux_fruta = pAux_fruta->pProx;
                }
                strcpy(pAux_fruta->nome, lido);
                cont_fruta++;
            break;
            case 1:
                strcpy(pAux_fruta->descricao, lido);
                etapa = -1;
                break;
            }
            etapa++;
          }
      }
    }
    else{
     cout << "Sem dados no arquivo\n";
     system("pause");
    }

}//função onde devemos ordenar a partir do arquivo;


/****************** FUNCAO INSERIR ******************/
void inserir_fruta(){
    pAux_dicio = &inicio_dicio;
    //Verifica inicial

    gotoxy(0, 1);
    cout << "Informe a fruta que deseja inserir: ";
    gotoxy(0, 2);
    cout << "Descrição da fruta: ";
    gotoxy(37, 1);
    fflush(stdin);
    gets(palavra);

    while((pAux_dicio->pProx) && (toupper(pAux_dicio->inicial) != toupper(palavra[0]))){
        pAnt_dicio = pAux_dicio;
        pAux_dicio = pAux_dicio->pProx;
    }
    if(pAux_dicio->inicial != palavra[0]) { //Inicial não encontrada
        pAux_dicio->pProx = new Dicionario; //Cria novo nodo para essa inicial
        pAux_dicio = pAux_dicio->pProx;
        pAux_dicio->inicial = palavra[0];
        pAux_dicio->pProx = NULL; //Faz o próximo item(último) apontar para nulo(necessário)
    }
    //Validar palavra
    pAux_fruta = &pAux_dicio->inicio_fruta;
    while((pAux_fruta->pProx) && (strcmp(pAux_fruta->nome, palavra) != 0)) {
        pAux_fruta = pAux_fruta->pProx;
    }
    if(strcmp(pAux_fruta->nome, palavra) == 0) { //Palavra já inserida
        cout << "Fruta já inserida!";
    } else { //Cria espaço para nova fruta
        pAux_dicio->quant++;
        pAux_fruta->pProx = new Fruta;
        pAux_fruta = pAux_fruta->pProx;
        strcpy(pAux_fruta->nome, palavra);
        gotoxy(21, 2);
        fflush(stdin);
        gets(pAux_fruta->descricao);
        cont_fruta++;
    }
    gravar();
    pAux_dicio = NULL;
    pAux_fruta = NULL;
}

/****************** FUNCAO BUSCAR ******************/
Fruta* buscar(){

    cout<<"Informe a fruta\n:";
    fflush(stdin);
    gets(elemento);
    pAux_dicio=&inicio_dicio;
    if(pAux_dicio->pProx!=NULL){
        pbuscarLetra=pAux_dicio->pProx;
        while(pbuscarLetra){
           if(toupper(elemento[0])==toupper(pbuscarLetra->inicial)){
               pbuscarFruta=&pbuscarLetra->inicio_fruta;
               while(pbuscarFruta->pProx){
                    pbuscarFruta=pbuscarFruta->pProx;
                    if(strcmp(elemento, pbuscarFruta->nome)==0){
                        return pbuscarFruta;
                    }
               }
           }
           pbuscarLetra=pbuscarLetra->pProx ;
        }
    } else {
        cout<<"\nNão existe fruta cadastrada na lista!\n";
    }
}

/****************** FUNCAO EXCLUIR INICIAL ******************/
void excluir_inicial(){

}


/****************** FUNCAO EXCLUIR ******************/
void menu_excluir(){

}

/****************** FUNCAO ALTERAR ******************/
void alterar(Fruta *achada){
    if(inicio_dicio.pProx){
        pAux_fruta = achada;
        fflush(stdin);
        cout<<"\nNova descrição\n:";
        gets(pAux_fruta->descricao);
        gravar();
    } else {
        cout << "Não existem registros de frutas!\n";
    }
}

/****************** FUNCAO CABEÇALHO DE EXIBIR ******************/
void cabecalhoExibir() {
    cout<<"                       *******************FRUTAS DO DICIONÁRIO*********************";
    gotoxy(0, cont_linha);
    cout << "----------------------------------------------------------------------------------------------------------------";
    gotoxy(0, cont_linha+1);
    cout << "|Nome ";
    gotoxy(50, cont_linha+1);
    cout << "| Descrição ";
    gotoxy(111, cont_linha+1);
    cout << "|";
    gotoxy(0, cont_linha+2);
    cout << "----------------------------------------------------------------------------------------------------------------";
    cont_linha=cont_linha+2;
}

void cabecalhoExibirReferecia() {
    cout<<"                         *******************BUSCAR POR RELEVÂNCIA*********************\n";
    cout << "----------------------------------------------------------------------------------------------------------------";
    gotoxy(0, cont_linha+1);
    cout << "|Qtd ";
    gotoxy(6, cont_linha+1);
    cout << "|Nome ";
    gotoxy(50, cont_linha+1);
    cout << "| Descrição";
    gotoxy(111, cont_linha+1);
    cout<<"|";
    gotoxy(0, cont_linha+2);
    cout << "----------------------------------------------------------------------------------------------------------------";
    cont_linha=cont_linha+2;
}

void exibirReferencia(){
    char aux[500];
    int qual, cont=0, cont2=1;
    float quant;
            gotoxy(0, cont_linha+1);
            cout << "|" << pAux_fruta->relevancia;
            gotoxy(6, cont_linha+1);
            cout << "|"<<pAux_fruta->nome;
            if(strlen(pAux_fruta->descricao)<60){
            gotoxy(50, cont_linha+1);
            cout << "|" << pAux_fruta->descricao;
                        gotoxy(111, cont_linha+1);
                        cout<<"|";
                        cont_linha++;
                        gotoxy(0, cont_linha+1);
                        cout << "----------------------------------------------------------------------------------------------------------------";
                        cont_linha++;
                        }
                        else{
                          strcpy(aux,pAux_fruta->descricao);

                              for(quant=0;quant<=strlen(aux)/60;quant++){
                                gotoxy(50, cont_linha+1);
                                cout << "|";
                                gotoxy(51, cont_linha+1);
                                for(cont;cont<(59*cont2);cont++){
                                   cout<<aux[cont];
                                }
                                gotoxy(111, cont_linha+1);
                                cout << "|";
                                cont_linha++;
                                cont2++;
                           }
                           cont2=0;
                        gotoxy(0, cont_linha+1);
                        cout << "----------------------------------------------------------------------------------------------------------------";
                        cont_linha++;
                          }

}


/****************** FUNCAO EXIBIR FRUTA ******************/
void exibir_fruta(Fruta *exibir){
    char aux[500];
    int qual, cont=0, cont2=1;
    float quant;

    gotoxy(0, cont_linha+1);
    cout << "|" << exibir->nome;
     if(strlen(exibir->descricao)<60){
            gotoxy(50, cont_linha+1);
            cout << "|" <<exibir->descricao;
            gotoxy(111, cont_linha+1);
            cout<<"|";
            cont_linha++;
            gotoxy(0, cont_linha+1);
            cout << "----------------------------------------------------------------------------------------------------------------";
            cont_linha++;
                }
                else{
                 strcpy(aux,exibir->descricao);
                    for(quant=0;quant<=strlen(aux)/60;quant++){
                    gotoxy(50, cont_linha+1);
                    cout << "|";
                    gotoxy(51, cont_linha+1);
                        for(cont;cont<(59*cont2);cont++){
                                cout<<aux[cont];
                            }
                            gotoxy(111, cont_linha+1);
                            cout << "|";
                            cont_linha++;
                            cont2++;
                           }
                           cont2=0;
                    gotoxy(0, cont_linha+1);
                    cout << "----------------------------------------------------------------------------------------------------------------";
                    cont_linha++;
                    }
}

/****************** FUNCAO EXIBIR INICIAL ******************/
 void exibir_inicial(){ //todas palavras de tal letra
    pAux_dicio = &inicio_dicio;
    cont_linha = 1;
    cout << "Inicial: ";
    cin >> letra;
    while((pAux_dicio->pProx) && (toupper(pAux_dicio->inicial) != toupper(letra))){
        pAux_dicio = pAux_dicio->pProx;
    }
    if(toupper(pAux_dicio->inicial) != toupper(letra)) { //Inicial não encontrada
        cout << "Essa inicial não existe!";
        system("pause");
    } else {
        cabecalhoExibir();
        pAux_fruta = &pAux_dicio->inicio_fruta;
        while(pAux_fruta->pProx) {
            pAux_fruta = pAux_fruta->pProx;
            exibir_fruta(pAux_fruta);
        }
        cout << "\n";
    }
 }



void listar_tudo(Dicionario exibir){
    cont_linha = 1;
    if(exibir.pProx) {
        cabecalhoExibir();
        pAux_dicio = &exibir;
        while(pAux_dicio->pProx) {
            pAux_dicio = pAux_dicio->pProx;
            pAux_fruta = &pAux_dicio->inicio_fruta;
            while(pAux_fruta->pProx) {
                pAux_fruta = pAux_fruta->pProx;
                exibir_fruta(pAux_fruta);
            }
        }
        cout << "\n";
    } else {
        cout << "Não existem registros de frutas!\n";
    }
}

/****************** FUNCAO EXCLUIR FRUTA ******************/
void excluir_fruta(){
    if(inicio_dicio.pProx){
        char elemento[40];
        int encontrou;
        cout<<"Informe a fruta\n:";
        fflush(stdin);
        gets(elemento);
        pAux_dicio=&inicio_dicio;
        if(pAux_dicio->pProx!=NULL){
            pbuscarLetra=pAux_dicio->pProx;
            while(pbuscarLetra){
                pAnt_dicio = pbuscarLetra;
               if(toupper(elemento[0])==toupper(pbuscarLetra->inicial)){
                   pbuscarFruta=&pbuscarLetra->inicio_fruta;
                   while(pbuscarFruta->pProx){
                        pAnt_fruta = pbuscarFruta; //Anterior recebe atual
                        pbuscarFruta=pbuscarFruta->pProx; //Atual recebe próximo
                        if(strcmp(elemento, pbuscarFruta->nome)==0){
                            //Fruta encontrada
                            encontrou = 1;
                            pAnt_fruta->pProx = pbuscarFruta->pProx;
                            delete pbuscarFruta;
                        }
                   }
                   if(pbuscarLetra->inicio_fruta.pProx == NULL){
                        if(pbuscarLetra->pProx) { //Não é o último da lista
                            if(pAnt_dicio != pbuscarLetra) { //Tem anterior
                                pAnt_dicio->pProx = pbuscarLetra->pProx;
                                delete pbuscarLetra;
                                pbuscarLetra = pAnt_dicio->pProx;
                                pbuscarLetra->pAnt = pAnt_dicio;
                            } else { //Não tem anterior
                                inicio_dicio.pProx = pbuscarLetra->pProx;
                                pbuscarLetra = inicio_dicio.pProx;
                                delete pAnt_dicio;
                                pbuscarLetra->pAnt = &inicio_dicio;
                            }
                        } else { //É o último da lista
                            if(inicio_dicio.pProx != pbuscarLetra) { // Tem anterior
                                pAnt_dicio->pProx = NULL;
                                pbuscarLetra = pAnt_dicio;
                            } else { //Não tem anterior
                                pbuscarLetra = &inicio_dicio;
                                pbuscarLetra->pProx = NULL;
                            }
                        }
                   }
               }
               pbuscarLetra=pbuscarLetra->pProx;
            }
            if(encontrou != 1) {
                cout << "Fruta " << elemento << " não encontrada!\n";
                system("pause");
            }
        } else {
            cout<<"\nNão existe fruta cadastrada na lista!\n";
        }
    } else {
        cout << "Não existem registros de frutas!\n";
    }
    pAux_dicio = NULL;
    pAux_fruta = NULL;
    gravar();
}

/****************** FUNCAO LISTAR REMISSO ******************/
void listar_remisso(){//exibir como tá no arquivo
    listar_tudo(inicio_dicio);
}

/****************** FUNCAO MENU EXIBIR ******************/
void menu_exibir(){
    if(inicio_dicio.pProx){
        int op=1;
        do{
           system("cls");
           cout<<"\t\tComo deseja exibir?\n";
           cout<<"Voltar-0\nExibir remisso-1\nExibir letra-2\nExibir Fruta-3\n:";
           cin>>op;
           switch(op){
           case 0:
           break;
           case 1:
               system("cls");
               listar_remisso();
               system("pause");
           break;
           case 2:
               system("cls");
               exibir_inicial();
               system("pause");
           break;
           case 3:
               system("cls");
               pLer_fruta = buscar();
               if(pLer_fruta!= NULL){
                   system("cls");
                   cont_linha = 1;
                   cabecalhoExibir();
                   exibir_fruta(pLer_fruta);
                   cout << "\n";
                   system("pause");
               }else{
                 printf("Essa fruta não foi adicionado(a) ao dicionário\n");
                 system("pause");
               }
           break;
           default:
            cout<<"\nOpção inválida, tente novamente!\n";
            system("pause");
           break;
           }
        }while(op!=0);
    } else {
        cout << "Não existem registros de frutas!\n";
    }
}

/****************** FUNCAO ORDENAR ALFABÉTICO ******************/
void ordenar_alfabetico() { //Ordenação por comparação
    //##########Precisa criar uma lista auxiliar e usar ela para ordenar
    pAux_dicio = inicio_dicio.pProx;
    Dicionario *pAux_Temp_Dicio;
    pAux_Temp_Dicio = &dicio_temp;
    while(pAux_dicio) { //Percorre os nodos do dicionario
        pAux_Temp_Dicio->pProx = new Dicionario;//Cria novo nodo para dicionario temporario
        pAux_Temp_Dicio = pAux_Temp_Dicio->pProx; //Ponteiro temporario aponta para novo nodo
        pAux_fruta_temp = &pAux_Temp_Dicio->inicio_fruta; //Ponteira auxiliar temp para fruta aponta para o inicio de frutas
        pAux_Temp_Dicio->inicial = pAux_dicio->inicial; //Copia a inicial da original para temporario
        pAux_fruta = pAux_dicio->inicio_fruta.pProx;//Aponta para o primeiro da lista de frutas com inicial igual
        while(pAux_fruta){ //Percorre as frutas de um nodo original
            pAux_fruta_temp->pProx = new Fruta; //Cria novo nodo para fruta no dicionario temporario
            pAux_fruta_temp = pAux_fruta_temp->pProx;
            strcpy(pAux_fruta_temp->nome, pAux_fruta->nome); //Copia o nome para a temporaria
            strcpy(pAux_fruta_temp->descricao, pAux_fruta->descricao); //Copia a descrição para a temporária
            pAux_fruta_temp->pProx = NULL;
            pAux_fruta = pAux_fruta->pProx;
        }
        pAux_dicio = pAux_dicio->pProx;
    }
    //Ordenar lista temporária principal
    pAnt_dicio = dicio_temp.pProx;
    Dicionario *temporario;
    while(pAnt_dicio->pProx){
        pAux_dicio = pAnt_dicio->pProx;
        while(pAux_dicio){
            //cout << "\ncomparando " << pAnt_dicio->inicial << " e " << pAux_dicio->inicial << " ";
            if(pAnt_dicio->inicial > pAux_dicio->inicial){
                //cout << pAnt_dicio->inicial << " E maior que " << pAux_dicio->inicial;
                //cout << "\ntrocar " << pAnt_dicio->inicial << " e " << pAux_dicio->inicial << " ";
                /*
                X = A
                A = B
                B = X
                */
                temporario->inicial = pAnt_dicio->inicial;
                temporario->inicio_fruta = pAnt_dicio->inicio_fruta;

                pAnt_dicio->inicial = pAux_dicio->inicial;
                pAnt_dicio->inicio_fruta = pAux_dicio->inicio_fruta;

                pAux_dicio->inicial = temporario->inicial;
                pAux_dicio->inicio_fruta = temporario->inicio_fruta;
            }
            pAux_dicio = pAux_dicio->pProx;
        }
        pAnt_dicio = pAnt_dicio->pProx;
    }
    //Ordenando as sub-listas
    pAux_dicio = dicio_temp.pProx;
    while(pAux_dicio){
        pAux_fruta = pAux_dicio->inicio_fruta.pProx;
        while(pAux_fruta->pProx){
            pProx_fruta = pAux_fruta->pProx;
            while(pProx_fruta) {
                //cout << " comparando " << pAux_fruta->nome << " e " << pProx_fruta->nome << "\n";
                if(strcmp(pAux_fruta->nome, pProx_fruta->nome) > 0) {
                    //cout << pAux_fruta->nome << " maior que " << pProx_fruta->nome << "\n";
                    strcpy(tempFruta->nome, pAux_fruta->nome);
                    strcpy(tempFruta->descricao, pAux_fruta->descricao);

                    strcpy(pAux_fruta->nome, pProx_fruta->nome);
                    strcpy(pAux_fruta->descricao, pProx_fruta->descricao);

                    strcpy(pProx_fruta->nome, tempFruta->nome);
                    strcpy(pProx_fruta->descricao, tempFruta->descricao);
                }
                pProx_fruta = pProx_fruta->pProx;
            }
            pAux_fruta = pAux_fruta->pProx;
        }
        pAux_dicio = pAux_dicio->pProx;
    }
    //Exibindo lista temporária
    listar_tudo(dicio_temp);
}


/****************** FUNCAO MENU ORDENAR ******************/
void ordenar(){//escolhe como serão ordenadas as palavras(alfabética, criação e randomica);
    if(inicio_dicio.pProx){
        int op = -1;
        do {
            system("cls");
            cout << "SAIR [0]\nOrdenar por: \nALFABÉTICA [1] \nCRIAÇÃO [2] \nRANDÔMICA [3] \n:";
            cin >> op;
            switch(op) {
            case 0:
            break;
            case 1:
                system("cls");
                ordenar_alfabetico();
                system("pause");
            break;
            case 2:
                system("cls");
                listar_remisso();
                system("pause");
            break;
            case 3:
                system("cls");
                //ordenar_randomica();
                system("pause");
            break;
            default:
                cout<<"\nOpção inválida, tente novamente!\n";
                system("pause");
            break;
            }
        } while(op != 0);
    } else {
        cout << "Não existem registros de frutas!\n";
    }
}

/****************** FUNCAO ORDENAR POR RELEVÂNCIA ******************/
void ordenar_relevancia(){
    //Ordenando as sub-listas
    pAux_dicio = dicio_temp.pProx;
    while(pAux_dicio){
        pAux_fruta = pAux_dicio->inicio_fruta.pProx;
        while(pAux_fruta->pProx){
            pProx_fruta = pAux_fruta->pProx;
            while(pProx_fruta) {
                //cout << " comparando " << pAux_fruta->nome << " e " << pProx_fruta->nome << "\n";
                if(pAux_fruta->relevancia < pProx_fruta->relevancia) {
                    //cout << pAux_fruta->nome << " menor que " << pProx_fruta->nome << "\n";
                    strcpy(tempFruta->nome, pAux_fruta->nome);
                    strcpy(tempFruta->descricao, pAux_fruta->descricao);
                    tempFruta->relevancia = pAux_fruta->relevancia;

                    strcpy(pAux_fruta->nome, pProx_fruta->nome);
                    strcpy(pAux_fruta->descricao, pProx_fruta->descricao);
                    pAux_fruta->relevancia = pProx_fruta->relevancia;

                    strcpy(pProx_fruta->nome, tempFruta->nome);
                    strcpy(pProx_fruta->descricao, tempFruta->descricao);
                    pProx_fruta->relevancia = tempFruta->relevancia;
                }
                pProx_fruta = pProx_fruta->pProx;
            }
            pAux_fruta = pAux_fruta->pProx;
        }
        pAux_dicio = pAux_dicio->pProx;
    }
}

/****************** FUNCAO PESQUISAR POR RELEVÂNCIA ******************/
void pesquisar() {
    if(inicio_dicio.pProx) {
        Fruta *pPesq_fruta;
        Dicionario *pPesq_dicio, *pAux_Temp_Dicio;
        dicio_temp.pProx = NULL;
        char pesquisa[40];
        int indice = 0, quantidade = 0;
        cout<<"Informe o que quer pesquisar\n:";
        fflush(stdin);
        gets(pesquisa);
        if(strlen(pesquisa) > 1) {
            pPesq_dicio = &inicio_dicio;
            while(pPesq_dicio->pProx) {
                pPesq_dicio = pPesq_dicio->pProx;
                pPesq_fruta = &pPesq_dicio->inicio_fruta;
                while(pPesq_fruta->pProx) {
                    pPesq_fruta = pPesq_fruta->pProx;
                    //Verifica se a pesquisa esta na descrição
                    //cout << "Verificando " << pPesq_fruta->nome << "\n";
                    indice = 0;
                    quantidade = 0;
                    do{
                        indice = existe(pPesq_fruta->descricao, pesquisa, indice);
                        if(indice != -1) {
                            quantidade++;
                            //Adicionar em lista temporária
                            //cout << quantidade << " quantidade em " << pPesq_fruta->nome << "\n";
                            pAux_dicio = &dicio_temp;
                            if(dicio_temp.pProx == NULL) {
                                //cout << "nova inicial primeira";
                                pAux_dicio->pProx = new Dicionario; //Cria novo nodo para essa inicial
                                pAux_dicio = pAux_dicio->pProx;
                                pAux_dicio->inicial = pesquisa[0];
                                pAux_dicio->pProx = NULL; //Faz o próximo item(último) apontar para nulo(necessário)
                            } else {
                                while((pAux_dicio->pProx) && (toupper(pAux_dicio->inicial) != toupper(pesquisa[0]))){
                                    pAnt_dicio = pAux_dicio;
                                    pAux_dicio = pAux_dicio->pProx;
                                }
                                if(toupper(pAux_dicio->inicial) != toupper(pesquisa[0])) { //Inicial não encontrada
                                    pAux_dicio->pProx = new Dicionario; //Cria novo nodo para essa inicial
                                    pAux_dicio = pAux_dicio->pProx;
                                    pAux_dicio->inicial = pesquisa[0];
                                    //cout << "inicial: " << pAux_dicio->inicial;
                                    pAux_dicio->pProx = NULL; //Faz o próximo item(último) apontar para nulo(necessário)
                                }
                            }

                            //Validar palavra
                            pAux_fruta = &pAux_dicio->inicio_fruta;
                            while((pAux_fruta->pProx) && (strcmp(pAux_fruta->nome, pPesq_fruta->nome) != 0)) {
                                pAux_fruta = pAux_fruta->pProx;
                            }
                             //Cria espaço para nova fruta
                             if(strcmp(pAux_fruta->nome, pPesq_fruta->nome) != 0) {
                                pAux_fruta->pProx = new Fruta;
                                pAux_fruta = pAux_fruta->pProx;
                                pAux_fruta->pProx = NULL;
                                strcpy(pAux_fruta->nome, pPesq_fruta->nome);
                                strcpy(pAux_fruta->descricao, pPesq_fruta->descricao);
                                pAux_fruta->relevancia = 1;
                             } else {
                                 //cout << "incrementa";
                                 pAux_fruta->relevancia++;
                             }
                        }
                    } while(indice != -1);
                }
            }
            //Ordenar por relevância
            ordenar_relevancia();
            //Exibir por relevância
            system("cls");
            cont_linha = 1;
            if(dicio_temp.pProx) {
                cabecalhoExibirReferecia();
                pAux_dicio = &dicio_temp;
                while(pAux_dicio->pProx) {
                    pAux_dicio = pAux_dicio->pProx;
                    pAux_fruta = &pAux_dicio->inicio_fruta;
                    while(pAux_fruta->pProx) {
                        pAux_fruta = pAux_fruta->pProx;
                        exibirReferencia();
                        }
                    }
                }
                cout << "\n";
            }
    } else {
        cout << "Não existem registros de frutas!\n";
    }
}

/****************** FUNCAO MENU PRINCIPAL ******************/
void menu(){
    int op=1;
    do{
       system("cls");
       cout<<"\t\tO QUE DESEJA FAZER?\n";
       cout<<"SAIR-0\nINSERIR FRUTA(S)-1\nEXIBIR DICIONÁRIO-2\nEXCLUIR FRUTA(S)-3\nALTERAR FRUTA(S)-4\nORDENAR DICIONÁRIO-5\nPESQUISAR-6\n:";
       cin>>op;
       switch(op){
       case 0:
           system("cls");
           cout<<"TCHAU";
       break;
       case 1:
           system("cls");
           inserir_fruta();
           system("pause");
       break;
       case 2:
           system("cls");
           menu_exibir();
           system("pause");
       break;
       case 3:
           system("cls");
           excluir_fruta();
           system("pause");
       break;
       case 4:
           system("cls");
            if(inicio_dicio.pProx){
                alterar(buscar());
            } else {
                cout << "Não existem registros de frutas!\n";
            }
           system("pause");
       break;
       case 5:
           system("cls");
           ordenar();
           system("pause");
       break;
       case 6:
           system("cls");
           pesquisar();
           system("pause");
       break;
       default:
        cout<<"\nOpção inválida, tente novamente!\n";
        system("pause");
       break;
       }
    }while(op!=0);
}

/****************** FUNCAO PRINCIPAL ******************/
int main() {
    setlocale(LC_ALL, "Portuguese");
    ler();
    menu();
}
