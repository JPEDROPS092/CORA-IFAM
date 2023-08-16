#include <stdio.h>
#include <string.h>
#include <locale.h>

#define MAX_ARMARIOS 100
#define MAX_ALUNOS 300

typedef struct {
    int numero;
    int status; // 0 - Disponível, 1 - Reservado, 2 - Em Uso
    int aluno_associado;
} Armario;

typedef struct {
    int matricula;
    char nome[100];
    int armario_associado;
} Aluno;

Armario armarios[MAX_ARMARIOS];
Aluno alunos[MAX_ALUNOS];
int num_armarios = 0;
int num_alunos = 0;
int next_aluno_id = 1;
int next_armario_id = 1;

int encontrarArmarioDisponivel(int serie) {
    for (int i = 0; i < num_armarios; i++) {
        if (armarios[i].status == 0 && armarios[i].aluno_associado == -1) {
            armarios[i].status = 1;
            return i;
        }
    }
    return -1; //  armário Não fica disponivel
}

void cadastrarAluno(const char *nome, int serie) {
    if (num_alunos < MAX_ALUNOS) {
        int armario_index = encontrarArmarioDisponivel(serie);
        if (armario_index != -1) {
            Aluno novo_aluno;
            novo_aluno.matricula = next_aluno_id++;
            strcpy(novo_aluno.nome, nome);
            novo_aluno.armario_associado = armario_index;
            alunos[num_alunos] = novo_aluno;
            num_alunos++;
            armarios[armario_index].aluno_associado = novo_aluno.matricula;
            printf("Aluno cadastrado e armário associado com sucesso!\n");
        } else {
            printf("Erro: Não há armários disponíveis para essa série.\n");
        }
    } else {
        printf("Erro: Limite máximo de alunos atingido\n");
    }
}

void cadastrarArmario() {
    if (num_armarios < MAX_ARMARIOS) {
        Armario novo_armario;
        novo_armario.numero = next_armario_id++;
        novo_armario.status = 0;
        novo_armario.aluno_associado = -1;
        armarios[num_armarios] = novo_armario;
        num_armarios++;
        printf("Armário cadastrado com sucesso!\n");
    } else {
        printf("Erro: Limite máximo de armários atingido\n");
    }
}

void relatorioArmarios() {
    printf("Relatório de Armários:\n");
    for (int i = 0; i < num_armarios; i++) {
        printf("Armário %d: ", armarios[i].numero);
        if (armarios[i].status == 0) {
            printf("Disponível\n");
        } else if (armarios[i].status == 1) {
            printf("Reservado\n");
        } else {
            printf("Em Uso\n");
        }
    }
}

void relatorioAlunos() {
    printf("Relatório de Alunos:\n");
    for (int i = 0; i < num_alunos; i++) {
        printf("Matrícula: %d, Nome: %s, Armário: %d\n", alunos[i].matricula, alunos[i].nome, alunos[i].armario_associado);
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese"); // set localizou
    int opcao;

    do {
        printf("Menu:\n");
        printf("1 - Cadastrar Armário\n");
        printf("2 - Cadastrar Aluno\n");
        printf("3 - Relatório de Armários\n");
        printf("4 - Relatório de Alunos\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarArmario();
                break;
            case 2: {
                char nome[100];
                int serie;
                printf("Digite o nome do aluno: ");
                scanf(" %[^\n]", nome);
                printf("Digite a série do aluno: ");
                scanf("%d", &serie);
                cadastrarAluno(nome, serie);
                break;
            }
            case 3:
                relatorioArmarios();
                break;
            case 4:
                relatorioAlunos();
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida\n");
        }

    } while (opcao != 0);

    return 0;
}
