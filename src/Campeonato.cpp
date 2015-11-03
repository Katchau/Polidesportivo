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
	// podia fazer isto em varias funcoes a parte. Mb a good ideia
	ifstream ReadConfig(filename.c_str());
	string nomeEq, nomeInf, desporto, modalidade;
	ReadConfig.ignore(100, '\n');
	while (true) {
		getline(ReadConfig, nomeEq);
		if (nomeEq == "") //ou '\n'?
			break;
		nomeEq = nomeEq + ".txt";
		try{
		Equipa eq(nomeEq);
		Equipas.push_back(eq);
		}
		catch(Equipa::EquipaNaoExistente &e){
			cout << "A equipa nao existe" << endl;
		}

	}
	ReadConfig.ignore(100,'\n');
	while (true) {
			getline(ReadConfig, nomeInf);
			if (nomeInf == "") //ou '\n'?
				break;
			Infraestrutura * infa = new Infraestrutura(nomeInf);
			Infraestruturas.push_back(infa);
		}
	/*NAO PERCEBO ISTO AQUI
	ReadConfig.ignore(100,'\n');
	while (true) {
				getline(ReadConfig, nomeInf);
				if (nomeInf == "") //ou '\n'?
					break;
				Infraestrutura * infa = new Infraestrutura(nomeInf);
				Infraestruturas.push_back(infa);
			}*/
	ReadConfig.ignore(100,'\n');
	while(desporto != ".")
	{
		ReadConfig >> desporto;
		ReadConfig.ignore(3);
		ReadConfig >> modalidade;
		Desporto * p = new Modalidade(desporto, modalidade);
		Modalidades.push_back(p);
		ReadConfig >> desporto;
	}
	//falta a parte das provas e whatnot
	// codigo do Jonas, esta no git na versao anterior.Updated, ainda nao testei

	system("pause");
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
{do{
	cout << "    " << nome << endl;
	cout << "1 - Equipas" << endl;
	cout << "2 - Infraestruturas" << endl;
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
		menuInfraestruturas();
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
	}while(!cin.eof());
}

void Campeonato::menuEquipas()
{
	cout << "    Equipas" << endl;
		cout << "1 - Ver lista de equipas -- por fazer" << endl;
		cout << "2 - Adicionar equipa -- por fazer" << endl;
		cout << "3 - Remover equipa -- por fazer" << endl;
		cout << "4 - Sair"<< endl;
		cout << "\nIntroduza a opcao pretendida: ";

		switch (selectMenu('1','4'))
		{
		case '1':
			listaEquipas();
			break;
		case '2':
			//adicionarEquipa();
			break;
		case '3':
			//removerEquipa();
			break;
		case '4':
			return;
			break;
		}
		system("pause");
}

void Campeonato::listaEquipas(){
	cout << "    Equipas" << endl;
	unsigned int i = 0;
	for(i; i < Equipas.size();i++){
		cout << i+1 << " - " << Equipas[i].getNomeEquipa() << endl;
	}


}
void Campeonato::menuInfraestruturas(){
	cout << " Infraestruturas" << endl;
			cout << "1 - Ver lista de infraestruturas -- por fazer" << endl;
			cout << "2 - Adicionar infraestrutura -- por fazer" << endl;
			cout << "3 - Remover infraestrutura -- por fazer" << endl;
			cout << "4 - Sair -- depois altero isto para ser para voltar atras" << endl;
			cout << "\nIntroduza a opcao pretendida: ";
			switch (selectMenu('1','4'))
					{
					case '1':
						//listaInfraestruturas();
						break;
					case '2':
						//adicionarInfraestrutura();
						break;
					case '3':
						//removerInfraestrutura();
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
	ofstream save;
	string nomeficheiro = nome + ".txt";
	save << "Equipas:" << endl;
	for(unsigned int i = 0;i<Equipas.size();i++)
	{
		save << Equipas[i].getNomeEquipa() << endl;
	}
	save << endl << "Infraestruturas:" << endl;

	for(unsigned int i = 0;i<Infraestruturas.size();i++)
	{
		save << Infraestruturas[i]->getNome() << endl;
	}

	save << endl << "Modalidades:" << endl;

	for(unsigned int i = 0;i < Modalidades.size();i++)
	{
		if(Modalidades.size()-i == 1)
		{
			save << Modalidades[i]->getNome() << " ." << endl;
		}
		else
		{
			save << Modalidades[i]->getNome() << " ," << endl;
		}
	}

	//TO DO
}

