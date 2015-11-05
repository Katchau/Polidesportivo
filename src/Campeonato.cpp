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
		cout << " teste 4" << endl;
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
   cout << "PROVA" << endl;
	while(!Provas.eof())
	{
		string tipo,desporto,modalidade,dataI,horaI,dataF,horaF,infra;
		getline(Provas,tipo);
		getline(Provas,desporto);
		getline(Provas,modalidade);
		cout << " teste 2" << endl;
		string nomeTotal =desporto+" , " + modalidade;
		getline(Provas,dataI);
		getline(Provas,horaI);
		getline(Provas,dataF);
		getline(Provas,horaF);
		getline(Provas,infra);
		cout << " teste 3" << endl;
		evento *novo =  transParaEvento(dataI,horaI,dataF,horaF,modalidade,tipo);

		for(unsigned int i = 0;i < Modalidades.size();i++)
		{
			if(Modalidades[i]->getNome() == nomeTotal)
			{cout << " teste 6" << endl;
				Modalidades[i]->adicionaProva(novo);
			}
		}
		cout << Infraestruturas.size() << endl;
		for(unsigned int i = 0;i < Infraestruturas.size();i++)
		{	cout << i << endl;
			if(Infraestruturas[i]->getNome() == infra)
			{cout << " teste 7" << endl;
			if(Infraestruturas[i]->getCalendario()->getInicio() == Data()
					&& Infraestruturas[i]->getCalendario()->getFim() == Data())
			{
				Infraestruturas[i]->getCalendario()->setFim(Data(31,12,9999));
			}
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
			menuModalidades();
			break;
		case '4':
			menuCalendario();
			break;
		case '5':
			return;
			break;
		}
	};
}
//MENU EQUIPAS
void Campeonato::menuEquipas()
{
	while (1)
	{
		cout << "    Equipas" << endl;
		cout << "1 - Ver lista de equipas" << endl;
		cout << "2 - Adicionar equipa" << endl;
		cout << "3 - Remover equipa" << endl;
		cout << "4 - Atletas -- por fazer" << endl;
		cout << "5 - Voltar atras"<< endl;
		cout << "\nIntroduza a opcao pretendida: ";

		switch (selectMenu('1','5'))
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
					menuAtletas();
					break;
		case '5':
							return;
							break;
		}
	}
}
void Campeonato::adicionaAtleta()
{	while(1)
{
	cout<< "Introduza o nome do atleta: ";
	string nome;
	getline(cin,nome);
	cout << "Introduza o nome da equipa: ";
	string equipa;
	getline(cin,equipa);
    if(ExisteEquipa(equipa))
    {
    	cout << " Equipa ja existe !" << endl;
    	continue;
    }
    if(ExisteAtleta(nome))
    {
    	cout << " O atleta ja existe!" << endl;
    	continue;
    }

    if(AdicionaAtletaEquipa(nome,equipa))
    {
    	cout << "Atleta adicionado " << endl;
    	return;
    }
    else
    {
    	cout << "Nao foi possivel adicionar o atleta " << endl;
    	continue;
    }
	//TODO testar isto
}


}
void Campeonato::menuAtletas()
{ while(1){
	    cout << "    Atletas	 " << endl;
		cout << "1 - Adicionar Atleta -- por fazer" << endl;
		cout << "2 - Remover Atleta -- porfazer" << endl;
		cout << "3 - Listar Atletas -- por fazer" << endl;
		cout << "4 - Sair" << endl;
		cout << "\nIntroduza a opcao pretendida: ";

		switch (selectMenu('1','3'))
		{
		case '1':
			//TODO AdicionarAtleta();
			break;
		case '2':
			//TODO RemoverAtleta();
			break;
		case '3':
			//TODO ListarAtletas();
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
	system("pause");
	cout << "\n";

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

//INFRAESTRUTURA
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
	cout << "\n";
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

	// TODO testar quando á eventos
	do{
		cout << "Introduza o nome da infraestrutura a apagar: ";
		string a;
		getline(cin,a);
		cout << "Input: " << a << endl;
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
				cout << "delete" << endl;
				delete Infraestruturas[i];
				Infraestruturas.erase(Infraestruturas.begin()+i);
			return;
		}
		}
	}while(true);

}


//MODALIDADE
void Campeonato::menuModalidades()
{
	while (1)
	{
		cout << "    Modalidades" << endl;
		cout << "1 - Ver lista de Modalidades -- testar" << endl;
		cout << "2 - Adicionar Modalidade -- testar" << endl;
		cout << "3 - Remover Modalidad -- testar" << endl;
		cout << "4 - Voltar atras"<< endl;
		cout << "\nIntroduza a opcao pretendida: ";

		switch (selectMenu('1','4'))
		{
		case '1':
			listaModalidades();
			break;
		case '2':
			AdicionarModalidade();
			break;
		case '3':
			RemoverModalidade();
			break;
		case '4':
			return;
			break;
		}
	}
}
void Campeonato::listaModalidades()
{
	while (1)
	{
		cout << "    Modalidades" << endl;
		cout << "1 - Ordem Alfabetica" << endl;
		cout << "2 - Proxima modalidade -- por fazer" << endl;
		cout << "3 - Sair " << endl;
		cout << "\nIntroduza a opcao pretendida: ";
		switch (selectMenu('1','3'))
		{
		case '1':
			OrdemAlfabeticaModalidades();
			break;
		case '2':
			//ProximaModalidade();
			break;
		case '3':
			return;
			break;
		}
	}
}
void Campeonato::OrdemAlfabeticaModalidades()
{	 cout << "MODALIDADES:SIZE(): " << Modalidades.size() << endl;
sort(Modalidades.begin(),Modalidades.end(),ordenaAlfaDesporto);
cout << "  Modalidades" << endl;
for(unsigned int i = 0; i < Modalidades.size();i++)
{
	cout << i+1 << " - " << Modalidades[i]->getTipo() << endl;
}
system("pause");
}
void Campeonato::AdicionarModalidade()
{
	string nome,tipo;
	Modalidade *Novo;
	bool valido = true;
	do
	{
		cin.clear();
		cout << "Introduza o nome o nome do Desporto: ";
		getline(cin, nome);
		cout << "Introduza o nome da nova Modalidade: ";
		getline(cin,tipo);
		if(nome == "")
		{
			cout << "Desporto vazio" << endl;
			continue;
		}
		if(tipo == "")
		{
			cout << "Modalidade vazio" << endl;
			continue;
		}
		Novo =new Modalidade (nome,tipo);
		valido =  true;
		cout << Modalidades.size() << endl;
		for(unsigned int i = 0; i < Modalidades.size();i++ )
		{	if(Modalidades[i]->getDesporto() == nome)
			if( Modalidades[i]->getTipo() == Novo->getTipo())
			{
				cout << "A modalidade ja existe! \n" ;
				valido = false;
				delete Novo;
			}
		}
	} while (cin.eof() || !valido);

	Modalidades.push_back(Novo);
	cout << "Modalidade adicionada! \n";

}
void Campeonato::RemoverModalidade()
{ //TODO remover atleras das provas
	do{
		cout << "Introduza o nome do desporto : ";
		string desp;
		cin >> desp;
		if(desp == "")
		{
			cout << "Introduza um nome não vazio! " << endl;
			continue;
		}
		cout << "Introduza o nome da modalidade a apagar: ";
		string mod;
		cin >> mod;
		if(mod == "")
		{
			cout << "Introduza um nome não vazio! " << endl;
			continue;
		}

		for(unsigned int i = 0; i <  Modalidades.size();i++)
		{cout << "FOR" << endl;
		if(mod == Modalidades[i]->getTipo())
		{
			cout << "entrou" << endl;

			if(desp == Modalidades[i]->getDesporto())
			{
				cout << "Modalidade removida " << endl;
				delete Modalidades[i];
				Modalidades.erase(Modalidades.begin()+i);
				return;
			}
		}


		}
		cout << "A modalidade não existe!" << endl;
	}while(true);
	cout << "\n";
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


int Campeonato::menuEscolhaInfra()
{
	unsigned int x,indice, s = Infraestruturas.size();
	for(unsigned int i=0;i<Infraestruturas.size();i++) // ou entao dar replace por InfraestruturasOrdemAlfabetica();
	{
		x = i+1;
		cout << x << ": " << Infraestruturas[i]->getNome() << endl;
	}
	do
	{
		cout << "Introduza um valor entre 1 e " << Infraestruturas.size() << endl;
		cin >> indice;
		while(cin.fail())
		{
			cin.clear();
			cin.ignore(1000,'\n');
			cout << "Porfavor introduza um valor valido" << endl;
			cin >> indice;
		}
		if(indice < 1 || indice > s)
		{
			cout << "Porfavor introduza um valor valido "<< endl;
			cin.clear();
			cin.ignore(1000,'\n');
		}
		else break;
	}while(true);

	indice--;
	return indice;
}


void Campeonato::totalCalendario()
{
	for(unsigned int i =0;i<Infraestruturas.size();i++)
	{
		cout << Infraestruturas[i]->getNome() << endl;
		Infraestruturas[i]->imprimeCalendario(); //choo choo comboio powaa
		cout << endl;
	}
	system("pause");
}

void Campeonato::calendarioInfra()
{
	string resposta;
	do
	{
		int indice = menuEscolhaInfra();
		Infraestruturas[indice]->imprimeCalendario();
		cout << endl << "Pretende visualizar outra vez?";
		cin >> resposta;
	}while(resposta != "nao");
	system("pause");
}

void Campeonato::listaCalendarios(){
	cout << " Calendarios: Identifique qual calendario a ver" << endl;
	cout << "1 - Todos os calendarios" << endl;
	cout << "2 - Calendario de Apenas 1 InfraEstrutra" << endl;
	cout << "3 - Sair " << endl;
	cout << "\nIntroduza a opcao pretendida: ";
	switch (selectMenu('1','3'))
	{
	case '1':
		totalCalendario();
		break;
	case '2':
		calendarioInfra();
		break;
	case '3':
		return;
		break;
	}
}

void Campeonato::adicionarEventos()
{
	string resposta;
	do
	{
		cout << "Qual das Infraestruturas pretende adicionar evento?" << endl;
		int indice = menuEscolhaInfra();

		cout << "Por favor introduza o nome do evento" << endl;
		string nomeEvento, tipo;
		cin >> nomeEvento;
		bool valid = false;
		while(!valid)
				{
					cout << "Porvavor introduza tempo ou pontos no Tipo" << endl;
					cin.clear();
					cin.ignore(100, '\n');
					cin >> tipo;
					if(tipo == "tempo" || tipo == "pontos")
							{
								valid = true;
							}
				}

		int d, m, a, h, mi, s=0;
		while(1){ cin.clear();
				cin.ignore(100,'\n');
			cout << "Data inicial" << endl;
					cout << "PS: No formato dia, mes, ano, hora e minuto" << endl;
					cin >> d >> m >> a >> h >> mi;
					if(cin.fail())
					{
						cout << "Data invalida" << endl;
						continue;
					}
					break;
		}
		Data di(d, m, a, h, mi, s);
		while(1){	cin.clear();
					cin.ignore(100,'\n');
			cout << "Data Final" << endl;
					cout << "PS: No formato dia, mes, ano, hora e minuto" << endl;
					cin >> d >> m >> a >> h >> mi;
					Data df(d, m, a, h, mi, s);
					if(cin.fail())
							{
								cout << "Data invalida" << endl;
								continue;
							}
					break;
		}
		Data df(d, m, a, h, mi, s);
		// TODO falta try catches e whatnot
		evento * ev = new evento(nomeEvento, di, df, tipo);
		if(Infraestruturas[indice]->getCalendario()->getFim() == Data())
			Infraestruturas[indice]->getCalendario()->setFim(df);
		Infraestruturas[indice]->adicionaEvento(ev);
		cout << Infraestruturas[indice]->Neventos();
		cout << "Adicionar outro evento ou sair?" << endl;
		cin >> resposta;
		transform(resposta.begin(),resposta.end(), resposta.begin(), ::towlower);
	}while(resposta != "sair");
}

void Campeonato::removerEventos()
{
	string resposta;
	do {
		cout << "Qual das Infraestruturas pretende remover evento?" << endl;
		int indice = menuEscolhaInfra();

		cout << "Por favor introduza o nome do evento" << endl;
		string nomeEvento, tipo;
		cin >> nomeEvento;
		bool valid = false;
		while (!valid) {
			cout << "Porvavor introduza tempo ou pontos no Tipo" << endl;
			cin.clear();
			cin.ignore(100, '\n');
			cin >> tipo;
			if (tipo == "tempo" || tipo == "pontos") {
				valid = true;
			}
		}

		cout << "Data inicial" << endl;
		cout << "PS: No formato dia, mes, ano, hora e minuto" << endl;
		int d, m, a, h, mi, s = 0;
		cin >> d >> m >> a >> h >> mi;
		Data di(d, m, a, h, mi, s);

		cout << "Data Final" << endl;
		cout << "PS: No formato dia, mes, ano, hora e minuto" << endl;
		cin >> d >> m >> a >> h >> mi;
		Data df(d, m, a, h, mi, s);
		// falta try catches e whatnot
		evento * ev = new evento(nomeEvento, di, df, tipo);
		if(Infraestruturas[indice]->getCalendario()->getFim() == Data())
				Infraestruturas[indice]->getCalendario()->setFim(df);

		Infraestruturas[indice]->removeEvento(ev);

		cout << "Remover outro evento ou sair?" << endl;
		cin >> resposta;
		transform(resposta.begin(), resposta.end(), resposta.begin(),
				::towlower);
	} while (resposta != "sair");
}


void Campeonato::menuCalendario(){
	cout << " Calendario" << endl;
	cout << "1 - Ver Calendarios do Campeonato " << getNome() << endl;
	cout << "2 - Adicionar Evento ao Calendario" << endl;
	cout << "3 - Remover Evento do Calendario" << endl;
	cout << "4 - Sair " << endl;
	cout << "\nIntroduza a opcao pretendida: ";
	switch (selectMenu('1','4'))
	{
	case '1':
		listaCalendarios();
		break;
	case '2':
		adicionarEventos();
		break;
	case '3':
		removerEventos();
		break;
	case '4':
		return;
		break;
	}
	system("pause");
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

	//TODO
}


//BOOLS
bool Campeonato::ExisteEquipa(string nome) const
{
	for(unsigned int i = 0; i < Equipas.size();i++)
	{
		if(nome == Equipas[i].getNomeEquipa())
			return true;
	}
	return false;
}
bool Campeonato::ExisteAtleta(string nome) const
{
	for(unsigned int i = 0; i < Equipas.size();i++)
	{
		for(unsigned int t = 0; t < Equipas[i].getAtletas().size();i++)
		{
			if(Equipas[i].getAtletas()[t].getNome() == nome)
				return true;
		}
	}
	return false;
}
bool Campeonato::AdicionaAtletaEquipa(string Atleta,string Equipa)
{
	for(unsigned int i = 0; i < Equipas.size();i++)
		{
			if(nome == Equipas[i].getNomeEquipa())
			{
				return Equipas[i].addAtleta(Atleta);
			}
		}
	return false;
}
bool Campeonato::RemoveAtletaEquipa(string equipa,string Atleta){
	for(unsigned int i = 0; i < Equipas.size();i++)
			{
				if(nome == Equipas[i].getNomeEquipa())
				{
					return Equipas[i].removeAtleta(Atleta);
				}
			}
		return false;
}
void Campeonato::RemoveAtletaProva(string Atleta) // TODO CONFIRMAR SE APONTADORES EM INFRASTRUTURAS
{												// È O MESMO DO QUE ESTA EM MODALIDADES
	for(unsigned int i = 0;i < Infraestruturas.size();i++)
	{
		Calendario *temp = Infraestruturas[i]->getCalendario();
		vector<evento *> Provas = temp->getEventos();
		for(unsigned int t = 0; t < Provas.size(); t++)
		{

		}


	}
}
