#include "Desporto.h"

Desporto::Desporto(string nome)
{
	this->nome = nome;
}

string Desporto::getNome()
{
	return nome;
}

bool Desporto::operator ==(Desporto * des) const
{
	string n1 = nome;
	string n2 = des->getNome();
	if(n1 == n2) return true;
	else return false;
}
