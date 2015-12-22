#ifndef CAMPEONATO_H
#define CAMPEONATO_H
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <set>
#include <sstream>
#include "Modalidade.h"
#include "Equipa.h"
#include "Infrastrutura.h"
#include "Atleta.h"
#include "Bilhete.h"

#include <sstream>
using namespace std;

bool checkExistence(string filename);
string selectFile();
int selectMenu(char menor, char maior);

class Campeonato {
private:
	string nome;
	vector<Infraestrutura *> Infraestruturas;
	vector<Equipa> Equipas;
	vector<Desporto*> Modalidades;
	priority_queue<Equipa> EquipasMedalhadas;
	Bilheteira bilheteira;
	set<evento*, evento::EventoCompare> CalendarioCompleto;
public:
	// Criar

	/**
	 *  Constroi um campeonato a partir de um ficheiro
	 *  criado segundo o formato do programa.
	 *
	 * @param filename nome do ficheiro do campeonato (incluindo extensao)
	 */
	Campeonato(const string &filename);

	/**
	 *  Constroi um campeonato a partir do proprio programa
	 *  pedindo ao utilizador o nome
	 */
	Campeonato();

	/**
	 *  Cria uma nova equipa a partir do proprio programa
	 *  chamando o construtor adequado e adiciona-a ao vetor
	 *  de equipas
	 */
	void criaEquipa();

	// Gerir
	/**
	 * Adiciona Equipa ao campeonato
	 * @param Equipa * A
	 */
	void adicionaEquipa(Equipa  A);
	/**
	 *  Faz display de um menu que permite visualizar e alterar
	 *  os atributos do campeonato
	 */
	void menuCampeonato();

	/**
	 *  Faz display de um menu que permite escolher entre visualizar ou alterar
	 *  as equipas do campeonato
	 */
	void menuEquipas();

	/**
	 * Faz display de todas as opçoes de ordenacao das equipas presentes no campeonato
	 */
	//template<class P>
	void listaEquipas();
	/**
	 * Permite adicionar uma equipa
	 */
	void adicionarEquipa();
	/**
	 * Permite remover uma equipa
	 */
	void removerEquipa();
	/**
	 * Faz display de todas as queipas presentes no campeonato por ordem alfabetica
	 */
	void EquipasOrdemAlfabetica();
	/**
		* Faz display de todas as equipas presentes numa modalidade por ordem de pontuacao total
		*/
	void EquipasOrdemPontuacao();
	/**
	 * Faz display de um menu que permite entre escolher entre visualizar ou alterar
	 * as infraestruturas do campeonato
	 */
	void menuInfraestruturas();
	/**
	 * Faz display das infraestruturas
	 */
	void listaInfraestruturas();
	/**
	 * Adiciona uma infraestrutura ao vector de infraestruturas
	 *
	 */
	void adicionarInfraestrutura();
	/**
	 * Permite apagar uma infraestrutura pertencente á lista
	 */
	void removerInfraestrutura();

	/**
	 * faz o display das infrastruturas por ordem alfabetica;
	 */
	void InfraestruturasOrdemAlfabetica();
	void menuModalidades();
	/**
	 * Faz display da lista de modalidades alfabeticamente
	 */
	void OrdemAlfabeticaModalidades();
	/**
	 * Faz o display das listas ordenadas possiveis para modalidades
	 */
	void listaModalidades();
	/**
	 * Permite adicionar modalidade á lista de modalidades
	 */
	void AdicionarModalidade();
	/**
	 * @return nome do campeonato
	 */
	/**
	 * Permite remover uma modalidade á lista de modalidades
	 */
	void RemoverModalidade();
	/**
	 * Faz o display do menu das provas
	 */
	int menuEscolhaInfra();
	/**
	 * Faz display de um menu que permite entre escolher entre visualizar ou alterar
	 * o calendario do campeonato
	 */
	void menuCalendario();
	/*
	 * Faz display do calendario de todas as infraestruturas
	 */
	void totalCalendario();
	/*
	 * Faz display do calendario de apenas uma infraestrutura
	 */
	void calendarioInfra();
	/*
	 * Faz display de um menu que permite escolher qual o calendario que se pretende visualizar
	 */
	void listaCalendarios();
	/*
	 * Permite adicionar um evento, permitindo ao utilizador escolher a infraestrutura e as caracteristicas do evento
	 */
	void adicionarEventos();
	/*
	 * Permite remover um evento, rendo o utilizador que indicar a infraestrutura
	 */
	void removerEventos();
/**
 * Faz display do menu relativo a gestao das provas
 */
	void menuProvas();

	/**
	 * Permite ao utilizador escolher uma modalidade e de seguida ver as classificacoes nessa mesma modalidade
	 */
	void verResultados();

	/**
	 * Permite adicionar uma prova de forma interativa com o utilizador
	 */
	void adicionarProvas();
/**
 * Permite remover uma prova de forma interativa com o utilizador
 */
	void removerProvas();
/**
 * Permite remover a classifiacao de um atleta numa prova
 */
	void removerClassProva();
/**
 * Faz display do menu que permite a gestao do atletas
 */
	void menuAtletas();
/**
 * Permite adicionar um atleta de forma interativa com o utilizador
 */
	void adicionaAtleta();
/**
 * Permite remover um atleta de forma interativa com o utilizador
 */
	void removeAtleta();
/**
 * Faz o display do menu com todas as listas de ordenacao de atletas
 */
	void listaAtletas();
/**
 * Faz o display de uma lista de atletas ordenados por equipas
 */
	void AtletasPorEquipa();

	/**
	 * Faz o display de uma lista de atletas ordenados por modalidades
	 */
	void AtletasPorModalidade();

	/**
	 * Faz o display de uma lista de atletas ordenados por desportos
	 */
	void AtletasPorDesporto();

	/**
	 * Permite obter as provas realizadas e por realizar
	 * @param seleciona  0 para provas realizadas  != 0 para provas por realizar
	 * @return provas realizadas se selciona = 0
	 * @return provas por realizar se seleciona != 0
	 */
	vector <evento*> ProvasOrganiza(unsigned int seleciona); // 0 Provas Realizadas  else Provas Por Realizar

	/**
	 * Verifica a existencia de uma equipa no campeonato
	 * @param nome Nome da equipa a procuram
	 * @return true se a equipa ja existir
	 * @return false se a  equipa nao existir
	 */
	bool ExisteEquipa(string nome) const;
	/**
	 * Verifica a existencia de um atleta no campeonato
	 * @param nome Nome do atleta
	 * @return true se o atleta existir
	 * @return false se o atleta nao  existir
	 */
	bool ExisteAtleta(string nome) const;
	/**
	 * Permite adicionar um atleta a uma equipa
	 * @param Atleta Nome do Atleta
	 * @param Equipa Nome da equipa
	 * @return true se atleta adicionado
	 * @return false se atleta nao adicionado
	 */
	bool AdicionaAtletaEquipa(string Atleta,string Equipa);
	/**
	 * Permite remover um atleta de uma equipa
	 * @param equipa Nome da Equipa
	 * @param Atleta Nome do atleta
	 * @return true se o atleta foi removido
	 * @return false se o atleta nao foi removido
	 */
	bool RemoveAtletaEquipa(string equipa,string Atleta);
	/**
	 * Permite remover um atleta de todas as provas
	 * @param Atleta Nome do atleta
	 */
	void RemoveAtletaProva(string Atleta);
	/**
	*  Permite inscrever um atleta numa determinada modalidade.
	*/
	void inscreverAtletaModalidade();
	/**
	 * @return Retorna os deportos presentes no campeonato
	 */
	vector<string>listaDesporto();
	/**
	 * @param Desporto Nome do desporto
	 * @return atletas inscritos no desporto
	 */
	vector<string>AtletasDesporto(string Desporto);
	/**
	 * Remove uma modalidade de todos os atletas
	 * @param desporto Nome do desporto
	 * @param modalidade Nome da modalidade
	 */
	void RemoveModalidadeAtletas(string desporto,string modalidade);
	/**
	 * Remove todos os eventos de uma  modalidade nas infraestruturas
	 */
	void RemoveEventosInfra(string modalidade);

	/**
	 * Imprime as provas realizadas no campeonato
	 */
	void ProvasRealizadas();
	/**
	 * Imprime as prvas por realizar no campeonato
	 */
	void ProvasPorRealizar();
	/**
	 * @return nome do campeonato
	 */
	string getNome() const;
	/**
	* @return numero de atletas inscritos no campeonato
	*/
	int numAtletas() const;
	/**
	 * @return vetor de infraestruturas
	 */
	vector<Infraestrutura *> getInfraestruturas();
	/**
	 * @return vetor de equipas
	 */
	vector<Equipa> getEquipas();
	/**
	 * @return vetor de modalidades
	 */
	vector<Desporto*> getModalidades();

	// Gravar

	/**
	 * Grava o campeonato num ficheiro .txt com nome igual ao nome do campeonato
	 *
	 */
	void gravarCampeonato();

	/**
	 * Grava as provas num ficheiro .txt com nome igual a Prova_nomedocampeonato
	 */
	void gravaProvas();
	/**
	 * Mostra o ranking das equipas, baseado nas medalhas que estes obtiveram.Só estao incluidas equipas com medalhas
	 */
	void EquipasOrdemMedalhadas();
	/**
	 * Display do menu relativo a simulacoes de resultados
	 */
	void menuSimulacao();
	/**
	 * Simula a finalizacao das provas de uma modalidade, e a respetiva obtencao de medalhas
	 */
	void simulacaoModalidade();
	/**
	 * Faz simulacao de um campeonato, devolvendo ao utilizador as medalhas de todas as equipas
	 */
	void simulacaoCampeonato();
	/**
	 * Altera certos parametros na simulacao efetuada,como por exemplo desqualificacao de uma equipa
	 */
	void alteraSimulacao();
	/**
	 * Menu da bilheteira
	 */
	void MenuBilheteira();
	void AdicionaBilhete();
	void RemoveBilhete();
	void VendeBilhete();
	void AdicionaProvaBilhete();
	void RemoveProvaBilhete();
	void ListarBilhetes();
	bool ExisteProva(string nome);
	void GravaBilhetes();

	// Excecoes
	class EquipaJaExistente
	{
	private:
		string nome;
	public:
		/**
		 * Construtor da classe de excecao EquipaJaExiste, atribuindo ao objeto o nome da equipa
		 * que ja existe
		 */
		EquipaJaExistente(string nome) {this->nome = nome;}
		/**
		 * @return Nome da equipa que ja existe
		 */
		string getNome() {return nome;}
	};

};

#endif



