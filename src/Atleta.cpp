#include "Atleta.h"

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
bool Atleta::adicionaDesporto(Desporto *d)
{
	bool repetido = false;
	for(unsigned int i = 0;i<desportosInscrito.size();i++)
	{
		if(desportosInscrito[i]->getNome() == d->getNome())
		{
			repetido = true;
			break;
		}
	}

	if(repetido)
	{
		throw DesportoRepetido();
		return false;
	}
	else
	{
		desportosInscrito.push_back(d);
		classificacoes.push_back(0);
		return true;
	}
}

/*// buggy nao sei pq, dou fix nisto dp
bool Atleta::adicionaDesporto(Desporto *d)
{
	//fazer excepcoes???

	vector<DesportoP> despPtr;
	for(unsigned int i = 0;i< desportosInscrito.size(); i++)
	{
		DesportoP p;
		p.poit = desportosInscrito[i];
		despPtr.push_back(p);
	}

	DesportoP novoDesp;
	novoDesp.poit = d;

	int x = sequentialSearch(despPtr, novoDesp);

	if(x != -1)
	{
		throw DesportoRepetido();
	}

	if (adicionaVetor(despPtr, novoDesp))
	{
		classificacoes.push_back(0);

		desportosInscrito.clear();
		for(unsigned int i = 0;i< despPtr.size(); i++)
		{
			desportosInscrito.push_back(despPtr[i].poit);
		}
		return true;
	}
	else return false;
}
 */

bool Atleta::removeDesporto(Desporto *d)
{
		for(unsigned int i = 0;i<desportosInscrito.size();i++)
		{
			if(desportosInscrito[i]->getNome() == d->getNome())
			{
				desportosInscrito.erase(desportosInscrito.begin()+i);
				return true;
			}
		}
	throw DesportoInexistente();
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
string Atleta::getNome()
{
	return nome;
}

void Atleta::classificacaoFinal(Desporto * des)
{
	for(unsigned int i = 0;i<desportosInscrito.size();i++)
	{
		if(desportosInscrito[i]->getNome() == des->getNome()) //w8 podia ter feito secSearch, oh well
		{
			int resultado = 0;
			//resultado = falta funcao que da ret disso
			classificacoes[i] = resultado;
		}
	}
}
