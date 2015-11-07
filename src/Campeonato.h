#ifndef CAMPEONATO_H
#define CAMPEONATO_H
#include <iostream>
#include <algorithm>
#include "Modalidade.h"
#include "Equipa.h"
#include "Infrastrutura.h"

#include <sstream>
using namespace std;

bool checkExistence(string filename);
string selectFile();
int selectMenu(char menor, char maior);

class Campeonato {
private:
	string nome;
	vector<Infraestrutura *> Infraestruturas;
	vector<Equipa> Equipas;
	vector<Desporto*> Modalidades;
public:
	// Criar

	/**
	 *  Constroi um campeonato a partir de um ficheiro
	 *  criado segundo o formato do programa.
	 *
	 * @param filename nome do ficheiro do campeonato (incluindo extensao)
	 */
	Campeonato(const string &filename);

	/**
	 *  Constroi um campeonato a partir do proprio programa
	 *  pedindo ao utilizador o nome
	 */
	Campeonato();

	/**
	 *  Cria uma nova equipa a partir do proprio programa
	 *  chamando o construtor adequado e adiciona-a ao vetor
	 *  de equipas
	 */
	void criaEquipa();

	// Gerir
	/**
	 * Adiciona Equipa ao campeonato
	 * @param Equipa * A
	 */
	void adicionaEquipa(Equipa  A);
	/**
	 *  Faz display de um menu que permite visualizar e alterar
	 *  os atributos do campeonato
	 */
	void menuCampeonato();

	/**
	 *  Faz display de um menu que permite escolher entre visualizar ou alterar
	 *  as equipas do campeonato
	 */
	void menuEquipas();

	/**
	 * Faz display de todas as opçoes de ordenacao das equipas presentes no campeonato
	 */
	void listaEquipas();
	/**
	 * Permite adicionar uma equipa
	 */
	void adicionarEquipa();
	/**
	 * Permite remover uma equipa
	 */
	void removerEquipa();
	/**
	 * Faz display de todas as queipas presentes no campeonato por ordem alfabetica
	 */
	void EquipasOrdemAlfabetica();
	/**
	 * Faz display de um menu que permite entre escolher entre visualizar ou alterar
	 * as infraestruturas do campeonato
	 */
	void menuInfraestruturas();
	/**
	 * Faz display das infraestruturas
	 */
	void listaInfraestruturas();
	/**
	 * Adiciona uma infraestrutura ao vector de infraestruturas
	 *
	 */
	void adicionarInfraestrutura();
	/**
	 * Permite apagar uma infraestrutura pertencente á lista
	 */
	void removerInfraestrutura();

	/**
	 * faz o display das infrastruturas por ordem alfabetica;
	 */
	void InfraestruturasOrdemAlfabetica();
	void menuModalidades();
	/**
	 * Faz display da lista de modalidades alfabeticamente
	 */
	void OrdemAlfabeticaModalidades();
	/**
	 * Faz o display das listas ordenadas possiveis para modalidades
	 */
	void listaModalidades();
	/**
	 * Permite adicionar modalidade á lista de modalidades
	 */
	void AdicionarModalidade();
	/**
	 * @return nome do campeonato
	 */
	/**
	 * Permite remover uma modalidade á lista de modalidades
	 */
	void RemoverModalidade();
	/**
	 * Faz o display do menu das provas
	 */
	int menuEscolhaInfra();
	/**
	 * Faz display de um menu que permite entre escolher entre visualizar ou alterar
	 * o calendario do campeonato
	 */
	void menuCalendario();

	void totalCalendario();

	void calendarioInfra();

	void listaCalendarios();

	void adicionarEventos();

	void removerEventos();

	void menuProvas();

	void verResultados();// já estao ordenados lel

	void adicionarProvas();

	void removerProvas();

	void removerClassProva();

	void menuAtletas();

	void adicionaAtleta();

	void removeAtleta();

	void listaAtletas();

	void AtletasPorEquipa();

	void AtletasPorModalidade();

	void AtletasPorDesporto();

	vector <evento*> ProvasOrganiza(unsigned int seleciona); // 0 Provas Realizadas  else Provas Por Realizar

	bool ExisteEquipa(string nome) const;
	bool ExisteAtleta(string nome) const;
	bool AdicionaAtletaEquipa(string Atleta,string Equipa);
	bool RemoveAtletaEquipa(string equipa,string Atleta);
	void RemoveAtletaProva(string Atleta);
	vector<string>listaDesporto();
	vector<string>AtletasDesporto(string Desporto);
	void RemoveModalidadeAtletas(string desporto,string modalidade);
	void RemoveEventosInfra(string modalidade); //apaga os eventos da modalidades;

	/**
	 * @return nome do campeonato
	 */
	// Ler
	string getNome() const;

	/**
	 * @return vetor de infraestruturas
	 */
	vector<Infraestrutura *> getInfraestruturas();

	/**
	 * @return vetor de equipas
	 */
	vector<Equipa> getEquipas();

	/**
	 * @return vetor de modalidades
	 */
	vector<Desporto*> getModalidades();

	// Gravar

	/**
	 * Grava o campeonato num ficheiro .txt com nome igual
	 * ao nome do campeonato
	 */
	void gravarCampeonato();

	// Excecoes
	class EquipaJaExistente
	{
	private:
		string nome;
	public:
		EquipaJaExistente(string nome) {this->nome = nome;}
		string getNome() {return nome;}
	};

};

#endif



