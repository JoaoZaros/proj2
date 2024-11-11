#ifndef PERGUNTA_CPP     // Verifica se ATUADOR_CPP não foi definido ainda
#define PERGUNTA_CPP     // Define ATUADOR_CPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

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

class PerguntaAberta : public Pergunta {
private:
    string resposta;

public:
    PerguntaAberta(const string& texto) : Pergunta(texto) {}

    void exibirPergunta() const override {
        cout << textoPergunta << " (Resposta aberta): ";
    }

    void registrarResposta() override {
        getline(cin, resposta);
    }

    void salvarResposta(ofstream& outFile) const override {
        outFile << textoPergunta << " Resposta: " << resposta << "\n";
    }
};

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
        cout << "Escolha uma opção: ";
    }

    void registrarResposta() override {
        cin >> resposta;
        cin.ignore();
    }

    void salvarResposta(ofstream& outFile) const override {
        outFile << textoPergunta << " Resposta: " << opcoes[resposta - 1] << "\n";
    }
};

class PerguntaEscala : public Pergunta {
private:
    int resposta;
    int escalaMin, escalaMax;

public:
    PerguntaEscala(const string& texto, int min, int max) 
        : Pergunta(texto), escalaMin(min), escalaMax(max), resposta(-1) {}

    void exibirPergunta() const override {
        cout << textoPergunta << " (De " << escalaMin << " a " << escalaMax << "): ";
    }

    void registrarResposta() override {
        cin >> resposta;
        cin.ignore();
    }

    void salvarResposta(ofstream& outFile) const override {
        outFile << textoPergunta << " Resposta: " << resposta << "\n";
    }
};

#endif