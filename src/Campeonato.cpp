#include "Campeonato.h"

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
bool checkExistence(std::string filename)
{
	ifstream f;
	f.open(filename.c_str());

	return f.is_open();
}

string selectFile()
{
	string a;

	bool invalido = false;

	do
	{
		if (invalido)
		{
			invalido = false;
			cout << "O ficheiro pretendido nao existe. Introduza novamente:" << endl;
			cin.clear();
		}
		cout << "Nome do ficheiro de campeonato (incluindo extensao): ";
		getline(cin, a);
		if (cin.eof())
			exit(1);
		if (!checkExistence(a))
			invalido = true;
	} while (cin.fail() || invalido); // realiza o ciclo enquanto o ficheiro introduzido nao for valido ou nao existir;
	return a;
}

int selectMenu(char menor, char maior)
{
	string linha = "";

	while (linha.length() != 1)
	{
		getline(cin, linha);
		if (cin.eof())
			cin.clear();

		if (linha.length() != 1 || (linha.length() == 1 && (linha[0] < menor || linha[0] > maior)))
		{
			cout << "Opcao invalida. Introduza a opcao pretendida: ";
			linha = "";
		}
	}
	return linha[0];
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

Campeonato::Campeonato(const string &filename)
{
	ifstream ReadConfig(filename.c_str());

	// codigo do Jonas, esta no git na versao anterior.

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

}

void Campeonato::criaEquipa()
{
	Equipa novaEquipa;

	adicionaVetor(Equipas, novaEquipa);
}


void Campeonato::menuCampeonato()
{
	cout << "    " << nome << endl;
	cout << "1 - Equipas" << endl;
	cout << "2 - Infraestruturas -- por fazer" << endl;
	cout << "3 - Modalidades -- por fazer" << endl;
	cout << "4 - Calendario -- por fazer" << endl;
	cout << "5 - Sair " << endl;
	cout << "\nIntroduza a opcao pretendida: ";

	switch (selectMenu('1','5'))
	{
	case '1':
		menuEquipas();
		break;
	case '2':
		//menuInfraestruturas();
		break;
	case '3':
		//menuModalidades();
		break;
	case '4':
		//menuCalendario();
		break;
	case '5':
		exit(0);
		break;
	}
	system("pause");
}

void Campeonato::menuEquipas()
{
	cout << "    Equipas" << endl;
		cout << "1 - Ver lista de equipas -- por fazer" << endl;
		cout << "2 - Adicionar equipa -- por fazer" << endl;
		cout << "3 - Remover equipa -- por fazer" << endl;
		cout << "4 - Sair -- depois altero isto para ser para voltar atras" << endl;
		cout << "\nIntroduza a opcao pretendida: ";

		switch (selectMenu('1','4'))
		{
		case '1':
			//listaEquipas();
			break;
		case '2':
			//adicionarEquipa();
			break;
		case '3':
			//removerEquipa();
			break;
		case '4':
			exit(0);
			break;
		}
		system("pause");
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
