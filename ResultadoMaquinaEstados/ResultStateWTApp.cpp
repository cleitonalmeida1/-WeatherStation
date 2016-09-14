/*
 * ResultStateWTApp.cpp
 *
 *  Created on: 22/07/2016
 *      Author: Cleiton GonÃ§alves
 */

#include "ResultStateWTApp.h"

/* -----------------------------------------------------------------------------
 * BubbleSort Class
 * ---------------------------------------------------------------------------*/
void BubbleSort::run(StateMachine &sm) {
	Sort::run();
	Sort::t.stop();
	Sort::logger.log("%f\t", Sort::t.read());
	Sort::desordenaVetor();
	Sort::t.reset();
	Sort::t.start();
	sm.setToState<InsertionSort>();
}

void BubbleSort::bubble(unsigned short vetorDesordenado[],
		unsigned short tamanhoVetor) {
	unsigned short i, j;
	for (i = 0; i < (tamanhoVetor - 1); i++) {
		for (j = 0; j < (tamanhoVetor - (i + 1)); j++) {
			if (vetorDesordenado[j] > vetorDesordenado[j + 1]) {
				BubbleSort::trocarPosicaoValores(&vetorDesordenado[j],
						&vetorDesordenado[j + 1]);
			}
		}
	}
}

void BubbleSort::trocarPosicaoValores(unsigned short *posicaoA,
		unsigned short *posicaoB) {
	unsigned short temporario;
	temporario = *posicaoA;
	*posicaoA = *posicaoB;
	*posicaoB = temporario;
}

void BubbleSort::sort() {
	bubble(Sort::array, Sort::n);
}

/* -----------------------------------------------------------------------------
 * InsertionSort Class
 * ---------------------------------------------------------------------------*/
void InsertionSort::run(StateMachine &sm) {
	Sort::run();
	Sort::t.stop();
	Sort::logger.log("%f\t", Sort::t.read());
	Sort::desordenaVetor();
	Sort::t.reset();
	Sort::t.start();
	sm.setToState<SelectionSort>();
}

void InsertionSort::insertion(unsigned short array[], unsigned short tamanho) {
	unsigned short i, j, tmp;
	for (i = 1; i < tamanho; i++) {
		j = i;
		while (j > 0 && array[j - 1] > array[j]) {
			tmp = array[j];
			array[j] = array[j - 1];
			array[j - 1] = tmp;
			j--;
		}
	}
}

void InsertionSort::sort() {
	insertion(Sort::array, Sort::n);
}

/* -----------------------------------------------------------------------------
 * SelectionSort Class
 * ---------------------------------------------------------------------------*/

void SelectionSort::run(StateMachine &sm) {
	Sort::run();
	Sort::t.stop();
	Sort::logger.log("%f\t", Sort::t.read());
	Sort::desordenaVetor();
	Sort::t.reset();
	Sort::t.start();
	sm.setToState<MergeSort>();
}

void SelectionSort::selection(unsigned short vetorDesordenado[],
		unsigned short tamanhoVetor) {
	unsigned short i, j, posicaoValorMinimo;

	for (i = 0; i < (tamanhoVetor - 1); i++) {
		posicaoValorMinimo = i;
		for (j = (i + 1); j < tamanhoVetor; j++) {
			if (vetorDesordenado[j] < vetorDesordenado[posicaoValorMinimo]) {
				posicaoValorMinimo = j;
			}
		}

		if (i != posicaoValorMinimo) {
			SelectionSort::trocarPosicaoValores(&vetorDesordenado[i],
					&vetorDesordenado[posicaoValorMinimo]);
		}
	}
	//Sort::logger.log("VETOR ORDENADO SELECTION SORT\r");
//	for (unsigned short i = 0; i < 4096; ++i) {
//		Sort::logger.log("%hu\r", Sort::array[i]);
//	}

}

void SelectionSort::trocarPosicaoValores(unsigned short *posicaoA,
		unsigned short *posicaoB) {
	unsigned short temporario;
	temporario = *posicaoA;
	*posicaoA = *posicaoB;
	*posicaoB = temporario;
}

void SelectionSort::sort() {
	//Sort::logger.log("VETOR DESORDENADO SELECTION SORT\r");
	//for (unsigned short i = 0; i < 4096; ++i) {
	//	Sort::logger.log("%hu\r", Sort::array[i]);
	//}
	selection(Sort::array, Sort::n);
}

/* -----------------------------------------------------------------------------
 * MergeSort Class
 * ---------------------------------------------------------------------------*/
void MergeSort::run(StateMachine &sm) {
	Sort::run();
	Sort::t.stop();
	Sort::logger.log("%f\t", Sort::t.read());
	Sort::desordenaVetor();
	Sort::t.reset();
	Sort::t.start();
	sm.setToState<CombSort>();
}
void MergeSort::merge(unsigned short *vetorDesordenado,
		unsigned short posicaoInicio, unsigned short posicaoFim) {
	unsigned short i, j, k, metadeTamanho, *vetorTemp;
	if (posicaoInicio == posicaoFim)
		return;

	// ordenacao recursiva das duas metades
	metadeTamanho = (posicaoInicio + posicaoFim) / 2;
	merge(vetorDesordenado, posicaoInicio, metadeTamanho);
	merge(vetorDesordenado, metadeTamanho + 1, posicaoFim);

	i = posicaoInicio;
	j = metadeTamanho + 1;
	k = 0;
	vetorTemp = (unsigned short *) malloc(
			sizeof(unsigned short) * (posicaoFim - posicaoInicio + 1));

	while (i < metadeTamanho + 1 || j < posicaoFim + 1) {
		if (i == metadeTamanho + 1) { // i passou do final da primeira metade, pegar v[j]
			vetorTemp[k] = vetorDesordenado[j];
			j++;
			k++;
		} else {
			if (j == posicaoFim + 1) {
				// j passou do final da segunda metade, pegar v[i]
				vetorTemp[k] = vetorDesordenado[i];
				i++;
				k++;
			} else {
				if (vetorDesordenado[i] < vetorDesordenado[j]) {
					vetorTemp[k] = vetorDesordenado[i];
					i++;
					k++;
				} else {
					vetorTemp[k] = vetorDesordenado[j];
					j++;
					k++;
				}
			}
		}

	}
	// copia vetor unsigned shortercalado para o vetor original
	for (i = posicaoInicio; i <= posicaoFim; i++) {
		vetorDesordenado[i] = vetorTemp[i - posicaoInicio];
	}
	free(vetorTemp);
}

void MergeSort::sort() {
	merge(Sort::array, 0, Sort::n);
}

/* -----------------------------------------------------------------------------
 * CombSort Class
 * ---------------------------------------------------------------------------*/

void CombSort::run(StateMachine &sm) {
	Sort::run();
	Sort::t.stop();
	Sort::logger.log("%f\r", Sort::t.read());
	Sort::desordenaVetor();
	Sort::t.reset();
	Sort::t.start();
	sm.setToState<BubbleSort>();
}

void CombSort::comb(unsigned short *arr, unsigned short size) {
	float shrink_factor = 1.247330950103979;
	unsigned short gap = size, swapped = 1, swap, i;

	while ((gap > 1) || swapped) {
		if (gap > 1)
			gap = gap / shrink_factor;

		swapped = 0;
		i = 0;

		while ((gap + i) < size) {
			if (arr[i] - arr[i + gap] > 0) {
				swap = arr[i];
				arr[i] = arr[i + gap];
				arr[i + gap] = swap;
				swapped = 1;
			}
			++i;
		}
	}
}

void CombSort::sort() {
	comb(Sort::array, Sort::n);
}

/* -----------------------------------------------------------------------------
 * SortApp Class
 * ---------------------------------------------------------------------------*/
void SortApp::start(StateMachine &sm) {
	sm.start<BubbleSort>();
}
