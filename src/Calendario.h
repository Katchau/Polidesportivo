#ifndef CALENDARIO_H
#define CALENDARIO_H

#include <vector>
#include <ctime>
using namespace std;

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


#endif
