/*
 * bilhete.h
 *
 *  Created on: 19/12/2015
 *      Author: Madnar
 */

#ifndef SRC_BILHETE_H_
#define SRC_BILHETE_H_


#include <tr1/unordered_set>
#include "bilhete.h"
#include "calendario.h"

class Bilhete {

private:
	static int counter;
	int ID;
	vector<string> acesso;
	string email;
	string nome;
	string morada;

public:
	/**
	 * Construtor da classe bilhete
	 * @param acesso nome das provas a que o bilhete da acesso
	 * @param email  correio eletronico do detentor do bilhete
	 * @param nome  nome do detentor do bilhete
	 * @param morada
	 */
	Bilhete(vector<string> acesso, string email, string nome, string morada);
	/**
	 * Atualiza o detentor do bilhete
	 * @param email  correio eletronico do detentor do bilhete
	 * @param nome  nome do detentor do bilhete
	 * @param morada
	 */
	void NovoDono( string email, string nome, string morada);
	/**
	 * Adiciona um acesso a uma prova
	 * @param nome da  prova a adicionar
	 * @return true  se a prova for adicionada
	 * @return false se a prova nao for adicionada
	 */
	bool Adiciona_evento(string prova);
	/**
	 * Remove um acesso a uma prova
	 * @param nome do evento
	 * @param
	 * @param
	 */
	bool Remove_evento(string nome);

	/**
	 * Retorna a email do detentor
	 */
	string getEmail() const;
	/**
	 * @return vetor de provas
	 */
	vector<string> getProvas() const;
	/**
	 * @return nome do detentor
	 */
	string getNome() const;
	/**
	 * @return morada do detentor
	 */
	string getMorada() const;
	/**
	 * @retorna o ID do bilhete
	 */
	int getID()const;
};

struct hBilhete {
	int operator()(const Bilhete& b1) const{
		return  b1.getID();
	}
	bool operator()(const Bilhete& a1, const Bilhete& a2) const {
		return a1.getID() == a2.getID();
	}
};

typedef tr1::unordered_set<Bilhete,hBilhete,hBilhete>  hasBilhete;


class Bilheteira {


private:
	hasBilhete vendidos;
public:
	/**
	 * Construtor de bilheteira
	 */
	Bilheteira();
	/**
	 * Adiciona Bilhete aos bilhetes vendidos
	 * @return true se o bilhete   for adicionado com sucesso
	 * @return false se o bilhete ja existir nos vendidos
	 */
	bool addBilhete(Bilhete novo);
	/**
	 * Remove Bilhete da bilheteira
	 * @param Bilhete a ser removido;
	 * @return true se o bilhete existir
	 * @return false  se o bilhete nao existir
	 */
	bool removeBilhete(Bilhete velho);
	/**
	 * Troca o dono do bilhete  e se o novo dono possuir um bilhete adiciona as provas a esse
	 * @param bilhete a ser vendido
	 * @param nome do novo dono
	 * @param email do novo dono
	 * @param morada do novo dono
	 */
	void vendeBilhete(Bilhete venda,string novodono,string email, string morada);
	/**
	 * Procura o bilhete de um dono
	 * @param nome do dono
	 * @return Bilhete se possuir bilhete
	 * @throw NaoExisteDono se a pessoa nao possuir bilhete
	 */
	Bilhete BilheteDeDono(string nome);
	/**
	 * Retorna os bilhetes vendidos
	 */
	hasBilhete getVendidos() const;
	/*
	 * classe para tratamento de excepcoes
	 */
	class NaoExiteDono{};
};


#endif /* SRC_BILHETE_H_ */
