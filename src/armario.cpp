#include "armario.h"
#include <iostream>

Armario::Armario(int id, int numero, const std::string& setor)
    : id(id), numero(numero), setor(setor), ocupado(false), usuarioId(0), dataOcupacao(0) {}

void Armario::ocupar(int idUsuario) {
    ocupado = true;
    usuarioId = idUsuario;
    dataOcupacao = std::time(nullptr);
}

void Armario::desocupar() {
    ocupado = false;
    usuarioId = 0;
    dataOcupacao = 0;
}

void Armario::serialize(std::ostream& os) const {
    os.write(reinterpret_cast<const char*>(&id), sizeof(id));
    os.write(reinterpret_cast<const char*>(&numero), sizeof(numero));
    
    size_t tamanho = setor.size();
    os.write(reinterpret_cast<const char*>(&tamanho), sizeof(tamanho));
    os.write(setor.c_str(), tamanho);
    
    os.write(reinterpret_cast<const char*>(&ocupado), sizeof(ocupado));
    os.write(reinterpret_cast<const char*>(&usuarioId), sizeof(usuarioId));
    os.write(reinterpret_cast<const char*>(&dataOcupacao), sizeof(dataOcupacao));
}

void Armario::deserialize(std::istream& is) {
    is.read(reinterpret_cast<char*>(&id), sizeof(id));
    is.read(reinterpret_cast<char*>(&numero), sizeof(numero));
    
    size_t tamanho;
    is.read(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));
    setor.resize(tamanho);
    is.read(&setor[0], tamanho);
    
    is.read(reinterpret_cast<char*>(&ocupado), sizeof(ocupado));
    is.read(reinterpret_cast<char*>(&usuarioId), sizeof(usuarioId));
    is.read(reinterpret_cast<char*>(&dataOcupacao), sizeof(dataOcupacao));
}
