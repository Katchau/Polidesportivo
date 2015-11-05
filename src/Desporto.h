#ifndef DESPORTO_H
#define DESPORTO_H

#include <string>
#include <vector>
#include <algorithm>
#include "templates.h"
#include "calendario.h"
using namespace std;

class Desporto{
private:
	string nome;
public:
	Desporto(string nome);
	virtual ~Desporto(){}
	virtual string getNome();
	virtual bool adicionaProva (evento * Prova);
	virtual	bool removeProva (evento * Prova);
	virtual bool operator == (const Desporto& des) const;
	virtual string getTipo()const;
	virtual string getDesporto() const;
	virtual vector<evento *> getProvas() const;
};

class DesportoP{ // usar para comparaçao entre desportos, uma vez que sao todos do formato pointer
public:
	virtual ~DesportoP(){}
	Desporto * poit;
	virtual bool operator == (const DesportoP * des) const;
};

bool ordenaAlfaDesporto(const Desporto *A,const Desporto *b);
bool ordenaAlfaModalidade(const Desporto *A,const Desporto *B);
#endif
