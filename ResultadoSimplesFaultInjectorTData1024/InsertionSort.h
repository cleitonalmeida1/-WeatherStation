/*
 * InsertionSort.h
 *
 *  Created on: 19/07/2016
 *      Author: Cleiton Gon�alves
 */

#include <stdio.h>
#include <iostream>

class InsertionSort {
public:
	InsertionSort() {

	}
	virtual ~InsertionSort() {

	}

	void insertion(TData<unsigned short> array[], unsigned short tamanho) {
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
};

