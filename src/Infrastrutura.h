#ifndef INFRAESTRUTURA_H
#define INFRAESTRUTURA_H

#include <string>
#include "Calendario.h"
#include <iostream>
#include <algorithm>
using namespace std;


class Infraestrutura {
private:
	string Nome;
	Calendario* Horario;

public:
	//Criar
	/**
	 * Controi uma Infraestrutura, pedindo ao utilizador que introduza o nome
	 */
	Infraestrutura();
	/**
	 * Constroi uma Infraestrutura sem horario
	 * @param Nome Nome da infraestrutura
	 */
	Infraestrutura(string Nome);
	/**
	 * Constroi uma Infraestrutura
	 * @param Nome Nome da infraestrutura
	 * @param Horario apontador para um objecto da classe calendario
	 */
	Infraestrutura(string Nome, Calendario * Horario);
	//Gerir
	/**
	 * Adiciona um evento ao horario
	 * imprime erro  "Evento Sobreposto" se houver um evento no mesmo intervalo de tempo
	 * imprime  erro  "O Evento já existe" se o evento ja existir no horario
	 * @param A apontador do evento a ser adicionado
	 */
	void adicionaEvento(evento* A );
	/**
	 * Remove um evento do horario
	 * imprime erro "O Evento nao existe!" se o evento nao fizer parte do horario
	 * @param B apontador do evento a ser removido
	 */
	void removeEvento(evento* B);
	/**
	 *Altera o apontador do horario
	 *@param Novo apontador para o novo horario
	 */
	void setCalendario( Calendario * Novo);
	//Ler
	/**
	 * Retorna o apontador para o calendario
	 */
	Calendario*  getCalendario() const;
	/**
	 * Retorna o nome da infraestrutura
	 */
	string getNome()const;
	/**
	 * Retorna o numero de eventos no calendario
	 */
	int Neventos() const;

	bool operator== (const Infraestrutura & A);

	void imprimeCalendario();
};
bool ordenaAlfaInfra(const Infraestrutura *A,const Infraestrutura *b);
#endif
