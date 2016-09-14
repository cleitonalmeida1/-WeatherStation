/*
 * BubbleSort.h
 *
 *  Created on: 19/07/2016
 *      Author: Cleiton Gon�alves
 */

#ifndef BUBBLESORT_H_
#define BUBBLESORT_H_

class BubbleSort {
public:
	BubbleSort() {

	}
	virtual ~BubbleSort() {

	}

	void bubble(TData<unsigned short> vetorDesordenado[], unsigned short tamanhoVetor) {
		unsigned short i, j;
		for (i = 0; i < (tamanhoVetor - 1); i++) {
			for (j = 0; j < (tamanhoVetor - (i + 1)); j++) {
				if (vetorDesordenado[j] > vetorDesordenado[j + 1]) {
					trocarPosicaoValores(&vetorDesordenado[j],
							&vetorDesordenado[j + 1]);
				}
			}
		}

		//for (int i = 0; i < tamanhoVetor; ++i) {
			//std::cout << vetorDesordenado[i] << std::endl;
		//}
	}

	void trocarPosicaoValores(TData<unsigned short> *posicaoA,
			TData<unsigned short> *posicaoB) {
		unsigned short temporario;
		temporario = *posicaoA;
		*posicaoA = *posicaoB;
		*posicaoB = temporario;
	}
};

#endif /* BUBBLESORT_H_ */
