#ifndef MODALIDADE_H
#define MODALIDADE_H

#include <string>
#include <vector>

#include "Desporto.h"
#include "Prova.h"

class Modalidade : public Desporto {
private:
	string tipo;
	string nomeT;
	vector<Prova *> Provas;
public:
	Modalidade (string nome, string tipo);
	bool adicionaProva (Prova * evento);
	bool removeProva (Prova * evento);
	string getNome();
	bool operator == (Desporto * des) const;
};


#endif
