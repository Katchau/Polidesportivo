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
		vector<Atleta> temp = atletasInscritos;
		adicionaVetor(temp,atleta);
		setAtletas(temp);
		cout << "Atletas Inscritos apos adicionar: "<< atletasInscritos.size() << endl;
		return true;
	}
	return false;
}

bool Equipa::removeAtleta(string nome)
{
	Atleta Sai(nome);
	if (sequentialSearch(atletasInscritos, Sai) == -1)
		return false;
	vector<Atleta> temp = atletasInscritos;
	removeVetor(temp,Sai);
	setAtletas(temp);
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
				cout << " |\n";
			else
				cout << " | ";
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

void Equipa::setAtletas(vector<Atleta> Atletas)
{
	atletasInscritos = Atletas;
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
