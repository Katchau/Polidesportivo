#ifndef INFRASTRUTURA_H
#define INFRASTRUTURA_H

#include <string>
#include "Calendario.h"

using namespace std;


class Infrastrutura {
private:
	string Nome;
	Calendario* Horario;

public:
	Infrastrutura(string Nome);
};

#endif
