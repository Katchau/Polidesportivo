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
	catch(EventoSobreposto &e){
		cout << "Evento Sobreposto \n";
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
bool Infraestrutura::operator== (const Infraestrutura & A){
	if(Nome == A.getNome())
		return true;
	return false;
}
bool ordenaAlfaInfra(const Infraestrutura &A,const Infraestrutura &B){
	if(A.getNome() <  B.getNome()) return true;
	return false;
}
