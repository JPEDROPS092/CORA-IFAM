#include <ncurses.h>
#include <locale.h>
#include "ui/MainMenu.hpp"
#include <memory>
#include <iostream>

void initializeColors() {
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);   // Títulos
    init_pair(2, COLOR_BLACK, COLOR_WHITE);  // Menu selecionado
    init_pair(3, COLOR_RED, COLOR_BLACK);    // Erro
    init_pair(4, COLOR_GREEN, COLOR_BLACK);  // Sucesso
    init_pair(5, COLOR_YELLOW, COLOR_BLACK); // Avisos
    init_pair(6, COLOR_CYAN, COLOR_BLACK);   // Info
}

int main() {
    try {
        setlocale(LC_ALL, "");  // Suporte a caracteres especiais
        
        // Inicializa ncurses
        initscr();
        noecho();
        cbreak();
        keypad(stdscr, TRUE);
        curs_set(0);  // Esconde o cursor
        
        // Inicializa cores
        initializeColors();
        
        // Limpa a tela
        clear();
        refresh();
        
        // Cria o menu principal
        int height = LINES - 2;  // -2 para a barra de status
        int width = COLS;
        ui::MainMenu mainMenu(height, width, 0, 0);
        
        // TODO: Implementar login
        // Por enquanto, define como admin para teste
        mainMenu.setUser(1, true);
        mainMenu.updateStatus("Bem-vindo ao Sistema de Gerenciamento de Armários | Pressione 'q' para sair");
        
        // Mostra o menu
        mainMenu.show();
        
        // Finaliza ncurses
        endwin();
        
        return 0;
    } catch (const std::exception& e) {
        endwin();
        std::cerr << "Erro fatal: " << e.what() << std::endl;
        return 1;
    }
}
