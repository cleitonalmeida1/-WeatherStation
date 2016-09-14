#include "TData.h"
#include "BubbleSort.h"
#include "InsertionSort.h"
#include "SelectionSort.h"
#include "MergeSort.h"
#include "CombSort.h"
#include "../FaultInjector/FaultInjector.h"
#include "../Logger/Logger.h"

using namespace std;

void povoarVetor(TData<unsigned short> vetor[], unsigned short n) {
	for (int i = n; i > 0; --i) {
		vetor[n - i] = i;
	}
}

/**
 * Ordena o vetor em ordem decresente.
 */

void ordenacaoDecrescente(TData<unsigned short> vetor[], unsigned short n) {
	unsigned short auxMaior = 0;
	for (unsigned short i = n; i > (n >> 1); --i) {
		auxMaior = vetor[i - 1];
		vetor[i - 1] = vetor[n - i];
		vetor[n - i] = auxMaior;
	}
}

int main() {

	float rcont;
	float result;
	unsigned short cont = 0;
	const unsigned short n = 1024;
	//unsigned short vetor[n];
	TData<unsigned short> vetor[n];
	FaultInjector f;
	Timer t;

	LocalFileSystem fs("local");
	Logger logger("/local/log.txt", false);

	BubbleSort bubble;
	InsertionSort insertion;
	SelectionSort selection;
	MergeSort merge;
	CombSort comb;

	unsigned long ini = (unsigned long) 0x10004000;
	unsigned long fim = (unsigned long) 0x10008000 - 1;

	//logger.log("Endereço %x\t", ini);
	//logger.log("Endereço %x\t\r", fim);

	for (unsigned short i = 0; i < 100; ++i) {
		//Início do ciclo de teste
		povoarVetor(vetor, n);
		ordenacaoDecrescente(vetor, n);
		cont = 0;
		/* -----------------------------------------------------------------------------
		 * BubbleSort Class
		 * ---------------------------------------------------------------------------*/

		f.injectFaults(ini, fim, 1, 0);

		//Injeta falha no microcontrolador
		t.reset();
		t.start();
		bubble.bubble(vetor, n);
		logger.log(" %f\t ", t.read());
		t.stop();

		//Verifica se algum elemento do vetor foi afetado pela falha
		for (unsigned short i = 0; i < n; ++i) {
			if (vetor[i] != i + 1) {
				cont++;
			}
		}
		//logger.log(" B %hu\t ", cont);

		rcont = (float) cont * 100.00;
		result = rcont / 1024.00;
		logger.log(" %f\t", result);

		logger.log("\t");

		cont = 0;

		/* -----------------------------------------------------------------------------
		 * Insertion Class
		 * ---------------------------------------------------------------------------*/
		ordenacaoDecrescente(vetor, n);

		//Injeta falha no microcontrolador
		f.injectFaults(ini, fim, 1, 0);

		t.reset();
		t.start();
		insertion.insertion(vetor, n);
		logger.log(" %f\t ", t.read());
		t.stop();

		//Verifica se algum elemento do vetor foi afetado pela falha
		for (unsigned short i = 0; i < n; ++i) {
			if (vetor[i] != i + 1) {
				cont++;
			}
		}
		//logger.log(" I %hu\t ", cont);

		rcont = (float) cont * 100.00;
		result = rcont / 1024.00;
		logger.log(" %f\t", result);
		logger.log("\t");
		cont = 0;

		/* -----------------------------------------------------------------------------
		 * Selection Class
		 * ---------------------------------------------------------------------------*/
		ordenacaoDecrescente(vetor, n);

		//Injeta falha no microcontrolador
		f.injectFaults(ini, fim, 1, 0);

		t.reset();
		t.start();
		selection.selection(vetor, n);
		logger.log(" %f\t ", t.read());
		t.stop();

		//Verifica se algum elemento do vetor foi afetado pela falha
		for (unsigned short i = 0; i < n; ++i) {
			if (vetor[i] != i + 1) {
				cont++;
			}
		}
		//logger.log(" S %hu\t ", cont);

		rcont = (float) cont * 100.00;
		result = rcont / 1024.00;
		logger.log(" %f\t", result);
		logger.log("\t");
		cont = 0;

		/* -----------------------------------------------------------------------------
		 * Merge Class
		 * ---------------------------------------------------------------------------*/
		ordenacaoDecrescente(vetor, n);

		//Injeta falha no microcontrolador
		f.injectFaults(ini, fim, 1, 0);

		t.reset();
		t.start();
		merge.merge(vetor, 0, n - 1);
		logger.log(" %f\t ", t.read());
		t.stop();

		//Verifica se algum elemento do vetor foi afetado pela falha
		for (unsigned short i = 0; i < n; ++i) {
			if (vetor[i] != i + 1) {
				cont++;
			}
		}
		//logger.log(" M %hu\t ", cont);

		rcont = (float) cont * 100.00;
		result = rcont / 1024.00;
		logger.log(" %f\t", result);
		logger.log("\t");
		cont = 0;

		/* -----------------------------------------------------------------------------
		 * Comb Class
		 * ---------------------------------------------------------------------------*/
		ordenacaoDecrescente(vetor, n);

		//Injeta falha no microcontrolador
		f.injectFaults(ini, fim, 1, 0);

		t.reset();
		t.start();
		comb.comb(vetor, n);
		logger.log(" %f\t ", t.read());
		t.stop();

		//Verifica se algum elemento do vetor foi afetado pela falha
		for (unsigned short i = 0; i < n; ++i) {
			if (vetor[i] != i + 1) {
				cont++;
			}
		}
		//logger.log(" C %hu\n\r ", cont);

		rcont = (float) cont * 100.00;
		result = rcont / 1024.00;
		logger.log(" %f\r", result);

	}
}
