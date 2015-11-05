#include "Prova.h"

//Posicao
/*
Posicao::Posicao(string atleta){
	this->atleta = atleta;

}


string Posicao::getAtleta()const{
	return atleta;
}
//posicao tempo
Posicao_tempo::Posicao_tempo(string atleta , Data tempo):Posicao(atleta){

	this->tempo = tempo;

}
Data Posicao_tempo::getTempo() const{
	return tempo;
}
void Posicao_tempo::setTempo(Data tempo) {
	this->tempo = tempo;
}
bool Posicao_tempo::operator < (const Posicao_tempo &A) const {
	return tempo < A.getTempo();
}

//posicao_pontos
Posicao_Pontos::Posicao_Pontos(string atleta, int pontuacao):Posicao(atleta){
	this->pontuacao = pontuacao;
}
int Posicao_Pontos::getPontuacao() const{
	return pontuacao;
}
void Posicao_Pontos::setpontuacao(int pontuacao){
	this->pontuacao = pontuacao;
}
bool Posicao_Pontos::operator < (const Posicao_Pontos &A) const{
	return pontuacao < A.getPontuacao();
}


//Prova_Pontuacao
void Prova_Pontuacao::ordena(){
	for (unsigned int p = 1; p < lugares.size(); p++)
	{
		Posicao_Pontos *tmp = lugares[p];
		int j;
		for (j = p; j > 0 && *tmp < *lugares[j-1]; j--)
			lugares[j] = lugares[j-1];
		lugares[j] = tmp;
	}
}
Prova_Pontuacao::Prova_Pontuacao(string nome,Data inicial,Data final,string tipo):evento(nome,inicial,final,tipo){}
//Prova_Tempo
void Prova_Tempo::ordena(){
	for (unsigned int p = 1; p < lugares.size(); p++)
		{
			Posicao_tempo *tmp = lugares[p];
			int j;
			for (j = p; j > 0 && *tmp < *lugares[j-1]; j--)
				lugares[j] = lugares[j-1];
			lugares[j] = tmp;
		}

}

Prova_Tempo::Prova_Tempo(string nome,Data inicial,Data final,string tipo):evento(nome,inicial,final,tipo){}


*/



