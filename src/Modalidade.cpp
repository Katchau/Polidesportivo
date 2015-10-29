#include "Modalidade.h"

Modalidade::Modalidade (string nome, string tipo) : Desporto(nome)
{
	this->tipo = tipo;
}

bool Modalidade::adicionaProva(Prova * evento)
{
	Provas.push_back(evento);
	return true;
}

bool Modalidade::removeProva(Prova * evento)
{
	int indice = sequentialSearch(Provas, evento);

	if (indice == -1)
		return false;

	Provas.erase(Provas.begin() + indice);
	return true;

}
