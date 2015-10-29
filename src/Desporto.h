#ifndef DESPORTO_H
#define DESPORTO_H

#include <string>
#include <vector>

using namespace std;

class Desporto{
private:
	string nome;
public:
	Desporto(string nome);
	string getNome();
};
#endif
