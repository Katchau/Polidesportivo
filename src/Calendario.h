#ifndef CALENDARIO_H
#define CALENDARIO_H

#include <vector>
#include <ctime>
#include <iterator>
#include <algorithm>
#include "templates.h"

using namespace std;

struct Data {
	unsigned int dia;
	unsigned int mes;
	unsigned int ano;
	unsigned int horas;
	unsigned int minutos;
	unsigned int segundos;
	Data(int dia,int mes,int ano);
	/**
	 * Contrutor da classe Data
	 * @param dia
	 * @param mes
	 * @param ano
	 * @param horas
	 * @param minutos
	 * @param segundos
	 */
	Data(unsigned int dia,unsigned int mes,unsigned int ano,unsigned int horas,unsigned int minutos,unsigned int segundos);
	/*
	 * Contrutor da classe data
	 * todos os atributos inicializados a 0
	 */
	Data();
	/**
	 * Operador  << permite escrever os atributos da classe Data
	 *  @return ostream
	 */
	friend ostream& operator<<(ostream& os, const Data& dt);
};
/**
 * Operador de < entre objectos da classe Data
 * @param inicio
 * @param fim
 * @return true se Data fim � posterior  � data inicio;
 * @return false se Data fim � anterior � data inicio;
 */
bool operator< (const Data &inicio,const Data &fim);
/**
 * Operador de == entre objectos da classe Data
 * @param inicio
 * @param fim
 * @return true se Data fim � igual � data inicio;
 * @return false se Data fim nao � � data inicio;
 */
bool operator == (const Data &esquerda, const Data &direita);
/**
 * Operador de <= entre objectos da classe Data
 * @param inicio
 * @param fim
 * @return true se Data fim � posterior ou igual � data inicio;
 * @return false se Data fim � anterior � data inicio;
 */
bool operator <= (const Data &inicio,const Data &fim);

class Posicao{
private:
	string atleta;
public:
	/**
	 * Construtor da classe Posicao
	 * @param atleta Nome do atleta
	 */
	Posicao(string atleta);
	/**
	 * Retorna o nome do atleta
	 *  @return string
	 */
	string getAtleta() const;
};

class Posicao_tempo : public Posicao{
private:
	Data tempo;
public:
	/**
	 * Contrutor da classe Posicao_tempo
	 * @param atleta Nome do atleta
	 * @param tempo Tempo obtido pelo atleta
	 */
	Posicao_tempo(string atleta , Data tempo);
	/**
	 * Retorna o tempo obtido por um atleta
	 *  @return Data
	 */
	Data getTempo() const;
	/**
	 * Permite alterar o tempo na classificacao do atleta
	 */
	void setTempo(Data tempo);
	/**
	 * Operador de menor entre objectos da classe Posicao_tempo, compara o tempo obtido pelos atletas;
	 *  @return true se o tempo de A � maior que o objecto da classe Posicao_Pontos
	 * @return false se  o tempo de  A � menor que o objecto da classe Posicao_Pontos
	 */
	bool operator < (const Posicao_tempo &A) const;
};

class Posicao_Pontos : public Posicao{
private:
	int pontuacao;
public:
	/**
	 * Construtor da classe Posicao_Pontos
	 * @param atleta  Nome do Atleta
	 * @param pontuacao Pontuacao obtida pelo atleta
	 */
	Posicao_Pontos(string atleta, int pontuacao);
	/**
	 * Retorna a pontuacao do atleta
	 *  @return int
	 */
	int getPontuacao() const;
	/**
	 * Permite atualizar  a pontuacao do atleta
	 */
	void setpontuacao(int pontuacao);
	/**
	 * Operador de < entre objectos da classe Posicao_Pontos, compara a pontuacao obtida pelos atletas
	 * @return true se a pontuacao de A � menor que o objecto da classe Posicao_Pontos
	 * @return false se a pontuaca de A � maior que o objecto da classe Posicao_Pontos
	 */
	bool operator < (const Posicao_Pontos &A) const;
};



class Prova_Pontuacao{
private:
	vector<Posicao_Pontos *> lugares;
	string nome;
	Data inicial;
	Data final;
	string tipo;
public:
	/**
		 * Construtor da prova pontuacao
		 * @param nome Nome da Prova
		 * @param inicial Data de inicio da prova
		 * @param final Data final da prova
		 * @param tipo se a pontuacao da prova � por tempo ou ponto
		 */
	Prova_Pontuacao(string nome,Data inicial,Data final,string tipo);
	/**
		 * Ordena as classifica�oes obtidas pelos atletas nas provas
		 */
	void ordena();
	/**
		 * Adiciona uma posicao ao vetor de classificao da prova
		 * @param *lugar apontador para a classificao do atleta
		 */
	void adicionaLugar(Posicao_Pontos *lugar);
	/**
		 * Remove o atleta da prova
		 * @param nome Nome do atleta
		 */
	void removeLugar(string nome);
	/**
		 * Retorna o vector de classifica�oes da prova
		 * return vector<Posicao_Pontos>
		 */
	vector<Posicao_Pontos *> getLugares() const;
	/**
		 * Imprime as classificacoes da prova
		 */
	void resultados();
	/**
		 * Retorna o nome dos atletas presentes na prova
		 *  @return vector<string>
		 */
	vector<string> getNomeAtletas() const;
};


class Prova_Tempo{
private:
	vector<Posicao_tempo *> lugares;
	string nome;
	Data inicial;
	Data final;
	string tipo;
public:
	/**
	 * Construtor da prova tempo
	 * @param nome Nome da Prova
	 * @param inicial Data de inicio da prova
	 * @param final Data final da prova
	 * @param tipo se a pontuacao da prova � por tempo ou ponto
	 */
	Prova_Tempo(string nome,Data inicial,Data final,string tipo);
	/**
	 * Ordena as classifica�oes obtidas pelos atletas nas provas
	 */
	void ordena();
	/**
	 * Adiciona uma posicao ao vetor de classificao da prova
	 * @param *lugar apontador para a classificao do atleta
	 */
	void adicionaLugar(Posicao_tempo *lugar);
	/**
	 * Remove o atleta da prova
	 * @param nome Nome do atleta
	 */
	void removeLugar(string nome);
	/**
	 * Retorna o vector de classifica�oes da prova
	 *  @return vector<Posicao_tempo *>
	 */
	vector<Posicao_tempo *> getLugares() const;
	/**
	 * Imprime as classificacoes da prova
	 */
	void resultados();
	/**
	 * Retorna o nome dos atletas presentes na prova
	 *  @return vector<string>
	 */
	vector<string> getNomeAtletas() const;

};

class lugarRepetida{
public:
	/**
	 * Construtor da excepcao lugarRepetida
	 */
	lugarRepetida(){};
};
class lugarNaoExiste{
public:
	/**
	 * Construtor da excepcao lugarNaoExistente
	 */
	lugarNaoExiste(){};
};







class evento {
private:
	string nome;
	Data inicial;
	Data final;
	string tipo;
	Prova_Tempo * provaT;
	Prova_Pontuacao * provaP;
public:

	/**
	 * Construtor de evento
	 * @param nome Nome do evento
	 * @param inicial Data do inicio do evento
	 * @param final Data final do evento
	 * @param tipo  Tipo da pontuacao  ( TEMPO ou PONTO )
	 */
	evento(string nome,Data inicial,Data final,string tipo);
	/**
	 * Retorna o nome do evento
	 *  @return string
	 */
	string getNome() const;
	/**
	 * Retorna o nome da modalidade
	 *  @return string
	 */
	string getTipo() const;
	/**
	 * Retorna a data inicial do evento
	 *  @return Data
	 */
	Data getInicial() const;
	/**
	 * Retorna a data final do evento
	 *  @return Data
	 */
	Data getFinal() const;
	/**
	 * Ordena as classifica�oes dos melhores resultados para os piores
	 *
	 */
	void ordena();
	void retProva(); //TODO
	void adicionaLugar(string nomeAtleta,int d, int m , int a, int h, int mi, int s, int score); //TODOalgumas duvidas
	/**
	 * Remove a classificacao do atleta na prova
	 * @param nomeAteta nome do Atleta
	 */
	void removeLugar(string nomeAtleta);
	/**
	 * Operador de igualdade entre dois eventos
	 * @param *ev;
	 */
	bool operator == (const evento * ev) const;
	/**
	 * Retorna o apontador de Prova tempo
	 *  @return Prova_Tempo*
	 */
	Prova_Tempo * getProvaT();
	/**
	 * Retorna o apontador de Prova por pontuacao
	 *  @return Prova_Pontuacao*
	 */
	Prova_Pontuacao * getProvaP();
	/**
	 * Imprime  a classificacao na prova
	 *
	 */
	void ProvaResultados();
	/**
	 * Retorna o nome dos que estejam a participar no evento
	 */
	vector<string> getNomeAtletas() const;
};
/**
 * Compara dois eventos e ve se o intervalo de tempo entre os dois eventos e retorna true se os eventos estiverem sobrepostos
 * @param *alpha
 * @param *beta
 *  @return true se os eventos estao sobrepostos
 *  @returm false se os eventos nao estao sobrepostos
 */
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
	/**
	 * Criar calendario
	 */
	Calendario();
	//Gerir
	/**
	 * Adiciona um evento ao Calendario
	 * lan�a objecto EventoSobreposto se houver um evento no mesmo intervalo de tempo
	 * lan�a objecto EventoExiste se o evento ja existir no calendario
	 * @param alpha  apontador para o evento
	 */
	void adiciona_evento(evento *alpha);
	/**
	 * Remove um evento do calendario
	 * lan�a objecto EventoNaoExiste se o evento nao existir no calendario
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
	 *  @return Data
	 */
	Data getInicio() const;
	/**
	 * Retorna a data final
	 *  @return Data
	 */
	Data getFim() const;
	/**
	 * Retorna os eventos;
	 *  @return vector<evento* >
	 */
	vector<evento *> getEventos() const;
	/**
	 * Retorna o numero de eventos
	 *  @return int
	 */
	int Neventos() const;
	/**
	 * imprime os detalhes da class
	 */
	void imprime() const;

};

class EventoExiste {
private:
	string nome;
public:
	/**
	 * Construtor da excepcao EventoExite
	 * @param nome Nome do evento que ja existe
	 */
	EventoExiste(string nome);
	/**
	 * Retorna o nome do evento que ja existe
	 *  @return string
	 */
	string getNome();
};
class EventoNaoExiste{
private:
	string nome;
public:
	/**
	 * Construtor da excepcao EventoNaoExite
	 * @param Nome do evento que nao existe
	 */
	EventoNaoExiste(string nome);
	/**
		 * Retorna o nome do evento que nao existe
		 *  @return string
		 */
	string getNome();
};
class EventoSobreposto{
public:
	/**
	 * Construtor da excepcao EventoSobreposto
	 */
	EventoSobreposto(){};
};



/**
 * Permite verificar se a data � valida
 * @param Marcacao Data a verificar
 * @param atual  Se igual a zero apenas verifica se os valores na data sao possiveis. \n
 * 				 Se igual a um verifica se os valores da data sao possiveis e se a Marcacao � posterior � data atual
 * 	@return true se data e valida
 *	@return false se a data nao � valida
 */
bool ValidaData(Data Marcacao, bool atual);

/**
 * Verifica se o ano � bissexto.Retorna true se for verdade
 * @param ano
 * @return true se o ano e bissexto
 * @return false se o ano nao e bissexto
 */
bool bissexto(int ano);
/**
 * Retorna o numero de dias de um mes
 * @param ano
 * @param mes
 * @return unsigend int
 */
unsigned int diasMes(int ano, int mes);

/**
 * 	Compara o evento A e o evento B. Retorna true se estao alfabeticamente ordenados
 * 	@param  evento A
 * 	@param evento B
 * 	@return true se ordenados alfabeticamente
 *  @return false se  nao estao ordenados alfabeticamente
 */
bool OrdenaEventosAlpha (const evento* A, const evento* B);

#endif
