#ifndef MENU_H
#define MENU_H

#include "interface.h"
#include "database.h"
#include <memory>

class Menu {
private:
    std::shared_ptr<Interface> interface;
    std::shared_ptr<Database> db;

    // Menus principais
    void menuArmarios();
    void menuUsuarios();
    void menuRelatorios();

    // Submenu Armários
    void cadastrarArmario();
    void editarArmario();
    void removerArmario();
    void listarArmarios();
    void ocuparArmario();
    void desocuparArmario();

    // Submenu Usuários
    void cadastrarUsuario();
    void editarUsuario();
    void removerUsuario();
    void listarUsuarios();
    void buscarUsuario();

    // Submenu Relatórios
    void relatorioOcupacao();
    void relatorioHistorico();
    void estatisticas();

    // Utilitários
    void mostrarArmario(const Armario& armario);
    void mostrarUsuario(const Usuario& usuario);

public:
    Menu(std::shared_ptr<Interface> interface, std::shared_ptr<Database> db);
    void executar();
};

#endif // MENU_H
