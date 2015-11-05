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
	static int idN; // id actual
	string nameFile; // nome do ficheiro txt que vai guardar(depende consoante o idN)
	string nome;

	vector<Desporto *> desportosInscritos;
	vector<medalha> medalhas;
	vector<Atleta> atletasInscritos;

public:
	Equipa();
	Equipa(string filename);
	class EquipaNaoExistente
	{
	public:
		string nomeficheiro;
		EquipaNaoExistente(string nomeficheiro);
	};
	void addAthletesFromFile();
	bool addAtleta(string nome);
	bool removeAtleta(string nome);
	void atualizarID(); //falta dar um nome decente a isto
	void writetoFile(); //TODO falta a parte das medalhas
	string getNomeEquipa() const;
	vector<Atleta> getAtletas(); // e mais para testes
	bool operator == (const Equipa& eqi) const;
};
	bool ordenaAlfaEquipa(const Equipa A, const Equipa B);
#endif
