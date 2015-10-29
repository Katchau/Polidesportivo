
//falta header files

#include "Equipa.h"
#include <fstream>

int Equipa::idN = 0;

Equipa::EquipaNaoExistente::EquipaNaoExistente(string nomeficheiro)
{
	this->nomeficheiro = nomeficheiro;
}


void Equipa::funcaoPorCoiso() // opah isto atualiza o id e o nome do ficheiro a guardar
{
    idN++;
    int id = idN;
    string nEq = "Equipa ";
    stringstream ss;
    ss << id;
    nEq =  nEq + ss.str() + ".txt";
    nameFile = nEq;
}

bool Equipa::addAtleta(string nome) //falta a condicao para false
{
    Atleta atl(nome);
    atletasInscritos.push_back(atl);
    return true;
}

bool Equipa::removeAtleta(string nome)
{
    for(vector<Atleta>::iterator it = atletasInscritos.begin();it!=atletasInscritos.end();it++)
    {
        if(it->getNome() == nome)
        {
            atletasInscritos.erase(it);
            it--;
            return true;
        }
    }
    return false;
}

Equipa::Equipa(string nome)
{
    name = nome;
    funcaoPorCoiso();

}

Equipa::Equipa() //buggs de ler no ficheiro: se tiver nomes com espaco nos desportos ou nas modalidades lixa isto td
{/*
    ifstream read;
    funcaoPorCoiso(); //edit later
    read.open(nameFile.c_str());
    if(read.fail()) // falta esta merda, n me apetece agr
    {
        read.close();
        throw Equipa::EquipaNaoExistente(nameFile);

    }
    importTeamFile(read);
    read.close();
    addAtlhetesFromFile();
    */
}

void Equipa::importTeamFile(ifstream &read) //falta comentar isto
{/*
    string lixo, name;
    read >> lixo;
    read.ignore(1);
    getline(read, name);
    this->name = name;
    */
}

void Equipa::addAtlhetesFromFile()
{
	/*
    ifstream read;
    string nome, desporto, modalidade,linha_1;
    read.open(nameFile.c_str());
    read.ignore(1000,'\n');
    read.ignore(1000,'\n');
    read >> linha_1;
    while(linha_1 != ";")
    {
        read.ignore(1);
        read >> desporto;
        read.ignore(1);
        read >> linha_1;
        Desporto * t = new Desporto(desporto);
        desportosInscritos.push_back(t);
    }

    read.ignore(1000,'\n');
    read.ignore(1000,'\n');
    read.ignore(1000,'\n');

    read >> linha_1;
    while(linha_1 != "Medalhas:")
    {
        read.ignore(1);
        read >> nome;
        read.ignore(100,'\n');
        read >> linha_1;
        read.ignore(1);
        Atleta atl(nome);
        while(linha_1 != ";")
        {
            read >> desporto;
            read.ignore(3);
            read >> modalidade;
            Desporto * p = new Modalidade(desporto,modalidade);
            atl.addDesporto(p);
            read >> linha_1;
        }
        atletasInscritos.push_back(atl);
        read >> linha_1;
    }
*/
}

void Equipa::writetoFile()
{
    ofstream save;
    string text_lixo;
    save.open(nameFile.c_str()); //dafuq isto nao deu erro????
    save << "nome: " << name << endl << endl;
    save << "Desportos: ";
    for(size_t i = 0;i<desportosInscritos.size();i++)
    {
        if(desportosInscritos.size()-i == 1)
        {
            save << desportosInscritos[i]->getNome() << " ;";
        }
        else
        {
            save << desportosInscritos[i]->getNome() << " | ";
        }

    }
    save << endl << endl << "Atletas: " << endl;
    for(unsigned int i = 0;i<atletasInscritos.size();i++)
    {

        vector<Desporto *> d = atletasInscritos[i].getDesportosInsc(); //eu nao percebo o eclipse ta td fdd
        save << "Nome: " << atletasInscritos[i].getNome() << endl << "Desportos: ";
        for(size_t j = 0; j < d.size(); j++)
        {
            if(d.size()-j == 1)
            {
                save << d[j]->getNome() << " ;" << endl;
            }
            else
            {
                save << d[j]->getNome() << " | ";
            }
        }
    }

    save << endl << endl << "Medalhas: "; //fazer dp
    save.close();
}

vector<Atleta> Equipa::getAtletas()
{
	return atletasInscritos;
}
