/*
 * bilhete.cpp
 *
 *  Created on: 19/12/2015
 *      Author: Madnar
 */
#include "bilhete.h"

int Bilhete::counter = 0;

Bilhete::Bilhete(vector<string> acesso, string email, string nome, string morada)
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
bool Bilhete::Adiciona_evento(string prova)
{
	vector<string>:: iterator it;
	for ( it = acesso.begin(); it != acesso.end(); it++)
	{
		string temp = *it;
		if(temp == prova)
			return false;
	}
	acesso.push_back(prova);
	return true;
}
bool Bilhete::Remove_evento(string nome)
{
	vector<string>:: iterator it;
	for ( it = acesso.begin(); it != acesso.end(); it++)
	{
		string temp = *it;
		if(temp == nome)
		{
			acesso.erase(it);
			return true;
		}
	}
	return false;
}

vector<string> Bilhete::getProvas() const
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
string Bilhete::getEmail() const
{
	return email;
}

/*******************************************************************************************************************/

Bilheteira::Bilheteira(){}
bool Bilheteira::addBilhete(Bilhete novo)
{

	if(vendidos.find(novo) == vendidos.end())
	{
		vendidos.insert(novo);
		return true;
	}
		return false;

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
		vector<string> eventos = venda.getProvas();
		for(vector<string> :: iterator it  = eventos.begin(); it != eventos.end(); it ++)
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
hasBilhete Bilheteira::getVendidos() const
{
	return vendidos;
}
