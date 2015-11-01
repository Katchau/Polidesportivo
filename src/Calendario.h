#ifndef CALENDARIO_H
#define CALENDARIO_H

#include <vector>
#include <ctime>
#include <iterator>
using namespace std;


bool ValidaData(Data Marcacao, bool atual);
bool bissexto(int ano);
unsigned int diasMes(int ano, int mes);

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

bool operator< (const Data &inicio,const Data &fim);
bool operator == (const Data &esquerda, const Data &direita);
bool operator <= (const Data &inicio,const Data &fim);

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

bool eventos_sobrepostos(const evento *alpha,const  evento *beta);

class Calendario {
private:
	Data inicio;
	Data fim;
	vector<evento*> eventos;
public:
	//Criar
	/**
	 * Cria calendario sem eventos
	 * @param inicio data inicial do horario
	 * @param fim data final do horario
	 */
	Calendario(Data inicio,Data fim);
	//Gerir
	/**
	 * Adiciona um evento ao Calendario
	 * lança objecto EventoSobreposto se houver um evento no mesmo intervalo de tempo
	 * lança objecto EventoExiste se o evento ja existir no calendario
	 * @param alpha  apontador para o evento
	 */
	void adiciona_evento(evento *alpha);
	/**
	 * Remove um evento do calendario
	 * lança objecto EventoNaoExiste se o evento nao existir no calendario
	 * @param alpha evento a ser removido
	 */
	void remove_evento(evento * alpha);
	/**
	 * Altera a data inicial
	 * @param inicio
	 */
	void setInicio(Data inicio);
	/**
	 * Altera data final
	 * @param fim
	 */
	void setFim(Data fim);
	//Ler
	/**
	 * Retorna a data inicial
	 */
	Data getInicio() const;
	/**
	 * Retorna a data final
	 */
	Data getFim() const;
	/**
	 * Retorna os eventos;
	 */
	vector<evento *> getEventos() const;
	/**
	 * imprime os detalhes da class
	 */
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







#endif
