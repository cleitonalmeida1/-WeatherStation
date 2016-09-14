/*
 * CombSort.h
 *
 *  Created on: 21/07/2016
 *      Author: Cleiton Gonçalves
 */

#ifndef RESULTWSWT_COMBSORT_H_
#define RESULTWSWT_COMBSORT_H_

class CombSort {
public:
	CombSort() {

	}
	virtual ~CombSort() {

	}

	void comb(unsigned short *arr, unsigned short size) {
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
};

#endif /* RESULTWSWT_COMBSORT_H_ */
