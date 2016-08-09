/*
 * DLinkedList.h
 *
 *  Created on: 24/02/2016
 *      Author: Cleiton Gon�alves
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "mbed.h"
#include "List.h"

template<typename T>
class LinkedList: public List<T> {
public:
	LinkedList() {
		initialize();
	}

	LinkedList(List<T>& orig) {
		initialize();
	}

	LinkedList(const T &item, LinkedList<T>* ptrnext = NULL) {
		this->data = item;
		this->next = ptrnext;
	}

	virtual ~LinkedList() {
		LinkedList<T> *tmp = next, *aux;
		while (tmp != NULL) {
			aux = tmp;
			tmp = tmp->next;
			free(aux);
		}
		next = NULL;
	}

	virtual unsigned int size() {
		unsigned int _size = 1;
		LinkedList<T> *tmp = next;
		while (tmp->next != NULL) {
			tmp = tmp->next;
			_size++;
		}

		return _size;
	}

	virtual bool isEmpty() {
		return next == NULL;
	}

	virtual bool remove(const T &t) {

		if (next == NULL) {
			std::cout << "Cannot Delete" << std::endl;
			return false;
		} else if (next->data == t) {
			next = next->next;
			return true;
		} else {

			LinkedList<T> *cur = next;
			LinkedList<T> *prev = NULL;

			while (cur != NULL && cur->data != t) {
				prev = cur;
				cur = cur->next;
			}

			if (cur == NULL) {
				return false;
			} else {
				//delete cur node
				prev->next = cur->next;
				return true;
			}
		}
	}

	virtual T get(const T& t) {
		LinkedList<T> *tmp = next;
		while (tmp != NULL && tmp->data != t) {
			tmp = tmp->next;
		}

		if (tmp != NULL)
			return tmp->data;
		else
			std::cout << "N�o est� na lista" << std::endl;
		return t;

	}

	bool addLast(const T &t) {

		if (next == NULL) {
			addFirst(t);
		} else {
			LinkedList<T> *tmp = next;
			while (tmp->next != NULL)
				tmp = tmp->next;

			tmp->next = new LinkedList<T>(t);
		}
		return true;
	}

	void addFirst(const T &t) {
		next = new LinkedList<T>(t, next);
	}

	bool addtAfter(const T &obj, const T &objAdd) {
		LinkedList<T> *tmp = next;
		while (tmp != NULL && tmp->data != obj)
			tmp = tmp->next;

		if (tmp != NULL) {
			tmp->next = new LinkedList<T>(objAdd, tmp->next);
			return true;
		}
		return false;
	}

	bool addBefore(const T &obj, const T &objAdd) {
		if (next == NULL)
			return false;
		if (next->data == obj) {
			addFirst(objAdd);
			return true;
		}

		LinkedList<T> *prev = NULL;
		LinkedList<T> *cur = next;

		while (cur != NULL && cur->data != obj) {
			prev = cur;
			cur = cur->next;
		}
		//insert between cur and prev
		if (cur != NULL) {
			prev->next = new LinkedList<T>(objAdd, cur);
			return true;
		}

		return false;

	}

	void removeAll() //Remove todos os n�s da Lista
	{
		LinkedList<T> *tmp = next, *aux;
		while (tmp != NULL) {
			aux = tmp;
			tmp = tmp->next;
			free(aux);
		}
		next = NULL;
	}

	void listAll() {
		LinkedList<int> *tmp = next;
		if (next != NULL) {
			for (unsigned int i = 0; i < size(); ++i) {

				std::cout << tmp->data << std::endl;
				if (getNext(tmp) != NULL) {
					getNext(tmp);
					tmp = getNext(tmp);
				}

			}
		} else {
			std::cout << "Lista Vazia" << std::endl;
		}

	}

	LinkedList<T>* getFirst() {
		return next;
	}

	LinkedList<T>* getNext(LinkedList<T>* cur) {
		return cur->next;
	}

	T getData() {
		return data;
	}

	LinkedList<T>* nextNode() {
		return this->next;
	}

	virtual void add(unsigned int index, const T &t) {

	}

	virtual void remove(unsigned int index) {

	}
private:

	LinkedList<T> *next;
	T data;

	void initialize() {
		this->next = NULL;

	}
};

#endif /* LINKEDLIST_H_ */

