#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

void lectura();
void tokens();
bool mientras();
bool cadena(string p);
bool numero(string p);
bool analisisS();
	char *token;
	
	string dividido;

	string texto;
	char converso[200];
	string TablaSimbolos[10] = {"mientras","si","sino","para","as"};
    int contador;
//arreglo para comparar
string buffer[200];
string palabra;
//tamaño del buffer
int tamanioBuffer = 0;

int main(){
	
	lectura();
	
		tokens();
     
enum TEstado { qO,q1,qe};

TEstado Estado;



int Simbolo;

bool EsNumero;

    analisisS();

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
bool mientras(){
	contador++;
	palabra=buffer[contador];
	//si encuentra parectesis avanza
	if(palabra=="("){
		contador++;
	palabra=buffer[contador];
	// si encuentra una cadena avanza
	if(cadena(palabra)){
		cout<<"aceptado";
		contador++;	
		//si encuentra un caracter logico avanza
		if(buffer[contador]=="<"||buffer[contador]==">"||buffer[contador]=="="||buffer[contador]=="!="){
			contador++;
			//si encuentra parentesis y luego cadena la acepta
			if(numero(buffer[contador])&&buffer[contador+1]==")"&&buffer[contador+2]=="{"){
				contador++;contador++;contador++;
		        //busca si las instrucciones estan correctas
            	if(analisisS()){
            	 contador++;
            	 cout<<buffer[contador]<<contador;
            	 // busca } si lo encuentra lo acepta
				 if(buffer[contador]=="}"){
				 	cout<<"cadena del mientras fue aceptada";
				 	return true;
				 	contador++;
				 	
				 }	else{
				 	return false;
				 }
			   }
		        	
		        
			}else{
				cout<<"rechazada";
			}
		}else{
			cout<<"cadena no aceptada";
			contador++;
		}
	}else{
		cout<<"no aceptado";
		contador++;
	}
}else{
		cout<<"no aceptada";
		contador++;
	}
	
	
}
//analiza si hay una cadena
bool cadena(string p){
	int w =0;
	while(w<p.size()){
	
	if(p[w]>='a' && p[w] <= 'z'||p[w]>= '0' && p[w] <= '9'){
			return true;
		
			}else{
				return false;
			}
		    w++;
			
	}
}
bool numero(string p){
	int w =0;
	while(w<p.size()){
	
	if(p[w]>= '0' && p[w] <= '9'){
			return true;
		
			}else{
				return false;
			}
		    w++;
			
	}
}
bool analisisS(){
		//analisis de palabras
	while(contador<tamanioBuffer){
	// encuentra espacios vacios en el buffer
	while(buffer[contador]==""){
		contador++;
		
	}
	//cout<<"mirar contador:"<<contador;
	palabra=buffer[contador];
	
	if(palabra=="mientras"){
		if(mientras()){
			cout<<"paso la cadena";
			return true;
		}else {
			return false;
		}
		
	}else{
		return true;
	}
	contador++;
}
}

