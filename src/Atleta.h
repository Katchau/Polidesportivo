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
    bool adicionaDesporto(Desporto *d);

    bool removeDesporto(Desporto * d);
    bool removeModalidade(string desporto,string modalidade);
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
