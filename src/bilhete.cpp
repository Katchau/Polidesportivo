/*
 * bilhete.cpp
 *
 *  Created on: 19/12/2015
 *      Author: Madnar
 */
#include "bilhete.h"

int Bilhete::counter = 0;

Bilhete::Bilhete(vector<evento*> acesso, string email, string nome, string morada)
{
	this->acesso = acesso;
	this->email = email;
	this->nome = nome;
	this->morada = morada;
	counter ++;
	ID = counter;

}
void Bilhete::NovoDono( string email, string nome, string morada)
{
	this->email = email;
	this->nome = nome;
	this->morada = morada;
}
bool Bilhete::Adiciona_evento(evento *prova)
{
	vector<evento*>:: iterator it;
	for ( it = acesso.begin(); it != acesso.end(); it++)
	{
		evento *temp = *it;
		if(temp->getNome() == prova->getNome())
			return false;
	}
	acesso.push_back(prova);
	return true;
}
bool Bilhete::Remove_evento(string nome)
{
	vector<evento*>:: iterator it;
	for ( it = acesso.begin(); it != acesso.end(); it++)
	{
		evento *temp = *it;
		if(temp->getNome() == nome)
		{
			acesso.erase(it);
			return true;
		}
	}
	return false;
}

vector<evento*> Bilhete::getProvas() const
{
	return acesso;
}
string Bilhete::getNome() const
{
	return nome;
}
string Bilhete::getMorada() const
{
	return morada;
}
int Bilhete::getID()const
{
	return ID;
}

/*******************************************************************************************************************/

Bilheteira::Bilheteira(){}
bool Bilheteira::addBilhete(Bilhete novo)
{

	if(vendidos.find(novo) == vendidos.end())
		return false;
	vendidos.insert(novo);
	return true;
}
bool Bilheteira::removeBilhete(Bilhete velho)
{
	if(vendidos.find(velho) == vendidos.end())
		return false;
	vendidos.erase(velho);
	return true;
}
void Bilheteira::vendeBilhete(Bilhete venda,string novodono,string email, string morada)
{
  vendidos.erase(venda);

	try
	{
		Bilhete temp = BilheteDeDono(novodono);
		vendidos.erase(temp);
		vector<evento *> eventos = venda.getProvas();
		for(vector<evento *> :: iterator it  = eventos.begin(); it != eventos.end(); it ++)
		{
			temp.Adiciona_evento(*it);
		}
		vendidos.insert(temp);

	}
	catch(NaoExiteDono &a)
	{
		venda.NovoDono(email,novodono,morada);
		vendidos.insert(venda);
	}


}
Bilhete Bilheteira::BilheteDeDono(string nome)
{
	hasBilhete::iterator it;

	for(it= vendidos.begin(); it != vendidos.end(); it ++)
	{
		Bilhete temp = *it;
		if(temp.getNome() == nome)
			return temp;
	}
	throw NaoExiteDono();
}
