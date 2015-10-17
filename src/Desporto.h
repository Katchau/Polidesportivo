#ifndef DESPORTO_H
#define DESPORTO_H

#include <string>
#include <vector>
#include "Modalidade.h"


class Desporto {
private:
	string Nome;
	vector < Modalidade *> Modalidades

public:
	bool adiciona_Modalidade(string Nome);
	bool remove_Modalidade(string Nome);
	string get_Nome();

};
#endif
