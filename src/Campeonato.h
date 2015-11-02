#ifndef CAMPEONATO_H
#define CAMPEONATO_H

#include "Modalidade.h"
#include "Equipa.h"
#include "Infrastrutura.h"

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
	 *  Faz display de um menu que permite visualizar e alterar
	 *  os atributos do campeonato
	 */
	void menuCampeonato();

	/**
	 *  Faz display de um menu que permite escolher entre visualizar ou alterar
	 *  as equipas do campeonato
	 */
	void menuEquipas();

	// Ler
	/**
	 * @return nome do campeonato
	 */
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



