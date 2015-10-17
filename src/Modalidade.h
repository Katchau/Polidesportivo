#ifndef MODALIDADE_H
#define MODALIDADE_H

#include "Infrastrutura.h"
#include "Prova.h"



class Modalidade {
private:
	string Nome;
	Infrastrutura* local;
	vector <Prova *> Provas;

public:
	bool adiciona_prova(Prova * evento);
	bool remove_prova(Prova * evento);
};

#endif
