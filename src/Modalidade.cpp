#include "Modalidade.h"

Modalidade::Modalidade (string nome, string tipo) : Desporto(nome)
{
	this->tipo = tipo;
	nomeT = nome + " , " + tipo;
}

bool Modalidade::adicionaProva(evento * evento)
{
	return adicionaVetor(Provas, evento);
}

bool Modalidade::removeProva(evento * evento)
{
	return removeVetor(Provas, evento);

}

string Modalidade::getNome()
{
	return nomeT;
}

bool Modalidade::operator == (Desporto * des) const
{
	string n1 = des->getNome();
	string n2 = nomeT;
	if(n2 == n1) return true;
	else return false;
}

/*
 bool Modalidade::operator == (Modalidade des) const
{
	string n1 = des.getNome();
	string n2 = nomeT;
	if(n2 == n1) return true;
	else return false;
}
 */
