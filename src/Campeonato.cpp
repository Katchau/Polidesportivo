#include "Campeonato.h"

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

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

Data transParaData(string dataI,string horaI)
{
	stringstream  DATAI;
		DATAI << dataI;
		int dia,mes,ano;
		DATAI>>dia;
		char lixo;
		DATAI >> lixo;
		DATAI >> mes;
		DATAI >> lixo;
		DATAI >> ano;
	stringstream HORAI;
		int horas,min;
		HORAI << horaI;
		HORAI >> horas;
		HORAI >> lixo;
		HORAI >> min;
		return Data(dia,mes,ano,horas,min,0);
}

evento* transParaEvento(string dataI,string horaI,string dataF,string horaF,string nome,string tipo)
{
	Data inicial = transParaData(dataI,horaI);
	Data final = transParaData(dataF,horaF);
	evento *novo = new evento(nome,inicial,final,tipo);
	return novo;

}
///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

Campeonato::Campeonato(const string &filename)
{ //LER EQUIPAS
	ifstream ReadConfig(filename.c_str());

	string nomeEq, nomeInf, desporto, modalidade;

	ReadConfig.ignore(100, '\n');
	while (true) {
		getline(ReadConfig, nomeEq);
		cout << nomeEq << endl;
		if (nomeEq == "") //ou '\n'? boa pergunta
			break;
		try{
			Equipa eq(nomeEq);
			Equipas.push_back(eq);
			cout << "EQUIPAS:SIZE() = "  << Equipas.size() << endl;
		}
		catch(Equipa::EquipaNaoExistente &e){
			cout << "O ficheiro  " << nomeEq <<" nao existe!"<< endl;
		}

	}
	ReadConfig.ignore(100,'\n');
	while (true) {
		cout << "entrou " << endl;
		getline(ReadConfig, nomeInf);
		cout << nomeInf << endl;
		if (nomeInf == "") //ou '\n'?
			break;
		Infraestrutura * infa = new Infraestrutura(nomeInf);
		Infraestruturas.push_back(infa);
	}

	ReadConfig.ignore(100,'\n');
	while(desporto != ".")
	{
		cout << "entrou " << endl;
		ReadConfig >> desporto;
		cout << desporto << endl;
		ReadConfig.ignore(3);
		ReadConfig >> modalidade;
		cout << modalidade << endl;
		Desporto * p = new Modalidade(desporto, modalidade);
		Modalidades.push_back(p);
		ReadConfig >> desporto;
	}

	//falta a parte das provas e whatnot
	// codigo do Jonas, esta no git na versao anterior.Updated, ainda nao testei
	string prova = "Prova.txt";
	ifstream Provas(prova.c_str());

	while(!Provas.eof())
	{
		string tipo,desporto,modalidade,dataI,horaI,dataF,horaF,infra;
		getline(Provas,tipo);
		getline(Provas,desporto);
		getline(Provas,modalidade);
		string nomeTotal =desporto+" , " + modalidade;
		getline(Provas,dataI);
		getline(Provas,horaI);
		getline(Provas,dataF);
		getline(Provas,horaF);
		getline(Provas,infra);
		evento *novo =  transParaEvento(dataI,horaI,dataF,horaF,modalidade,tipo);

		for(unsigned int i = 0;i < Modalidades.size();i++)
		{
			if(Modalidades[i]->getNome() == nomeTotal)
			{
				Modalidades[i]->adicionaProva(novo);
			}
		}
		for(unsigned int i = 0;i < Infraestruturas.size();i++)
		{
			if(Infraestruturas[i]->getNome() == infra)
			{
				Infraestruturas[i]->adicionaEvento(novo);
			}
		}
	}

	cout << "fim construtor campeonatoFILE" << endl;
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

void Campeonato::menuCampeonato()
{
	while(1)
	{
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
			return;
			break;
		}
	};
}

void Campeonato::menuEquipas()
{
	while (1)
	{
		cout << "    Equipas" << endl;
		cout << "1 - Ver lista de equipas" << endl;
		cout << "2 - Adicionar equipa" << endl;
		cout << "3 - Remover equipa" << endl;
		cout << "4 - Voltar atras"<< endl;
		cout << "\nIntroduza a opcao pretendida: ";

		switch (selectMenu('1','4'))
		{
		case '1':
			listaEquipas();
			break;
		case '2':
			criaEquipa();
			break;
		case '3':
			removerEquipa();
			break;
		case '4':
			return;
			break;
		}
	}
}

void Campeonato::listaEquipas(){

	cout << "    Lista de Equipas" << endl;
	cout << "1 - Por odem alfabetica" << endl;
	cout << "2 - Por pontuacao -- por fazer" << endl;
	cout << "3 - Sair" << endl;
	cout << "\nIntroduza a opcao pretendida: ";

	switch (selectMenu('1','3'))
	{
	case '1':
		EquipasOrdemAlfabetica();
		break;
	case '2':
		//EquipasOrdemPontuacao();
		break;
	case '3':
		return;
		break;
	}
}

void Campeonato::EquipasOrdemAlfabetica()
{
	sort (Equipas.begin(), Equipas.end(), ordenaAlfaEquipa);
	cout << "    Equipas" << endl;
	cout << "Número de equipas: " << Equipas.size()  << endl;
	for(unsigned int i = 0; i < Equipas.size(); i++)
	{
		cout << i+1 << " - " << Equipas[i].getNomeEquipa() << endl;
	}

}

void Campeonato::criaEquipa()
{
	bool invalido;

	do {
		invalido = false;
		Equipa novaEquipa;

		if(!adicionaVetor(Equipas, novaEquipa))
		{
			invalido = true;
			cout << "A equipa ja existe! \n";
		}
	} while (invalido == true);

	cout << "Equipa adicionada! \n";
}


void Campeonato::removerEquipa()
{
	string nome;

	bool removida = false;

	while (removida == false)
	{
		bool valido = true;

		do
		{
			cin.clear();
			if (!valido)
				cout << "Introduza um nome nao vazio: ";
			else
				cout << "Introduza o nome da Equipa a remover: ";

			getline(cin, nome);

			valido = false;

			for (size_t i = 0; i < nome.size(); i++)
				if (nome[i] != ' ')
					valido = true;
		} while (cin.eof() || !valido);

		for (size_t i = 0; i < Equipas.size(); i++)
			if (Equipas[i].getNomeEquipa() == nome)
			{
				removeVetor(Equipas, Equipas[i]);
				cout << "A equipa " << nome << " foi removida \n";
				removida = true;
			}

		if (removida == false)
			cout << "A equipa " << nome << " nao existe \n";
	};
}


void Campeonato::menuInfraestruturas()
{
	while (1)
	{
		cout << "    Infraestruturas" << endl;
		cout << "1 - Ver lista de infraestruturas" << endl;
		cout << "2 - Adicionar infraestrutura" << endl;
		cout << "3 - Remover infraestrutura -- 50/50" << endl;
		cout << "4 - Sair " << endl;
		cout << "\nIntroduza a opcao pretendida: ";
		switch (selectMenu('1','4'))
		{
		case '1':
			listaInfraestruturas();
			break;
		case '2':
			adicionarInfraestrutura();
			break;
		case '3':
			removerInfraestrutura();
			break;
		case '4':
			return;
			break;
		}
	}
}

void Campeonato::listaInfraestruturas()
{
	while (1)
	{
		cout << "    Infraestruturas" << endl;
		cout << "1 - Ordem alfabetica-- por fazer" << endl;
		cout << "2 - Onde  é a proxima prova? -- por fazer" << endl;
		cout << "3 - Sair " << endl;
		cout << "\nIntroduza a opcao pretendida: ";
		switch (selectMenu('1','3'))
		{
		case '1':
			InfraestruturasOrdemAlfabetica();
			break;
		case '2':
			//OndeProximaProva();
			break;
		case '3':
			return;
			break;
		}
	}
}

void Campeonato::InfraestruturasOrdemAlfabetica(){

	sort(Infraestruturas.begin(),Infraestruturas.end(),ordenaAlfaInfra);
	cout << " Infraestruturas" << endl;
	for(unsigned int i = 0; i < Infraestruturas.size();i++)
	{
		cout << i+ 1 << " - " << Infraestruturas[i]->getNome() << endl;
	}
	system("pause");
}

void Campeonato::adicionarInfraestrutura(){ // falta eliminar string so com espaços
	cout << " Infraestruturas" << endl;
	string nome;
	Infraestrutura *Novo;
	bool valido = true;
	do
	{
		cin.clear();
		cout << "Introduza o nome da nova infraestrutura: ";
		getline(cin, nome);
		if(nome == "")
		{
			cout << "Nome vazio" << endl;
			continue;
		}
		Novo =new Infraestrutura(nome);
		valido =  true;
		cout << Infraestruturas.size() << endl;
		for(unsigned int i = 0; i < Infraestruturas.size();i++ )
		{
			if( Infraestruturas[i]->getNome() == Novo->getNome())
			{
				cout << "A infraestrutura ja existe! \n" ;
				valido = false;
				delete Novo;
			}
		}
	} while (cin.eof() || !valido);

	Infraestruturas.push_back(Novo);
	cout << "Infraestrutura adicionada! \n";

}

void Campeonato::removerInfraestrutura(){
	// problema com string de espaços
	// FALTA testar quando á eventos
	do{
		cout << "Introduza o nome da infraestrutura a apagar: ";
		string a;
		cin >> a;
		if(a == "")
		{
			cout << "Introduza um nome não vazio! " << endl;
			continue;
		}

		for(unsigned int i = 0; i <  Infraestruturas.size();i++)
		{cout << "FOR" << endl;
		if(a == Infraestruturas[i]->getNome())
		{
			cout << "entrou" << endl;

			if(Infraestruturas[i]->getCalendario() != 0)
			{
				if(Infraestruturas[i]->Neventos() != 0)
				{
					cout << "Nao pede remover uma infraestrutura com eventos!" << endl;
					break;
				}
			}
			else
			{
				cout << "delete" << endl;
				delete Infraestruturas[i];
				Infraestruturas.erase(Infraestruturas.begin()+i);

			}



			return;
		}
		}
	}while(true);

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
	save << "Equipas:" << '\n';
	for(unsigned int i = 0;i<Equipas.size();i++)
	{
		save << Equipas[i].getNomeEquipa() << '\n';
	}
	save << '\n' << "Infraestruturas:" << '\n';

	for(unsigned int i = 0;i<Infraestruturas.size();i++)
	{
		save << Infraestruturas[i]->getNome() << '\n';
	}

	save << '\n' << "Modalidades:" << '\n';

	for(unsigned int i = 0;i < Modalidades.size();i++)
	{
		if(Modalidades.size()-i == 1)
		{
			save << Modalidades[i]->getNome() << " ." << '\n';
		}
		else
		{
			save << Modalidades[i]->getNome() << " ," << '\n';
		}
	}

	//TO DO
}


