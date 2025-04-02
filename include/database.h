#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "armario.h"
#include "usuario.h"

class Database {
private:
    std::string dbPath;
    std::unordered_map<int, int> armarioIndex;  // ID -> posição no arquivo
    std::unordered_map<int, int> usuarioIndex;  // ID -> posição no arquivo
    std::unordered_map<std::string, int> cpfIndex;  // CPF -> ID do usuário

    void carregarIndices();
    void salvarIndices();
    int proximoIdArmario();
    int proximoIdUsuario();

public:
    Database(const std::string& path = "data");
    ~Database();

    // Operações de Armário
    std::shared_ptr<Armario> getArmario(int id);
    std::vector<std::shared_ptr<Armario>> getTodosArmarios();
    std::vector<std::shared_ptr<Armario>> getArmariosLivres();
    void salvarArmario(const Armario& armario);
    void removerArmario(int id);

    // Operações de Usuário
    std::shared_ptr<Usuario> getUsuario(int id);
    std::shared_ptr<Usuario> getUsuarioPorCpf(const std::string& cpf);
    std::vector<std::shared_ptr<Usuario>> getTodosUsuarios();
    void salvarUsuario(const Usuario& usuario);
    void removerUsuario(int id);

    // Estatísticas
    int contarArmariosOcupados();
    int contarArmariosLivres();
};

#endif // DATABASE_H
