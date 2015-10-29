#ifndef ATLETA_H
#define ATLETA_H

#include  <string>
#include <vector>
#include <iostream>
#include "Desporto.h"



class Atleta {
private:

    string nome;
    vector<Desporto *> desportosInscrito; // pois pois xD
public:
    Atleta(string nome);
    void adicionaDesporto(Desporto *d);
    vector<Desporto *> getDesportos();
    void showDesportos();
    string getNome();
};

#endif
