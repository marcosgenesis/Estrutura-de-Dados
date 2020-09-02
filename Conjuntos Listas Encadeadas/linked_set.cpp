#include "linked_set.hpp"

#include <iostream>
#include <limits>

// Construir lista vazia, mas com capacidade máxima informada.
linked_set::linked_set() {
  this->primeiro = nullptr;
  this->tamanho = 0;
}

// --- Métodos de "Coleção" ---

// Inserir "elemento" na coleção.
// Retornar indicativo de sucesso da inserção.
// NOTE Deve aumentar a capacidade caso necessário.
// NOTE Observe que aumentar em apenas uma unidade não nos alivia da pressão que
// tínhamos antes...
bool linked_set::inserir(int elemento) {
  if (pertence(elemento)) {
    return false;
  }

  no_encadeado* novo_no = new no_encadeado(elemento, this->primeiro);
  this->primeiro = novo_no;

  this->tamanho++;
  return true;
}

// Remover "elemento" da coleção.
// Retornar indicativo de sucesso da remoção.
// NOTE Necessário preservar a ordem relativa dos que restarem.
bool linked_set::remover(int elemento) {
  if (this->tamanho == 0 || !pertence(elemento)) {
    return false;
  } else {
    unsigned int indice = 0;
    no_encadeado* no = this->primeiro;
    while (no->valor != elemento) {
      no = no->proximo;
      indice++;
    }
    no_encadeado* noASerRemovido = obter_no_em(indice);
    if (indice == 0) {
      this->primeiro = noASerRemovido->proximo;
      delete[] noASerRemovido;
      this->tamanho--;
      return true;
    } else {
      no_encadeado* noAnterior = obter_no_em(indice - 1);
      noAnterior->proximo = noASerRemovido->proximo;
      delete[] noASerRemovido;
      this->tamanho--;
      return true;
    }
  }
}

// Determinar se "elemento" é um dos elementos ainda na coleção.
bool linked_set::pertence(int elemento) const {
  no_encadeado* no = this->primeiro;
  while (no != nullptr) {
    if (no->valor == elemento) {
      return true;
    }
    no = no->proximo;
  }
  return false;
}

// --- Métodos de "Conjunto" ---

// Tornar o próprio conjunto (`this`) o resultado de sua união com o outro
// informado.
void linked_set::uniao_com(linked_set const& conjunto) {
  for (unsigned int l = 0; l < conjunto.tamanho; l++) {
    if (!pertence(conjunto.obter_no_em(l)->valor)) {
      inserir(conjunto.obter_no_em(l)->valor);
    }
  }
}

// Tornar o próprio conjunto (`this`) o resultado de sua intersecção com o outro
// informado.
void linked_set::intersecao_com(linked_set const& conjunto) {
  if (conjunto.tamanho == 0) {
    this->tamanho = 0;
  } else {
    for (unsigned int i = 0; i < tamanho; i++) {
      if (!conjunto.pertence(obter_no_em(i)->valor)) {
        remover(obter_no_em(i)->valor);
      }
    }
  }
  for (unsigned int i = 0; i < this->tamanho; i++) {
  }
}

// Testar se este conjunto (`this`) está contido no outro informado.
bool linked_set::esta_contido_em(linked_set const& conjunto) const {
  if (this->tamanho == 0) {
    return true;
  }

  bool estaContido = false;
  for (unsigned l = 0; l < this->tamanho; l++) {
    if (conjunto.pertence(obter_no_em(l)->valor)) {
      estaContido = true;
    } else {
      return false;
    }
  }
  return estaContido;
}

// --- Métodos Auxiliares ---

// Construtor de um nó, onde a informação do próximo, no momento construção, é
// opcional
linked_set::no_encadeado::no_encadeado(int valor, no_encadeado* proximo) {
  this->valor = valor;
  this->proximo = proximo;
}

// Desejamos obter o próprio nó que esteja no índice informado.
// Deve retornar `nullptr` quando tal nó não existe.
// Auxilia processos que dependem de encontrar nós baseado em um índice.
linked_set::no_encadeado* linked_set::obter_no_em(unsigned int indice) const {
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
// informado. (ou seja, `anterior.proximo.valor == valor`) Auxilia processos que
// dependem de encontrar nós baseado em um valor. Deve retornar `nullptr` quando
// tal nó não existe.
linked_set::no_encadeado* linked_set::obter_no_anterior_a(int valor) const {
  no_encadeado* no = this->primeiro;
  while (no != nullptr) {
    if (no->proximo->valor == valor) {
      return no;
    }
    no = no->proximo;
  }
}
