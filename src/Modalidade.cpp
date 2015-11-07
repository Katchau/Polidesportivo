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
	for(unsigned int i=0;i<Provas.size();i++)
	{
		if(Provas[i]->getNome() == evento->getNome())
		{
			Provas.erase(Provas.begin()+i);
			return true;
		}
	}
	return false;

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
string Modalidade::getTipo() const {
 return tipo;
}

vector<evento *> Modalidade::getProvas() const
{
	return Provas;
}

vector<string> Modalidade::getNomeAtletas() const
		{
			vector<string>Atletas;
			for(unsigned int i = 0; i < Provas.size();i++)
			{
				vector<string>AtletasProva = Provas[i]->getNomeAtletas();
				for(unsigned int t = 0; t < AtletasProva.size();t++)
				{
					adicionaVetor(Atletas,AtletasProva[t]);
				}
			}
			sort(Atletas.begin(),Atletas.end());
			return Atletas;
		}
void Modalidade::adicionaResultado(int indice, string nomeAtleta, int h, int m ,int s, int score)
{
	Provas[indice]->adicionaLugar(nomeAtleta,0,0,0,h,m,s,score);
}
void Modalidade::removeResultado(int indice, string nomeAtleta)
{
	Provas[indice]->removeLugar(nomeAtleta);
}
