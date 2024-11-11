#include <iostream>
#include <vector>
#include <string>
#include "pergunta.cpp"
#include "formulario.cpp"

using namespace std;

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
