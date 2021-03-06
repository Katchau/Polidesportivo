#include "FuncoesAdicionais.h"

int returnInt(std::string s1)
{
	int tmp;

	bool fail = false;
	bool eof = false;

	do
	{
		std::cin.clear();

		if (fail && !eof)
			std::cin.ignore(100,'\n');

		std::cout << s1;
		std::cin >> tmp;

		fail = false;
		eof = false;

		if (std::cin.fail())
			fail = true;

		if (std::cin.eof())
			eof = true;
	} while(fail || eof);

	return tmp;
}

std::string returnInput(std::string s1)
{
	std::string tmp;
	bool valido = true;

	do
	{
		std::cin.clear();

		if (!valido)
			std::cout << "Introduza um nome nao vazio: ";
		else
			std::cout << "Introduza o nome d" << s1 << ": ";

		getline(std::cin, tmp);

		valido = false;

		for (size_t i = 0; i < tmp.size(); i++)
			if (tmp[i] != ' ')
				valido = true;
	} while(std::cin.eof() || !valido);

	for (size_t i = tmp.size() -1; i >= 0; i--)
	{
		if (tmp[i] != ' ')
		{
			tmp.resize(i+1);
			break;
		}
	}

	return tmp;
}

bool checkExistence(std::string filename)
{
	std::ifstream f;
	f.open(filename.c_str());

	return f.is_open();
}


std::string selectFile()
{
	std::string a;

	bool invalido = false;

	do
	{
		if (invalido)
		{
			invalido = false;
			std::cout << "O ficheiro pretendido nao existe. Introduza novamente:" << std::endl;
			std::cin.clear();
		}
		std::cout << "Nome do ficheiro de campeonato (incluindo extensao): ";
		getline(std::cin, a);
		if (std::cin.eof())
			exit(1);
		if (!checkExistence(a))
			invalido = true;
	} while (std::cin.fail() || invalido); // realiza o ciclo enquanto o ficheiro introduzido nao for valido ou nao existir;
	return a;
}

int selectMenu(char menor, char maior)
{
	std::string linha = "";

	while (linha.length() != 1)
	{
		getline(std::cin, linha);
		if (std::cin.eof())
			std::cin.clear();

		if (linha.length() != 1 || (linha.length() == 1 && (linha[0] < menor || linha[0] > maior)))
		{
			std::cout << "Opcao invalida. Introduza a opcao pretendida: ";
			linha = "";
		}
	}
	return linha[0];
}
