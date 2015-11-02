#ifndef PROVA_H
#define PROVA_H


class Prova{


string Nome;
//FALTA COMO GUARDAR A PROVA;

public:

virtual void pontuacao();
};
class Prova_HIGH_SCORE : public Prova {
public:
void pontuacao();

};


class Prova_TIMER: public Prova{
public:
void pontuacao();
};
#endif



