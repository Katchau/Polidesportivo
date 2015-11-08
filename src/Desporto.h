#ifndef DESPORTO_H
#define DESPORTO_H

#include <string>
#include <vector>
#include <algorithm>
#include "calendario.h"

using namespace std;

class Desporto{
private:
	string nome;
public:
	/**
	 * Construtor de desporto
	 * @param nome nome do desporto
	 */
	Desporto(string nome);
	/**
	 * Destrutor da classe desporto
	 */
	virtual ~Desporto(){}

	virtual string getNome();
	/**
	 * Adiciona objecto do tipo evento se ele ainda nao existir na classe
	 * @param Prova a ser adicionada
	 * @return false se a prova nao foi adicionada
	 * @return true se a prova foi adicionada
	 */
	virtual bool adicionaProva (evento * Prova);
	/**
	 *Remove objecto do tipo evento da classe se ele existir
	 *@param Prova a ser removida
	 *@return true se adicionada
	 *@return false se o evento ja exitir
	 */
	virtual	bool removeProva (evento * Prova);
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
	virtual void adicionaResultado(int indice, string nomeAtleta, int h, int m ,int s, int score);
	/**
	 * @param indice da prova
	 * @param nomeAtleta nome do atleta a qual se vai remover o resultado da prova
	 *
	 * Remove um resultado a prova do atleta, sendo que este esta incluido num vetor do evento, onde se encontra
	 */
	virtual void removeResultado(int indice, string nomeAtleta);
	/**
	 * Permite comparar dois objectos da classe desporto
	 * @return true se  ambos os objectos tiverem o mesmo nome;
	 * @return false se ambos os objectos nao tiverem o mesmo nome;
	 */
	virtual bool operator == (const Desporto& des) const;
	/**
	 * Retorna o nome da  modalidade
	 *  @return string
	 */
	virtual string getTipo()const;
	/**
	 * Retorna o nome do desporto
	 *  @return string
	 */
	string getDesporto() const;
	/**
	 * Retorna as provas no desporto
	 * @return vector<evento *>
	 */
	virtual vector<evento *> getProvas() const;
};

class DesportoP{ // usar para comparaçao entre desportos, uma vez que sao todos do formato pointer
public:
	/**
	 * Desconstrutor de ~DesportoP
	 */
	virtual ~DesportoP(){}
	/**
	 * Apontador para desporto
	 */
	Desporto * poit;
	/**
	 * Permite comparar dois desportos
	 * @param des
	 * @return true se forem o mesmo desporto
	 * @return false se nao forem o mesmo desporto
	 */
	virtual bool operator == (const DesportoP * des) const;
};
/**
 * Permite comparar o nome dos desportos alfabeticamente
 * @param A
 * @param B
 * @return true se nome de A é menor (alfabeticamente) que o nome de B
 * @return false se nome de A é maior ou igual (alfabeticamente) ao nome de B
 */
bool ordenaAlfaDesporto(const Desporto *A,const Desporto *b);
/**
 * Permite comparar o nome das modalidades alfabeticamente
 * @param A
 * @param B
 * @return true se nome de A é menor (alfabeticamente) que o nome de B
 * @return false se nome de A é maior ou igual (alfabeticamente) ao nome de B
 */
bool ordenaAlfaModalidade(const Desporto *A,const Desporto *B);
#endif
