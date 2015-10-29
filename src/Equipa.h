#ifndef EQUIPA_H
#define EQUIPA_H

#include <string>
#include <sstream>

#include "Desporto.h"
#include "Atleta.h"

// falta header files
using namespace std;

class Equipa {
private:
	static int idN; // id actual
	string nameFile; // nome do ficheiro txt que vai guardar(depende consoante o idN)
	string name;

	vector<Desporto *> desportosInscritos;
	vector<medalha> medalhas;
	vector<Atleta> atletasInscritos;

public:
	Equipa(); //construtor para carregar equipas em formato txt. E necessario ser feito 1º este processo, caso hajam equipas em txt e as queiram aceder
	Equipa(string nome);
	class EquipaNaoExistente
	{
	public:
		string nomeficheiro;
		EquipaNaoExistente(string nomeficheiro);
	};
	void importTeamFile(ifstream &read);
	void addAtlhetesFromFile();
	bool addAtleta(string nome);
	bool removeAtleta(string nome);
	void funcaoPorCoiso(); //falta dar um nome decente a isto
	void writetoFile(); //TODO falta a parte das medalhas
	vector<Atleta> getAtletas(); // e mais para testes
};
#endif
