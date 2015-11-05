#include "Infrastrutura.h"

using namespace std;

Infraestrutura::Infraestrutura()
{
	bool valido = true;
	do
	{
		cin.clear();
		if (!valido)
			cout << "Introduza um nome nao vazio: ";
		else
			cout << "Introduza o nome da infraestrutura: ";

		getline(cin, Nome);

		valido = false;

		for (size_t i = 0; i < Nome.size(); i++)
			if (Nome[i] != ' ')
				valido = true;
	} while (cin.eof() || !valido);
}

Infraestrutura::Infraestrutura(string Nome){
	this-> Nome = Nome;
	Horario =  new Calendario();

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

int Infraestrutura:: Neventos() const{
	return Horario->Neventos();
}

bool ordenaAlfaInfra(const Infraestrutura *A,const Infraestrutura *B){

	string a = A->getNome();
	string b = B->getNome();
	transform(a.begin(), a.end(), a.begin(), ::tolower);
	transform(b.begin(), b.end(), b.begin(), ::tolower);

	if(a < b)	return true;
	return false;
}

void Infraestrutura::imprimeCalendario()
{
	Horario->imprime();
}
