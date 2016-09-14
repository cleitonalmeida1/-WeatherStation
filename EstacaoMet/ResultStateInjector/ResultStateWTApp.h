/*
 * ResultStateWTApp.h
 *
 *  Created on: 22/07/2016
 *      Author: Cleiton GonÃ§alves
 */

#ifndef RESULTSTATEWT_RESULTSTATEWTAPP_H_
#define RESULTSTATEWT_RESULTSTATEWTAPP_H_

#include "mbed.h"
#include "../FaultRecovery/StateMachine.h"
#include "../Logger/Logger.h"
#include <stdlib.h>
#include <iostream>

/* -----------------------------------------------------------------------------
 * Class Declarations
 * ---------------------------------------------------------------------------*/
class Sort;
class BubbleSort;
class InsertionSort;
class SelectionSort;
class CombSort;
class MergeSort;

/* -----------------------------------------------------------------------------
 * Class Definitions

 * ---------------------------------------------------------------------------*/

class Sort: public State {
protected:
	static unsigned short cont;
	static const unsigned short n = 4096;
	static unsigned short array[n];
	static Timer t;
	static Logger logger;
	static LocalFileSystem localFileSystem;

	virtual void desordenaVetor() {
		for (int i = Sort::n; i > 0; --i) {
			Sort::array[n - i] = i;
		}
	}

	virtual void run() {
		sort();
	}
	virtual void sort() = 0;
};

class BubbleSort: public Sort {
public:
	void run(StateMachine &sm);
	void bubble(unsigned short vetorDesordenado[], unsigned short tamanhoVetor);
	void trocarPosicaoValores(unsigned short *posicaoA,
			unsigned short *posicaoB);
	void sort();
};

class InsertionSort: public Sort {
public:
	void run(StateMachine &sm);
	void insertion(unsigned short array[], unsigned short tamanho);
	void sort();
};

class SelectionSort: public Sort {
public:
	void run(StateMachine &sm);
	void selection(unsigned short vetorDesordenado[],
			unsigned short tamanhoVetor);
	void trocarPosicaoValores(unsigned short *posicaoA,
			unsigned short *posicaoB);
	void sort();
};

class MergeSort: public Sort {
public:
	void run(StateMachine &sm);
	void merge(unsigned short *vetorDesordenado, unsigned short posicaoInicio,
			unsigned short posicaoFim);
	void sort();
};

class SortApp: public Application {
private:
	void start(StateMachine &sm);
	void createRecoveryPoints(StateMachine &sm);
};

class CombSort: public Sort {
public:
	void run(StateMachine &sm);
	void comb(unsigned short *arr, unsigned short size);
	void sort();
};

class RecoveryBubbleSort : public RecoveryPoint {
public:
    void run(StateMachine &sm);
};

class RecoveryInsertionSort : public RecoveryPoint {
public:
    void run(StateMachine &sm);
};

class RecoverySelectionSort : public RecoveryPoint {
public:
    void run(StateMachine &sm);
};

class RecoveryMergeSort : public RecoveryPoint {
public:
    void run(StateMachine &sm);
};

class RecoveryCombSort : public RecoveryPoint {
public:
    void run(StateMachine &sm);
};
#endif /* RESULTSTATEWT_RESULTSTATEWTAPP_H_ */

