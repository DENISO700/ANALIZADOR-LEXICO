

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

void lectura();
//test
void tokens();

	string texto;
	
	char converso[200];
	
	char *token;
	
	string dividido;
	
	
	string TablaSimbolos[10] = {"mientras","si","sino","para","as","(",")","{","}"};

int main(){
	
	lectura();

	


enum TEstado { qO,q1,qe};

TEstado Estado;

string cadena;

int Simbolo;

bool EsNumero;

char codigo[500];




int i;
int longitud;

i= longitud=0;

Estado = qO;

EsNumero = false;



longitud = texto.size();

while (longitud > i and Estado != qe){
	
	Simbolo = texto[i];
	
	EsNumero= (Simbolo>= '0' && Simbolo <= '9');
	
	switch(Estado){
		
		case qO:
			if(Simbolo>='a' && Simbolo <= 'z' || Simbolo == ' '){
			Estado= q1;
		
			}
		    break;
		case q1:
			if(Simbolo>='a' && Simbolo <= 'z'|| Simbolo == ' ' ){
			Estado= q1;
		
			}else{
				Estado=qe;
			}
		    break;
			
	}
	
	i++;

}

if(Estado==q1){
	
	cout<< "Cadena Aceptada\n"<<endl;
	
	tokens();
	
}else{
	cout<< "\nCadena no Valida\n"<<endl;
}

return 0;
}


//funcion para leer el archivo txt.
void lectura(){
	
	ifstream archivo;

	archivo.open("test.txt",ios::in);
	
	if(archivo.fail()){
		cout<<"Nose pudo abrir el archivo"<<endl;
		exit(1);
	}
	
	int i=0;
	while(!archivo.eof()){
		
		getline(archivo,texto);
			
		for(int i =0;i<texto.size();i++){
			
		 converso[i]=texto[i];	
			
		}
	
	}
	
	cout<<"El codigo fuente es:\n\n";
	
		cout<<converso<<endl<<endl;;
	
	
	archivo.close();
}



//Funcion para tokenizar
void tokens(){
	
	int j = 0;
	token = strtok(converso," ");
	
	while(token){
		
		dividido = token;
		
		int TamanioArreglo = sizeof TablaSimbolos/sizeof TablaSimbolos[0];
		for(j=0;j<TamanioArreglo;j++){
			
			if(dividido.compare(TablaSimbolos[j])==0){
				cout<<"Palabra Reservada "<<dividido<<endl;
			break;
			}
		}
		
		j++;
		
		token = strtok(NULL," ");
		
	}
	
	
}









