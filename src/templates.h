#include <vector>
#include <iostream>

using namespace std;

template <class T>
int sequentialSearch(const vector<T> &v, T x)
{
	for (unsigned int i = 0; i < v.size(); i++)
		if (v[i] == x)
			return i;
	return -1;
}

template <class T>
bool adicionaVetor(vector<T> &v, T elem)
{
	if (sequentialSearch(v, elem) == -1)
	{
		v.push_back(elem);
		return true;
	}
	else return false;
}

template <class T>
bool removeVetor(vector<T> &v, T elem)
{
	int indice = sequentialSearch(v, elem);

	if (indice == -1)
		return false;

	v.erase(v.begin() + indice);
	return true;
}

string returnInput(string s1)
{
	string tmp;
	bool valido = true;

	do
	{
		cin.clear();

		if (!valido)
			cout << "Introduza um nome nao vazio: ";
		else
			cout << "Introduza o nome d" << s1 << ": ";
		getline(cin, tmp);

		valido = false;

		for (size_t i = 0; i < tmp.size(); i++)
			if (tmp[i] != ' ')
				valido = true;
	} while(cin.eof() || !valido);
	return tmp;
}
