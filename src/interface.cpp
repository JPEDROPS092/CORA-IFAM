#include "interface.h"
#include <algorithm>

Interface::Interface() : janela(nullptr) {}

Interface::~Interface() {
    finalizar();
}

void Interface::inicializar() {
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    
    // Cores
    init_pair(1, COLOR_WHITE, COLOR_BLUE);   // Título
    init_pair(2, COLOR_RED, COLOR_BLACK);    // Erro
    init_pair(3, COLOR_GREEN, COLOR_BLACK);  // Sucesso
    init_pair(4, COLOR_YELLOW, COLOR_BLACK); // Destaque
    
    // Dimensões da janela principal
    altura = LINES - 2;
    largura = COLS - 2;
    startY = 1;
    startX = 1;
    
    // Criar janela principal
    janela = newwin(altura, largura, startY, startX);
    box(janela, 0, 0);
    refresh();
    wrefresh(janela);
}

void Interface::finalizar() {
    if (janela) {
        delwin(janela);
        janela = nullptr;
    }
    endwin();
}

void Interface::mostrarTitulo(const std::string& titulo) {
    wattron(janela, COLOR_PAIR(1) | A_BOLD);
    mvwprintw(janela, 1, (largura - titulo.length()) / 2, "%s", titulo.c_str());
    wattroff(janela, COLOR_PAIR(1) | A_BOLD);
    wrefresh(janela);
}

void Interface::mostrarMensagem(const std::string& mensagem, int linha) {
    if (linha == -1) {
        linha = altura - 2;
    }
    wmove(janela, linha, 2);
    wclrtoeol(janela);
    mvwprintw(janela, linha, 2, "%s", mensagem.c_str());
    wrefresh(janela);
}

void Interface::mostrarErro(const std::string& erro) {
    wattron(janela, COLOR_PAIR(2) | A_BOLD);
    mostrarMensagem(erro);
    wattroff(janela, COLOR_PAIR(2) | A_BOLD);
}

void Interface::limparLinha(int linha) {
    wmove(janela, linha, 1);
    wclrtoeol(janela);
    box(janela, 0, 0);
    wrefresh(janela);
}

void Interface::limparTela() {
    werase(janela);
    box(janela, 0, 0);
    wrefresh(janela);
}

std::string Interface::lerString(const std::string& prompt, int maxLength) {
    echo();
    curs_set(1);
    
    char buffer[256];
    mostrarMensagem(prompt, altura - 3);
    
    wmove(janela, altura - 2, 2);
    wclrtoeol(janela);
    box(janela, 0, 0);
    
    wgetnstr(janela, buffer, std::min(maxLength, 255));
    
    noecho();
    curs_set(0);
    
    return std::string(buffer);
}

int Interface::lerInteiro(const std::string& prompt) {
    while (true) {
        std::string entrada = lerString(prompt);
        try {
            return std::stoi(entrada);
        } catch (...) {
            mostrarErro("Por favor, digite um número válido.");
        }
    }
}

char Interface::lerCaracter(const std::string& prompt) {
    mostrarMensagem(prompt, altura - 3);
    noecho();
    wrefresh(janela);
    int ch = wgetch(janela);
    echo();
    return static_cast<char>(ch);
}

int Interface::mostrarMenu(const std::string& titulo, const std::vector<std::string>& opcoes) {
    int selecao = 0;
    int startY = 3;
    
    while (true) {
        limparTela();
        mostrarTitulo(titulo);
        
        for (size_t i = 0; i < opcoes.size(); i++) {
            if (i == selecao) {
                wattron(janela, COLOR_PAIR(4) | A_BOLD);
                mvwprintw(janela, startY + i, 2, "> %s", opcoes[i].c_str());
                wattroff(janela, COLOR_PAIR(4) | A_BOLD);
            } else {
                mvwprintw(janela, startY + i, 2, "  %s", opcoes[i].c_str());
            }
        }
        
        wrefresh(janela);
        
        int tecla = wgetch(janela);
        switch (tecla) {
            case KEY_UP:
                selecao = (selecao - 1 + opcoes.size()) % opcoes.size();
                break;
            case KEY_DOWN:
                selecao = (selecao + 1) % opcoes.size();
                break;
            case '\n':
                return selecao;
        }
    }
}

bool Interface::confirmar(const std::string& mensagem) {
    mostrarMensagem(mensagem + " (S/N)", altura - 3);
    char resposta = lerCaracter("");
    return toupper(resposta) == 'S';
}

void Interface::mostrarTabela(const std::vector<std::vector<std::string>>& dados,
                            const std::vector<std::string>& cabecalho,
                            const std::vector<int>& larguras) {
    int linha = 3;
    int coluna = 2;
    
    // Mostrar cabeçalho
    wattron(janela, A_BOLD);
    for (size_t i = 0; i < cabecalho.size(); i++) {
        mvwprintw(janela, linha, coluna, "%-*s", larguras[i], cabecalho[i].c_str());
        coluna += larguras[i] + 1;
    }
    wattroff(janela, A_BOLD);
    
    // Mostrar dados
    for (const auto& linha_dados : dados) {
        linha++;
        coluna = 2;
        for (size_t i = 0; i < linha_dados.size(); i++) {
            mvwprintw(janela, linha, coluna, "%-*s", larguras[i], linha_dados[i].c_str());
            coluna += larguras[i] + 1;
        }
    }
    
    wrefresh(janela);
}

void Interface::aguardarTecla() {
    mostrarMensagem("Pressione qualquer tecla para continuar...");
    wgetch(janela);
}

void Interface::refresh() {
    wrefresh(janela);
}
