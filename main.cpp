#include <iostream>
#include "formulario.cpp"

using namespace std;

int main() {
    Formulario form("Pesquisa de Satisfação");

    // Adicionando perguntas ao formulário
    form.adicionarPergunta(new PerguntaAberta("Qual é o seu nome?"));
    form.adicionarPergunta(new PerguntaMultiplaEscolha("Qual é a sua área?", {"Administração", "Tecnologia", "Marketing"}));
    form.adicionarPergunta(new PerguntaEscala("De 1 a 5, quanto você gostou do serviço?", 1, 5));

    form.exibirFormulario();
    form.coletarRespostas();

    form.gerarRelatorio("respostas.txt");

    return 0;
}
