#include "Infrastrutura.h"

using namespace std;

Infraestrutura::Infraestrutura(string Nome){
	this-> Nome = Nome;
	Horario = 0;
}
Infraestrutura::Infraestrutura(string Nome, Calendario * Horario){
	this-> Nome = Nome;
	this->Horario = Horario;
}
void Infraestrutura::adicionaEvento(evento* A ){
	try{Horario->adiciona_evento(A);}
	catch(EventoExiste &e){
		cout << "O Evento já exite! \n";
	}
	catch(EventoNaoAdicionado &e){
		cout << "Nao foi possivel adiconar o evento \n";
	}

}
void Infraestrutura::removeEvento(evento* B){
	try{Horario->remove_evento(B);}
	catch(EventoNaoExiste &e){
		cout << "O Evento nao existe! \n";
	}

}
Calendario*  Infraestrutura::getCalendario() const{
	return Horario;
}
void  Infraestrutura::setCalendario(Calendario * Novo){
 Horario = Novo;
}
string Infraestrutura::getNome()const{
	return Nome;
}
void Infraestrutura::imprime() const{

}
