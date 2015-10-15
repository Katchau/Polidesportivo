#include "Calendario.h"

using namespace std;

bool bissexto(int ano)
{
	if (ano % 400 == 0 || (ano % 4 == 0 && ano % 100 != 0))
		return true;
	return false;
}
unsigned int diasMes(int ano, int mes)
{
	if ((bissexto(ano)) && mes == 2)
		return 29;
	else if (!(bissexto(ano)) && mes == 2)
		return  28;
	else if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
		return 31;
	return 30;
}

bool ValidaData(Data Marcacao, bool atual)
{
	if (Marcacao.mes >12 || Marcacao.dia > 0)
		return false;
	if (Marcacao.dia > diasMes(Marcacao.ano,Marcacao.mes))
		return false;
	if (Marcacao.horas > 23)
		return false;
	if (Marcacao.minutos > 60)
		return false;
	if (atual) /* se a data é de um evento futuro*/
	{
		time_t Tempo_Atual = time(NULL);
		struct tm *tempo_info= localtime(&Tempo_Atual);
		unsigned int min = tempo_info->tm_min;
		unsigned int horas = tempo_info->tm_hour;
		unsigned int dia = tempo_info->tm_mday;
		unsigned int mes = tempo_info->tm_mon;/* varia de 0 a 11*/
		unsigned int ano = tempo_info -> tm_year + 1000; /* ano atual*/
		if( Marcacao.ano < ano )
			return false;
		if(!(Marcacao.ano < ano) && Marcacao.mes < mes )
			return false;
		if (Marcacao.mes == mes && Marcacao.dia < dia)
			return false;
        if (Marcacao.horas < horas ||Marcacao.minutos < min )
        	return false;
	}
	return true;
}
Calendario::Calendario(Data inicio,Data fim){



}
bool Calendario::adiciona_evento(evento * alpha)
{

}
bool Calendario::remove_evento(evento *alpha)
{

}
void print()
{

}


