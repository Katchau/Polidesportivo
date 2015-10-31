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
	virtual bool operator == (Desporto * des) const;
};
#endif
