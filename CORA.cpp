#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <limits>
#include <memory>

using namespace std;

class Armario {
private:
    int numero;
    string ocupante;
    string senha;
    bool ocupado;
    string dataOcupacao;

public:
    Armario(int num = 0) : numero(num), ocupado(false) {}

    void ocupar(const string& nome, const string& novaSenha) {
        ocupante = nome;
        senha = novaSenha;
        ocupado = true;
        
        time_t now = time(0);
        tm* ltm = localtime(&now);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", ltm);
        dataOcupacao = string(buffer);
    }

    void desocupar() {
        ocupante = "";
        senha = "";
        ocupado = false;
        dataOcupacao = "";
    }

    bool estaOcupado() const { return ocupado; }
    int getNumero() const { return numero; }
    string getOcupante() const { return ocupante; }
    string getSenha() const { return senha; }
    string getDataOcupacao() const { return dataOcupacao; }
};

class SistemaArmarios {
private:
    vector<Armario> armarios;
    const string ARQUIVO_DADOS = "armarios.dat";

    void salvarDados() {
        ofstream arquivo(ARQUIVO_DADOS, ios::binary);
        if (!arquivo) {
            cout << "Erro ao abrir arquivo para salvar dados!" << endl;
            return;
        }

        size_t tamanho = armarios.size();
        arquivo.write(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));

        for (const auto& armario : armarios) {
            int numero = armario.getNumero();
            bool ocupado = armario.estaOcupado();
            string ocupante = armario.getOcupante();
            string senha = armario.getSenha();
            string data = armario.getDataOcupacao();

            arquivo.write(reinterpret_cast<char*>(&numero), sizeof(numero));
            arquivo.write(reinterpret_cast<char*>(&ocupado), sizeof(ocupado));

            size_t len = ocupante.length();
            arquivo.write(reinterpret_cast<char*>(&len), sizeof(len));
            arquivo.write(ocupante.c_str(), len);

            len = senha.length();
            arquivo.write(reinterpret_cast<char*>(&len), sizeof(len));
            arquivo.write(senha.c_str(), len);

            len = data.length();
            arquivo.write(reinterpret_cast<char*>(&len), sizeof(len));
            arquivo.write(data.c_str(), len);
        }
        arquivo.close();
    }

    void carregarDados() {
        ifstream arquivo(ARQUIVO_DADOS, ios::binary);
        if (!arquivo) {
            cout << "Nenhum dado anterior encontrado. Iniciando sistema novo." << endl;
            return;
        }

        size_t tamanho;
        arquivo.read(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));

        armarios.clear();
        for (size_t i = 0; i < tamanho; i++) {
            int numero;
            bool ocupado;
            string ocupante, senha, data;

            arquivo.read(reinterpret_cast<char*>(&numero), sizeof(numero));
            arquivo.read(reinterpret_cast<char*>(&ocupado), sizeof(ocupado));

            size_t len;
            arquivo.read(reinterpret_cast<char*>(&len), sizeof(len));
            ocupante.resize(len);
            arquivo.read(&ocupante[0], len);

            arquivo.read(reinterpret_cast<char*>(&len), sizeof(len));
            senha.resize(len);
            arquivo.read(&senha[0], len);

            arquivo.read(reinterpret_cast<char*>(&len), sizeof(len));
            data.resize(len);
            arquivo.read(&data[0], len);

            Armario armario(numero);
            if (ocupado) {
                armario.ocupar(ocupante, senha);
            }
            armarios.push_back(armario);
        }
        arquivo.close();
    }

public:
    SistemaArmarios(int quantidade = 100) {
        for (int i = 1; i <= quantidade; i++) {
            armarios.push_back(Armario(i));
        }
        carregarDados();
    }

    ~SistemaArmarios() {
        salvarDados();
    }

    void ocuparArmario() {
        clear();
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(0, 0, "OCUPAR ARMARIO");
        mvprintw(1, 0, "-------------");
        attroff(COLOR_PAIR(1) | A_BOLD);

        echo(); // Habilita echo para entrada de texto

        char nome[50];
        mvprintw(3, 0, "Nome do ocupante: ");
        refresh();
        getnstr(nome, sizeof(nome)-1);

        char senha[20];
        mvprintw(4, 0, "Digite uma senha: ");
        refresh();
        getnstr(senha, sizeof(senha)-1);

        noecho(); // Desabilita echo

        for (auto& armario : armarios) {
            if (!armario.estaOcupado()) {
                armario.ocupar(nome, senha);
                attron(COLOR_PAIR(4));
                mvprintw(6, 0, "Armario %d ocupado com sucesso!", armario.getNumero());
                attroff(COLOR_PAIR(4));
                refresh();
                getch();
                return;
            }
        }

        attron(COLOR_PAIR(3));
        mvprintw(6, 0, "Nao ha armarios disponiveis!");
        attroff(COLOR_PAIR(3));
        refresh();
        getch();
    }

    void desocuparArmario() {
        clear();
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(0, 0, "DESOCUPAR ARMARIO");
        mvprintw(1, 0, "----------------");
        attroff(COLOR_PAIR(1) | A_BOLD);

        char input[10];
        mvprintw(3, 0, "Numero do armario: ");
        echo();
        refresh();
        getnstr(input, sizeof(input)-1);
        int numero = atoi(input);

        if (numero < 1 || numero > static_cast<int>(armarios.size())) {
            attron(COLOR_PAIR(3));
            mvprintw(5, 0, "Numero de armario invalido!");
            attroff(COLOR_PAIR(3));
            refresh();
            getch();
            return;
        }

        Armario& armario = armarios[numero - 1];
        if (!armario.estaOcupado()) {
            attron(COLOR_PAIR(3));
            mvprintw(5, 0, "Este armario ja esta vazio!");
            attroff(COLOR_PAIR(3));
            refresh();
            getch();
            return;
        }

        char senha[20];
        mvprintw(4, 0, "Digite a senha: ");
        refresh();
        getnstr(senha, sizeof(senha)-1);
        noecho();

        if (senha != armario.getSenha()) {
            attron(COLOR_PAIR(3));
            mvprintw(5, 0, "Senha incorreta!");
            attroff(COLOR_PAIR(3));
            refresh();
            getch();
            return;
        }

        armario.desocupar();
        attron(COLOR_PAIR(4));
        mvprintw(5, 0, "Armario desocupado com sucesso!");
        attroff(COLOR_PAIR(4));
        refresh();
        getch();
    }

    void consultarArmario() {
        clear();
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(0, 0, "CONSULTAR ARMARIO");
        mvprintw(1, 0, "-----------------");
        attroff(COLOR_PAIR(1) | A_BOLD);

        char input[10];
        mvprintw(3, 0, "Numero do armario: ");
        echo();
        refresh();
        getnstr(input, sizeof(input)-1);
        noecho();
        int numero = atoi(input);

        if (numero < 1 || numero > static_cast<int>(armarios.size())) {
            attron(COLOR_PAIR(3));
            mvprintw(5, 0, "Numero de armario invalido!");
            attroff(COLOR_PAIR(3));
            refresh();
            getch();
            return;
        }

        const Armario& armario = armarios[numero - 1];
        mvprintw(5, 0, "Status do armario %d:", numero);
        mvprintw(6, 0, "Ocupado: %s", armario.estaOcupado() ? "Sim" : "Nao");

        if (armario.estaOcupado()) {
            mvprintw(7, 0, "Ocupante: %s", armario.getOcupante().c_str());
            mvprintw(8, 0, "Data de ocupacao: %s", armario.getDataOcupacao().c_str());
        }

        refresh();
        getch();
    }

    void listarArmarios() {
        clear();
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(0, 0, "LISTA DE ARMARIOS");
        mvprintw(1, 0, "----------------");
        attroff(COLOR_PAIR(1) | A_BOLD);

        int ocupados = 0;
        for (const auto& armario : armarios) {
            if (armario.estaOcupado()) ocupados++;
        }

        mvprintw(3, 0, "Total de armarios: %d", armarios.size());
        mvprintw(4, 0, "Armarios ocupados: %d", ocupados);
        mvprintw(5, 0, "Armarios disponiveis: %d", armarios.size() - ocupados);

        mvprintw(7, 0, "Pressione 'D' para ver lista detalhada ou qualquer outra tecla para voltar");
        refresh();

        int ch = getch();
        if (toupper(ch) == 'D') {
            clear();
            attron(COLOR_PAIR(1) | A_BOLD);
            mvprintw(0, 0, "LISTA DETALHADA DE ARMARIOS");
            mvprintw(1, 0, "------------------------");
            attroff(COLOR_PAIR(1) | A_BOLD);

            mvprintw(3, 0, "No  Status     Ocupante");
            mvprintw(4, 0, "------------------------");

            int linha = 5;
            int pagina = 0;
            const int ITENS_POR_PAGINA = 15;

            while (true) {
                clear();
                attron(COLOR_PAIR(1) | A_BOLD);
                mvprintw(0, 0, "LISTA DETALHADA DE ARMARIOS - Pagina %d", pagina + 1);
                mvprintw(1, 0, "------------------------");
                attroff(COLOR_PAIR(1) | A_BOLD);

                mvprintw(3, 0, "No  Status     Ocupante");
                mvprintw(4, 0, "------------------------");

                linha = 5;
                for (size_t i = pagina * ITENS_POR_PAGINA;
                     i < std::min<size_t>((pagina + 1) * ITENS_POR_PAGINA, armarios.size());
                     i++) {
                    const auto& armario = armarios[i];
                    mvprintw(linha, 0, "%3d", armario.getNumero());
                    mvprintw(linha, 4, "%10s", armario.estaOcupado() ? "Ocupado" : "Livre");
                    if (armario.estaOcupado()) {
                        mvprintw(linha, 15, "%s", armario.getOcupante().c_str());
                    }
                    linha++;
                }

                mvprintw(linha + 1, 0, "Use as setas <- -> para navegar entre paginas ou 'Q' para sair");
                refresh();

                int tecla = getch();
                if (tecla == 'q' || tecla == 'Q') break;
                if (tecla == KEY_RIGHT && (pagina + 1) * ITENS_POR_PAGINA < armarios.size()) pagina++;
                if (tecla == KEY_LEFT && pagina > 0) pagina--;
            }
        }
    }
};

int main() {
    // Inicializa ncurses
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Define pares de cores
    init_pair(1, COLOR_WHITE, COLOR_BLUE);   // Para títulos
    init_pair(2, COLOR_BLACK, COLOR_WHITE);  // Para menus
    init_pair(3, COLOR_RED, COLOR_BLACK);    // Para erros
    init_pair(4, COLOR_GREEN, COLOR_BLACK);  // Para sucesso

    SistemaArmarios sistema;
    int opcao;
    int highlight = 0;
    vector<string> menu_items = {
        "Ocupar armario",
        "Desocupar armario",
        "Consultar armario",
        "Listar armarios",
        "Sair"
    };

    do {
        clear();
        // Título
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(0, 0, "SISTEMA DE GERENCIAMENTO DE ARMARIOS");
        mvprintw(1, 0, "--------------------------------");
        attroff(COLOR_PAIR(1) | A_BOLD);

        // Menu
        for(int i = 0; i < menu_items.size(); i++) {
            if(i == highlight) {
                attron(COLOR_PAIR(2) | A_BOLD);
                mvprintw(i+3, 0, "> %s", menu_items[i].c_str());
                attroff(COLOR_PAIR(2) | A_BOLD);
            } else {
                mvprintw(i+3, 2, "%s", menu_items[i].c_str());
            }
        }

        refresh();

        int ch = getch();
        switch(ch) {
            case KEY_UP:
                if(highlight > 0) highlight--;
                break;
            case KEY_DOWN:
                if(highlight < menu_items.size()-1) highlight++;
                break;
            case 10: // Enter key
                switch(highlight) {
                    case 0: sistema.ocuparArmario(); break;
                    case 1: sistema.desocuparArmario(); break;
                    case 2: sistema.consultarArmario(); break;
                    case 3: sistema.listarArmarios(); break;
                    case 4: opcao = 0; break;
                }
                break;
        }
    } while (opcao != 0);

    // Finaliza ncurses
    endwin();
    return 0;

    return 0;
}
