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
	vector<evento *> acesso;
	string email;
	string nome;
	string morada;

public:
	Bilhete(vector<evento*> acesso, string email, string nome, string morada);
	void NovoDono( string email, string nome, string morada);
	bool Adiciona_evento(evento *prova);
	bool Remove_evento(string nome);

	vector<evento*> getProvas() const;
	string getNome() const;
	string getMorada() const;
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
	Bilheteira();
	bool addBilhete(Bilhete novo);
	bool removeBilhete(Bilhete velho);
	void vendeBilhete(Bilhete venda,string novodono,string email, string morada);
	Bilhete BilheteDeDono(string nome);
	class NaoExiteDono{};
};


#endif /* SRC_BILHETE_H_ */
