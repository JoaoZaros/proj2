#ifndef PERGUNTA_CPP
#define PERGUNTA_CPP

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
    virtual void salvarResposta(ofstream& outFile) const = 0; // Função para salvar resposta
    virtual void salvarPergunta(ofstream& outFile) const = 0;
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

    void salvarPergunta(ofstream& outFile) const override {
    outFile << "Pergunta Aberta: " << textoPergunta << "\n";
    }
    
    void salvarResposta(ofstream& outFile) const override {
    outFile << "Resposta Aberta: " << resposta << "\n";  // Alterado para "Resposta Aberta"
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

    void salvarPergunta(ofstream& outFile) const override {
    outFile << "Pergunta Multipla Escolha: " << textoPergunta << "\n";
    }
    
    void salvarResposta(ofstream& outFile) const override {
    outFile << "Resposta Múltipla Escolha: " << opcoes[resposta - 1] << "\n";  // Alterado para "Resposta Múltipla Escolha"
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
    
    void salvarPergunta(ofstream& outFile) const override {
    outFile << "Pergunta Escala: " << textoPergunta << "\n";
    }

    void salvarResposta(ofstream& outFile) const override {
    outFile << "Resposta Escala: " << resposta << "\n";  // Alterado para "Resposta Escala"
}

};

#endif
