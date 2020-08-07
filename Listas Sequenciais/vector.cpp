#include "vector.hpp"

#include <algorithm>
#include <iostream>
#include <limits>

// Construir lista vazia, mas com capacidade máxima informada.
vector::vector(unsigned int capacidade) {
  vetor = new int[capacidade];
  tamanho = 0;
  this->capacidade = capacidade;
}

// Construir lista com "tamanho" cópias do valor "inicial".
vector::vector(unsigned int tamanho, int inicial) {
  vetor = new int[tamanho];
  capacidade = tamanho;
  this->tamanho = tamanho;

  for (unsigned int i = 0; i < tamanho; i++) {
    vetor[i] = inicial;
  }
}

// --- Métodos de "Coleção" ---

// Inserir "elemento" na coleção. Sempre deve executar a inserção.
// FIXME Fazer realocação quando não houver espaço.
// NOTE  Observe que aumentar em apenas uma unidade não nos alivia da pressão
// que tínhamos antes...
void vector::inserir(int elemento) {
  // TODO Reorganizar o código
  if (tamanho < capacidade) {
    vetor[tamanho] = elemento;
    tamanho++;
    remover(0);
    // print();
  } else {
    // TODO Realocar o vetor e inserir "elemento"
    int* vetorDuplicado = new int[capacidade * 2];
    for (unsigned int i = 0; i < tamanho; i++) {
      vetorDuplicado[i] = vetor[i];
    }
    vetorDuplicado[capacidade] = elemento;
    delete[] vetor;
    vetor = vetorDuplicado;
    remover(0);
    tamanho++;
    capacidade *= 2;
    // print();
  }
}

// Remover "elemento" da coleção.
// Retornar indicativo de sucesso da remoção.
// NOTE Necessário preservar a ordem relativa dos que restarem.
bool vector::remover(int elemento) {
  if (pertence(elemento)) {
    for (unsigned int i = 0; i < tamanho; i++) {
      if (vetor[i] == elemento) {
        for (unsigned int j = i; j < tamanho; j++) {
          int aux = vetor[j];
          vetor[j] = vetor[j + 1];
          vetor[j + 1] = aux;
        }
        tamanho--;
        // print();
        return true;
      }
    }
    return false;
  } else {
    return false;
  }
}

// Determinar se "elemento" é um dos elementos ainda na coleção.
bool vector::pertence(int elemento) {
  for (unsigned int i = 0; i < tamanho; i++) {
    if (vetor[i] == elemento) {
      return true;
    }
  }
  return false;
}

// --- Métodos de "Lista" ---
// Inserir "elemento" na lista de forma que ele passe a constar no índice
// "indice". NOTE Necessário preservar a ordem relativa dos demais elementos.
void vector::inserir_em(unsigned int indice, int elemento) {
  // TODO Implementação.
  if (vetor[indice] == 0) {
    vetor[indice] = elemento;
  } else {
    tamanho++;
    for (unsigned int j = tamanho - 1; j > indice; j--) {
      vetor[j + 1] = vetor[j];
      vetor[j] = vetor[j - 1];
    }
    vetor[indice] = elemento;
  }
  // print();
}

// Remover o elemento associado a "indice".
// Retornar indicativo de sucesso da remoção.
bool vector::remover_de(unsigned int indice) {
  if (indice >= tamanho) {
    return false;
  }

  for (unsigned int i = indice + 1; i < tamanho; i++) {
    vetor[i - 1] = vetor[i];
  }
  tamanho--;
}

// Retornar o valor associado ao índice "indice".
// NOTE Quando o índice for inválido, retornar `std::numeric_limits<int>::max()`
//      (forma de obter o maior valor representável).
int vector::obter_elemento_em(unsigned int indice) {
  if (indice < 0 || indice > tamanho) {
    return std::numeric_limits<int>::max();
  } else {
    return vetor[indice];
  }
}

// Retornar o índice associado a "elemento".
// NOTE Quando o índice for inválido, retornar `std::numeric_limits<unsigned
// int>::max()`
//      (forma de obter o maior valor representável).
unsigned int vector::obter_indice_de(int elemento) {
  for (unsigned int i = 0; i < tamanho; i++) {
    if (vetor[i] == elemento) {
      return i;
    }
  }
  return std::numeric_limits<unsigned int>::max();
}

// void vector::print() {
//   std::cout << "[";
//   for (unsigned int i = 0; i < tamanho; i++) {
//     std::cout << vetor[i] << ",";
//   }
//   std::cout << "]";
// }