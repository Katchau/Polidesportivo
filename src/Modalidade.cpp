#include "Modalidade.h"

Modalidade::Modalidade (string nome, string tipo) : Desporto(nome)
{
	this->tipo = tipo;
}

bool Modalidade::adicionaProva(Prova * evento)
{
	return adicionaVetor(Provas, evento);
}

bool Modalidade::removeProva(Prova * evento)
{
	return removeVetor(Provas, evento);

}

string Modalidade::getNome()
{
	string nome;
	nome = Desporto::getNome() + " , " + tipo;
	nomeT = nome;
	return nome;
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
