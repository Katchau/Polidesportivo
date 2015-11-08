#include "Equipa.h"

Equipa::EquipaNaoExistente::EquipaNaoExistente(string nomeficheiro)
{
	this->nomeficheiro = nomeficheiro;
}

bool Equipa::addAtleta(string nome)
{
	Atleta atleta(nome);
	cout << "Atletas Inscritos  "<< atletasInscritos.size() << endl;
	if (sequentialSearch(atletasInscritos, atleta) == -1)
	{
		atletasInscritos.push_back(atleta);
		cout << "Atletas Inscritos apos adicionar: "<< atletasInscritos.size() << endl;
		return true;
	}
	return false;
}

bool Equipa::removeAtleta(string nome)
{

	Atleta Sai(nome);
	int indice = sequentialSearch(atletasInscritos, Sai);
	if (indice == -1)
		return false;

	atletasInscritos.erase(atletasInscritos.begin()+indice);

	return true;
}

bool Equipa::existeAtleta(string nome)
{
	Atleta atleta(nome);
	if (sequentialSearch(atletasInscritos, atleta) == -1)
		return false;

	return true;
}

Equipa::Equipa()
{
	nome = returnInput("a equipa");

	nameFile = nome + ".txt";

}

Equipa::Equipa(string nome)
{
	this->nome = nome;
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

			// le desporto ate encontrar uma virgula
			do
			{
				Read >> tmp;
				if (tmp != "," && desporto != "")
					desporto = desporto + " " + tmp;
				if (tmp != "," && desporto == "")
					desporto = tmp;
			} while (tmp != ",");

			// le modalidade ate encontrar um |
			do
			{
				Read >> tmp;
				if (tmp != "|" && modalidade != "")
					modalidade = modalidade + " " + tmp;
				if (tmp != "," && modalidade == "")
					modalidade = tmp;
			} while (tmp != "|");

			Desporto * pmod = new Modalidade(desporto, modalidade);
			tmpatl.adicionaModalidade(pmod);

			adicionaVetor(desportosInscritos, pmod);
		}
		adicionaVetor(atletasInscritos, tmpatl);
	}
}


void Equipa::writetoFile()
{
	ofstream save(nameFile.c_str());

	save << "Atletas: " << atletasInscritos.size() << "\n";

	for (size_t i = 0; i < atletasInscritos.size(); i++)
	{
		save << "Nome: " << atletasInscritos[i].getNome() << "\n";

		vector<Desporto *> modalidades = atletasInscritos[i].getDesportosInsc();
		save << "Modalidades: " << modalidades.size() << "\n";

		for (size_t j = 0; j < modalidades.size(); j++)
		{
			save << modalidades[j]->getDesporto() << " , " << modalidades[j]->getTipo();

			if (j == (modalidades.size() -1))
				save << " |\n";
			else
				save << " | ";
		}
	}
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

	unsigned int i ;
	cout << "DESPORTOS INCRITOS SIZE :" <<desportosInscritos.size() << endl;
	for( i = 0; i < desportosInscritos.size();i++)
	{

		if(desporto == desportosInscritos[i]->getDesporto() && modalidade == desportosInscritos[i]->getDesporto())
		{

			cout << "Apagar modalidade da equipa" << endl;
			desportosInscritos.erase(desportosInscritos.begin() + i);
			break;
		}
	}
	for(unsigned int i = 0; i < atletasInscritos.size(); i++)
	{ cout << "Apagar desporto do Atleta" << endl;
	atletasInscritos[i].removeModalidade(desporto, modalidade);
	}

}
int Equipa::pontuacaoGeral(Desporto * mod)
{
	int score=0;
	for(unsigned int i=0;i<atletasInscritos.size();i++)
	{
		vector<Desporto * > desp = atletasInscritos[i].getDesportosInsc();
		for(unsigned int j = 0;j<desp.size();j++)
		{
			if(*(desp[j]) == *(mod))
			{
				vector<evento *> ev = mod->getProvas();
				for(unsigned int k =0;k<ev.size();k++)
				{
					score += ev[k]->getProvaP()->getPontos(atletasInscritos[i].getNome());
				}
			}
		}
	}
	return score;
}

Data Equipa::melhorTempo(Desporto * mod)
{
	Data melhor(999,999,999,0,0,0);
	for(unsigned int i=0;i<atletasInscritos.size();i++)
	{
		vector<Desporto * > desp = atletasInscritos[i].getDesportosInsc();
		for(unsigned int j = 0;j<desp.size();j++)
		{
			if(*(desp[j]) == *(mod))
			{
				vector<evento *> ev = mod->getProvas();
				for(unsigned int k =0;k<ev.size();k++)
				{
					if(ev[k]->getProvaT()->getTempo(atletasInscritos[i].getNome()) < melhor)
					{
						melhor = ev[k]->getProvaT()->getTempo(atletasInscritos[i].getNome());
					}
				}
			}
		}
	}
	return melhor;
}

