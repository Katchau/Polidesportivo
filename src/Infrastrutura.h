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
};

#endif
