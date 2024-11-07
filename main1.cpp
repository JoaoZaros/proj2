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

// Pergunta aberta
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

// Pergunta de múltipla escolha
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

// Pergunta de escala
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

// Funções auxiliares
Formulario* criarFormulario() {
    string nome;
    cout << "Digite o nome do formulário: ";
    getline(cin, nome);

    Formulario* formulario = new Formulario(nome);

    int numPerguntasAbertas, numPerguntasMultipla, numPerguntasEscala;
    cout << "Quantas perguntas abertas? ";
    cin >> numPerguntasAbertas;
    cin.ignore();

    for (int i = 0; i < numPerguntasAbertas; ++i) {
        string texto;
        cout << "Digite o texto da pergunta aberta " << i + 1 << ": ";
        getline(cin, texto);
        formulario->adicionarPergunta(new PerguntaAberta(texto));
    }

    cout << "Quantas perguntas de múltipla escolha? ";
    cin >> numPerguntasMultipla;
    cin.ignore();

    for (int i = 0; i < numPerguntasMultipla; ++i) {
        string texto;
        cout << "Digite o texto da pergunta de múltipla escolha " << i + 1 << ": ";
        getline(cin, texto);

        int numOpcoes;
        cout << "Quantas opções? ";
        cin >> numOpcoes;
        cin.ignore();

        vector<string> opcoes;
        for (int j = 0; j < numOpcoes; ++j) {
            string opcao;
            cout << "Opção " << j + 1 << ": ";
            getline(cin, opcao);
            opcoes.push_back(opcao);
        }

        formulario->adicionarPergunta(new PerguntaMultiplaEscolha(texto, opcoes));
    }

    cout << "Quantas perguntas de escala? ";
    cin >> numPerguntasEscala;
    cin.ignore();

    for (int i = 0; i < numPerguntasEscala; ++i) {
        string texto;
        int min, max;
        cout << "Digite o texto da pergunta de escala " << i + 1 << ": ";
        getline(cin, texto);
        cout << "Digite o valor mínimo da escala: ";
        cin >> min;
        cout << "Digite o valor máximo da escala: ";
        cin >> max;
        cin.ignore();

        formulario->adicionarPergunta(new PerguntaEscala(texto, min, max));
    }

    return formulario;
}

void responderFormulario(const vector<Formulario*>& formularios) {
    cout << "Formularios disponíveis:\n";
    for (size_t i = 0; i < formularios.size(); ++i) {
        cout << i + 1 << ". " << formularios[i]->getNomeFormulario() << "\n";
    }
    cout << "Escolha um formulário para responder: ";
    int escolha;
    cin >> escolha;
    cin.ignore();

    Formulario* formularioSelecionado = formularios[escolha - 1];
    formularioSelecionado->coletarRespostas();
    formularioSelecionado->salvarRespostas("respostas_" + formularioSelecionado->getNomeFormulario() + ".txt");
}

int main() {
    vector<Formulario*> formularios;
    int opcao;

    do {
        cout << "\nMenu:\n1. Criar formulário\n2. Responder formulário\n3. Sair\nEscolha uma opção: ";
        cin >> opcao;
        cin.ignore();

        if (opcao == 1) {
            formularios.push_back(criarFormulario());
        } else if (opcao == 2) {
            if (!formularios.empty()) {
                responderFormulario(formularios);
            } else {
                cout << "Nenhum formulário disponível para responder.\n";
            }
        }
    } while (opcao != 3);

    for (Formulario* formulario : formularios) {
        delete formulario;
    }

    return 0;
}
