/*
 * TripleData.h
 *
 *  Created on: 13/06/2016
 *      Author: Cleiton Gonçalves
 */





#include "mbed.h"

#include <iostream>

template<class T>
class TripleData {
public:


	TripleData() {
	}

	T getData();

	T* getDataObject();

	void injectFault();

	void print() {
		cout << "Idade da Pessoa1 = " << d1.getIdade() << endl;
		cout << "Idade da Pessoa2 = " << d2.getIdade() << endl;
		cout << "Idade da Pessoa3 = " << d3.getIdade() << endl;

		cout << "Idade do Animal = " << d2.getAnimal().getIdade() << endl;
		cout << "Idade do Animal = " << d2.getAnimal().getIdade() << endl;
		cout << "Idade do Animal = " << d2.getAnimal().getIdade() << endl;

		cout << "Idade do Animal2 = " << d3.getAnimal2()->getIdade() << endl;
		cout << "Idade do Animal2 = " << d3.getAnimal2()->getIdade() << endl;
		cout << "Idade do Animal2 = " << d3.getAnimal2()->getIdade() << endl;

	}

private:

	T d1;
	T d2;
	T d3;

	T dataObject;

	T getByVotting();
};

template<class T>
T TripleData<T>::getByVotting() {

	if (d1 == d2) {
		if (d1 != d3) {
			d3 = d1;
			//memcpy(&d3, &d1, sizeof(T));
		}
	} else if (d1 == d3)
		d2 = d1;
	//memcpy(&d2, &d1, sizeof(T));
	else if (d2 == d3)
		d1 = d2;
	//memcpy(&d1, &d2, sizeof(T));
	else {
		cout << "throws exception" << endl;
	}

	return d1;
}

template<class T>
T* TripleData<T>::getDataObject() {
	d1 = dataObject;
	d2 = dataObject;
	d3 = dataObject;
	dataObject = getByVotting();
	return &dataObject;
}

template<class T>
void TripleData<T>::injectFault() {
	d2.setIdade(99);
}

