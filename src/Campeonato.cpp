#include "Campeonato.h"

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

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
	int horas,min,sec;
	HORAI << horaI;
	HORAI >> horas;
	HORAI >> lixo;
	HORAI >> min;
	HORAI >> lixo;
	HORAI >> sec;
	return Data(dia,mes,ano,horas,min,sec);
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

	nome = filename; //me need this!!

	string nomeEq, nomeInf, desporto, modalidade;

	ReadConfig.ignore(100, '\n');
	while (true) {
		getline(ReadConfig, nomeEq);
		if (nomeEq == "") //ou '\n'? boa pergunta
			break;
		try {
			Equipa eq(nomeEq);
			Equipas.push_back(eq);
		} catch (Equipa::EquipaNaoExistente &e) {
			cout << "O ficheiro  " << nomeEq << " nao existe!" << endl;
		}

	}
	ReadConfig.ignore(100, '\n');
	while (true) {
		getline(ReadConfig, nomeInf);
		if (nomeInf == "") //ou '\n'?
			break;
		Infraestrutura * infa = new Infraestrutura(nomeInf);
		Infraestruturas.push_back(infa);
	}

	ReadConfig.ignore(100, '\n');
	string tmp = "";
	do {
		ReadConfig >> desporto;
		ReadConfig >> tmp;
		while (tmp != ",") {
			desporto = desporto + " " + tmp;
			ReadConfig >> tmp;
		}
		tmp = "";
		ReadConfig >> modalidade;
		ReadConfig >> tmp;
		while (tmp != "," && tmp != ".") {
			modalidade = modalidade + " " + tmp;
			ReadConfig >> tmp;
		}

		Desporto * p = new Modalidade(desporto, modalidade);

		Modalidades.push_back(p);
	} while (tmp != ".");

	//falta a parte das provas e whatnot
	// codigo do Jonas, esta no git na versao anterior.Updated, ainda nao testei
	string prova = "Prova_" + filename;
	ifstream Provas(prova.c_str());
	while (!Provas.eof()) {
		string tipo, desporto, modalidade, dataI, horaI, dataF, horaF, infra,
		nome_ev;
		getline(Provas, nome_ev);
		if(nome_ev == "")
		{
			break;
		}
		getline(Provas, tipo);
		getline(Provas, desporto);
		getline(Provas, modalidade);
		string nomeTotal = desporto + " , " + modalidade;
		getline(Provas, dataI);
		getline(Provas, horaI);
		getline(Provas, dataF);
		getline(Provas, horaF);
		getline(Provas, infra);
		evento *novo = transParaEvento(dataI, horaI, dataF, horaF, nome_ev,
				tipo);
		int indice_mod, indice_evento;

		for (unsigned int i = 0; i < Modalidades.size(); i++) {
			if (Modalidades[i]->getNome() == nomeTotal) {
				Modalidades[i]->adicionaProva(novo);
				indice_mod = i;
			}
		}
		for (unsigned int i = 0; i < Infraestruturas.size(); i++) {
			if (Infraestruturas[i]->getNome() == infra) {
				if (Infraestruturas[i]->getCalendario()->getInicio() == Data()
						&& Infraestruturas[i]->getCalendario()->getFim()
						== Data()) {
					Infraestruturas[i]->getCalendario()->setFim(
							Data(31, 12, 9999));
				}
				Infraestruturas[i]->adicionaEvento(novo);

			}
		}

		indice_evento = Modalidades[indice_mod]->getProvas().size() - 1;
		string nomeAtleta = "Default", horaR, score;
		int pontuacao;
		getline(Provas, nomeAtleta);
		while (nomeAtleta != "") {
			if (tipo == "PONTO") {
				getline(Provas, score);
				stringstream convertoint;
				convertoint << score;
				convertoint >> pontuacao;
				Modalidades[indice_mod]->adicionaResultado(indice_evento,
						nomeAtleta, 0, 0, 0, pontuacao);
			}
			if (tipo == "TEMPO") {
				getline(Provas, horaR);
				stringstream horatoint;
				int horas, minutos, segundos;
				char lix;
				horatoint << horaR;
				horatoint >> horas;
				horatoint >> lix;
				horatoint >> minutos;
				horatoint >> lix;
				horatoint >> segundos;
				Modalidades[indice_mod]->adicionaResultado(indice_evento,
						nomeAtleta, horas, minutos, segundos, 0);
			}
			getline(Provas, nomeAtleta);
		}
	}

	cout << "Carregou!" << endl;
}

Campeonato::Campeonato()
{
	nome = returnInput("o campeonato");
	nome += ".txt";
}

void Campeonato::menuCampeonato()
{
	bool sair = false;

	while (!sair)
	{
		cout << "\n    " << nome << endl;
		cout << "1 - Equipas" << endl;
		cout << "2 - Infraestruturas" << endl;
		cout << "3 - Modalidades" << endl;
		cout << "4 - Calendario" << endl;
		cout << "5 - Gravar e sair " << endl;
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
			sair = true;
			break;
		}
	};
	gravarCampeonato();
	exit(1);
}
//MENU EQUIPAS
void Campeonato::menuEquipas()
{
	while (1)
	{
		cout << "\n    Equipas" << endl;
		cout << "1 - Ver lista de equipas" << endl;
		cout << "2 - Adicionar equipa" << endl;
		cout << "3 - Remover equipa" << endl;
		cout << "4 - Atletas" << endl;
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
{
	if (Equipas.size() == 0)
	{
		cout << "Nao existem equipas no campeonato. Adicione uma equipa antes de adicionar um atleta." << endl;
		return;
	}

	bool existe = false;
	string nomeAtleta, nomeEquipa;

	do
	{
		existe = false;
		nomeAtleta = returnInput("o atleta");

		if(ExisteAtleta(nomeAtleta))
		{
			cout << "O atleta " << nomeAtleta << " ja existe! Escolha um novo nome." << endl;
			existe = true;
		}
	} while (existe);

	while (!existe)
	{
		existe = false;
		nomeEquipa = returnInput("a equipa");
		if(ExisteEquipa(nomeEquipa))
		{
			if(AdicionaAtletaEquipa(nomeAtleta,nomeEquipa))
			{
				cout << nomeAtleta << " adicionado a " << nomeEquipa << "." << endl;
				return;
			}
			else
			{
				cout << "Nao foi possivel adicionar o atleta." << endl;
			}
		}
		else
		{
			cout << "A equipa " << nomeEquipa << " nao existe. Escolha uma das seguintes: " << endl;
			sort (Equipas.begin(), Equipas.end(), ordenaAlfaEquipa);
			for(unsigned int i = 0; i < Equipas.size(); i++)
			{
				cout << i+1 << " - " << Equipas[i].getNomeEquipa() << endl;
			}
		}
	}
}

void Campeonato::removeAtleta()
{
	if (Equipas.size() == 0)
	{
		cout << "Nao existem equipas no campeonato. Adicione uma equipa antes de remover um atleta." << endl;
		return;
	}

	bool existe = false;
	string nomeAtleta, nomeEquipa;

	do
	{
		existe = false;
		nomeEquipa = returnInput("a equipa");

		if (ExisteEquipa(nomeEquipa))
			existe = true;
		else
		{
			cout << "A equipa " << nomeEquipa << " nao existe. Escolha uma das seguintes: " << endl;
			sort (Equipas.begin(), Equipas.end(), ordenaAlfaEquipa);
			for(size_t i = 0; i < Equipas.size(); i++)
			{
				cout << i+1 << " - " << Equipas[i].getNomeEquipa() << endl;
			}
		}
	} while (!existe);

	size_t i;

	for (i = 0; i < Equipas.size(); i++)
		if (Equipas[i].getNomeEquipa() == nomeEquipa)
			break;

	if (Equipas[i].getAtletas().size() == 0)
	{
		cout << "Nao existem atletas nessa equipa. Adicione um atleta antes de o poder remover." << endl;
		return;
	}

	do
	{
		existe = false;
		nomeAtleta = returnInput("o atleta");

		if (Equipas[i].existeAtleta(nomeAtleta))
			existe = true;
		else
		{
			cout << "O atleta " << nomeAtleta << " nao existe. Escolha um dos seguintes: " << endl;
			vector<Atleta> Atle = Equipas[i].getAtletas();
			sort(Atle.begin(),Atle.end(),ordenaAlfaAtletas);
			for(unsigned int t = 0; t < Atle.size();t++)
			{
				cout << Atle[t].getNome() << endl;
			}
		}
	} while (!existe);

	if(RemoveAtletaEquipa(nomeEquipa,nomeAtleta))
	{
		RemoveAtletaProva(nome);
		cout << "Atleta Removido!" << endl;
	}

}

void Campeonato::AtletasPorEquipa()
{
	cout<< "Atletas por equipa:" << endl;
	for(unsigned int i = 0; i < Equipas.size();i++)
	{
		vector<Atleta> Atle = Equipas[i].getAtletas();
		sort(Atle.begin(),Atle.end(),ordenaAlfaAtletas);
		cout << "\n" << Equipas[i].getNomeEquipa() << ": " << Equipas[i].getAtletas().size() << endl;
		for(unsigned int t = 0; t < Atle.size();t++)
		{
			cout << t+1 << " - " << Atle[t].getNome() << endl;
		}
	}
}

void Campeonato::AtletasPorDesporto(){
	vector<string>Desportos = listaDesporto();
	cout<< "Atletas por desporto " << endl;
	for(unsigned int i = 0; i < Desportos.size();i++)
	{
		vector<string>Atletas = AtletasDesporto(Desportos[i]);

		sort(Atletas.begin(),Atletas.end());
		cout <<i+1 << " - " << Desportos[i] << endl;
		for(unsigned int k = 0; k < Atletas.size();k++)
		{
			cout << Atletas[k] << endl;
		}
	}
	cout << "\n";
}

void Campeonato::AtletasPorModalidade()
{
	cout << "Atletas por modalidades (apenas os que estao inscritos numa prova)" << endl;

	sort(Modalidades.begin(),Modalidades.end(),ordenaAlfaModalidade);
	for(unsigned int i = 0; i < Modalidades.size();i++)
	{
		vector<evento* > Provas = Modalidades[i]->getProvas();
		cout << i + 1 << " - " << Modalidades[i]->getTipo() <<  " - " << Modalidades[i]->getDesporto() << endl;
		vector<string > Atletas;

		for(unsigned int  t = 0; t < Provas.size();t++)//Juntar todos os atletas
		{
			vector <string> Atle = Provas[t]->getNomeAtletas();

			for(unsigned int k = 0; k < Atle.size();k++)
			{
				adicionaVetor(Atletas,Atle[k]);
			}
		}
		sort(Atletas.begin(),Atletas.end());
		for(unsigned int k = 0; k < Atletas.size();k++)
		{
			cout << Atletas[k] << endl;
		}

	}
}
void Campeonato::listaAtletas()
{
	while(1)

	{
		cout << "\n    Listar Atletas	 " << endl;
		cout << "1 - Por equipa" << endl;
		cout << "2 - Por modalidade" << endl;
		cout << "3 - Por desporto" << endl;
		cout << "4 - Voltar atras" << endl;
		cout << "\nIntroduza a opcao pretendida: ";

		switch (selectMenu('1','4'))
		{
		case '1':
			AtletasPorEquipa();
			break;
		case '2':
			AtletasPorModalidade();
			break;
		case '3':
			AtletasPorDesporto();
			break;
		case '4':
			return;
			break;
		}
	}
}
void Campeonato::menuAtletas()
{
	while(1)

	{
		cout << "\n    Atletas	 " << endl;
		cout << "1 - Adicionar Atleta" << endl;
		cout << "2 - Remover Atleta" << endl;
		cout << "3 - Listar Atletas" << endl;
		cout << "4 - Inscrever Atleta numa Modalidade" << endl;
		cout << "5 - Voltar atras" << endl;
		cout << "\nIntroduza a opcao pretendida: ";

		switch (selectMenu('1','6'))
		{
		case '1':
			adicionaAtleta();
			break;
		case '2':
			removeAtleta();
			break;
		case '3':
			listaAtletas();
			break;
		case '4':
			inscreverAtletaModalidade();
			break;
		case '5':
			return;
			break;

		}
	}
}
void Campeonato::listaEquipas(){

	cout << "    Lista de Equipas" << endl;
	cout << "1 - Por odem alfabetica" << endl;
	cout << "2 - Por pontuacao" << endl;
	cout << "3 - Voltar atras" << endl;
	cout << "\nIntroduza a opcao pretendida: ";

	switch (selectMenu('1','3'))
	{
	case '1':
		EquipasOrdemAlfabetica();
		break;
	case '2':
		EquipasOrdemPontuacao();
		break;
	case '3':
		return;
		break;
	}
}

void Campeonato::EquipasOrdemPontuacao()
{
	if (Modalidades.size() == 0)
	{
		cout << "O campeonato ainda nao tem modalidade. Adicione uma modalidade." << endl;
		return;
	}

	if (Equipas.size() == 0)
	{
		cout << "O campeonato ainda nao tem equipas. Adicione uma equipa." << endl;
		return;
	}

	cout << "    Modalidades: " << endl;

	for (unsigned int i = 0; i < Modalidades.size(); i++) {
		{
			cout << i+1 << ": " << Modalidades[i]->getDesporto() << " - " << Modalidades[i]->getTipo() << endl;
		}
	}

	cout << "Introduza o numero da modalidade desejada: ";
	int escolha = (selectMenu('1','0'+Modalidades.size()) -1) - '0';

	cout << "\n";

	if (Modalidades[escolha]->getProvas().size() == 0)
	{
		cout << "A modalidade escolhida ainda nao tem provas. Adicione uma prova." << endl;
		return;
	}

	cout << "    Equipas" << endl;
	cout << "Numero de equipas: " << Equipas.size()  << endl;

	if (Modalidades[escolha]->getProvas()[0]->getTipo() == "PONTO") {
		for (unsigned int i = 0; i < Equipas.size(); i++) {
			int tmp = Equipas[i].pontuacaoGeral(Modalidades[escolha]);
			Equipa tmp2 = Equipas[i];
			int j;
			for (j = i;
					j > 0
					&& tmp
					> Equipas[j - 1].pontuacaoGeral(
							Modalidades[escolha]); j--)
				Equipas[j] = Equipas[j - 1];
			Equipas[j] = tmp2;
		}
	}
	if (Modalidades[escolha]->getProvas()[0]->getTipo() == "TEMPO") {
		for (unsigned int i = 0; i < Equipas.size(); i++) {

			Data tmp = Equipas[i].melhorTempo(Modalidades[escolha]);
			Equipa tmp2 = Equipas[i];
			int j;
			for (j = i;
					j > 0
					&& tmp
					< Equipas[j - 1].melhorTempo(
							Modalidades[escolha]); j--)
				Equipas[j] = Equipas[j - 1];
			Equipas[j] = tmp2;
		}
	}
	for(unsigned int i = 0; i < Equipas.size(); i++)
	{
		cout << i+1 << " - " << Equipas[i].getNomeEquipa() << endl;
	}
}

void Campeonato::EquipasOrdemAlfabetica()
{
	sort (Equipas.begin(), Equipas.end(), ordenaAlfaEquipa);
	cout << "    Equipas" << endl;
	cout << "Numero de equipas: " << Equipas.size()  << endl;
	for(unsigned int i = 0; i < Equipas.size(); i++)
	{
		cout << i+1 << " - " << Equipas[i].getNomeEquipa() << endl;
	}
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
	if (Equipas.size() == 0)
	{
		cout << "Nao existem equipas no campeonato. Adicione uma equipa antes de a poder remover." << endl;
		return;
	}

	string nome;

	bool removida = false;

	while (removida == false)
	{
		nome = returnInput("a equipa a remover");

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
		cout << "\n    Infraestruturas" << endl;
		cout << "1 - Ver lista de infraestruturas" << endl;
		cout << "2 - Adicionar infraestrutura" << endl;
		cout << "3 - Remover infraestrutura" << endl;
		cout << "4 - Voltar Atras " << endl;
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
		cout << "\n    Infraestruturas" << endl;
		cout << "1 - Ordem alfabetica" << endl;
		cout << "2 - Voltar Atras" << endl;
		cout << "\nIntroduza a opcao pretendida: ";
		switch (selectMenu('1','2'))
		{
		case '1':
			InfraestruturasOrdemAlfabetica();
			break;
		case '2':
			return;
			break;
		}
	}
}

void Campeonato::InfraestruturasOrdemAlfabetica(){

	sort(Infraestruturas.begin(),Infraestruturas.end(),ordenaAlfaInfra);
	cout << "\n    Infraestruturas" << endl;
	for(unsigned int i = 0; i < Infraestruturas.size();i++)
	{
		cout << i+ 1 << " - " << Infraestruturas[i]->getNome() << endl;
	}
}

void Campeonato::adicionarInfraestrutura()
{
	cout << "\n    Infraestruturas" << endl;
	string nomeInfra;
	Infraestrutura *Novo;
	bool valido;

	do
	{
		valido = true;
		nomeInfra = returnInput("a infraestrutura");

		Novo = new Infraestrutura(nomeInfra);

		for(unsigned int i = 0; i < Infraestruturas.size();i++ )
		{
			if( Infraestruturas[i]->getNome() == Novo->getNome())
			{
				cout << "A infraestrutura " << Novo->getNome() << " ja existe! Escolha um novo nome." << endl;
				valido = false;
				delete Novo;
			}
		}
	} while (!valido);

	Infraestruturas.push_back(Novo);
	cout << "Infraestrutura adicionada! \n";

}

void Campeonato::removerInfraestrutura()
{
	if (Infraestruturas.size() == 0)
	{
		cout << "Nao existem infraestruturas no campeonato. Adicione uma infraestrutura antes de a poder remover." << endl;
		return;
	}

	string nomeInfra;
	bool existe;
	size_t indice;

	do
	{
		existe = false;
		nomeInfra = returnInput("a infraestrutura a apagar");

		for (size_t i = 0; i < Infraestruturas.size(); i++)
			if (Infraestruturas[i]->getNome() == nomeInfra)
			{
				existe = true;
				indice = i;
			}

		if (!existe)
		{
			cout << "A infraestrutura " << nomeInfra << " nao existe. Escolha uma das seguintes: " << endl;
			sort(Infraestruturas.begin(),Infraestruturas.end(),ordenaAlfaInfra);
			for(size_t i = 0; i < Infraestruturas.size();i++)
			{
				cout << i+1 << " - " << Infraestruturas[i]->getNome() << endl;
			}
		}
	} while (!existe);

	if(Infraestruturas[indice]->getCalendario() != 0)
	{
		if(Infraestruturas[indice]->Neventos() != 0)
		{
			cout << "Nao pode remover uma infraestrutura com eventos. Remova-os primeiro." << endl;
			return;
		}
	}

	cout << "Infraestrutura removida!" << endl;
	delete Infraestruturas[indice];
	Infraestruturas.erase(Infraestruturas.begin()+indice);

}

//MODALIDADE
void Campeonato::menuModalidades()
{
	while (1)
	{
		cout << "\n    Modalidades" << endl;
		cout << "1 - Ver lista de Modalidades" << endl;
		cout << "2 - Adicionar Modalidade" << endl;
		cout << "3 - Remover Modalidade" << endl;
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
		cout << "\n    Modalidades" << endl;
		cout << "1 - Ordem Alfabetica" << endl;
		cout << "2 - Voltar Atras" << endl;
		cout << "\nIntroduza a opcao pretendida: ";
		switch (selectMenu('1','2'))
		{
		case '1':
			OrdemAlfabeticaModalidades();
			break;
		case '2':
			return;
			break;
		}
	}
}
void Campeonato::OrdemAlfabeticaModalidades()
{
	sort(Modalidades.begin(),Modalidades.end(),ordenaAlfaDesporto);
	cout << "\n    Modalidades: " << endl;
	for(unsigned int i = 0; i < Modalidades.size();i++)
	{
		cout << i+1 << " - " << Modalidades[i]->getTipo() << " (" << Modalidades[i]->getDesporto() << ")" << endl;
	}
}

void Campeonato::AdicionarModalidade()
{

	string nome, tipo;

	nome = returnInput("o desporto");
	tipo = returnInput("a modalidade");

	Modalidade *Novo = new Modalidade(nome, tipo);

	for(unsigned int i = 0; i < Modalidades.size();i++ )
	{
		if(Modalidades[i]->getDesporto() == nome)
			if( Modalidades[i]->getTipo() == Novo->getTipo())
			{
				cout << "A modalidade ja existe! \n" ;
				delete Novo;
				return;
			}
	}
	Modalidades.push_back(Novo);
	cout << "Modalidade adicionada! \n";
}

void Campeonato::RemoverModalidade()
{
	string nome, tipo;

	nome = returnInput("o desporto");
	tipo = returnInput("a modalidade a apagar");

	for(unsigned int i = 0; i <  Modalidades.size();i++)
	{
		if(tipo == Modalidades[i]->getTipo())
		{
			if(nome == Modalidades[i]->getDesporto())
			{
				RemoveModalidadeAtletas(nome, tipo);
				RemoveEventosInfra(tipo);
				cout << "Modalidade removida!" << endl;
				delete Modalidades[i];
				Modalidades.erase(Modalidades.begin()+i);
				return;
			}
		}
	}
	cout << "A modalidade não existe!" << endl;
}

int Campeonato::numAtletas() const
{
	int num;

	for (size_t i = 0; i < Equipas.size(); i++)
		for (size_t j = 0; j < Equipas[i].getAtletas().size(); j++)
			num++;

	return num;
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
	for (size_t i = 0; i < Infraestruturas.size(); i++)
	{
		cout << i + 1 << " - " << Infraestruturas[i]->getNome() << endl;
	}

	cout << "Introduza o numero correspondente a infraestrutura desejada: ";
	int indice = selectMenu('1','0'+Infraestruturas.size()) - '1';

	return indice;
}


void Campeonato::totalCalendario()
{
	cout << "\n";
	for(unsigned int i =0;i<Infraestruturas.size();i++)
	{
		cout << Infraestruturas[i]->getNome() << ":" << endl;
		Infraestruturas[i]->imprimeCalendario();
		cout << endl;
	}
}

void Campeonato::calendarioInfra()
{
	int indice = menuEscolhaInfra();
	cout << "\n";
	Infraestruturas[indice]->imprimeCalendario();

}

void Campeonato::listaCalendarios(){
	cout << "\n    Calendarios: " << endl;
	cout << "1 - Todos os calendarios" << endl;
	cout << "2 - Calendario de apenas 1 Infraestrutra" << endl;
	cout << "3 - Voltar atras" << endl;
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
	if(Infraestruturas.size() == 0)
	{
		cout << "O campeonato ainda nao tem infraestrutura. Adicione uma infraestruturas antes de adicionar provas." << endl;
		return;
	}

	if(Modalidades.size() == 0)
	{
		cout << "O campeonato ainda nao tem modalidades. Adicione uma modalidade antes de adicionar provas." << endl;
		return;

	}

	cout << "\n    Adicionar Evento\n" << endl;

	string nomeEvento, tipo;
	string resposta, modalidade;
	cout << "Escolha a infraestrutura a que pretende adicionar o evento: " << endl;
	int indice = menuEscolhaInfra();

	nomeEvento = returnInput("o evento");

	cout << "Escolha o tipo de classificacao: " << endl;
	cout << "1 - Tempo" << endl;
	cout << "2 - Pontuacao" << endl;
	cout << "Introduza a opcao correspondente ao tipo de classificacao desejado: ";
	if (selectMenu('1','2') == '1')
		tipo = "TEMPO";
	else
		tipo = "PONTO";

	Data inicial, final;
	bool invalido;
	unsigned int dia, mes, ano, horas, minutos;

	do
	{
		invalido = false;

		cout << "Data Inicial: (introduza numeros inteiros)" << endl;

		dia = returnInt("Dia: ");
		mes = returnInt("Mes: ");
		ano = returnInt("Ano: ");
		horas = returnInt("Horas: ");
		minutos = returnInt("Minutos: ");

		inicial=Data(dia, mes, ano, horas, minutos, 0);

		if(!ValidaData(inicial,false))
		{
			cout << "A data introduzida nao e valida. Tente novamente!" << endl;
			invalido = true;
		}

	} while (invalido);

	cout << "Data inicial: " << inicial << endl;

	do
	{
		invalido = false;

		cout << "Data Final: (introduza numeros inteiros)" << endl;

		dia = returnInt("Dia: ");
		mes = returnInt("Mes: ");
		ano = returnInt("Ano: ");
		horas = returnInt("Horas: ");
		minutos = returnInt("Minutos: ");

		final=Data(dia, mes, ano, horas, minutos, 0);

		if(!ValidaData(inicial,false))
		{
			cout << "A data introduzida nao e valida. Tente novamente!" << endl;
			invalido = true;
		}

	} while (invalido);

	cout << "Data final: " << final << endl;

	if(final <= inicial)
	{
		cout << "Erro! A data inicial e igual ou posterior a data final." << endl;
		return;
	}

	evento * ev = new evento(nomeEvento, inicial, final, tipo);

	int n = Infraestruturas[indice]->Neventos();
	if (Infraestruturas[indice]->getCalendario()->getFim() == Data())
		Infraestruturas[indice]->getCalendario()->setFim(final);
	Infraestruturas[indice]->adicionaEvento(ev);

	int n_next = Infraestruturas[indice]->Neventos();
	size_t escolha;
	if (n_next != n) {

		cin.ignore(100, '\n');
		cout << "Escolha a modalidade da prova que deseja adicionar: " << endl;
		for (size_t i = 0; i < Modalidades.size(); i++)
		{
			cout << i+1 << ": " << Modalidades[i]->getDesporto() << " - " << Modalidades[i]->getTipo() << endl;
		}
		cout << "Introduza a opcao correspondente a modalidade desejada: ";
		escolha = selectMenu('1',Modalidades.size()+'0') - '1';

		Modalidades[escolha]->adicionaProva(ev);
	}
}

void Campeonato::removerEventos()
{
	if(Infraestruturas.size() == 0)
	{
		cout << "O campeonato ainda nao tem infraestruturas. Adicione uma infraestrutura antes de remover provas." << endl;
		return;
	}

	if(Modalidades.size() == 0)
	{
		cout << "O campeonato ainda nao tem modalidades. Adicione uma modalidade antes de remover provas." << endl;
		return;

	}

	cout << "\n    Remover Evento\n" << endl;

	string nomeEvento, tipo;
	string resposta, modalidade;
	cout << "Escolha a infraestrutura de que pretende remover o evento: " << endl;
	int indice = menuEscolhaInfra();

	int indiceEvento;

	vector<evento *> eventos = Infraestruturas[indice]->getCalendario()->getEventos();

	cout << "Escolha o evento a remover: " << endl;
	for (size_t i = 0; i < eventos.size(); i++)
	{
		cout << i+1 << " - " << eventos[i]->getNome() << endl;
	}
	cout << "Introduza o numero correspondente ao evento que deseja remover: ";

	indiceEvento = selectMenu('1', '0' + eventos.size()) - '1';

	nomeEvento = eventos[indiceEvento]->getNome();

	for (size_t i = 0; i < Modalidades.size(); i++)
	{
		for (size_t j = 0; j < Modalidades[i]->getProvas().size(); j++)
			if (Modalidades[i]->getProvas()[j]->getNome() == nomeEvento)
			{
				Modalidades[i]->removeProva(Modalidades[i]->getProvas()[j]);
			}
	}

	Infraestruturas[indice]->removeEvento(eventos[indiceEvento]);
}
//PROVAS
vector<evento *> Campeonato::ProvasOrganiza(unsigned int seleciona){
	//DATA ATUAL
	time_t Tempo_Atual = time(NULL);
	struct tm *tempo_info= localtime(&Tempo_Atual);
	unsigned int sec = tempo_info->tm_sec;
	unsigned int min = tempo_info->tm_min;
	unsigned int horas = tempo_info->tm_hour;
	unsigned int dia = tempo_info->tm_mday;
	unsigned int mes = tempo_info->tm_mon + 1;/* varia de 0 a 11*/
	unsigned int ano = tempo_info -> tm_year +1900 ; /* ano atual*/
	Data Atual (dia,mes,ano,horas,min,sec);
	cout << "Data Atual :" << Atual << endl;
	vector<evento *> ProvasRealizadas;
	vector<evento *> ProvasPorRealizar;
	for(unsigned int i = 0; i < Infraestruturas.size(); i++)
	{ vector <evento *> Provas = Infraestruturas[i]->getCalendario()->getEventos();
	for(unsigned int t = 0; t < Provas.size(); t ++)
	{
		Data Final = Provas[t]->getFinal();
		if(Final <= Atual)
			ProvasRealizadas.push_back(Provas[t]);
		else
			ProvasPorRealizar.push_back(Provas[t]);
	}

	}
	if(seleciona == 0){
		sort(ProvasRealizadas.begin(),ProvasRealizadas.end(),  OrdenaEventosAlpha);
		return ProvasRealizadas;
	}

	else
	{
		sort(ProvasPorRealizar.begin(),ProvasPorRealizar.end(), OrdenaEventosAlpha);
		return ProvasPorRealizar;
	}

}


void Campeonato::verResultados()
{
	size_t escolha;

	cout << "Escolha a modalidade cujos resultados pretende visualizar: " << endl;
	for (size_t i = 0; i < Modalidades.size(); i++)
	{
		cout << i+1 << ": " << Modalidades[i]->getDesporto() << " - " << Modalidades[i]->getTipo() << endl;
	}
	cout << "Introduza a opcao correspondente a modalidade desejada: ";
	escolha = selectMenu('1', Modalidades.size() + '0') - '1';


	vector<evento *> eventos = Modalidades[escolha]->getProvas();
	cout << "Eventos: " << endl;
	for(unsigned int i = 0; i < eventos.size(); i++)
	{
		cout << "\nNome: " << eventos[i]->getNome() << endl;
		cout << "Data inicial: " <<  eventos[i]->getInicial() << endl;
		cout << "Data final: " << eventos[i]->getFinal() << endl;
		cout << "Resultados: " << endl;
		eventos[i]->ProvaResultados();
	}
}


void Campeonato::adicionarProvas()
{
	if (Infraestruturas.size() == 0)
	{
		cout << "Nao existem infraestruturas no campeonato. Adicione uma infraestrutura antes de poder inscrever atletas em provas." << endl;
		return;
	}

	if (Equipas.size() == 0)
	{
		cout << "Ainda nao existem equipas inscritas no campeonato. Crie uma equipa antes de inscrever atletas.";
		return;
	}

	size_t indiceEquipa, indiceAtleta, indiceModalidade, indiceProva;
	bool sobreposto;

	cout << "Escolha a equipa do atleta que pretende inscrever: " << endl;

	for(size_t i = 0; i < Equipas.size(); i++)
		cout << i+1 << " - " << Equipas[i].getNomeEquipa() << endl;

	cout << "Introduza a opcao correspondente a equipa desejada: ";
	indiceEquipa = selectMenu('1',Equipas.size()+'0') - '1';

	if (Equipas[indiceEquipa].getAtletas().size() == 0)
	{
		cout << "Ainda nao existem atletas inscritos nessa equipa. Crie um atleta antes de o poder inscrever numa prova.";
		return;
	}

	cout << "Escolha o atleta que pretende inscrever: " << endl;

	for(size_t i = 0; i < Equipas[indiceEquipa].getAtletas().size(); i++)
		cout << i+1 << " - " << Equipas[indiceEquipa].getAtletas()[i].getNome() << endl;

	cout << "Introduza a opcao correspondente a equipa desejada: ";
	indiceAtleta = selectMenu('1',Equipas[indiceEquipa].getAtletas().size()+'0') - '1';

	Atleta atleta = Equipas[indiceEquipa].getAtletas()[indiceAtleta];

	if (atleta.getDesportosInsc().size() == 0)
	{
		cout << "O atleta escolhido nao esta inscrito em nenhuma modalidade.\n";
		cout << "Inscreva-o numa modalidade antes de o inscrever na prova.\n";
		return;
	}

	cout << "Escolha a modalidade da prova em que pretende inscrever o atleta: " << endl;

	for (size_t i = 0; i < Modalidades.size(); i++)
		cout << i+1 << ": " << Modalidades[i]->getDesporto() << " - " << Modalidades[i]->getTipo() << endl;

	cout << "Introduza a opcao correspondente a modalidade desejada: ";
	indiceModalidade = selectMenu('1',Modalidades.size()+'0') - '1';

	vector<evento *> provas = Modalidades[indiceModalidade]->getProvas();

	if (provas.size() == 0)
	{
		cout << "A modalidade selecionada nao tem provas. Crie um evento antes de tentar inscrever um atleta.\n";
	}

	cout << "Escolha a prova em que pretende inscrever o atleta: " << endl;

	for (size_t i = 0; i < provas.size(); i++)
		cout << i+1 << " - " << provas[i]->getNome() << endl;

	cout << "Introduza a opcao correspondente a prova desejada: ";
	indiceProva = selectMenu('1',provas.size()+'0') - '1';

	for (size_t i = 0; i < provas.size(); i++)
	{
		int indice = sequentialSearch(provas[i]->getNomeAtletas(), atleta.getNome());
		if(indice != -1)
			if (eventos_sobrepostos(provas[i], provas[indiceProva]))
				sobreposto = true;
	}

	if (sobreposto)
	{
		cout << "Evento sobreposto a um evento em que o atleta ja inscrito!" << endl;
		return;
	}

	Modalidades[indiceModalidade]->adicionaResultado(indiceProva, atleta.getNome(), 0, 0, 0, 0);

	return;

}

void Campeonato::removerProvas()
{
	string resposta,atleta, equipa,modalidade;
	int indice;
	do {
		bool existeE = false, existeA = false;
		cout << "Em que equipa se encntra o Atleta?" << endl;
		getline(cin, equipa);
		for(unsigned int i =0;i<Equipas.size();i++)
		{
			if(Equipas[i].getNomeEquipa() == equipa)
			{
				indice = i;
				existeE = true;
				break;
			}
		}
		if(existeE)
		{
			cout << "Qual atleta pretende remover a prova? E Modalidade?(1 em cada linha)" << endl;
			getline(cin, atleta);
			getline(cin, modalidade);
			for(unsigned int i =0;i<Equipas[indice].getAtletas().size();i++)
			{
				vector<Atleta> atletas = Equipas[indice].getAtletas();
				if(atletas[i].getNome() == atleta)
				{
					for (unsigned int j = 0; j < Modalidades.size(); j++) {
						if (modalidade == Modalidades[j]->getNome()) {
							indice = j;
							existeA = true;
							break;
						}
					}
					break;
				}
			}
		}


		if (existeA) {
			vector<evento *> ev = Modalidades[indice]->getProvas();
			cout << "Eventos: " << endl;
			for (unsigned int i = 0; i < ev.size(); i++) {
				cout << ev[i]->getNome() << "Data inicial: "
						<< ev[i]->getInicial() << " data final: "
						<< ev[i]->getFinal() << endl;
				cout << "Pretende remover uma prova a este evento?" << endl;
				cin >> resposta;
				if (resposta == "sim" || resposta == "Sim") {
					Modalidades[indice]->removeResultado(i,atleta);
					break;
				}

			}
		}
		else
		{
			cout << "Nao foi encontrado um ou mais  parametros pretendidos!" << endl;
		}
		cout << "Remover outro Resultado ou sair?" << endl;
		cin >> resposta;
		transform(resposta.begin(), resposta.end(), resposta.begin(),
				::towlower);
		cin.clear();
		cin.ignore(1000,'\n');
	} while (resposta != "sair");
}

void Campeonato::ProvasRealizadas()
{	vector<evento *> Provas = ProvasOrganiza(0);
cout << "Provas Realizadas" << endl;
for(unsigned int i = 0; i< Provas.size(); i++)
{
	cout << i+1 <<" - " << Provas[i]->getNome() << " Data Inicial: " << Provas[i]->getInicial() << " " << Provas[i]->getFinal() << endl;
}
cout << "\n";

}
void Campeonato::ProvasPorRealizar()
{
	vector<evento *> Provas = ProvasOrganiza(1);
	cout << "Provas Por Realizar" << endl;
	for(unsigned int i = 0; i< Provas.size(); i++)
	{
		cout << i+1 <<" - " << Provas[i]->getNome() << " Data Inicial: " << Provas[i]->getInicial() << " " << Provas[i]->getFinal() << endl;
	}
	cout << "\n";
}
void Campeonato::menuProvas()
{
	while(1)
	{
		cout << "\n    Provas" << endl;
		cout << "1 - Ver todas os Resultados" << endl;
		cout << "2 - Inscrever atleta numa prova" << endl;
		cout << "3 - Remover atleta duma prova" << endl;
		cout << "4 - Provas por realizar" << endl;
		cout << "5 - Provas realizadas "  << endl;
		cout << "6 - Voltar Atras" << endl;
		cout << "\nIntroduza a opcao pretendida: ";
		switch (selectMenu('1', '6')) {
		case '1':
			verResultados();
			break;
		case '2':
			adicionarProvas();
			break;
		case '3':
			removerProvas();
			break;
		case '4':
			ProvasPorRealizar();
			break;
		case '5':
			ProvasRealizadas();
			break;
		case '6':
			return;
			break;
		}
	}
}



void Campeonato::menuCalendario()
{
	while(1)
	{
		cout << "\n    Calendario" << endl;
		cout << "1 - Ver Calendarios do Campeonato " << getNome() << endl;
		cout << "2 - Adicionar Evento ao Calendario" << endl;
		cout << "3 - Remover Evento do Calendario" << endl;
		cout << "4 - Provas" << endl;
		cout << "5 - Voltar Atras" << endl;
		cout << "\nIntroduza a opcao pretendida: ";
		switch (selectMenu('1','5'))
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
			menuProvas();
			break;
		case '5':
			return;
			break;
		}
	}
}



void Campeonato::gravarCampeonato()
{
	for (size_t i = 0; i < Equipas.size(); i++)
	{
		Equipas[i].writetoFile();
	}
	ofstream grava;
	grava.open(nome.c_str());
	grava << "Equipas:" << '\n';
	for (size_t i = 0; i < Equipas.size(); i++)
	{
		grava << Equipas[i].getNomeEquipa() << '\n';
	}
	grava << '\n' << "InfraEstruturas:" << '\n';
	for (unsigned int i =0;i<Infraestruturas.size();i++)
	{
		grava << Infraestruturas[i]->getNome() << '\n';
	}
	grava << '\n' << "Modalidades:" << '\n';
	for (unsigned int i=0;i<Modalidades.size();i++)
	{
		if(Modalidades.size()-i == 1)
		{
			grava << Modalidades[i]->getNome() << " .";
		}
		else grava << Modalidades[i]->getNome() << " ," << '\n';
	}
	grava.close();
	gravaProvas();
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
		for(unsigned int k = 0; k < Equipas[i].getAtletas().size(); k++)
		{
			if(Equipas[i].getAtletas()[k].getNome() == nome)
				return true;
		}
	}
	return false;
}
bool Campeonato::AdicionaAtletaEquipa(string Atleta,string Equipa)
{
	cout << "Equipa: " << Equipa << endl;
	cout << "Atleta: " << Atleta << endl;
	for(unsigned int i = 0; i < Equipas.size();i++)
	{
		if(Equipa == Equipas[i].getNomeEquipa())
		{
			return Equipas[i].addAtleta(Atleta);
		}
	}
	return false;
}
bool Campeonato::RemoveAtletaEquipa(string equipa,string Atleta){

	for(unsigned int i = 0; i < Equipas.size();i++)
	{
		if(equipa == Equipas[i].getNomeEquipa())
		{
			return Equipas[i].removeAtleta(Atleta);
		}
	}
	return false;
}
void Campeonato::RemoveAtletaProva(string Atleta)
{
	for(unsigned int i = 0;i < Infraestruturas.size();i++)
	{
		Calendario *temp = Infraestruturas[i]->getCalendario();
		vector<evento *> Provas = temp->getEventos();
		for(unsigned int k = 0; k < Provas.size(); k++)
		{
			Provas[k]->removeLugar(Atleta);
		}
	}
}

void Campeonato::inscreverAtletaModalidade()
{
	if (Equipas.size() == 0)
	{
		cout << "Ainda nao existem equipas inscritas no campeonato. Crie uma equipa antes de inscrever atletas.";
		return;
	}

	if (numAtletas() == 0)
	{
		cout << "Ainda nao existem atletas inscritos no campeonato. Crie um atleta antes de o poder inscrever numa modalidade.";
		return;
	}

	bool existe = false;
	string nomeAtleta, nomeEquipa;

	do
	{
		existe = false;
		nomeEquipa = returnInput("a equipa");

		if (ExisteEquipa(nomeEquipa))
			existe = true;
		else
		{
			cout << "A equipa " << nomeEquipa << " nao existe. Escolha uma das seguintes: " << endl;
			sort (Equipas.begin(), Equipas.end(), ordenaAlfaEquipa);
			for(size_t i = 0; i < Equipas.size(); i++)
			{
				cout << i+1 << " - " << Equipas[i].getNomeEquipa() << endl;
			}
		}
	} while (!existe);

	size_t indice;

	for (indice = 0; indice < Equipas.size(); indice++)
		if (Equipas[indice].getNomeEquipa() == nomeEquipa)
			break;

	if (Equipas[indice].getAtletas().size() == 0)
	{
		cout << "Nao existem atletas nessa equipa. Adicione um atleta antes de o poder inscrever numa modalidade." << endl;
		return;
	}
	do
	{
		existe = false;
		nomeAtleta = returnInput("o atleta");

		if (Equipas[indice].existeAtleta(nomeAtleta))
			existe = true;
		else
		{
			cout << "O atleta " << nomeAtleta << " nao existe. Escolha um dos seguintes: " << endl;
			vector<Atleta> Atle = Equipas[indice].getAtletas();
			sort(Atle.begin(),Atle.end(),ordenaAlfaAtletas);
			for(unsigned int t = 0; t < Atle.size();t++)
			{
				cout << Atle[t].getNome() << endl;
			}
		}
	} while (!existe);

	for (size_t i = 0; i < Equipas[indice].getAtletas().size(); i++)
		if (Equipas[indice].getAtletas()[i].getNome() == nomeAtleta)
		{
			size_t modIndice;

			string nomeDes, nomeMod;
			nomeDes = returnInput("o desporto");
			bool existeDes = false;
			bool existeMod = false;

			for (size_t t = 0; t < Modalidades.size(); t++)
				if(Modalidades[t]->getDesporto() == nomeDes)
					existeDes = true;

			if(existeDes)
			{
				nomeMod = returnInput("a modalidade");

				for (size_t t = 0; t < Modalidades.size(); t++)
					if(Modalidades[t]->getDesporto() == nomeDes && Modalidades[t]->getTipo() == nomeMod)
					{
						existeMod = true;
						modIndice = t;
					}
				if(!existeMod)
				{
					cout << "A modalidade introduzida nao existe! " << endl;
					return;
				}
			}

			if (existeDes && existeMod)
			{
				Equipas[indice].adicionaModalidadeAtleta(i, Modalidades[modIndice]);
				cout << "O atleta " << Equipas[indice].getAtletas()[i].getNome() << " foi inscrito na modalidade especificada." << endl;
				return;
			}

		}
	cout << "O desporto introduzido nao existe!" << endl;
}

vector<string> Campeonato::listaDesporto()
{
	vector<string> Desporto;
	for(unsigned int i = 0; i < Modalidades.size();i++)
	{
		adicionaVetor(Desporto,Modalidades[i]->getDesporto());
	}
	return Desporto;
}
vector<string> Campeonato::AtletasDesporto(string Desporto)
{
	vector<string> Atletas;
	for(unsigned int i = 0; i < Modalidades.size();i++)
	{
		if(Modalidades[i]->getDesporto() == Desporto)
		{
			vector<evento* > Provas = Modalidades[i]->getProvas();
			cout << "Provas na Modadalidade : " << Provas.size() << endl;
			for(unsigned int  t = 0; t < Provas.size();t++)//Juntar todos os atletas
			{
				vector <string> Atle = Provas[t]->getNomeAtletas();

				for(unsigned int k = 0; k < Atle.size();k++)
				{
					adicionaVetor(Atletas,Atle[k]);
				}

			}
		}
	}
	return Atletas;
}

void Campeonato::RemoveModalidadeAtletas(string desporto,string modalidade)
{
	for(unsigned int i = 0; i < Equipas.size(); i++)
	{
		Equipas[i].removeModalidade(desporto,modalidade);
	}
}

void Campeonato::RemoveEventosInfra(string modalidade)
{
	vector<evento *> temp;
	for(unsigned int i = 0; i < Modalidades.size();i++)
	{
		if(Modalidades[i]->getTipo() == modalidade)
		{
			temp = Modalidades[i]->getProvas();
		}
	}
	for(unsigned int pra = 0; pra < temp.size(); pra++)
	{
		for(unsigned int i = 0; i < Infraestruturas.size();i++)
		{
			vector<evento* > Provas = Infraestruturas[i]->getCalendario()->getEventos();
			for(unsigned int k = 0; k < Provas.size(); k++)
			{
				if(Provas[k] == temp[pra])
				{
					cout << "Esta a fazer cenas";
					Infraestruturas[i]->getCalendario()->remove_evento(Provas[k]);
				}
			}
		}
	}

}

void Campeonato::gravaProvas()
{
	string filename = "Prova_" + nome;
	ofstream gravar;
	gravar.open(filename.c_str());
	for (unsigned int i = 0; i < Modalidades.size(); i++) {
		vector<evento *> provas = Modalidades[i]->getProvas();
		for (unsigned int j = 0; j < provas.size(); j++) {
			gravar << provas[j]->getNome() << '\n';
			gravar << provas[j]->getTipo() << '\n';
			gravar << Modalidades[i]->getDesporto() << '\n';
			gravar << Modalidades[i]->getTipo() << '\n';
			Data di = provas[j]->getInicial();// nao sei se da para fazer isto!
			Data df = provas[j]->getFinal();
			gravar << di.dia << "/" << di.mes << "/" << di.ano << '\n';
			gravar << di.horas << ":" << di.minutos << ":" << di.segundos << '\n';
			gravar << df.dia << "/" << df.mes << "/" << df.ano << '\n';
			gravar << df.horas << ":" << df.minutos << ":" << df.segundos << '\n';
			for (unsigned int k = 0; k < Infraestruturas.size(); k++) {
				vector<evento *> infraprovas =
						Infraestruturas[k]->getCalendario()->getEventos();
				for (unsigned int l = 0; l < infraprovas.size(); l++) {
					if (infraprovas[l] == provas[j]) {
						gravar << Infraestruturas[k]->getNome() << '\n';
						break;
					}
				}
			}
			if (provas[j]->getTipo() == "TEMPO") {

				Prova_Tempo * provaT = provas[j]->getProvaT();
				vector<Posicao_tempo *> pTvec = provaT->getLugares();
				for (unsigned int k = 0; k < pTvec.size(); k++) {
					gravar << pTvec[k]->getAtleta() << '\n';
					Data tempoA = pTvec[k]->getTempo();
					gravar << tempoA.horas << ":" << tempoA.minutos << ":" << tempoA.segundos << '\n';
				}

			}
			if (provas[j]->getTipo() == "PONTO") {

				Prova_Pontuacao * provaP = provas[j]->getProvaP();
				vector<Posicao_Pontos *> pTvec = provaP->getLugares();
				for (unsigned int k = 0; k < pTvec.size(); k++) {
					gravar << pTvec[k]->getAtleta() << '\n';
					gravar << pTvec[k]->getPontuacao() << '\n';
				}

			}
			gravar << '\n';
		}
	}

	gravar.close();
}
