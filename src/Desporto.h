#ifndef DESPORTO_H
#define DESPORTO_H

#include <string>
#include <vector>
#include "Modalidade.h"



class Desporto{
	string nome;
	vector<Modalidade *> modalidades;
public:
	Desporto(string nome);
	void adicionaModalidade(Modalidade *m);
	vector<Modalidade* > getModalidades();
	string getNome();



};
#endif
