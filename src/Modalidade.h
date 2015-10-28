#ifndef MODALIDADE_H
#define MODALIDADE_H

#include "Infrastrutura.h"
#include "Prova.h"


<<<<<<< HEAD
class Modalidade{
string Nome;
Infrastrutura* local;
vector <Prova *> Provas;
=======

class Modalidade {
private:
	string Nome;
	Infrastrutura* local;
	vector <Prova *> Provas;
>>>>>>> origin/master

public:
	bool adiciona_prova(Prova * evento);
	bool remove_prova(Prova * evento);
};

#endif
