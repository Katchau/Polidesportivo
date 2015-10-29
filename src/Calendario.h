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
};

struct evento {
	Data inicial;
	Data final;
	evento(Data inicial,Data final);
};

class Calendario {
private:
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
bool operator == (const Data &esquerda, const Data &direita);
bool operator <= (const Data &inicio,const Data &fim);
/*EVENTOS*/

bool eventos_sobrepostos(const evento *alpha,const  evento *beta);

#endif
