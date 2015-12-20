#ifndef EQUIPA_H
#define EQUIPA_H

#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

#include "Desporto.h"
#include "Atleta.h"
#include "Modalidade.h"

// falta header files
using namespace std;

class Equipa {
private:
	string nameFile; // nome do ficheiro txt que vai guardar(depende consoante o idN)
	string nome;

	vector<Desporto *> desportosInscritos;
	medalha medalhas;
	vector<Atleta> atletasInscritos;

public:
	/**
	 * Cria uma equipa, pedindo ao utilizador que introduza o nome
	 * Atualiza o nome do ficheiro onde vai ser guardada a equipa para nome.txt, sendo nome o nome da equipa
	 */
	Equipa();

	/**
	 * @param filename nome do ficheiro de equipa
	 *
	 * Cria uma equipa, lendo de um ficheiro a seua configuracao.
	 */
	Equipa(string filename);

	/**
	 * Le a configuracao da equipa a partir do ficheiro
	 */
	void addAthletesFromFile();

	/**
	 * @param nome nome do atleta a criar
	 *
	 * Cria um atleta com o nome pretendido e adiciona-o ao vetor atletasInscritos.
	 *
	 * @return true se for possivel adicionar o atleta
	 * @return false se ja existir esse atleta e nao for possivel adiciona-lo
	 */
	bool addAtleta(string nome);

	/**
	 * @param nome nome do atleta a criar
	 *
	 * Remove o atleta com o nome pretendido do vetor atletasInscritos.
	 *
	 * @return true se for possivel remover o atleta
	 * @return false se nao existir esse atleta e nao for possivel remove-lo
	 */
	bool removeAtleta(string nome);

	/**
	 * @param nome nome do atleta a procura
	 *
	 * Procura se um atleta existe na equipa
	 *
	 * @return true se o atleta existir
	 * @return false se o atleta nao existir
	 */
	bool existeAtleta(string nome);

	/**
	 * Grava num ficheiro .txt com o nome igual ao nome da equipa
	 * as informacoes necessarias para carregar a equipa quando voltar a abrir o programa
	 */
	void writetoFile();

	/**
	 * @return nome da equipa
	 */
	string getNomeEquipa() const;

	/**
	 * @return vetor de atletas da equipa
	 */
	vector<Atleta> getAtletas() const;

	/**
	 * @param equipa a comparar
	 *
	 * Compara duas equipas
	 *
	 * @return true se o nome for igual
	 * @return false se o nome for diferente
	 */
	bool operator == (const Equipa& eqi) const;

	/**
	 * @param indice indice do atleta no vetor de atletas
	 * @param d modalidade a adicionar
	 *
	 * Adiciona a modalidade especificada ao atleta especificado
	 *
	 * @return true se for possivel adicionar
	 * @return false se a modalidade ja existir
	 */
	bool adicionaModalidadeAtleta(int indice, Desporto* d);

	/**
	 * @param d modalidade a adicionar
	 *
	 * Adiciona a modalidade especificada
	 *
	 * @return true se for possivel adicionar
	 * @return false se a modalidade ja existir
	 */
	bool adicionaModalidade(Desporto* d);

	/**
	 * @param desporto nome do desporto
	 * @param modalidade nome da modalidade
	 *
	 * Remove a modalidade especificada
	 */
	void removeModalidade(string desporto,string modalidade);
	/**
	 * @param desporto para verificar a pontuacao
	 *
	 * soma a pontuacao de todos os atletas da equipa numa modalidade
	 *
	 * @return total das pontuacoes
	 *
	 */
	int pontuacaoGeral(Desporto * mod);
	/**
	 * @param desporto para verificar a pontuacao
	 *
	 * verifica o melhor tempo de todos os atletas de uma modalidade
	 *
	 * @return melhor tempo
	 *
	 */
	Data melhorTempo(Desporto * mod);
	/**
	 * @param prova realizada para poder verificar resultados de atletas
	 *
	 * verifica todos os resultados dos atletas da equipa, e obtem as medalhas totais relativamente á prestacao os atletas
	 *
	 */
	void getMedalhas(evento * prov);
	/**
	 * coloca as medalhas da equipa a valores iniciais(ou seja, tudo a 0)
	 */
	void removeMedalhas();
	/**
	 * permite vizualizar as medalhas que a equipa possui ao utilizador
	 */
	void printMedalhas();
	/**
	 * retorna as medalhas da equipa
	 * @return medalhas da equipa
	 */
	medalha getMedalhasEquipa();
	/**
	 * @param equipa a comparar
	 *
	 *	Compara e devolve resultado equivalente a uma equipa a comparar
	 *
	 * @return true se a equipa tiver menor numero de equipas
	 * @return false se a equipa tiver maior numero de equipas
	 */
	bool operator < (const Equipa eq) const;
	/**
	 * @param equipa a comparar
	 *
	 *	Compara e devolve resultado equivalente a uma equipa a comparar
	 *
	 * @return true se a equipa tiver maior numero de equipas
	 * @return false se a equipa tiver menor numero de equipas
	 */
	bool operator > (const Equipa eq) const;


	class EquipaNaoExistente
	{
	public:
		string nomeficheiro;
		EquipaNaoExistente(string nomeficheiro);
	};
};
bool ordenaAlfaEquipa(const Equipa A, const Equipa B);
#endif
