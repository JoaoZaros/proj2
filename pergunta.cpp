#ifndef PERGUNTA_CPP
#define PERGUNTA_CPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Classe base Pergunta
class Pergunta {
protected:
    string textoPergunta;

public:
    Pergunta(const string& texto) : textoPergunta(texto) {}
    virtual ~Pergunta() {}

    virtual void exibirPergunta() const = 0;
    virtual void registrarResposta() = 0;
    virtual void salvarResposta(ofstream& outFile) const = 0;
};

// Classe PerguntaAberta
class PerguntaAberta : public Pergunta {
private:
    string resposta;

public:
    PerguntaAberta(const string& texto) : Pergunta(texto) {}

    void exibirPergunta() const override {
        cout << textoPergunta << " (resposta aberta): ";
    }

    void registrarResposta() override {
        getline(cin, resposta);
    }

    void salvarResposta(ofstream& outFile) const override {
        outFile << "Resposta aberta: " << resposta << "\n";
    }
};

// Classe PerguntaMultiplaEscolha
class PerguntaMultiplaEscolha : public Pergunta {
private:
    vector<string> opcoes;
    int resposta;

public:
    PerguntaMultiplaEscolha(const string& texto, const vector<string>& opcoes)
        : Pergunta(texto), opcoes(opcoes), resposta(-1) {}

    void exibirPergunta() const override {
        cout << textoPergunta << "\n";
        for (size_t i = 0; i < opcoes.size(); ++i) {
            cout << i + 1 << ". " << opcoes[i] << "\n";
        }
    }

    void registrarResposta() override {
        cin >> resposta;
        cin.ignore(); // Limpa o buffer de entrada
    }

    void salvarResposta(ofstream& outFile) const override {
        outFile << "Resposta de múltipla escolha: " << resposta << "\n";
    }
};

// Classe PerguntaEscala
class PerguntaEscala : public Pergunta {
private:
    int resposta;
    int escalaMin, escalaMax;

public:
    PerguntaEscala(const string& texto, int min, int max)
        : Pergunta(texto), escalaMin(min), escalaMax(max), resposta(-1) {}

    void exibirPergunta() const override {
        cout << textoPergunta << " (de " << escalaMin << " a " << escalaMax << "): ";
    }

    void registrarResposta() override {
        cin >> resposta;
        cin.ignore(); // Limpa o buffer de entrada
    }

    void salvarResposta(ofstream& outFile) const override {
        outFile << "Resposta de escala: " << resposta << "\n";
    }
};

#endif