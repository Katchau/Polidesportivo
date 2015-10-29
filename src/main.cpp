#include <iostream>
#include "Calendario.h"
int main()
{/*CLASS CALENDARIO TEST*/
	//DATA STRUCT
	cout << "Data \n";
	Data a1 (1,2,1994);
	Data a2 (1,2,1995);
	Data a3 (1,3,1995);
	Data a4 (3,3,1995);


	// Comp. Ano<Ano
	if(a1 < a2) cout << "Test 1: success \n";
	else cout << "Test 1: failed \n";
	// Comp. Mes<Mes
	if(a2<a3)cout << "Test 2: success \n";
	else cout << "Test 2: failed \n";
	//Comp. Dia< Dia
	if(a3 < a4)cout << "Test 3: success \n";
	else cout << "Test 3: failed \n";

	//Comp. a1 < a1

	if(!(a1<a1))cout << "Test 4: success \n";
	else cout << "Test 4: failed \n";

	cout <<"Valida Data \n";
	// Valida Data
	Data b1 (1,11,2015);

	if(ValidaData(b1,0))cout << "Test 5: success \n";
	else cout << "Test 5: failed \n";

	// Se a data  é atual
	if(!(ValidaData(a1,1)))cout << "Test 6: success \n";
	else cout << "Test 6: failed \n";

	Data b2(60,2,2015);
	Data b3(2,30,2015);
	Data b4(1,30,-2);

	if(!(ValidaData(b2,0)))cout << "Test 7: success \n";
		else cout << "Test 7: failed \n";
	if(!(ValidaData(b3,0)))cout << "Test 7: success \n";
		else cout << "Test 7: failed \n";
	if(!(ValidaData(b4,0)))cout << "Test 8: success \n";
		else cout << "Test 8: failed \n";



	cout << "bissexto \n";
	//bissexto
	// é bissexto
	if(bissexto(2016))cout << "Test 6: success \n";
	else cout << "Test 6: failed \n";
	// nao é bissexto
	if(!bissexto(2015))cout << "Test 6: success \n";
		else cout << "Test 6: failed \n";

	//eventos
	cout << "eventos \n";
	evento c1(a1,a2);
	evento c2(a3,a4);
	if(!(eventos_sobrepostos(&c1,&c2)))cout << "Test 7: success \n";
	else cout << "Test 7: failed \n";
	if(eventos_sobrepostos(&c1,&c1))cout << "Test 8: success \n";
		else cout << "Test 8: failed \n";

	// calendario
	cout << "calendario\n";
	Data e1(1,1,1993);
	Data e3(1,1,3000);

	Calendario jota(e1,e3);
	if(jota.adiciona_evento(&c1))cout << "Test 9: success \n";
	else cout << "Test 9: failed \n";
	if(!(jota.adiciona_evento(&c1)))cout << "Test 9: success \n";
	else cout << "Test 9: failed \n";
	if(jota.adiciona_evento(&c2))cout << "Test 10: success \n";
		else cout << "Test 10: failed \n";
	if(jota.remove_evento(&c1))cout << "Test 11: success \n";
	else cout << "Test 11: failed \n";
	if(!(jota.remove_evento(&c1)))cout << "Test 12: success \n";
		else cout << "Test 12: failed \n";
	return 0;
}
