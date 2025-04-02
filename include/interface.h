#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include <vector>
#include <ncurses.h>

class Interface {
private:
    WINDOW* janela;
    int altura;
    int largura;
    int startY;
    int startX;

    void desenharBorda();
    void limparJanela();

public:
    Interface();
    ~Interface();

    // Inicialização
    void inicializar();
    void finalizar();

    // Elementos básicos
    void mostrarTitulo(const std::string& titulo);
    void mostrarMensagem(const std::string& mensagem, int linha = -1);
    void mostrarErro(const std::string& erro);
    void limparLinha(int linha);
    void limparTela();

    // Entrada de dados
    std::string lerString(const std::string& prompt, int maxLength = 50);
    int lerInteiro(const std::string& prompt);
    char lerCaracter(const std::string& prompt);

    // Menus
    int mostrarMenu(const std::string& titulo, const std::vector<std::string>& opcoes);
    bool confirmar(const std::string& mensagem);

    // Tabelas
    void mostrarTabela(const std::vector<std::vector<std::string>>& dados,
                      const std::vector<std::string>& cabecalho,
                      const std::vector<int>& larguras);

    // Utilitários
    void aguardarTecla();
    void refresh();
};

#endif // INTERFACE_H
