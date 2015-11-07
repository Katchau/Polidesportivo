#ifndef MODALIDADE_H
#define MODALIDADE_H

#include <string>
#include <vector>

#include "Desporto.h"
#include "Prova.h"

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
	 * Cria a modalidade "tipo", derivada do desporto "nome"
	 */
	Modalidade (string nome, string tipo); // TODO Melhorar Doxygen

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
	 * @param indice
	 * @param nomeAtleta
	 * @param h
	 * @param m
	 * @param s
	 * @param score
	 *
	 *
	 */
	void adicionaResultado(int indice, string nomeAtleta, int h, int m ,int s, int score); // TODO doxygen

	/**
	 * @param indice
	 * @param nomeAtleta
	 * @param h
	 * @param m
	 * @param s
	 * @param score
	 *
	 *
	 */
	void removeResultado(int indice, string nomeAtleta); // TODO doxygen

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

	 /*
	  * @return nome da modalidade
	  */
	 string getTipo() const;

	 /*
	  * @return vetor de provas da modalidade
	  */
	 vector<evento *> getProvas() const;

	 /*
	  * @return vetor de atletas inscritos na modalidade
	  */
	 vector<string> getNomeAtletas() const;
};


#endif
