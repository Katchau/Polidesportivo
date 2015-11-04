#ifndef DESPORTO_H
#define DESPORTO_H

#include <string>
#include <vector>

#include "templates.h"

using namespace std;

class Desporto{
private:
	string nome;
public:
	Desporto(string nome);
	virtual ~Desporto(){}
	virtual string getNome();
	bool operator == (const Desporto& des) const;
};

class DesportoP{ // usar para comparaçao entre desportos, uma vez que sao todos do formato pointer
public:
	virtual ~DesportoP(){}
	Desporto * poit;
	virtual bool operator == (const DesportoP * des) const;
};

#endif
