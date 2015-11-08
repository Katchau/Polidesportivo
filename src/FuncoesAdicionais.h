#ifndef SRC_FUNCOESADICIONAIS_H_
#define SRC_FUNCOESADICIONAIS_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>

/**
 * @param s1 string que representa o valor a retornar
 *
 * Recebe input do utilizador de acordo com o pedido em s1.
 *
 * @return int
 */
int returnInt(std::string s1);

/**
 * @param s1 string que representa a string a retornar
 *
 * Recebe input do utilizador de acordo com o pedido em s1.
 * Valida o input e ignora whitespaces no fim da string.
 *
 * @return string com o input do utilizador.
 *
 */
std::string returnInput(std::string s1);

/**
 * @param filename nome do ficheiro
 *
 * Verifica se o ficheiro existe no diretorio do executavel
 *
 * @return true se existir
 * @return false se nao existir
 */
bool checkExistence(std::string filename);

/**
 * Permite ao utilizador introduzir o nome de um ficheiro
 *
 * @return nome do ficheiro
 */
std::string selectFile();

/**
 * @param menor menor opcao possivel
 * @param maior maior opcao possivel
 *
 * Permite selecionar uma opcao de um menu, tendo a menor e a maior opcao possivel
 *
 * @return opcao escolhida
 */
int selectMenu(char menor, char maior);

/**
 * @param v vetor onde pesquisar
 * @param x elemento a pesquisar
 *
 * Pesquisa sequencial de um elemento num vetor
 *
 * @return -1 se nao existir
 * @return indice do elemento no vetor se existir
 */
template <class T>
int sequentialSearch(const std::vector<T> &v, T x)
{
	for (unsigned int i = 0; i < v.size(); i++)
		if (v[i] == x)
			return i;
	return -1;
}

/**
 * @param v vetor onde adicionar
 * @param x elemento a adicionar
 *
 * Adiciona um elemento a um vetor
 *
 * @return true se adicionar o elemento
 * @return false se o elemento ja existir no vetor
 */
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

/**
 * @param v vetor onde remover
 * @param x elemento a remover
 *
 * Remove um elemento de um vetor
 *
 * @return true se remover o elemento
 * @return false se o elemento nao existir no vetor
 */
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
