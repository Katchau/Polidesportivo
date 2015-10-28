#ifndef DESPORTO_H
#define DESPORTO_H

#include <string>
#include <vector>
#include "Modalidade.h"


<<<<<<< HEAD
class Desporto{
	string nome;
	vector<Modalidade *> modalidades;
public:
	Desporto(string nome);
	void adicionaModalidade(Modalidade *m);
	vector<Modalidade* > getModalidades();
	string getNome();
=======
class Desporto {
private:
	string Nome;
	vector < Modalidade *> Modalidades

public:
	bool adiciona_Modalidade(string Nome);
	bool remove_Modalidade(string Nome);
	string get_Nome();

>>>>>>> origin/master
};
#endif
