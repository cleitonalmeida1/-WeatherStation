/*
 * StateMachine.h
 *
 *  Created on: 23/06/2016
 *      Author: Cleiton Gonçalves
 */

#ifndef STATEMACHINE_STATEMACHINE_H_
#define STATEMACHINE_STATEMACHINE_H_

#include "mbed.h"
#include <map>

using namespace std;

class TypeIDGenerator;
class State;
class StateMachine;
class Application;

typedef unsigned long TypeID;

class TypeIDGenerator {
public:
	template<typename T>
	static TypeID generateID() {
		static TypeID id = counter++;
		return id;
	}

private:
	TypeIDGenerator() {

	}

	virtual ~TypeIDGenerator() {

	}

	static TypeID counter;
};

class State {
public:

	virtual double getTimeLimit() {
		return 0.0;
	}

	virtual void runOnRecovery(StateMachine &sm) {
	}
	virtual void run(StateMachine &sm) = 0;

protected:

	State() {
	}

	State(State &orig) {

	}

	virtual ~State() {
	}

};

class StateMachine {
public:
	StateMachine() {

	}

	StateMachine(StateMachine &orig) {

	}

	virtual ~StateMachine() {

	}

	template<class S>
	void addState(){
		TypeID id = TypeIDGenerator::generateID<S>();
		states[id] = new S;
	}
	;

	template<class S>
	void setToState() {
		current = TypeIDGenerator::generateID<S>();
		if (states[current] == NULL) {
			addState<S>();
		}
	}
	;

	template<class S>
	void start() {
		setToState<S>();
		run();
	}
	;

	void run() {
		bool RUNNING = true;
		while (RUNNING) {
			states[current]->run(*this);
		}
	}
private:

	std::map<TypeID, State *> states;
	TypeID current;
};

class Application {
protected:
	Application() {
	}
	Application(Application &orig) {
	}
	virtual ~Application() {
	}

private:
	virtual void setup() {

	}

};

#endif /* STATEMACHINE_STATEMACHINE_H_ */
