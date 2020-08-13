#include "ordered_vector.hpp"

#include <limits>

// Construir lista vazia, mas com capacidade máxima informada.
ordered_vector::ordered_vector(unsigned int capacidade) {
  vetor = new int[capacidade];
  tamanho = 0;
  this->capacidade = capacidade;
}

// Construir lista com "tamanho" cópias do valor "inicial".
ordered_vector::ordered_vector(unsigned int tamanho, int inicial) {
  vetor = new int[tamanho];
  capacidade = tamanho;
  this->tamanho = tamanho;

  for (unsigned int i = 0; i < tamanho; i++) {
    vetor[i] = inicial;
  }
}

// --- Métodos de "Coleção" ---

// Inserir "elemento" na coleção. Sempre deve executar a inserção.
// NOTE  Observe que aumentar em apenas uma unidade não nos alivia da pressão
// que tínhamos antes...
void ordered_vector::inserir(int elemento) {
  if (tamanho < capacidade) {
    vetor[tamanho] = elemento;
    tamanho++;
  } else {
    int* vetorDuplicado = new int[capacidade * 2];
    for (unsigned int i = 0; i < tamanho; i++) {
      vetorDuplicado[i] = vetor[i];
    }
    vetorDuplicado[capacidade] = elemento;
    delete[] vetor;
    vetor = vetorDuplicado;
    tamanho++;
    capacidade *= 2;
  }
  for (int i = 0; i < tamanho - 1; i++) {
    int menor = i;
    for (int j = i + 1; j < tamanho; j++) {
      if (vetor[j] < vetor[menor]) {
        menor = j;
      }
      if (i != menor) {
        int aux = vetor[i];
        vetor[i] = vetor[menor];
        vetor[menor] = aux;
      }
    }
  }
}

// Remover "elemento" da coleção.
// Retornar indicativo de sucesso da remoção.
// NOTE Necessário preservar a ordem relativa dos que restarem.
bool ordered_vector::remover(int elemento) {
  if (pertence(elemento)) {
    for (unsigned int i = 0; i < tamanho; i++) {
      if (vetor[i] == elemento) {
        for (unsigned int j = i; j < tamanho; j++) {
          int aux = vetor[j];
          vetor[j] = vetor[j + 1];
          vetor[j + 1] = aux;
        }
        tamanho--;
        return true;
      }
    }
    return false;
  } else {
    return false;
  }
}

// Determinar se "elemento" é um dos elementos ainda na coleção.
bool ordered_vector::pertence(int elemento) {
  for (unsigned int i = 0; i < tamanho; i++) {
    if (vetor[i] == elemento) {
      return true;
    }
  }
  return false;
}

// --- Métodos de "Lista" ---

// Remover o elemento associado a "indice".
// Retornar indicativo de sucesso da remoção.
bool ordered_vector::remover_de(unsigned int indice) {
  if (indice >= tamanho) {
    return false;
  }

  for (unsigned int i = indice + 1; i < tamanho; i++) {
    vetor[i - 1] = vetor[i];
  }
  tamanho--;
  return true;
}

// Retornar o valor associado ao índice "indice".
// NOTE Quando o índice for inválido, retornar `std::numeric_limits<int>::max()`
//      (forma de obter o maior valor representável).
int ordered_vector::obter_elemento_em(unsigned int indice) {
  if (indice < 0 || indice >= tamanho || tamanho == 0) {
    return std::numeric_limits<int>::max();
  } else {
    return vetor[indice];
  }
}

// Retornar o índice associado a "elemento".
// NOTE Quando o índice for inválido, retornar `std::numeric_limits<unsigned
// int>::max()`
//      (forma de obter o maior valor representável).
unsigned int ordered_vector::obter_indice_de(int elemento) {
  for (unsigned int i = 0; i < tamanho; i++) {
    if (vetor[i] == elemento) {
      return i;
    }
  }
  return std::numeric_limits<unsigned int>::max();
}
