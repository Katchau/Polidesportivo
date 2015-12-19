#include "Atleta.h"

bool medalha::operator <(const medalha md) const
{
	if(ouro < md.ouro)return true;
	if(ouro == md.ouro && prata < md.prata) return true;
	if(ouro == md.ouro && prata == md.prata && bronze < md.bronze)return true;
	return false;
}

Atleta::Atleta()
{
	bool valido = true;
	do
	{
		cin.clear();
		if (!valido)
			cout << "Introduza um nome nao vazio: ";
		else
			cout << "Introduza o nome do atleta: ";

		getline(cin, nome);

		valido = false;

		for (size_t i = 0; i < nome.size(); i++)
			if (nome[i] != ' ')
				valido = true;

	} while (cin.eof() || !valido);
}

Atleta::Atleta(string nome)
{
	this->nome = nome;
}

bool Atleta::adicionaModalidade(Desporto *d)
{
	bool existe = false;

	for (size_t i = 0; i < desportosInscrito.size(); i++)
	{
		if (d->getNome() == desportosInscrito[i]->getNome())
		{
			existe = true;
		}
	}

	if (existe)
		throw DesportoRepetido();

	desportosInscrito.push_back(d);

	return true;
}

bool Atleta::removeModalidade(string desporto,string modalidade)
{
	cout << desportosInscrito.size() << endl;


	for (unsigned int i = 0; i < desportosInscrito.size(); i++) {
		cout << desportosInscrito[i]->getNome();
        string nome = desporto + " , " + modalidade;
		if (desportosInscrito[i]->getNome() == nome) {
			showDesportos();
			cout << endl;
			desportosInscrito.erase(desportosInscrito.begin() + i);
			return true;
		}
	}


	return false;
}

vector<Desporto *> Atleta::getDesportosInsc()
{
	return desportosInscrito;
}

void Atleta::showDesportos()
{
	for(size_t i = 0;i<desportosInscrito.size();i++)
	{
		cout << desportosInscrito[i]->getNome() << endl;
	}
}
string Atleta::getNome() const
{
	return nome;
}

int Atleta::classificacaoFinal(evento * prova)
{
	int resultado;
	Data tempo;
	int posicaoFinal = 1;
	if(prova->getTipo() == "TEMPO")
	{
		Prova_Tempo * pt=prova->getProvaT();
		vector<Posicao_tempo *> vpt = pt->getLugares();
		tempo=pt->getTempo(nome);
		if(tempo == Data(-1,-1,-1)) return 0;
		for(size_t i = 0;i<vpt.size();i++)
		{
			if(tempo <= vpt[i]->getTempo())
			{
			}
			else
			{
				posicaoFinal++;
			}
		}
	}
	if(prova->getTipo() == "PONTO")
		{
		Prova_Pontuacao * pt = prova->getProvaP();
		vector<Posicao_Pontos *> vpt = pt->getLugares();
		resultado=pt->getPontos(nome);
		if(resultado == -1) return 0;
		for (size_t i = 0; i < vpt.size(); i++)
		{
			if(resultado < vpt[i]->getPontuacao())
			{
				posicaoFinal++;
			}
		}
	}
	return posicaoFinal;
}

bool Atleta::operator == (const Atleta& atl) const
		{
	string nome1 = nome;
	string nome2 = atl.nome;
	if(nome1 == nome2)
	{
		return true;
	}
	else return false;
		}

bool ordenaAlfaAtletas(const Atleta A, const Atleta B){
	string a = A.getNome();
	string b = B.getNome();
	transform(a.begin(), a.end(), a.begin(), ::tolower);
	transform(b.begin(), b.end(), b.begin(), ::tolower);

	if(a < b)
		return true;
	return false;
}
