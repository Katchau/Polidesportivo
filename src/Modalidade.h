#ifndef MODALIDADE_H
#define MODALIDADE_H

#include <string>
#include <vector>

#include "Desporto.h"
#include "Prova.h"
#include "templates.h"

class Modalidade : public Desporto {
private:
	string tipo;
	vector<Prova *> Provas;
public:
	Modalidade (string nome, string tipo);
	bool adicionaProva (Prova * evento);
	bool removeProva (Prova * evento);
};

#endif
