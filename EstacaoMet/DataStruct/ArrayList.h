/*
 * ArrayList.h
 *
 *  Created on: 22/02/2016
 *      Author: Cleiton Gon�alves
 */

#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_

#include "mbed.h"
#include "List.h"

template<typename T>
class ArrayList: public List<T> {
public:

	ArrayList() {
		initialize();
	}

	ArrayList(ArrayList<T>& orig) {
		initialize();

		for (unsigned int i = 0; i < orig.size(); ++i) {
			add(orig.get(i));
		}
	}

	virtual ~ArrayList() {
		free(_elementData);
	}

	T operator[](int _index) {
		return getForIndex(_index);
	}

	virtual bool add(const T &t) {

		changedCapacity(_elementData, _size);

		_elementData[_size] = t;
		_size++;
		return true;
	}

	virtual unsigned int size() {
		return _size;
	}

	virtual bool isEmpty() {
		return _size == 0;
	}

	virtual void add(unsigned int _index, const T &t) {

		changedCapacity(_elementData, _size);
		memmove(_elementData + _index + 1, _elementData + _index,
				(_size - _index) * sizeof(T));
		_elementData[_index] = t;
		_size++;

	}

	virtual void remove(unsigned int _index) {

		memmove(_elementData + _index, _elementData + _index + 1,
				(_size - _index + 1) * sizeof(T));
		_size--;
	}

	virtual bool remove(const T &t) {

		for (unsigned int i = 0; i < _size; ++i) {
			if (_elementData[i] == t) {
				remove(i);
			}
		}
		return false;
	}

	T getForIndex(int _index) {

		return _elementData[_index];

	}

	void changedCapacity(T* _elementData, unsigned int size) {

		if (size == DEFAULT_CAPACITY) {
			capacity = capacity * 2;
			more_elementData = (T*) realloc(_elementData, capacity * sizeof(T));

			if (more_elementData != NULL) {
				_elementData = more_elementData;
			}
		}
	}

private:

	T* _elementData = NULL;
	T* more_elementData = NULL;
	unsigned int _size;
	static const unsigned int DEFAULT_CAPACITY = 10;
	unsigned int capacity;

	void initialize() {
		_elementData = (T*) calloc(DEFAULT_CAPACITY, sizeof(T));
		more_elementData = NULL;
		_size = 0;
		capacity = DEFAULT_CAPACITY;
	}

};

#endif /* ARRAYLIST_H_ */
