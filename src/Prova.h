#ifndef PROVA_H
#define PROVA_H

#include <string>

#include "atleta.h"
#include "Calendario.h"

class Posicao{
private:
	Atleta * atleta;
public:
	Posicao(Atleta * atleta);
	Atleta *getAtleta() const;
};

class Posicao_tempo : public Posicao{
private:
	Data tempo;
public:
	Posicao_tempo(Atleta * atleta , Data tempo);
	Data getTempo() const;
	void setTempo(Data tempo);
	 bool operator < (const Posicao_tempo &A) const;
};

class Posicao_Pontos : public Posicao{
private:
	int pontuacao;
public:
	Posicao_Pontos(Atleta * atleta, int pontuacao);
	int getPontuacao() const;
	void setpontuacao(int pontuacao);
	bool operator < (const Posicao_Pontos &A) const;
};



class Prova_Pontuacao : public evento {
private:
	vector<Posicao_Pontos *> lugares;
public:
	Prova_Pontuacao(string nome,Data inicial,Data final,string tipo);
	void ordena();
	void adicionaLugar(Posicao_Pontos *lugar);
	void removeLugar(Posicao_Pontos *lugar);
	vector<Posicao_Pontos *> getLugares() const;

};


class Prova_Tempo: public evento{
private:
	vector<Posicao_tempo *> lugares;
public:
	Prova_Tempo(string nome,Data inicial,Data final,string tipo);
	void ordena();
	void adicionaLugar(Posicao_tempo *lugar);
	void removeLugar(Posicao_tempo *lugar);
	vector<Posicao_tempo *> getLugares() const;

};

class lugarRepetida{
public:
	lugarRepetida(){};
};
class lugarNaoExiste{
public:
	lugarNaoExiste(){};
};
#endif



