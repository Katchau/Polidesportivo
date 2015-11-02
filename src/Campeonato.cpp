#include "Campeonato.h"

Campeonato::Campeonato(const string &filename)
{
	ifstream ReadConfig(filename.c_str());
}

Campeonato::Campeonato()
{
	bool valido = true;
	do
	{
		cin.clear();
		if (!valido)
			cout << "Introduza um nome nao vazio: ";
		else
			cout << "Introduza o nome do campeonato: ";

		getline(cin, nome);

		valido = false;

		for (size_t i = 0; i < nome.size(); i++)
			if (nome[i] != ' ')
				valido = true;

	} while (cin.eof() || !valido);

	ifstream read;
	string nomeEq, filenome = nome + ".txt";
	read.open(filenome.c_str());
	while(read.fail())
	{
		cout << "Please introduce a valid name" << endl;
		getline(cin, nome);
	}
	read.ignore(100, '\n');
	while (true) {
		getline(read, nomeEq);
		if (nomeEq == "Provas: ")
			break;
		nomeEq = nomeEq + ".txt";
		Equipa eq(nomeEq);
		Equipas.push_back(eq);
	}
}

void Campeonato::criaEquipa()
{
	Equipa novaEquipa;

	adicionaVetor(Equipas, novaEquipa);
}

string Campeonato::getNome() const
{
	return nome;
}

vector<Infraestrutura *> Campeonato::getInfraestruturas()
{
	return Infraestruturas;
}

vector<Equipa> Campeonato::getEquipas()
{
	return Equipas;
}

vector<Desporto*> Campeonato::getModalidades()
{
	return Modalidades;
}

void Campeonato::gravarCampeonato()
{

}
