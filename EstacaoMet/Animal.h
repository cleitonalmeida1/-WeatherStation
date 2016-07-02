/*
 * Animal.h
 *
 *  Created on: 13/06/2016
 *      Author: Cleiton Gonçalves
 */

#ifndef ANIMAL_H_
#define ANIMAL_H_


class Animal {
public:
	Animal() {
		idade = 0;
	}
	virtual ~Animal() {

	}

	bool operator==(Animal a) {

		if (idade == a.getIdade()) {
			return true;
		}
		return false;
	}

	bool operator!=(Animal a) {

		if (idade != a.getIdade()) {
			return true;
		}
		return false;
	}

	void setIdade(unsigned int idade) {
		this->idade = idade;
	}

	unsigned int getIdade() {
		return this->idade;
	}

private:
	unsigned int idade;
};


#endif /* ANIMAL_H_ */
