#include "usuario.h"
#include <iostream>

Usuario::Usuario(int id, const std::string& nome, const std::string& cpf, const std::string& telefone)
    : id(id), nome(nome), cpf(cpf), telefone(telefone), armarioId(0) {}

void Usuario::serialize(std::ostream& os) const {
    os.write(reinterpret_cast<const char*>(&id), sizeof(id));
    
    size_t tamanho;
    
    tamanho = nome.size();
    os.write(reinterpret_cast<const char*>(&tamanho), sizeof(tamanho));
    os.write(nome.c_str(), tamanho);
    
    tamanho = cpf.size();
    os.write(reinterpret_cast<const char*>(&tamanho), sizeof(tamanho));
    os.write(cpf.c_str(), tamanho);
    
    tamanho = telefone.size();
    os.write(reinterpret_cast<const char*>(&tamanho), sizeof(tamanho));
    os.write(telefone.c_str(), tamanho);
    
    os.write(reinterpret_cast<const char*>(&armarioId), sizeof(armarioId));
}

void Usuario::deserialize(std::istream& is) {
    is.read(reinterpret_cast<char*>(&id), sizeof(id));
    
    size_t tamanho;
    
    is.read(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));
    nome.resize(tamanho);
    is.read(&nome[0], tamanho);
    
    is.read(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));
    cpf.resize(tamanho);
    is.read(&cpf[0], tamanho);
    
    is.read(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));
    telefone.resize(tamanho);
    is.read(&telefone[0], tamanho);
    
    is.read(reinterpret_cast<char*>(&armarioId), sizeof(armarioId));
}
