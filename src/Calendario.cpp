#include "Calendario.h"

using namespace std;


Calendario::Calendario(Data inicio,Data fim){
this->inicio = inicio;
this->fim = fim;

}
bool Calendario::adiciona_evento(evento * alpha)
{
  for(unsigned int i = 0; i < eventos.size(); i++)
  {
     if(eventos_sobrepostos(eventos[i],alpha))
    	 return false;
  }
  eventos.push_back(alpha);
  return true;
}
bool Calendario::remove_evento(evento *alpha)
{
   for(unsigned int i = 0; i < eventos.size(); i++)
   {
	   if(eventos[i] == alpha){
		   eventos.erase(eventos.begin()+i);
		   return true;
	   }
   }
   return false;
}
void Calendario::print()
{

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
	if (atual) /* se a data � de um evento futuro*/
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
bool operator< (const Data &inicio,const Data &fim){
	if(inicio.ano <  fim.ano )
		return true;
	if(inicio.mes < fim.ano)
		return true;
	if(inicio.dia < fim.dia)
		return true;
	return false;
}
bool eventos_sobrepostos(evento *alpha, evento *beta){

	if(alpha->inicial < beta->final && beta->inicial < alpha->final)
		return false;
	if(beta->inicial <  alpha->final && alpha->inicial < beta->final)
		return false;
	if(beta->inicial < alpha->inicial && alpha->final < beta->final)
		return false;
	if(alpha->inicial < beta->inicial && beta->final < alpha->inicial)
		return false;

	return true;
}
