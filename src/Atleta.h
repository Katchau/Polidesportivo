#ifndef ATLETA_H
#define ATLETA_H

#include  <string>
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
    vector<Desporto *> desportosInscrito; // pois pois xD
    vector<int> classificacoes;
public:
    Atleta();
    Atleta(string nome);
    bool adicionaDesporto(Desporto *d);
    bool removeDesporto(Desporto * d);

    class DesportoInexistente
    {};

    class DesportoRepetido{};

    vector<Desporto *> getDesportosInsc();
    void showDesportos();
    string getNome() const;
    void classificacaoFinal(Desporto * des); //not yeti ready
    bool operator == (const Atleta& atl) const;
};
bool ordenaAlfaAtletas(const Atleta A, const Atleta B);
#endif
