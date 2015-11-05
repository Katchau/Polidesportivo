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

	cout << d->getNome() << endl;
	desportosInscrito.push_back(d);

	return true;
	//this shall not work!
	//if(!adicionaVetor(desportosInscrito, d))
	//throw DesportoRepetido();
	//
	//return true;
}

bool Atleta::removeDesporto(Desporto *d)
{
	for (unsigned int i = 0; i < desportosInscrito.size(); i++) {
		if (desportosInscrito[i]->getNome() == d->getNome()) {
			desportosInscrito.erase(desportosInscrito.begin() + i);
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
string Atleta::getNome() const
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
