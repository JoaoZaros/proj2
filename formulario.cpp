#ifndef FORMULARIO_CPP
#define FORMULARIO_CPP

#include <iostream>
#include <vector>
#include "pergunta.cpp"
#include <fstream>

using namespace std;

// Classe Formulario
class Formulario {
private:
    string nomeFormulario;
    vector<Pergunta*> perguntas;

public:
    Formulario(const string& nome) : nomeFormulario(nome) {}

    ~Formulario() {
        for (Pergunta* pergunta : perguntas) {
            delete pergunta;
        }
    }

    void adicionarPergunta(Pergunta* pergunta) {
        perguntas.push_back(pergunta);
    }

    void exibirFormulario() const {
        for (const Pergunta* pergunta : perguntas) {
            pergunta->exibirPergunta();
        }
    }

    void coletarRespostas() {
        for (Pergunta* pergunta : perguntas) {
            pergunta->exibirPergunta();
            pergunta->registrarResposta();
        }
    }

    void gerarRelatorio(const string& filename) const {
        ofstream outFile(filename);
        for (const Pergunta* pergunta : perguntas) {
            pergunta->salvarResposta(outFile);
        }
    }

    void salvarFormulario(const string& filename) const {
        ofstream outFile(filename, ios::binary);
        size_t nomeSize = nomeFormulario.size();
        outFile.write(reinterpret_cast<const char*>(&nomeSize), sizeof(nomeSize));
        outFile.write(nomeFormulario.c_str(), nomeSize);

        size_t numPerguntas = perguntas.size();
        outFile.write(reinterpret_cast<const char*>(&numPerguntas), sizeof(numPerguntas));

        for (const Pergunta* pergunta : perguntas) {
            // Serialização a ser detalhada dependendo do tipo da pergunta
        }
    }

    void carregarFormulario(const string& filename) {
        ifstream inFile(filename, ios::binary);
        size_t nomeSize;
        inFile.read(reinterpret_cast<char*>(&nomeSize), sizeof(nomeSize));
        nomeFormulario.resize(nomeSize);
        inFile.read(&nomeFormulario[0], nomeSize);

        size_t numPerguntas;
        inFile.read(reinterpret_cast<char*>(&numPerguntas), sizeof(numPerguntas));

        for (size_t i = 0; i < numPerguntas; ++i) {
            // Desserialização a ser detalhada dependendo do tipo da pergunta
        }
    }
};

#endif