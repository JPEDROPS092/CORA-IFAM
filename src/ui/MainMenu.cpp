#include "ui/MainMenu.hpp"
#include <ncurses.h>
#include <string>
#include <memory>

namespace ui {

MainMenu::MainMenu(int height, int width, int y, int x) {
    window = std::make_shared<Window>(height, width, y, x);
    statusBar = std::make_shared<StatusBar>();
    currentUser = -1;
    isAdmin = false;
}

void MainMenu::setUser(int userId, bool admin) {
    currentUser = userId;
    isAdmin = admin;
}

void MainMenu::updateStatus(const std::string& status) {
    statusBar->update(status);
}

void MainMenu::show() {
    if (isAdmin) {
        showAdminMenu();
    } else {
        showUserMenu();
    }
}

void MainMenu::showAdminMenu() {
    std::vector<std::string> items = {
        "Gerenciar Usuários",
        "Gerenciar Armários",
        "Relatórios",
        "Configurações do Sistema",
        "Sair"
    };

    while (true) {
        window->clear();
        window->printCentered(1, "SISTEMA DE GERENCIAMENTO DE ARMÁRIOS");
        window->printCentered(2, "MENU ADMINISTRADOR");
        
        int choice = window->showMenu(items, 4);
        
        if (choice == items.size() - 1) break;
        handleAdminChoice(choice);
    }
}

void MainMenu::showUserMenu() {
    std::vector<std::string> items = {
        "Visualizar Meu Armário",
        "Solicitar Armário",
        "Liberar Armário",
        "Alterar Senha",
        "Sair"
    };

    while (true) {
        window->clear();
        window->printCentered(1, "SISTEMA DE GERENCIAMENTO DE ARMÁRIOS");
        window->printCentered(2, "MENU USUÁRIO");
        
        int choice = window->showMenu(items, 4);
        
        if (choice == items.size() - 1) break;
        handleUserChoice(choice);
    }
}

void MainMenu::handleAdminChoice(int choice) {
    switch (choice) {
        case 0: manageUsers(); break;
        case 1: manageLockers(); break;
        case 2: viewReports(); break;
        case 3: systemSettings(); break;
    }
}

void MainMenu::handleUserChoice(int choice) {
    switch (choice) {
        case 0: viewMyLocker(); break;
        case 1: requestLocker(); break;
        case 2: releaseLocker(); break;
        case 3: changePassword(); break;
    }
}

void MainMenu::manageUsers() {
    std::vector<std::string> items = {
        "Adicionar Usuário",
        "Editar Usuário",
        "Remover Usuário",
        "Listar Usuários",
        "Voltar"
    };

    while (true) {
        window->clear();
        window->printCentered(1, "GERENCIAMENTO DE USUÁRIOS");
        
        int choice = window->showMenu(items, 3);
        if (choice == items.size() - 1) break;

        switch (choice) {
            case 0: {
                Dialog dialog("NOVO USUÁRIO");
                std::string nome = dialog.input("Nome: ");
                std::string cpf = dialog.input("CPF: ");
                std::string senha = dialog.input("Senha: ");
                bool isAdmin = dialog.confirm("Usuário é administrador?");
                // TODO: Implementar lógica de adicionar usuário
                window->showMessage("Usuário adicionado com sucesso!");
                break;
            }
            case 1: {
                Dialog dialog("EDITAR USUÁRIO");
                std::string cpf = dialog.input("CPF do usuário: ");
                // TODO: Implementar lógica de editar usuário
                break;
            }
            case 2: {
                Dialog dialog("REMOVER USUÁRIO");
                std::string cpf = dialog.input("CPF do usuário: ");
                if (dialog.confirm("Tem certeza que deseja remover este usuário?")) {
                    // TODO: Implementar lógica de remover usuário
                }
                break;
            }
            case 3: {
                // TODO: Implementar listagem de usuários
                break;
            }
        }
    }
}

void MainMenu::manageLockers() {
    std::vector<std::string> items = {
        "Adicionar Armário",
        "Editar Armário",
        "Remover Armário",
        "Listar Armários",
        "Manutenção",
        "Voltar"
    };

    while (true) {
        window->clear();
        window->printCentered(1, "GERENCIAMENTO DE ARMÁRIOS");
        
        int choice = window->showMenu(items, 3);
        if (choice == items.size() - 1) break;

        switch (choice) {
            case 0: {
                Dialog dialog("NOVO ARMÁRIO");
                std::string numero = dialog.input("Número: ");
                std::string setor = dialog.input("Setor: ");
                // TODO: Implementar lógica de adicionar armário
                window->showMessage("Armário adicionado com sucesso!");
                break;
            }
            case 1: {
                Dialog dialog("EDITAR ARMÁRIO");
                std::string numero = dialog.input("Número do armário: ");
                // TODO: Implementar lógica de editar armário
                break;
            }
            case 2: {
                Dialog dialog("REMOVER ARMÁRIO");
                std::string numero = dialog.input("Número do armário: ");
                if (dialog.confirm("Tem certeza que deseja remover este armário?")) {
                    // TODO: Implementar lógica de remover armário
                }
                break;
            }
            case 3: {
                // TODO: Implementar listagem de armários
                break;
            }
            case 4: {
                Dialog dialog("MANUTENÇÃO");
                std::string numero = dialog.input("Número do armário: ");
                if (dialog.confirm("Colocar armário em manutenção?")) {
                    // TODO: Implementar lógica de manutenção
                }
                break;
            }
        }
    }
}

void MainMenu::viewReports() {
    std::vector<std::string> items = {
        "Ocupação Atual",
        "Histórico de Uso",
        "Estatísticas",
        "Manutenções",
        "Exportar Relatórios",
        "Voltar"
    };

    while (true) {
        window->clear();
        window->printCentered(1, "RELATÓRIOS");
        
        int choice = window->showMenu(items, 3);
        if (choice == items.size() - 1) break;

        switch (choice) {
            case 0: {
                // TODO: Implementar relatório de ocupação
                break;
            }
            case 1: {
                // TODO: Implementar histórico de uso
                break;
            }
            case 2: {
                // TODO: Implementar estatísticas
                break;
            }
            case 3: {
                // TODO: Implementar relatório de manutenções
                break;
            }
            case 4: {
                Dialog dialog("EXPORTAR");
                if (dialog.confirm("Exportar todos os relatórios?")) {
                    // TODO: Implementar exportação
                }
                break;
            }
        }
    }
}

void MainMenu::systemSettings() {
    std::vector<std::string> items = {
        "Backup do Sistema",
        "Restaurar Backup",
        "Configurações de Email",
        "Logs do Sistema",
        "Voltar"
    };

    while (true) {
        window->clear();
        window->printCentered(1, "CONFIGURAÇÕES DO SISTEMA");
        
        int choice = window->showMenu(items, 3);
        if (choice == items.size() - 1) break;

        switch (choice) {
            case 0: {
                Dialog dialog("BACKUP");
                if (dialog.confirm("Realizar backup do sistema?")) {
                    // TODO: Implementar backup
                }
                break;
            }
            case 1: {
                Dialog dialog("RESTAURAR");
                if (dialog.confirm("Restaurar backup do sistema?")) {
                    // TODO: Implementar restauração
                }
                break;
            }
            case 2: {
                Dialog dialog("EMAIL");
                std::string servidor = dialog.input("Servidor SMTP: ");
                std::string porta = dialog.input("Porta: ");
                std::string email = dialog.input("Email: ");
                std::string senha = dialog.input("Senha: ");
                // TODO: Implementar configuração de email
                break;
            }
            case 3: {
                // TODO: Implementar visualização de logs
                break;
            }
        }
    }
}

void MainMenu::viewMyLocker() {
    // TODO: Implementar visualização do armário do usuário
    window->showMessage("Função em desenvolvimento");
}

void MainMenu::requestLocker() {
    Dialog dialog("SOLICITAR ARMÁRIO");
    std::string setor = dialog.input("Setor desejado: ");
    // TODO: Implementar solicitação de armário
    window->showMessage("Solicitação enviada com sucesso!");
}

void MainMenu::releaseLocker() {
    Dialog dialog("LIBERAR ARMÁRIO");
    if (dialog.confirm("Tem certeza que deseja liberar seu armário?")) {
        // TODO: Implementar liberação de armário
        window->showMessage("Armário liberado com sucesso!");
    }
}

void MainMenu::changePassword() {
    Dialog dialog("ALTERAR SENHA");
    std::string atual = dialog.input("Senha atual: ");
    std::string nova = dialog.input("Nova senha: ");
    std::string confirma = dialog.input("Confirme a nova senha: ");
    
    if (nova != confirma) {
        window->showMessage("As senhas não conferem!", true);
        return;
    }
    
    // TODO: Implementar alteração de senha
    window->showMessage("Senha alterada com sucesso!");
}

}
