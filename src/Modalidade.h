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
	vector<evento *> Provas;
public:
	Modalidade (string nome, string tipo);
	bool adicionaProva (evento * Prova);
	bool removeProva (evento * Prova);
	string getNome();
	bool operator == (Desporto * des) const;
	string getDesporto() const;
};


#endif
