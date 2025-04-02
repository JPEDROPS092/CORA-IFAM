#include "database.h"
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <algorithm>

namespace fs = std::filesystem;

Database::Database(const std::string& path) : dbPath(path) {
    // Criar diretório de dados se não existir
    fs::create_directories(dbPath);
    carregarIndices();
}

Database::~Database() {
    salvarIndices();
}

void Database::carregarIndices() {
    std::ifstream indexFile(dbPath + "/indices.dat", std::ios::binary);
    if (!indexFile) return;

    size_t numArmarios, numUsuarios;
    indexFile.read(reinterpret_cast<char*>(&numArmarios), sizeof(numArmarios));
    
    for (size_t i = 0; i < numArmarios; i++) {
        int id, pos;
        indexFile.read(reinterpret_cast<char*>(&id), sizeof(id));
        indexFile.read(reinterpret_cast<char*>(&pos), sizeof(pos));
        armarioIndex[id] = pos;
    }
    
    indexFile.read(reinterpret_cast<char*>(&numUsuarios), sizeof(numUsuarios));
    for (size_t i = 0; i < numUsuarios; i++) {
        int id, pos;
        size_t cpfLen;
        std::string cpf;
        
        indexFile.read(reinterpret_cast<char*>(&id), sizeof(id));
        indexFile.read(reinterpret_cast<char*>(&pos), sizeof(pos));
        indexFile.read(reinterpret_cast<char*>(&cpfLen), sizeof(cpfLen));
        
        cpf.resize(cpfLen);
        indexFile.read(&cpf[0], cpfLen);
        
        usuarioIndex[id] = pos;
        cpfIndex[cpf] = id;
    }
}

void Database::salvarIndices() {
    std::ofstream indexFile(dbPath + "/indices.dat", std::ios::binary);
    
    size_t numArmarios = armarioIndex.size();
    indexFile.write(reinterpret_cast<char*>(&numArmarios), sizeof(numArmarios));
    
    for (const auto& [id, pos] : armarioIndex) {
        indexFile.write(reinterpret_cast<const char*>(&id), sizeof(id));
        indexFile.write(reinterpret_cast<const char*>(&pos), sizeof(pos));
    }
    
    size_t numUsuarios = usuarioIndex.size();
    indexFile.write(reinterpret_cast<char*>(&numUsuarios), sizeof(numUsuarios));
    
    for (const auto& [id, pos] : usuarioIndex) {
        auto usuario = getUsuario(id);
        std::string cpf = usuario->getCpf();
        size_t cpfLen = cpf.length();
        
        indexFile.write(reinterpret_cast<const char*>(&id), sizeof(id));
        indexFile.write(reinterpret_cast<const char*>(&pos), sizeof(pos));
        indexFile.write(reinterpret_cast<const char*>(&cpfLen), sizeof(cpfLen));
        indexFile.write(cpf.c_str(), cpfLen);
    }
}

int Database::proximoIdArmario() {
    if (armarioIndex.empty()) return 1;
    return std::max_element(armarioIndex.begin(), armarioIndex.end(),
        [](const auto& p1, const auto& p2) { return p1.first < p2.first; })->first + 1;
}

int Database::proximoIdUsuario() {
    if (usuarioIndex.empty()) return 1;
    return std::max_element(usuarioIndex.begin(), usuarioIndex.end(),
        [](const auto& p1, const auto& p2) { return p1.first < p2.first; })->first + 1;
}

std::shared_ptr<Armario> Database::getArmario(int id) {
    auto it = armarioIndex.find(id);
    if (it == armarioIndex.end()) return nullptr;

    std::ifstream file(dbPath + "/armarios.dat", std::ios::binary);
    file.seekg(it->second);
    
    auto armario = std::make_shared<Armario>();
    armario->deserialize(file);
    return armario;
}

void Database::salvarArmario(const Armario& armario) {
    std::fstream file(dbPath + "/armarios.dat", std::ios::in | std::ios::out | std::ios::binary);
    if (!file) {
        file.open(dbPath + "/armarios.dat", std::ios::out | std::ios::binary);
    }
    
    int pos;
    auto it = armarioIndex.find(armario.getId());
    
    if (it != armarioIndex.end()) {
        pos = it->second;
        file.seekp(pos);
    } else {
        file.seekp(0, std::ios::end);
        pos = file.tellp();
        armarioIndex[armario.getId()] = pos;
    }
    
    armario.serialize(file);
}

std::shared_ptr<Usuario> Database::getUsuario(int id) {
    auto it = usuarioIndex.find(id);
    if (it == usuarioIndex.end()) return nullptr;

    std::ifstream file(dbPath + "/usuarios.dat", std::ios::binary);
    file.seekg(it->second);
    
    auto usuario = std::make_shared<Usuario>();
    usuario->deserialize(file);
    return usuario;
}

std::shared_ptr<Usuario> Database::getUsuarioPorCpf(const std::string& cpf) {
    auto it = cpfIndex.find(cpf);
    if (it == cpfIndex.end()) return nullptr;
    return getUsuario(it->second);
}

void Database::salvarUsuario(const Usuario& usuario) {
    std::fstream file(dbPath + "/usuarios.dat", std::ios::in | std::ios::out | std::ios::binary);
    if (!file) {
        file.open(dbPath + "/usuarios.dat", std::ios::out | std::ios::binary);
    }
    
    int pos;
    auto it = usuarioIndex.find(usuario.getId());
    
    if (it != usuarioIndex.end()) {
        pos = it->second;
        file.seekp(pos);
    } else {
        file.seekp(0, std::ios::end);
        pos = file.tellp();
        usuarioIndex[usuario.getId()] = pos;
    }
    
    cpfIndex[usuario.getCpf()] = usuario.getId();
    usuario.serialize(file);
}

std::vector<std::shared_ptr<Armario>> Database::getTodosArmarios() {
    std::vector<std::shared_ptr<Armario>> armarios;
    for (const auto& [id, _] : armarioIndex) {
        armarios.push_back(getArmario(id));
    }
    return armarios;
}

std::vector<std::shared_ptr<Armario>> Database::getArmariosLivres() {
    std::vector<std::shared_ptr<Armario>> armarios;
    for (const auto& [id, _] : armarioIndex) {
        auto armario = getArmario(id);
        if (!armario->estaOcupado()) {
            armarios.push_back(armario);
        }
    }
    return armarios;
}

std::vector<std::shared_ptr<Usuario>> Database::getTodosUsuarios() {
    std::vector<std::shared_ptr<Usuario>> usuarios;
    for (const auto& [id, _] : usuarioIndex) {
        usuarios.push_back(getUsuario(id));
    }
    return usuarios;
}

void Database::removerArmario(int id) {
    armarioIndex.erase(id);
}

void Database::removerUsuario(int id) {
    auto usuario = getUsuario(id);
    if (usuario) {
        cpfIndex.erase(usuario->getCpf());
    }
    usuarioIndex.erase(id);
}

int Database::contarArmariosOcupados() {
    int count = 0;
    for (const auto& [id, _] : armarioIndex) {
        if (getArmario(id)->estaOcupado()) count++;
    }
    return count;
}

int Database::contarArmariosLivres() {
    return armarioIndex.size() - contarArmariosOcupados();
}
