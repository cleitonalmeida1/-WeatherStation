/*
 * List.h
 *
 *  Created on: 22/02/2016
 *      Author: Cleiton Gon�alves
 */

#ifndef LIST_H_
#define LIST_H_

#include "mbed.h"

template<typename T>
class List {
public:

	/**
	 * Construtor default
	 */
	List() {

	}
	/**
	 * Construtor de C�pia
	 */
	List(List<T> &orig) {

	}

	/**
	 * Destrutor
	 */
	virtual ~List() {

	}

	bool add(const T &t);

	virtual unsigned int size() = 0;

	virtual bool isEmpty() = 0;

	virtual void remove(unsigned int index) = 0;

	virtual bool remove(const T &t) = 0;

	T getForIndex(int index);

	virtual void add(unsigned int index, const T &t) = 0;

};

#endif /* LIST_H_ */
