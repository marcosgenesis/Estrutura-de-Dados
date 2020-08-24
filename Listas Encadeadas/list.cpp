#include "list.hpp"

#include <limits>

list::list() {
  this->primeiro = nullptr;
  this->tamanho = 0;
}

list::list(unsigned int tamanho, int inicial) {
  this->tamanho = tamanho;
  this->primeiro = nullptr;
  for (unsigned int i = 0; i < this->tamanho; i++) {
    no_encadeado* novo_no = new no_encadeado(inicial);
    this->primeiro = novo_no;
  }
}

void list::inserir(int elemento) {
  if (tamanho == 0) {
    no_encadeado* novo_no = new no_encadeado(elemento);
    this->primeiro = novo_no;

    this->tamanho++;
  } else {
    no_encadeado* anterior = obter_no_em(tamanho - 1);
    no_encadeado* novo_no = new no_encadeado(elemento);
    anterior->proximo = novo_no;
    this->tamanho++;
  }
}
bool list::remover(int elemento) {
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
bool list::pertence(int elemento) {
  no_encadeado* no = this->primeiro;
  while (no != nullptr) {
    if (no->valor == elemento) {
      return true;
    }
    no = no->proximo;
  }
  return false;
}

bool list::inserir_em(unsigned int indice, int elemento) {
  if (indice == 0) {
    no_encadeado* novo_no = new no_encadeado(elemento, this->primeiro);
    this->primeiro = novo_no;

    this->tamanho++;

    return true;
  } else {
    no_encadeado* anterior = obter_no_em(indice - 1);

    if (anterior != nullptr) {
      no_encadeado* novo_no = new no_encadeado(elemento);
      novo_no->proximo = anterior->proximo;
      anterior->proximo = novo_no;

      this->tamanho++;

      return true;
    } else {
      return false;
    }
  }
}

bool list::remover_de(unsigned int indice) {
  if (indice < tamanho) {
    no_encadeado* noASerRemovido = obter_no_em(indice);
    remover(noASerRemovido->valor);
    return true;
  } else {
    return false;
  }
}

int list::obter_elemento_em(unsigned int indice) {
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

unsigned int list::obter_indice_de(int elemento) {
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

list::no_encadeado::no_encadeado(int valor, no_encadeado* proximo) {
  this->valor = valor;
  this->proximo = proximo;
}

list::no_encadeado* list::obter_no_em(unsigned int indice) {
  if (this->tamanho == 0 || indice > this->tamanho) {
    return nullptr;
  }
  no_encadeado* no = this->primeiro;
  for (unsigned int i = 0; i < indice; i++) {
    no = no->proximo;
  }
  return no;
}

list::no_encadeado* list::obter_no_anterior_a(int valor) {
  no_encadeado* no = this->primeiro;
  while (no != nullptr) {
    if (no->proximo->valor == valor) {
      return no;
    }
    no = no->proximo;
  }
}
