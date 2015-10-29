#ifndef CAMPEONATO_H
#define CAMPEONATO_H

#include "Modalidade.h"
#include "Equipa.h"
#include "Infrastrutura.h"

using namespace std;

class Campeonato {
private:
	string nome;
	vector<Infraestrutura *> Infraestruturas;
	vector<Equipa *> Equipas;
	vector<Desporto*> Modalidades;
public:
	Campeonato(string nome);
	bool adicionaInfraestrutura(Infraestrutura *i);
	bool removeInfraestrutura(Infraestrutura *i);
	bool adicionaEquipa(Equipa *e);
	bool removeEquipa(Equipa *e);
	bool adicionaModalidade(Desporto *m);
	bool removeModalidade(Desporto *m);
	string getNome() const;

};

#endif



