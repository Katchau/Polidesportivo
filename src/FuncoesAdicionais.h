#ifndef SRC_FUNCOESADICIONAIS_H_
#define SRC_FUNCOESADICIONAIS_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>

std::string returnInput(std::string s1);
bool checkExistence(std::string filename);
std::string selectFile();
int selectMenu(char menor, char maior);

template <class T>
int sequentialSearch(const std::vector<T> &v, T x)
{
	for (unsigned int i = 0; i < v.size(); i++)
		if (v[i] == x)
			return i;
	return -1;
}

template <class T>
bool adicionaVetor(std::vector<T> &v, T elem)
{
	if (sequentialSearch(v, elem) == -1)
	{
		v.push_back(elem);
		return true;
	}
	else return false;
}

template <class T>
bool removeVetor(std::vector<T> &v, T elem)
{
	int indice = sequentialSearch(v, elem);

	if (indice == -1)
		return false;

	v.erase(v.begin() + indice);
	return true;
}

#endif
