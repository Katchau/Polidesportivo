#ifndef MODALIDADE_H
#define MODALIDADE_H

#include <string>
#include <vector>

#include "Desporto.h"

class Modalidade : public Desporto {
private:
	string tipo;
	string nomeT;
	vector<evento *> Provas;
public:

	/**
	 * @param nome nome do desporto
	 * @param tipo nome da modalidade
	 *
	 * Cria o objecto modalidade
	 */
	Modalidade (string nome, string tipo);

	/**
	 * @param Prova prova a adicionar
	 *
	 * Adiciona uma prova ao vetor de Provas
	 */
	bool adicionaProva (evento * Prova);

	/**
	 * @param Prova prova a remover
	 *
	 * Remove a prova do vetor de Provas.
	 */
	bool removeProva (evento * Prova);

	/**
	 * @param indice da prova
	 * @param nomeAtleta nome do atleta a qual se vai colocar o resultado da prova
	 * @param h horas do tempo que o atleta fez, caso seja uma prova de tempo
	 * @param m minutos do tempo que o atleta fez, caso seja uma prova de tempo
	 * @param s segundos do tempo que o atleta fez, caso seja uma prova de tempo
	 * @param score pontuacao do atleta, caso seja uma prova por pontuacao
	 *
	 * Adiciona um resultado a prova do atleta, sendo que este esta incluido num vetor do evento, onde se encontra
	 */
	void adicionaResultado(int indice, string nomeAtleta, int h, int m ,int s, int score);

	/**
	 * @param indice da prova
	 * @param nomeAtleta nome do atleta a qual se vai remover o resultado da prova
	 *
	 * Remove um resultado a prova do atleta, sendo que este esta incluido num vetor do evento, onde se encontra
	 */
	void removeResultado(int indice, string nomeAtleta);

	/*
	 * @return string que contem o nome do desporto e da modalidade
	 */
	string getNome();

	/*
	 * @param modalidade a comparar
	 *
	 * Compara duas modalidades
	 *
	 * @return true se o nome do desporto e da modalidade for igual
	 * @return false se o nome do desporto e da modalidade for diferente
	 */
	 bool operator == (Desporto * des) const;

	 /**
	  * @return nome da modalidade
	  */
	 string getTipo() const;

	 /**
	  * Retorna as provas existentes na modalidade
	  * @return vetor de provas da modalidade
	  */
	 vector<evento *> getProvas() const;

	 /**
	  * Retorna o nome dos Atletas inscritos na modalidade
	  * @return vetor de atletas inscritos na modalidade
	  */
	 vector<string> getNomeAtletas() const;
};


#endif
