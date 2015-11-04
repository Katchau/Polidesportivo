#include "Desporto.h"

Desporto::Desporto(string nome)
{
	this->nome = nome;
}

string Desporto::getNome()
{
	return nome;
}

bool Desporto::operator ==(const Desporto& des) const
{
	string n1 = nome;
	string n2 = des.nome;
	if(n1 == n2) return true;
	else return false;
}

bool Desporto::adicionaProva (evento * Prova){return false;};
bool Desporto::removeProva (evento * Prova){return false;};
