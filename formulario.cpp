#ifndef FORMULARIO_CPP     // Verifica se ATUADOR_CPP não foi definido ainda
#define FORMULARIO_CPP     // Define ATUADOR_CPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "pergunta.cpp"

using namespace std;

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
        cout << "Formulario: " << nomeFormulario << "\n";
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

    void salvarRespostas(const string& filename) const {
        ofstream outFile(filename);
        for (const Pergunta* pergunta : perguntas) {
            pergunta->salvarResposta(outFile);
        }
    }

    string getNomeFormulario() const {
        return nomeFormulario;
    }
};

#endif  