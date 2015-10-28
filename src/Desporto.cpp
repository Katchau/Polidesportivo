#include "Desporto.h"

Desporto::Desporto(string nome)
{
	this->nome = nome;
}

void Desporto::adicionaModalidade(Modalidade *m)
{
	modalidades.push_back(m);
}

vector<Modalidade* > Desporto::getModalidades()
{
	return modalidades;
}

string Desporto::getNome()
{
	return nome;
}
