#include "Equipa.h"


int Equipa::idN = 0;

Equipa::EquipaNaoExistente::EquipaNaoExistente(string nomeficheiro)
{
	this->nomeficheiro = nomeficheiro;
}

void Equipa::atualizarID()
{
	idN++;
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

Equipa::Equipa()
{
	bool valido = true;
	do
	{
		cin.clear();
		if (!valido)
			cout << "Introduza um nome nao vazio: ";
		else
			cout << "Introduza o nome da equipa: ";

		getline(cin, nome);

		valido = false;

		for (size_t i = 0; i < nome.size(); i++)
			if (nome[i] != ' ')
				valido = true;
	} while (cin.eof() || !valido);

	atualizarID();

	nameFile = nome + ".txt";

}
bool checkExistence(std::string filename)
{
	ifstream f;
	f.open(filename.c_str());

	return f.is_open();
}



Equipa::Equipa(string nome) //buggs de ler no ficheiro: se tiver nomes com espaco nos desportos ou nas modalidades lixa isto td
{
    ifstream read;
    this->nome = nome;
    atualizarID(); //edit later
    nameFile = nome + ".txt";

    if(checkExistence(nameFile))
    {
    	addAtlhetesFromFile();

    }
    else throw Equipa::EquipaNaoExistente(nameFile);


}



void Equipa::addAtlhetesFromFile()
{
	cout << "bananas!";
    ifstream read;
    string nome, desporto, modalidade,linha_1;
    read.open(nameFile.c_str());
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
            Desporto * p = new Modalidade (desporto, modalidade);
            atl.adicionaDesporto(p);
            read >> linha_1;
            cout << "bananas2!";
        }
        atletasInscritos.push_back(atl);
        read >> linha_1;
        cout << "bananas3!";
    }
    read.close();
}

void Equipa::writetoFile()
{
	ofstream save;
	string text_lixo;
	save.open(nameFile.c_str()); //dafuq isto nao deu erro????
	save << "nome: " << nome << '\n' << '\n';
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
	save << '\n' << '\n' << "Atletas: " << '\n';
	for(unsigned int i = 0;i<atletasInscritos.size();i++)
	{

		vector<Desporto *> d = atletasInscritos[i].getDesportosInsc(); //eu nao percebo o eclipse ta td fdd
		save << "Nome: " << atletasInscritos[i].getNome() << '\n' << "Desportos: ";
		for(size_t j = 0; j < d.size(); j++)
		{
			if(d.size()-j == 1)
			{
				save << d[j]->getNome() << " ;" << '\n';
			}
			else
			{
				save << d[j]->getNome() << " | ";
			}
		}
	}

	save << '\n' << '\n' << "Medalhas: "; //fazer dp
	save.close();
}

string Equipa::getNomeEquipa() const
{
	return nome;
}

vector<Atleta> Equipa::getAtletas()
{
	return atletasInscritos;
}

bool Equipa::operator == (const Equipa& eqi) const
{
	string nome1 = nome;
	string nome2 = eqi.nome;
	if(nome1 == nome2)
	{
		return true;
	}
	else return false;
}
bool ordenaAlfaEquipa(const Equipa A, const Equipa B){
	string a = A.getNomeEquipa();
		string b = B.getNomeEquipa();
		transform(a.begin(), a.end(), a.begin(), ::tolower);
		transform(b.begin(), b.end(), b.begin(), ::tolower);

		if(a < b)
			return true;
		return false;
}

