#include <iostream>
#include "Calendario.h"
#include "Campeonato.h"
/**
 * Menu principal do programa
 */
void menu();
/**
 * Permite criar um campeonato de raiz onde as suas caracteristicas serao introduzidas pelo utilizador
 */
void criarCampeonato();
/**
 * Permite carregar um campeonato previamente criado
 */
void carregarCampeonato();
/**
 * Funcao com informacoes sobre o programa
 */
void sobre();

void menu()
{	while(1)
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
		sobre();
		break;
	case '4':
		exit(0);
		break;
	}

}
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
void sobre()
{
	cout << "Campeonatos Polidesportivos \n \n"
	<<"O projeto e sobre a gestao de campeonatos polidesportivos, onde \n"
	<<"e possivel gerir atletas, desportos,modalidades,provas e infraestruturas.\n"
	<<"Foi desenvolvido para a cadeira de Algoritmos e Estruturas de Dados por \n"
	<<"alunos do MIEIC."
	<<"\n"
	<<"\n"
	<<"Diogo Campos \n"
	<<"Jonas Loureiro \n"
    <<"Pedro Soares \n";

}

int main()
{
	menu();
	return 0;
}
