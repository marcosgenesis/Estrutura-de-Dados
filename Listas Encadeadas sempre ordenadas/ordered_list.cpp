#include "ordered_list.hpp"

#include <iostream>
#include <limits>

// Construir lista vazia, mas com capacidade máxima informada.
ordered_list::ordered_list() {
  this->primeiro = nullptr;
  this->tamanho = 0;
}

// Construir lista com "tamanho" cópias do valor "inicial".
ordered_list::ordered_list(unsigned int tamanho, int inicial) {
  this->tamanho = tamanho;
  this->primeiro = nullptr;
  for (unsigned int i = 0; i < this->tamanho; i++) {
    no_encadeado* novo_no = new no_encadeado(inicial);
    this->primeiro = novo_no;
  }
}

void ordered_list::inserir(int elemento) {
  if (tamanho == 0) {
    no_encadeado* novo_no = new no_encadeado(elemento);
    this->primeiro = novo_no;
    this->tamanho++;
  } else {
    no_encadeado* anterior = obter_no_em(tamanho - 1);
    no_encadeado* novo_no = new no_encadeado(elemento);
    anterior->proximo = novo_no;
    this->tamanho++;
    // 5 4 3
    no_encadeado* no = this->primeiro;

    for (int x = 0; x < this->tamanho; x++) {
      for (int y = 0; y < this->tamanho - 1; y++) {
        if (obter_no_em(y)->valor < obter_no_em(y + 1)->valor) {
          int aux = obter_no_em(y)->valor;
          obter_no_em(y)->valor = obter_no_em(y + 1)->valor;
          obter_no_em(y + 1)->valor = aux;
        }
      }
    }

    for (unsigned int i = 0; i < tamanho; i++) {
      std::cout << obter_elemento_em(i) << " ";
    }
  }
};
/

    // Remover "elemento" da coleção.
    // Retornar indicativo de sucesso da remoção.
    bool ordered_list::remover(int elemento) {
  if (this->tamanho == 0 || !pertence(elemento)) {
    return false;
  } else {
    int indice = obter_indice_de(elemento);
    no_encadeado* noASerRemovido = obter_no_em(indice);
    no_encadeado* noAnterior = obter_no_em(indice - 1);
    if (indice == 0) {
      this->primeiro = noASerRemovido->proximo;
      delete[] noASerRemovido;
      this->tamanho--;
      return true;
    } else {
      noAnterior->proximo = noASerRemovido->proximo;
      delete[] noASerRemovido;
      this->tamanho--;
      return true;
    }
  }
}

// Determinar se "elemento" é um dos elementos ainda na coleção.
bool ordered_list::pertence(int elemento) {
  no_encadeado* no = this->primeiro;
  while (no != nullptr) {
    if (no->valor == elemento) {
      return true;
    }
    no = no->proximo;
  }
  return false;
}

// --- Métodos de "Lista" ---

// Remover o elemento associado a "indice".
// Retornar indicativo de sucesso da remoção.
bool ordered_list::remover_de(unsigned int indice) {
  if (indice < tamanho) {
    no_encadeado* noASerRemovido = obter_no_em(indice);
    remover(noASerRemovido->valor);
    return true;
  } else {
    return false;
  }
}

// Retornar o valor associado ao índice "indice".
// NOTE Quando o índice for inválido, retornar
// `std::numeric_limits<int>::max()`
//      (forma de obter o maior valor representável).
int ordered_list::obter_elemento_em(unsigned int indice) {
  if (indice > this->tamanho) {
    std::numeric_limits<int>::max();
  }

  no_encadeado* no = obter_no_em(indice);
  if (no == nullptr) {
    return std::numeric_limits<int>::max();
  } else {
    return no->valor;
  }
}

// Retornar o índice associado a "elemento".
// NOTE Quando o índice for inválido, retornar `std::numeric_limits<unsigned
// int>::max()`
//      (forma de obter o maior valor representável).
unsigned int ordered_list::obter_indice_de(int elemento) {
  unsigned int indice = 0;
  no_encadeado* no = this->primeiro;
  while (no != nullptr) {
    if (no->valor == elemento) {
      return indice;
    }
    indice++;
    no = no->proximo;
  }

  return std::numeric_limits<unsigned int>::max();
}

// --- Métodos Auxiliares ---

// Construtor de um nó, onde a informação do próximo, no momento construção, é
// opcional
ordered_list::no_encadeado::no_encadeado(int valor, no_encadeado* proximo) {
  this->valor = valor;
  this->proximo = proximo;
}

// Desejamos obter o próprio nó que esteja no índice informado.
// Deve retornar `nullptr` quando tal nó não existe.
// Auxilia processos que dependem de encontrar nós baseado em um índice.
ordered_list::no_encadeado* ordered_list::obter_no_em(unsigned int indice) {
  if (this->tamanho == 0 || indice > this->tamanho) {
    return nullptr;
  }
  no_encadeado* no = this->primeiro;
  for (unsigned int i = 0; i < indice; i++) {
    no = no->proximo;
  }
  return no;
}

// Desejamos obter o próprio nó que veja **antes** de algum com o valor
// informado. (ou seja, `anterior.proximo.valor == valor`) Auxilia processos
// que dependem de encontrar nós baseado em um valor. Deve retornar `nullptr`
// quando tal nó não existe.
ordered_list::no_encadeado* ordered_list::obter_no_anterior_a(int valor) {
  no_encadeado* no = this->primeiro;
  while (no != nullptr) {
    if (no->proximo->valor == valor) {
      return no;
    }
    no = no->proximo;
  }
}
