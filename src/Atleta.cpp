
#include "Atleta.h"


Atleta::Atleta(string nome)
{
	this->nome = nome;
}
void Atleta::addDesporto(Desporto * p)
{
	desportosInscrito.push_back(p);
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
