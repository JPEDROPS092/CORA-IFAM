#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
private:
    int id;
    std::string nome;
    std::string cpf;
    std::string telefone;
    int armarioId;

public:
    Usuario(int id = 0, const std::string& nome = "", const std::string& cpf = "", const std::string& telefone = "");
    
    // Getters
    int getId() const { return id; }
    std::string getNome() const { return nome; }
    std::string getCpf() const { return cpf; }
    std::string getTelefone() const { return telefone; }
    int getArmarioId() const { return armarioId; }
    
    // Setters
    void setNome(const std::string& novoNome) { nome = novoNome; }
    void setCpf(const std::string& novoCpf) { cpf = novoCpf; }
    void setTelefone(const std::string& novoTelefone) { telefone = novoTelefone; }
    void setArmarioId(int novoArmarioId) { armarioId = novoArmarioId; }
    
    // Serialização
    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);
};

#endif // USUARIO_H
