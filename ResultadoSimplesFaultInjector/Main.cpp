#include "mbed.h"
#include "../FaultInjector/FaultInjector.h"
#include "../Logger/Logger.h"
#include "InsertionSort.h"
#include "SelectionSort.h"
#include "BubbleSort.h"
#include "MergeSort.h"
#include "CombSort.h"

void povoarVetor(unsigned short vetor[], unsigned short n) {
	for (int i = n; i > 0; --i) {
		vetor[n - i] = i;
	}
}

/**
 * Ordena o vetor em ordem decresente.
 */

void ordenacaoDecrescente(unsigned short vetor[], unsigned short n) {
	unsigned short auxMaior = 0;
	for (unsigned short i = n; i > (n >> 1); --i) {
		auxMaior = vetor[i - 1];
		vetor[i - 1] = vetor[n - i];
		vetor[n - i] = auxMaior;
	}
}

int main() {
	const unsigned short n = 4096;
	unsigned short vetor[n];
	unsigned short cont = 0;
	float rcont;
	float result;

	LocalFileSystem fs("local");
	Logger logger("/local/log.txt", false);
	FaultInjector f;

	BubbleSort bubble;
	InsertionSort insertion;
	SelectionSort selection;
	MergeSort merge;
	CombSort comb;

	unsigned long ini = (unsigned long) 0x10000000;
	unsigned long fim = 0x10008000 - 1;
	//logger.log("Endereço %x\t", ini);
	//logger.log("Endereço %x\t\r", fim);
	for (unsigned short i = 0; i < 100; ++i) {
		//Início do ciclo de teste
		povoarVetor(vetor, n);
		cont = 0;
		/* -----------------------------------------------------------------------------
		 * BubbleSort Class
		 * ---------------------------------------------------------------------------*/
		ordenacaoDecrescente(vetor, n);

		//Injeta falha no microcontrolador
		f.injectFaults(ini, fim, 1, 0);

		bubble.bubble(vetor, n);

		//Verifica se algum elemento do vetor foi afetado pela falha
		for (unsigned short i = 0; i < n; ++i) {
			if (vetor[i] != i + 1) {
				cont++;
			}
		}
		logger.log("B %hu ", cont);
		if (cont > 410) {
			rcont = (float) cont * 100.00;
			result = rcont / 4096.00;
			logger.log(" %f\r", result);
			continue;
		}
		cont = 0;
		/* -----------------------------------------------------------------------------
		 * Insertion Class
		 * ---------------------------------------------------------------------------*/
		ordenacaoDecrescente(vetor, n);

		//Injeta falha no microcontrolador
		f.injectFaults(ini, fim, 1, 0);

		insertion.insertion(vetor, n);

		//Verifica se algum elemento do vetor foi afetado pela falha
		for (unsigned short i = 0; i < n; ++i) {
			if (vetor[i] != i + 1) {
				cont++;
			}
		}
		logger.log("\t I %hu ", cont);
		if (cont > 410) {
			rcont = (float) cont * 100.00;
			result = rcont / 4096.00;
			logger.log(" %f\r", result);
			continue;
		}
		cont = 0;

		/* -----------------------------------------------------------------------------
		 * Selection Class
		 * ---------------------------------------------------------------------------*/
		ordenacaoDecrescente(vetor, n);

		//Injeta falha no microcontrolador
		f.injectFaults(ini, fim, 1, 0);

		selection.selection(vetor, n);

		//Verifica se algum elemento do vetor foi afetado pela falha
		for (unsigned short i = 0; i < n; ++i) {
			if (vetor[i] != i + 1) {
				cont++;
			}
		}
		logger.log("\t S %hu ", cont);
		if (cont > 410) {
			rcont = (float) cont * 100.00;
			result = rcont / 4096.00;
			logger.log(" %f\r", result);
			continue;
		}
		cont = 0;

		/* -----------------------------------------------------------------------------
		 * Merge Class
		 * ---------------------------------------------------------------------------*/
		ordenacaoDecrescente(vetor, n);

		//Injeta falha no microcontrolador
		f.injectFaults(ini, fim, 1, 0);

		merge.merge(vetor, 0, n - 1);

		//Verifica se algum elemento do vetor foi afetado pela falha
		for (unsigned short i = 0; i < n; ++i) {
			if (vetor[i] != i + 1) {
				cont++;
			}
		}
		logger.log("\t M %hu ", cont);
		if (cont > 410) {
			rcont = (float) cont * 100.00;
			result = rcont / 4096.00;
			logger.log(" %f\r", result);
			continue;
		}
		cont = 0;

		/* -----------------------------------------------------------------------------
		 * Comb Class
		 * ---------------------------------------------------------------------------*/
		ordenacaoDecrescente(vetor, n);

		//Injeta falha no microcontrolador
		f.injectFaults(ini, fim, 1, 0);

		comb.comb(vetor, n);

		//Verifica se algum elemento do vetor foi afetado pela falha
		for (unsigned short i = 0; i < n; ++i) {
			if (vetor[i] != i + 1) {
				cont++;
			}
		}
		logger.log("\t C %hu ", cont);
		if (cont > 410) {
			rcont = (float) cont * 100.00;
			result = rcont / 4096.00;
			logger.log(" %f\r", result);
			continue;
		} else {
			logger.log("\r", cont);
		}

	}
	return 0;
}
