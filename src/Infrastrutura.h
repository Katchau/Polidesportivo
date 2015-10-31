#ifndef INFRAESTRUTURA_H
#define INFRAESTRUTURA_H

#include <string>
#include "Calendario.h"

using namespace std;


class Infraestrutura {
private:
	string Nome;
	Calendario* Horario;

public:
	Infraestrutura(string Nome);
	Infraestrutura(string Nome, Calendario * Horario);
	void adicionaEvento(evento* A );
	void removeEvento(evento* B);
	Calendario*  getCalendario() const;
	Calendario*  setCalendario();
	string getNome()const;
	void imprime() const;
};

#endif
