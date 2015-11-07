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
	return adicionaVetor(atletasInscritos, atl);
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

Equipa::Equipa(string nome)
{

	this->nome = nome;
	atualizarID();
	nameFile = nome + ".txt";

	if(checkExistence(nameFile))
	{
		addAthletesFromFile();
	}
	else throw Equipa::EquipaNaoExistente(nameFile);
}



void Equipa::addAthletesFromFile()
{
	ifstream Read(nameFile.c_str());

	string lixo;
	int n_atletas;

	Read >> lixo >> n_atletas;

	for (int i = 0; i < n_atletas; i++)
	{
		string nome;
		int n_modal;

		Read >> lixo >> nome >> lixo >> n_modal;

		Atleta tmpatl(nome);

		for (int i = 0; i < n_modal; i++)
		{
			string desporto = "";
			string modalidade = "";
			string especialidade = "";
			string tmp = "";

			do
			{
				Read >> tmp;
				if (tmp != ",")
					desporto += tmp;
			} while (tmp != ",");
			do
			{
				Read >> tmp;
				if (tmp != "," && tmp != "|")
					modalidade += tmp;
			} while (tmp != "," && tmp != "|");
			/*
			if (tmp == ",")
			{
				tmp = "";
				do
				{
					especialidade += tmp;
					Read >> tmp;
				} while (tmp != "|");
			}

			Modalidade mod(desporto, modalidade);
			Desporto* pmod = &mod;
			*/
			Desporto * pmod = new Modalidade(desporto, modalidade);
			tmpatl.adicionaDesporto(pmod);

			adicionaVetor(desportosInscritos, pmod);
		}
		adicionaVetor(atletasInscritos, tmpatl);
	}
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

vector<Atleta> Equipa::getAtletas() const
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
void Equipa::removeModalidade(string desporto,string modalidade){
	Desporto * Desport;
	for(unsigned int i = 0; i < desportosInscritos.size();i++)
	{
		if(desporto == desportosInscritos[i]->getDesporto() && modalidade == desportosInscritos[i]->getDesporto())
		{	Desport = desportosInscritos[i];
			desportosInscritos.erase(desportosInscritos.begin() + i);
			break;
		}
	}
	for(unsigned int i = 0; i < atletasInscritos.size(); i++)
	{
		atletasInscritos[i].removeDesporto(Desport);
	}
}
