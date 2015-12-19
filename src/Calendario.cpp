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
			unsigned int mes = tempo_info->tm_mon + 1;/* varia de 0 a 11*/
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
Calendario::Calendario(){
	inicio = Data();
	fim = Data();

}

bool evento::operator == (const evento * ev) const
								{
	if (inicial == ev->getInicial() && final == ev->getFinal())
	{
		return true;
	}
	else return false;
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
		if(eventos[i]->getNome() == alpha->getNome()){
			eventos.erase(eventos.begin()+i);
			return;
		}
	}
	throw EventoNaoExiste(alpha->getNome());
}

void Calendario::imprime() const
{
	for(unsigned int i = 0;i < eventos.size();i++){
		cout << "Nome da prova: " << eventos[i]->getNome() << endl;
		cout << "Data inicial: " <<  eventos[i]->getInicial() << endl;
		cout << "Data final: " << eventos[i]->getFinal() << endl;
		cout << endl;
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
	if(inicio.ano <  fim.ano)
		return true;
	if(inicio.mes < fim.mes && inicio.ano == fim.ano )
		return true;
	if(inicio.dia < fim.dia && inicio.mes == fim.mes &&inicio.ano == fim.ano)
		return true;
	if(inicio.minutos < fim.minutos && inicio.dia == fim.dia&& inicio.mes == fim.mes &&inicio.ano == fim.ano)
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
	os << " " << dt.horas << ':'<<dt.minutos << ':' << dt.segundos;
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

evento::evento(string nome,Data inicial,Data final,string tipo){
	this->inicial=inicial;
	this->final = final;
	this->nome = nome;
	this->tipo = tipo;
	if(tipo == "PONTO") // ao criar garante q tipo seja igual a uma das 2, por isso no need for other stuff
	{
		Prova_Pontuacao * pP = new Prova_Pontuacao(nome,inicial,final,tipo);
		provaP = pP;
		string coiso = "";
		Prova_Tempo * pT = new Prova_Tempo(coiso,inicial,final,coiso);
		provaT = pT;
	}
	if(tipo == "TEMPO")
	{
		Prova_Tempo * pT = new Prova_Tempo(nome,inicial,final,tipo);
		provaT = pT;
		Prova_Pontuacao * pP = new Prova_Pontuacao("",inicial,final,"");
		provaP = pP;
	}

}


vector<Posicao_tempo *> Prova_Tempo:: getLugares() const
{
	return lugares;
}

vector<Posicao_Pontos *> Prova_Pontuacao:: getLugares() const
{
	return lugares;
}

void Prova_Tempo::resultados()
{
	for(unsigned int i = 0; i<lugares.size();i++)
	{
		cout << i+1 << " lugar " << lugares[i]->getAtleta() << " " << lugares[i]->getTempo() << endl;
	}
}

void Prova_Pontuacao::resultados()
{
	for(unsigned int i = 0; i<lugares.size();i++)
	{
		cout << i+1 << " lugar " << lugares[i]->getAtleta() << " " << lugares[i]->getPontuacao() << endl;
	}
}

void evento::ProvaResultados()
{
	if(tipo == "TEMPO")
	{
		ordena();
		provaT->resultados();
	}
	if(tipo == "PONTO")
	{
		ordena();
		provaP->resultados();
	}
}


Prova_Tempo * evento::getProvaT()
{
	return provaT;
}

Prova_Pontuacao * evento::getProvaP()
{
	return provaP;
}

bool eventos_sobrepostos(const evento *alpha,const  evento *beta){

	if(alpha->getInicial()< beta->getFinal() && beta->getFinal() < alpha -> getFinal())
		return true;
	if(alpha->getInicial()< beta-> getInicial() && beta->getInicial()< alpha -> getFinal())
		return true;
	if(beta->getInicial() < alpha-> getInicial()&& alpha-> getInicial()< beta->getFinal())
		return true;
	if(beta->getInicial()  < alpha-> getFinal()&& alpha->getFinal() < beta->getFinal())
		return true;

	if(alpha->getInicial() == beta->getInicial()) return true;
	if(alpha->getFinal()== beta-> getFinal()) return true;
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

string EventoExiste::getNome()
{
	return nome;
}

string EventoNaoExiste::getNome()
{
	return nome;
}










Posicao::Posicao(string atleta){
	this->atleta = atleta;
}


string Posicao::getAtleta()const{
	return atleta;
}
//posicao tempo
Posicao_tempo::Posicao_tempo(string atleta , Data tempo):Posicao(atleta){

	this->tempo = tempo;

}
Data Posicao_tempo::getTempo() const{
	return tempo;
}
void Posicao_tempo::setTempo(Data tempo) {
	this->tempo = tempo;
}
bool Posicao_tempo::operator < (const Posicao_tempo &A) const {
	return tempo < A.getTempo();
}

//posicao_pontos
Posicao_Pontos::Posicao_Pontos(string atleta, int pontuacao):Posicao(atleta){
	this->pontuacao = pontuacao;
}
int Posicao_Pontos::getPontuacao() const{
	return pontuacao;
}
void Posicao_Pontos::setpontuacao(int pontuacao){
	this->pontuacao = pontuacao;
}
bool Posicao_Pontos::operator < (const Posicao_Pontos &A) const{
	return pontuacao > A.getPontuacao(); // e por ordem crescente de pontos?
}

void evento::ordena()
{
	if(tipo == "TEMPO") provaT->ordena();
	if(tipo == "PONTO") provaP->ordena();
}


//Prova_Pontuacao
void Prova_Pontuacao::ordena(){
	for (unsigned int p = 1; p < lugares.size(); p++)
	{
		Posicao_Pontos *tmp = lugares[p];
		int j;
		for (j = p; j > 0 && *tmp < *lugares[j-1]; j--)
			lugares[j] = lugares[j-1];
		lugares[j] = tmp;
	}
}
Prova_Pontuacao::Prova_Pontuacao(string nome,Data inicial,Data final,string tipo){
	this->inicial=inicial;
	this->final = final;
	this->nome = nome;
	this->tipo = tipo;
}

void evento::adicionaLugar(string nomeAtleta,int d, int m , int a, int h, int mi, int s, int score)
{
	if(tipo == "TEMPO")
	{
		Data da(d,m,a,h,mi,s);
		Posicao_tempo * lugar = new Posicao_tempo(nomeAtleta, da);
		provaT->adicionaLugar(lugar);
	}
	if(tipo == "PONTO")
	{
		Posicao_Pontos * lugar = new Posicao_Pontos(nomeAtleta, score);
		provaP->adicionaLugar(lugar);
	}
}

void evento::removeLugar(string nomeAtleta)
{
	if(tipo == "TEMPO")
	{
		provaT->removeLugar(nomeAtleta);
	}
	if(tipo == "PONTO")
	{
		provaP->removeLugar(nomeAtleta);
	}
}
vector<string> evento::getNomeAtletas() const
{

	if(tipo =="TEMPO")
	{
		return provaT->getNomeAtletas();
	}
	if(tipo == "PONTO")
		return provaP->getNomeAtletas();

	vector<string> Atletas;
	return Atletas;
}
void Prova_Pontuacao::adicionaLugar(Posicao_Pontos * lugar)
{
	bool naoexiste = true;
	for(unsigned int i = 0;i<lugares.size();i++)
	{
		if(lugares[i]->getAtleta() == lugar->getAtleta())
		{
			naoexiste = false;
		}
	}
	if(naoexiste) lugares.push_back(lugar);

}

void Prova_Tempo::adicionaLugar(Posicao_tempo * lugar)
{
	bool naoexiste = true;
	for(unsigned int i = 0;i<lugares.size();i++)
	{
		if(lugares[i]->getAtleta() == lugar->getAtleta())
		{
			naoexiste = false;
		}
	}
	if(naoexiste) lugares.push_back(lugar);

}

void Prova_Tempo::removeLugar(string nome)
{
	bool existe = false;
	unsigned int indice;
	for(unsigned int i = 0;i<lugares.size();i++)
	{
		if(lugares[i]->getAtleta() == nome)
		{
			existe = true;
			indice = i;
			break;
		}
	}
	if(existe) lugares.erase(lugares.begin()+indice);

}

void Prova_Pontuacao::removeLugar(string nome)
{
	bool existe = false;
	unsigned int indice;
	for(unsigned int i = 0;i<lugares.size();i++)
	{
		if(lugares[i]->getAtleta() == nome)
		{
			existe = true;
			indice = i;
			break;
		}
	}
	if(existe) lugares.erase(lugares.begin()+indice);

}
vector<string> Prova_Pontuacao::getNomeAtletas() const
{
	vector<string> Atletas;
	for(unsigned int i = 0; i < lugares.size();i++)
	{
		Atletas.push_back(lugares[i]->getAtleta());
	}
	return Atletas;
}

// Prova Tempo crg!!
void Prova_Tempo::ordena(){
	for (unsigned int p = 1; p < lugares.size(); p++)
	{
		Posicao_tempo *tmp = lugares[p];
		int j;
		for (j = p; j > 0 && *tmp < *lugares[j-1]; j--)
			lugares[j] = lugares[j-1];
		lugares[j] = tmp;
	}
}

Prova_Tempo::Prova_Tempo(string nome,Data inicial,Data final,string tipo){
	this->inicial=inicial;
	this->final = final;
	this->nome = nome;
	this->tipo = tipo;
}
vector<string> Prova_Tempo::getNomeAtletas() const
{	vector<string> Atletas;
for(unsigned int i = 0; i < lugares.size();i++)
{
	Atletas.push_back(lugares[i]->getAtleta());
}
return Atletas;
}

bool OrdenaEventosAlpha (const evento* A, const evento* B)
{
	string a = A->getNome();
	string b = B->getNome();
	transform(a.begin(), a.end(), a.begin(), ::tolower);
	transform(b.begin(), b.end(), b.begin(), ::tolower);

	if(a < b)
		return true;
	return false;
}
string evento::getTipo() const{
	return tipo;
}
Data Prova_Tempo::getTempo(string nomeAtleta)
{
	for(unsigned int i=0;i<lugares.size();i++)
	{
		if(lugares[i]->getAtleta() == nomeAtleta)
		{
			return lugares[i]->getTempo();
		}
	}
	return Data(-1,-1,-1);

}
int Prova_Pontuacao::getPontos(string nomeAtleta)
{
	for(unsigned int i=0;i<lugares.size();i++)
	{
		if(lugares[i]->getAtleta() == nomeAtleta)
		{
			return lugares[i]->getPontuacao();
		}
	}
	return -1;
}
