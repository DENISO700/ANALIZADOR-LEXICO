#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

void lectura();
void tokens();

	char *token;
	
	string dividido;
	
	string texto;
	char converso[200];
	string TablaSimbolos[10] = {"mientras","si","sino","para","as"};

//arreglo para comparar
string buffer[200];

//tamaño del buffer
int tamanioBuffer = 0;

int main(){
	
	lectura();
	
		tokens();
     
enum TEstado { qO,q1,qe};

TEstado Estado;

string cadena;

int Simbolo;

bool EsNumero;


int i;
int longitud;

i= longitud=0;

Estado = qO;

EsNumero = false;

cadena=converso;

longitud = cadena.size();

int test=0;

while (longitud > i and Estado != qe){
	
	Simbolo = cadena[i];
	
	EsNumero= (Simbolo>= '0' && Simbolo <= '9');
	
	switch(Estado){
		
		case qO:
			
			if(buffer[i] != " "){
				
				if(Simbolo >= 'a' and Simbolo <= 'z'){
			
		
				for(int j=0;j<tamanioBuffer;j++) {
				
				if(buffer[i].compare(TablaSimbolos[j])==0){
				cout<<"\n\tPalabra Reservada Test2 "<<i<<endl;
				Estado= q1;
		
			   test=j;
				cout<<"\n\tPalabra Reservada Test2 "<<i<<endl;
				break;
				}
				
				
			}
				
				
			}else{
				Estado= qO;	
					
			}
		
			
		
		
		}else{
			Estado= qO;
		
		}
		break;
		    
		    
		case q1:
			
		
			if(Simbolo>='a' && Simbolo <= 'z'){
			Estado= q1;
		
			}else{
				Estado=qe;
			}
		    break;
			
	}
	
	i++;

}

if(Estado==q1){
	
	cout<< "\tCadena Aceptada"<<endl;
	


}else{
	
	cout<< "\tCadena no Valida"<<endl;
}

	//test buffer almacenado 
	
	cout<<endl;

		for(int k=0;k<tamanioBuffer;k++){
			
		
				cout<<"posicion "<<k<<buffer[k]<<endl;
		
			}
		
	



return 0;
}


//funcion para leer el archivo txt.
void lectura(){
	 
	 system("notepad test.txt");
	ifstream archivo;

	archivo.open("test.txt",ios::in);
	
	if(archivo.fail()){
		cout<<"Nose pudo abrir el archivo"<<endl;
		exit(1);
	}
	
	int i=0;
	
	int control=0;
	
int k;

k=0;
	
	cout<<"\n\tEl codigo fuente es:\n\n";
	while(!archivo.eof()){
		
		getline(archivo,texto,'\n');
			
		for(i =0;i<texto.size();i++){
			
		 converso[k]=texto[i];	
		 
		 
		 //acumula la ultima posicion en el salto de liena
		 k++;
		 	
		}
		
		
		
		cout<<"\t"<<texto<<endl<<endl;;
	}
	
	archivo.close();
}


//funcion token



void tokens(){
	int c= 1;
	token = strtok(converso," ,;");
	
	while(token){
		c++;
		dividido = token;
		
		
		
		int TamanioArreglo = sizeof TablaSimbolos/sizeof TablaSimbolos[0];
		
		for(tamanioBuffer=0;tamanioBuffer<TamanioArreglo;tamanioBuffer++){
			
			if(dividido.compare(TablaSimbolos[tamanioBuffer])==0){
				cout<<"\n\tPalabra Reservada "<<dividido<<endl;
			break;
			}
		}
		
		//cantidad de cubetas ocupoadas del arreglo buffer
		
		token = strtok(NULL," ,;");
	//almacenar palabras para comparar despues
		buffer[c]=dividido;
	  
	}
	tamanioBuffer=c+1;
}
