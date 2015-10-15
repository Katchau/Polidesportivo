#ifndef CALENDARIO_H
#define CALENDARIO_H

struct Data {
	int dia;
	int mes;
	int ano;
	int horas;
	int minutos;
	int segundos;
};
class Calendario{

	Data inicio;
	Data fim;

public:
Calendario(Data inicio,Data fim);
bool adiciona_evento();
bool remove_evento();
};


#endif
