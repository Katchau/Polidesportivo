#include "Calendario.h"
#include <iostream>
using namespace std;

bool ValidaData(Data Marcacao, bool atual)
{
	if (Marcacao.mes >12 || Marcacao.dia < 0)
		return false;
	if (Marcacao.dia > diasMes(Marcacao.ano,Marcacao.mes))
		return false;
	if (Marcacao.horas > 23)
		return false;
	if (Marcacao.minutos > 59)
		return false;
	if(Marcacao.segundos > 59)
	if (atual) /* se a data é de um evento futuro*/
	{
		time_t Tempo_Atual = time(NULL);
		struct tm *tempo_info= localtime(&Tempo_Atual);
		unsigned int sec = tempo_info->tm_sec;
		unsigned int min = tempo_info->tm_min;
		unsigned int horas = tempo_info->tm_hour;
		unsigned int dia = tempo_info->tm_mday;
		unsigned int mes = tempo_info->tm_mon;/* varia de 0 a 11*/
		unsigned int ano = tempo_info -> tm_year + 1000; /* ano atual*/
		if( Marcacao.ano < ano )
			return false;
		if( Marcacao.ano == ano && Marcacao.mes < mes )
			return false;
		if (Marcacao.mes == mes && Marcacao.dia < dia)
			return false;
		if(Marcacao.dia == dia && Marcacao.horas < horas)
			return false;
		if(Marcacao.horas == horas && Marcacao.minutos < min)
		return false;
		if(Marcacao.minutos == min && Marcacao.segundos < sec)
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
	if (bissexto(ano) && mes == 2)
		return 29;
	else if (!bissexto(ano) && mes == 2)
		return  28;
	else if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
		return 31;
	return 30;
}


//Calendario
Calendario::Calendario(Data inicio,Data fim){
	this->inicio = inicio;
	this->fim = fim;

}
void Calendario::adiciona_evento(evento * alpha)
{
	if((inicio <= alpha-> getInicial() && alpha-> getInicial() <= fim)||
			(inicio <= alpha->getFinal() && alpha->getFinal() <= fim)||
			(inicio <= alpha->getFinal() && alpha->getFinal() <= fim)){
		for(unsigned int i = 0; i < eventos.size(); i++)
		{
			if(eventos_sobrepostos(eventos[i],alpha) ){

				throw EventoSobreposto();}
			if(alpha == eventos[i])
			{

				throw EventoExiste(alpha->getNome());
			}
		}
		eventos.push_back(alpha);
	}


}
void Calendario::remove_evento(evento *alpha)
{
	for(unsigned int i = 0; i < eventos.size(); i++)
	{
		if(eventos[i] == alpha){
			eventos.erase(eventos.begin()+i);
			return;
		}
	}
	throw EventoNaoExiste(alpha->getNome());
}
void Calendario::imprime() const
{
	for(unsigned int i = 0;i < eventos.size();i++){
		cout << eventos[i]->getNome() << " " <<eventos[i]->getInicial() << " "<<eventos[i]->getFinal()<< endl;
	}
}
void Calendario::setInicio(Data inicio){
	this->inicio = inicio;
}
void Calendario::setFim(Data fim){
	this->fim=fim;
}
Data Calendario::getInicio() const{
	return inicio;
}
Data Calendario::getFim() const{
	return fim;
}
vector<evento *> Calendario::getEventos() const{
	return eventos;
}


int Calendario::Neventos() const{
	return eventos.size();
}




EventoNaoExiste::EventoNaoExiste(string nome){
 this->nome = nome;
}
EventoExiste::EventoExiste(string nome){
	this->nome = nome;
}

//data
bool operator< (const Data &inicio,const Data &fim){


	if(inicio.ano <  fim.ano )
		return true;
	if(inicio.mes < fim.mes && inicio.ano == fim.ano )
		return true;
	if(inicio.dia < fim.dia && inicio.mes == fim.mes &&inicio.ano == fim.ano)
		return true;
	if(inicio.minutos < fim.minutos && inicio.dia == fim.dia&& inicio.mes == fim.mes &&inicio.ano == fim.ano)
		return true;
	if(inicio.segundos < fim.segundos && inicio.minutos == fim.minutos && inicio.dia == fim.dia&& inicio.mes == fim.mes &&inicio.ano == fim.ano)
	return true;
	return false;

}
bool operator <= (const Data &inicio,const Data &fim){
	if(inicio.ano <=  fim.ano )
			return true;
		if(inicio.mes <= fim.mes && inicio.ano == fim.ano )
			return true;
		if(inicio.dia <= fim.dia && inicio.mes == fim.mes &&inicio.ano == fim.ano)
			return true;
		if(inicio.minutos <= fim.minutos && inicio.dia == fim.dia&& inicio.mes == fim.mes &&inicio.ano == fim.ano)
			return true;
		if(inicio.segundos <= fim.segundos && inicio.minutos == fim.minutos && inicio.dia == fim.dia&& inicio.mes == fim.mes &&inicio.ano == fim.ano)
		return true;
		return false;
}
bool operator == (const Data &esquerda, const Data &direita){
	if(esquerda.ano != direita.ano) return  false;
	if(esquerda.dia != direita.dia) return false;
	if(esquerda.mes != direita.mes) return false;
	if(esquerda.horas != direita.horas) return false;
	if(esquerda.minutos != direita.minutos) return false;
	if(esquerda.segundos != direita.segundos) return false;
	return true;
}

ostream& operator<<(ostream& os, const Data& dt)
{
    os << dt.dia << '/' << dt.mes << '/' << dt.ano;
    os << dt.horas << ':'<<dt.minutos;
    return os;
}


Data::Data(){
	dia =0;
	mes= 0;
	ano = 0;
	horas= 0;
	minutos= 0;
	segundos = 0;
};

Data::Data(int dia,int mes,int ano){
	this->dia = dia;
	this->mes = mes;
	this->ano= ano;
	horas = 0;
	minutos = 0;
	segundos = 0;
}
Data::Data(unsigned int dia,unsigned int mes,unsigned int ano,unsigned int horas,unsigned int minutos,unsigned int segundos){
	this->dia = dia;
	this->mes= mes;
	this-> ano = ano;
	this->horas = horas;
	this->minutos = minutos;
	this->segundos = segundos;
}
//evento
evento::evento(Data inicial,Data final){
	this->inicial = inicial;
	this->final = final;
	nome = "sem nome";
	tipo = "";
}
evento::evento(string nome,Data inicial,Data final,string tipo){
	this->inicial=inicial;
	this->final = final;
	this->nome = nome;
	this->tipo = tipo;

}
bool eventos_sobrepostos(const evento *alpha,const  evento *beta){

	if(alpha->getInicial()< beta-> getFinal() && beta-> getFinal() < alpha -> getFinal())
		return true;
	if(alpha->getInicial()< beta-> getInicial() && beta-> getInicial() < alpha -> getFinal())
		return true;
	if(beta->getInicial()  < alpha-> getInicial()&& alpha-> getInicial() < beta->getFinal())
		return true;
	if(beta->getInicial()  < alpha-> getFinal()&& alpha-> getFinal() < beta->getFinal())
		return true;
	if(alpha->getInicial() == beta-> getFinal()) return true;
	if(alpha->getInicial() == beta->getInicial()) return true;
	if(alpha->getInicial()== beta-> getFinal()) return true;





	return false;
}

string evento::getNome() const{
	return nome;
}
Data evento::getInicial() const{
	return inicial;
}
Data evento::getFinal() const{
	return final;
}
