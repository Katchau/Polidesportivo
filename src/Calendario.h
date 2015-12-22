#ifndef CALENDARIO_H
#define CALENDARIO_H

#include <vector>
#include <ctime>
#include <iterator>
#include <algorithm>
#include "FuncoesAdicionais.h"

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
 * @return true se Data fim e posterior  a data inicio;
 * @return false se Data fim e anterior a data inicio;
 */
bool operator< (const Data &inicio,const Data &fim);
/**
 * Operador de == entre objectos da classe Data
 * @param inicio
 * @param fim
 * @return true se Data fim e igual a data inicio;
 * @return false se Data fim nao e igual a data inicio;
 */
bool operator == (const Data &esquerda, const Data &direita);
/**
 * Operador de <= entre objectos da classe Data
 * @param inicio
 * @param fim
 * @return true se Data fim e posterior ou igual a data inicio;
 * @return false se Data fim e anterior a data inicio;
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
	 *  @return Retorna o nome do atleta
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
	 *  @return  Retorna o tempo obtido por um atleta
	 */
	Data getTempo() const;
	/**
	 * Permite alterar o tempo na classificacao do atleta
	 */
	void setTempo(Data tempo);
	/**
	 * Operador de menor entre objectos da classe Posicao_tempo, compara o tempo obtido pelos atletas;
	 *  @return true se o tempo de A e maior que o objecto da classe Posicao_Pontos
	 * @return false se  o tempo de  A e menor que o objecto da classe Posicao_Pontos
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
	 *
	 *  @return Retorna a pontuacao do atleta
	 */
	int getPontuacao() const;
	/**
	 * Permite atualizar  a pontuacao do atleta
	 */
	void setpontuacao(int pontuacao);
	/**
	 * Operador de < entre objectos da classe Posicao_Pontos, compara a pontuacao obtida pelos atletas
	 * @return true se a pontuacao de A e menor que o objecto da classe Posicao_Pontos
	 * @return false se a pontuaca de A e maior que o objecto da classe Posicao_Pontos
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
		 * @param tipo se a pontuacao da prova e por tempo ou ponto
		 */
	Prova_Pontuacao(string nome,Data inicial,Data final,string tipo);
	/**
		 * Ordena as classificacoes obtidas pelos atletas nas provas
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
		 *
		 * return Retorna o vector de classificacoes da prova
		 */
	vector<Posicao_Pontos *> getLugares() const;
	/**
		 * Imprime as classificacoes da prova
		 */
	void resultados();
	/**
		 *
		 *  @return  Retorna o nome dos atletas presentes na prova
		 */
	vector<string> getNomeAtletas() const;
	/**
		 	 * Retorna a pontuacao de um atleta
		 	 *@param nomeAtleta nome do atleta
		 	 *@return pontuacao de um atleta
			 */
		int getPontos(string nomeAtleta);
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
	 * @param tipo se a pontuacao da prova  por tempo ou ponto
	 */
	Prova_Tempo(string nome,Data inicial,Data final,string tipo);
	/**
	 * Ordena as classificacoes obtidas pelos atletas nas provas
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
	 *
	 *  @return Retorna o vector de classificacoes da prova
	 */
	vector<Posicao_tempo *> getLugares() const;
	/**
	 * Imprime as classificacoes da prova
	 */
	void resultados();
	/**
	 *
	 *  @return Retorna o nome dos atletas presentes na prova
	 */
	vector<string> getNomeAtletas() const;

	/**
	 * Retorna o tempo de um atleta
	 *@param nomeAtleta nome do atleta
	 *@return tempo de um atleta
	 */
	Data getTempo(string nomeAtleta);


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
	 *
	 *  @return Retorna o nome do evento
	 */
	string getNome() const;
	/**
	 *
	 *  @return Retorna o tipo de classificacao
	 */
	string getTipo() const;
	/**
	 *
	 *  @return Retorna a data inicial do evento
	 */
	Data getInicial() const;
	/**
	 *
	 *  @return Retorna a data final do evento
	 */
	Data getFinal() const;
	/**
	 * Atribui uma nova data inicial ao evento
	 */
	void setInicial(Data inicialdata);
	/**
	 * Atribui uma nova data final ao evento
	 */
	void setFinal(Data finaldata);
	/**
	 * Atribui um novo nome ao evento
	 */
	void setNome(string nome);
	/**
	 * Ordena as classificacoes dos melhores resultados para os piores
	 *
	 */
	void ordena();

	void adicionaLugar(string nomeAtleta,int d, int m , int a, int h, int mi, int s, int score); //TODOalgumas duvidas
	/**
	 * Remove a classificacao do atleta na prova
	 * @param nomeAteta nome do Atleta
	 */
	void removeLugar(string nomeAtleta);
	/**
	 * Operador de igualdade entre dois eventos
	 * @param *ev evento a comparar
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
	/**
	 * Struct com comparador de eventos para a Árvore Binária
	 */
	struct EventoCompare {
		/**
		 * Comparador de eventos para a BST
		 *
		 * @param *ev1 evento 1
		 * @param *ev2 evento 2
		 *
		 * @return true se o evento 1 tiver data inicial inferior ao evento 2 ou no caso de igualdade se for alfabeticamente menor
		 * @return false se o evento 1 tiver data inicial superior ao evento 2 ou no caso de igualdade se for alfabeticamente maior
		 */
		bool operator() (const evento *ev1, const evento *ev2)
		{
			if (ev1->getInicial() < ev2->getInicial())
				return true;
			if (ev1->getInicial() == ev2->getInicial())
				if (ev1->getNome() < ev2->getNome())
					return true;

			return false;
		}
	};
	/**
	 * Adia o evento de acordo com a duração escolhida pelo utilizador
	 */
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
	 * lanca objecto EventoSobreposto se houver um evento no mesmo intervalo de tempo
	 * lanca objecto EventoExiste se o evento ja existir no calendario
	 * @param alpha  apontador para o evento
	 */
	void adiciona_evento(evento *alpha);
	/**
	 * Remove um evento do calendario
	 * lanca objecto EventoNaoExiste se o evento nao existir no calendario
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
	 *
	 *  @return Retorna a data inicial
	 */
	Data getInicio() const;
	/**
	 *
	 *  @return  Retorna a data final
	 */
	Data getFim() const;
	/**
	 *  @return Retorna os eventos;
	 */
	vector<evento *> getEventos() const;
	/**
	 *
	 *  @return Retorna o numero de eventos
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
		 *
		 *  @return Retorna o nome do evento que nao existe
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
 * Permite verificar se a data e valida
 * @param Marcacao Data a verificar
 * @param atual  Se igual a zero apenas verifica se os valores na data sao possiveis. \n
 * 				 Se igual a um verifica se os valores da data sao possiveis e se a Marcacao e posterior á data atual
 * 	@return true se data e valida
 *	@return false se a data nao e valida
 */
bool ValidaData(Data Marcacao, bool atual);

/**
 * Verifica se o ano e bissexto.Retorna true se for verdade
 * @param ano
 * @return true se o ano e bissexto
 * @return false se o ano nao e bissexto
 */
bool bissexto(int ano);
/**
 *
 * @param ano
 * @param mes
 * @return Retorna o numero de dias de um mes
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
