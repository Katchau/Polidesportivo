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
	//fazer excepcoes???
	if (adicionaVetor(desportosInscrito, d))
	{
		classificacoes.push_back(0);
		return true;
	}
	else return false;
}

bool Atleta::removeDesporto(Desporto *d)
{
	return removeVetor(desportosInscrito,d);
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
