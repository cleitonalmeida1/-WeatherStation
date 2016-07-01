#include "mbed.h"
#include "WeatherStation.h"
#include "TripleData.h"
#include "../StateMachine/StateMachine.h"

#include <iostream>

class EsperandoCarroChegar;
class EsperandoApertarBotao;
class EsperandoCarroEntrar;
class FecharCancela;


class EsperandoCarroChegar: public State {
	void run(StateMachine &sm) {
		char c;
		cout << "[C] - Carro chegou" << endl;
		cin >> c;
		cout << "" << endl;

		switch (c) {
		case 'C':
		case 'c':
			sm.setToState<EsperandoApertarBotao>();
		}
	}
};

class EsperandoApertarBotao: public State {
	void run(StateMachine &sm) {
		char t;
		cout << "[T] - apertando o botão" << endl;
		cout << "[V] - Voltar" << endl;
		cin >> t;
		cout << "" << endl;

		switch (t) {
		case 'T':
		case 't':
			sm.setToState<EsperandoCarroEntrar>();
			break;

		case 'V':
		case 'v':
			sm.setToState<EsperandoCarroChegar>();
			break;
		}
	}
};

class EsperandoCarroEntrar: public State {
	void run(StateMachine &sm) {
		char t;
		cout << "[E] - Entrar" << endl;
		cout << "[V] - Voltar" << endl;
		cin >> t;
		cout << "" << endl;

		switch (t) {
		case 'E':
		case 'e':
			sm.setToState<FecharCancela>();
			break;

		case 'V':
		case 'v':
			sm.setToState<EsperandoCarroChegar>();
			break;
		}
	};
};

	class FecharCancela: public State {
		void run(StateMachine &sm) {
			cout << " ... fechando a cancela ... " << endl;
			sm.setToState<EsperandoCarroChegar>();
		};
	};

	int main() {
		/*
		 WeatherStation w;
		 w.getInstance()->start();
		 */

		StateMachine sm;
		sm.start<EsperandoCarroChegar>();
	}

