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


string Desporto::getTipo()const {return NULL;};
string Desporto::getDesporto() const
{
	return nome;
}

bool ordenaAlfaDesporto(const Desporto *A,const Desporto *B)
{      string a = A->getTipo();
		string b = B->getTipo();
		transform(a.begin(), a.end(), a.begin(), ::tolower);
		transform(b.begin(), b.end(), b.begin(), ::tolower);

		if(a < b)	return true;
		return false;
}

vector<evento *> Desporto::getProvas() const
		{vector<evento *> a;
			return a;
		}

bool ordenaAlfaModalidade(const Desporto *A,const Desporto *B)
{	    string a = A->getTipo();
		string b = B->getTipo();
		transform(a.begin(), a.end(), a.begin(), ::tolower);
		transform(b.begin(), b.end(), b.begin(), ::tolower);
		if(a < b)
			return true;
		return false;
}
