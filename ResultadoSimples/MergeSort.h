/*
 * MergeSort.h
 *
 *  Created on: 19/07/2016
 *      Author: Cleiton Gon�alves
 */

#ifndef MERGESORT_H_
#define MERGESORT_H_

#include <stdlib.h>

class MergeSort {
public:
	MergeSort() {

	}
	virtual ~MergeSort() {

	}

	void mergeSort(unsigned short *vetorDesordenado,
			unsigned short posicaoInicio, unsigned short posicaoFim) {
		unsigned short i, j, k, metadeTamanho, *vetorTemp;
		if (posicaoInicio == posicaoFim)
			return;

		// ordenacao recursiva das duas metades
		metadeTamanho = (posicaoInicio + posicaoFim) / 2;
		mergeSort(vetorDesordenado, posicaoInicio, metadeTamanho);
		mergeSort(vetorDesordenado, metadeTamanho + 1, posicaoFim);

		// unsigned shortercalacao no vetor temporario t
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
};

#endif /* MERGESORT_H_ */
