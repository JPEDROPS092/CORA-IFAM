#ifndef ARMARIO_H
#define ARMARIO_H

#include <string>
#include <ctime>

class Armario {
private:
    int id;
    int numero;
    std::string setor;
    bool ocupado;
    int usuarioId;
    time_t dataOcupacao;

public:
    Armario(int id = 0, int numero = 0, const std::string& setor = "");
    
    // Getters
    int getId() const { return id; }
    int getNumero() const { return numero; }
    std::string getSetor() const { return setor; }
    bool estaOcupado() const { return ocupado; }
    int getUsuarioId() const { return usuarioId; }
    time_t getDataOcupacao() const { return dataOcupacao; }
    
    // Setters
    void setNumero(int novoNumero) { numero = novoNumero; }
    void setSetor(const std::string& novoSetor) { setor = novoSetor; }
    
    // Operações
    void ocupar(int idUsuario);
    void desocupar();
    
    // Serialização
    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);
};

#endif // ARMARIO_H
