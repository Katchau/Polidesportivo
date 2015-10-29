#include "Campeonato.h"

Campeonato::Campeonato(string nome)
{
	this->nome = nome;
}

bool Campeonato::adicionaInfraestrutura(Infraestrutura *i)
{
	return adicionaVetor(Infraestruturas, i);
}

bool Campeonato::removeInfraestrutura(Infraestrutura *i)
{
	return removeVetor(Infraestruturas, i);
}

bool Campeonato::adicionaEquipa(Equipa *e)
{
	return adicionaVetor(Equipas, e);
}

bool Campeonato::removeEquipa(Equipa *e)
{
	return removeVetor(Equipas, e);
}

bool Campeonato::adicionaModalidade(Desporto *m)
{
	return adicionaVetor(Modalidades, m);
}

bool Campeonato::removeModalidade(Desporto *m)
{
	return removeVetor(Modalidades, m);
}

string Campeonato::getNome() const
{
	return nome;
}

