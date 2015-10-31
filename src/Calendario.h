#ifndef CALENDARIO_H
#define CALENDARIO_H

#include <vector>
#include <ctime>
#include <iterator>
using namespace std;


/* FALTA FUNCAO PRINT E TESTAR */
struct Data {
	unsigned int dia;
	unsigned int mes;
	unsigned int ano;
	unsigned int horas;
	unsigned int minutos;
	Data(int dia,int mes,int ano);
	Data(int dia,int mes,int ano,int horas,int minutos);
	Data();
	friend ostream& operator<<(ostream& os, const Data& dt);
};

class evento {
private:
	string nome;
	Data inicial;
	Data final;
public:
	evento(Data inicial,Data final);
	evento(string nome,Data inicial,Data final);
	string getNome() const;
	Data getInicial() const;
	Data getFinal() const;
};

class Calendario {
private:
	Data inicio;
	Data fim;
	vector<evento*> eventos;
public:
	Calendario(Data inicio,Data fim);
	void adiciona_evento(evento *alpha);
	void remove_evento(evento * alpha);
	void imprime() const;

};

class EventoExiste {
private:
	string nome;
public:
	EventoExiste(string nome);
};
class EventoNaoExiste{
private:
	string nome;
public:
	EventoNaoExiste(string nome);
};
class EventoSobreposto{
public:
	EventoSobreposto(){};
};
class EventoNaoAdicionado{
public:
	EventoNaoAdicionado(){};
};

/* DATA */
bool ValidaData(Data Marcacao, bool atual);
bool bissexto(int ano);
unsigned int diasMes(int ano, int mes);
bool operator< (const Data &inicio,const Data &fim);
bool operator == (const Data &esquerda, const Data &direita);
bool operator <= (const Data &inicio,const Data &fim);
/*EVENTOS*/

bool eventos_sobrepostos(const evento *alpha,const  evento *beta);

#endif
