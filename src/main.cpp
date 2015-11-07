#include <iostream>
#include "Calendario.h"
#include "Campeonato.h"

void menu();
void criarCampeonato();
void carregarCampeonato();
void sobre();

void menu()
{
	cout << "    Campeonatos Polidesportivos" << endl;
	cout << "1 - Criar um campeonato" << endl;
	cout << "2 - Carregar um campeonato" << endl;
	cout << "3 - Sobre o trabalho -- por fazer" << endl;
	cout << "4 - Sair " << endl;
	cout << "\nIntroduza a opcao pretendida: ";

	switch (selectMenu('1','4'))
	{
	case '1':
		criarCampeonato();
		break;
	case '2':
		carregarCampeonato();
		break;
	case '3':
		//sobre();
		break;
	case '4':
		exit(0);
		break;
	}
	system("pause");
}

void criarCampeonato()
{
	Campeonato novoCampeonato;

	novoCampeonato.menuCampeonato();
}

void carregarCampeonato()
{
	Campeonato loadCampeonato(selectFile());

	loadCampeonato.menuCampeonato();
}

int main()
{
	menu();
	return 0;
}
