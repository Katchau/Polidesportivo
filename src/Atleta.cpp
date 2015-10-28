#include "Atleta.h"


Atleta::Atleta(string nome)
{
	this->nome = nome;
}
void Atleta::adicionaDesporto(Desporto *d)
{
	desportosInscrito.push_back(d);
}

vector<Desporto *> Atleta::getDesportos()
{
	return desportosInscrito;
}

void Atleta::showDesportos()
{
	for(size_t i = 0;i<desportosInscrito.size();i++)
	{
		/*cout << desportosInscrito[i]->getNome();*/
	}
}
string Atleta::getNome()
{
	return nome;
}
