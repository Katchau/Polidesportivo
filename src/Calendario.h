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

};

struct evento {
	Data inicial;
	Data final;
};
class Calendario{

	Data inicio;
	Data fim;
	vector<evento*> eventos;
public:
Calendario(Data inicio,Data fim);
bool adiciona_evento(evento *alpha);
bool remove_evento(evento * alpha);
void print();

};
/* DATA */
bool ValidaData(Data Marcacao, bool atual);
bool bissexto(int ano);
unsigned int diasMes(int ano, int mes);
bool operator< (const Data &inicio,const Data &fim);
/*Eventos*/
bool eventos_sobrepostos(evento *alpha, evento *beta);

#endif
