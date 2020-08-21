#include <iostream>
#include <limits>

#include "set.hpp"

using namespace std;

int main() {
  unsigned int capacidade_v, capacidade_u;
  unsigned int comandos;

  cin >> capacidade_v >> capacidade_u >> comandos;

  set v(capacidade_v);
  set u(capacidade_u);

  while (comandos-- > 0) {
    char acao, conjunto;
    int elemento;
    set *alvo, *outro;

    cin >> acao >> conjunto;

    if (conjunto == 'u') {
      alvo = &u;
      outro = &v;
    } else {
      alvo = &v;
      outro = &u;
    }

    switch (acao) {
      case 'i':
        cin >> elemento;
        cout << alvo->inserir(elemento) << endl;
        alvo->print();
        break;
      case 'r':
        cin >> elemento;
        cout << alvo->remover(elemento) << endl;
        alvo->print();
        break;
      case 'p':
        cin >> elemento;
        cout << alvo->pertence(elemento) << endl;
        alvo->print();
        break;
      case 't':
        cout << alvo->obter_tamanho() << endl;
        alvo->print();
        break;
      case 'c':
        cout << (alvo->obter_capacidade() >= alvo->obter_tamanho()) << endl;
        break;
      case 'U':
        alvo->uniao_com(*outro);
        cout << "ok" << endl;
        alvo->print();
        break;
      case 'I':
        alvo->intersecao_com(*outro);
        cout << "ok" << endl;
        alvo->print();
        break;
      case 'S':
        cout << alvo->esta_contido_em(*outro) << endl;
        alvo->print();
        break;
    }
  }

  return 0;
}