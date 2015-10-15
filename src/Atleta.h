#ifndef ATLETA_H
#define ATLETA_H

#include  <string>
#include <vector>
#include <iostream>
#include "Desporto.h"




class Atleta
{
    string nome;
    vector<Desporto *> desportosInscrito; // pois pois xD
public:
    Atleta(string nome);
    void addDesporto(Desporto * p);
    void showDesportos();
    string getNome();
};

#endif
