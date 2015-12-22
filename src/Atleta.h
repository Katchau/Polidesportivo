#ifndef ATLETA_H
#define ATLETA_H

#include <string>
#include <vector>
#include <iostream>
#include "Desporto.h"

class medalha
{
public:
	int ouro,prata,bronze;
	/**
	 * @param medalha a comparar
	 *
	 *	Compara e devolve um resultado, dependendo do numero de medalhas e do tipo
	 *
	 * @return true se a medalha tiver menor numero de de ouro for menor, caso seja igual compara o numero de prata,repetindo-se o procedimento para as de bronze
	 * @return false se a medalha a comparar tiver maior nº de ouro, ou tiver o msm nº de medalhas em to do o caso
	 */
	bool operator < (const medalha md) const;
	/**
	 * @param medalha a comparar
	 *
	 *	Compara e devolve um resultado dependendo do numero de medalhas
	 *
	 * @return true se tiverem quantidades iguais
	 * @return false se a quantidade for diferente
	 */
	bool operator == (const medalha md) const;
};

class Atleta {
private:
	string nome;
	vector<Desporto *> desportosInscrito;
	vector<int> classificacoes;
public:
	/**
	 * Cria um atleta, pedindo ao utilizador que introduza o nome
	 */
	Atleta();

	/**
	 * @param nome nome do atleta a criar
	 *
	 * Cria um atleta com o nome recebido pelo parametro nome.
	 */
	Atleta(string nome);

	/**
	 * @param d modalidade a adicionar
	 *
	 * Adiciona a modalidade ao vetor desportosInscrito
	 * Lanca excecao se ja existir essa modalidade
	 *
	 * @return true se for possivel adicionar o desporto
	 *
	 */
	bool adicionaModalidade(Desporto *d);

	/**
	 * @param  modalidade Nome da Modalidade
	 * @param desporto  Nome do Desporto
	 *
	 * Remove a modalidade do vetor desportosInscrito
	 *
	 * @return true se se remover a modalidade
	 * @return false se nao existir a modalidade
	 *
	 */
	bool removeModalidade(string desporto,string modalidade);

	/**
	 * @return copia do vetor desportosInscritos que contem as modalidades em que o atleta esta inscrito
	 */
	vector<Desporto *> getDesportosInsc();

	/**
	 * Imprime no ecra todos as modalidades em que o atleta esta inscrito
	 */
	void showDesportos();

	/**
	 * @return nome do atleta
	 */
	string getNome() const;
	/**
	 * @param prova realizada
	 *
	 * Calcula a posicao que o atleta ficou numa certa prova. Retorna 0 caso nao tenha participado
	 *
	 * @return valor da posicao final do atletan uma prova
	 */
	int classificacaoFinal(evento * prova);

	/**
	 * @param atleta a comparar
	 *
	 * Compara dois atletas
	 *
	 * @return true se o nome for igual
	 * @return false se o nome for diferente
	 */
	bool operator == (const Atleta& atl) const;
	/**
	 *  Classe para o tratamento de excessoes
	 */
	class DesportoInexistente{};

	/**
	 * Classe para o tratamento de excessoes
	 */
	class DesportoRepetido{};

};

/**
 * Permite comparar dois atletas alfabeticamente
 * @return true se nome do atleta A  e menor que o nome do atleta B
 */
bool ordenaAlfaAtletas(const Atleta A, const Atleta B);
#endif
