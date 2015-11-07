#ifndef ATLETA_H
#define ATLETA_H

#include <string>
#include <vector>
#include <iostream>
#include "Desporto.h"

class medalha
{
	string desporto;
	string tipo;
};

class Atleta {
private:
	string nome;
	vector<Desporto *> desportosInscrito;
	vector<int> classificacoes;
public:
	/*
	 * Cria um atleta, pedindo ao utilizador que introduza o nome
	 */
	Atleta();

	/*
	 * @param nome nome do atleta a criar
	 *
	 * Cria um atleta com o nome recebido pelo parametro nome.
	 */
	Atleta(string nome);

	/*
	 * @param d modalidade a adicionar
	 *
	 * Adiciona a modalidade ao vetor desportosInscrito
	 * Lanca excecao se ja existir essa modalidade
	 *
	 * @return true se for possivel adicionar o desporto
	 */
	bool adicionaModalidade(Desporto *d);

	/*
	 * @param d modalidade
	 *
	 * Remove a modalidade do vetor desportosInscrito
	 *
	 * @return true se for possivel remover a modalidade
	 * @return false se nao existir a modalidade d
	 *
	 */
	bool removeModalidade(string desporto,string modalidade);

	/*
	 * @return copia do vetor desportosInscritos que contem as modalidades em que o atleta esta inscrito
	 */
	vector<Desporto *> getDesportosInsc();

	/*
	 * Imprime no ecra todos as modalidades em que o atleta esta inscrito
	 */
	void showDesportos();

	/*
	 * @return nome do atleta
	 */
	string getNome() const;

	void classificacaoFinal(Desporto * des); // TODO nao esta feito

	/*
	 * @param atleta a comparar
	 *
	 * Compara dois atletas
	 *
	 * @return true se o nome for igual
	 * @return false se o nome for diferente
	 */
	bool operator == (const Atleta& atl) const;

	class DesportoInexistente{};

	class DesportoRepetido{};

};

bool ordenaAlfaAtletas(const Atleta A, const Atleta B);
#endif
