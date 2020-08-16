#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

//prototipos de las funciones 
void lectura();
void tokens();
bool mientras();
bool declaracion();
bool cadena(string p);
bool caracter(string p);
bool numero(string p);
bool decimales(string p);
bool analisisS();
	
	char *token;
	
	string dividido;
	string texto;
	
	char converso[200];
	
	string TablaSimbolos[16] = {"mientras","si","sino","para","as","interruptor","leer","imprimir","operar","declare","decimal","booleano","caracter","entero","cadena"};
	
    int contador;
    
	//arreglo para comparar
	string buffer[200];
	string palabra;
	//tamaño del buffer
	int tamanioBuffer = 0;
	
	enum TEstado { qO,q1,q2,q3,q4,qe};

TEstado Estado;

int main(){
	
	 cout<<"\n\t\t\t * * * * * Codigo Fuente * * * * * \n\n";
	lectura();
	
	 cout<<"\n\t\t\t***** Lista de Palabras Reservadas *****\n";
	tokens();
  
   string test;
   
   test="+2.5";
   
  
    cout<<"\n\t\t\t***** Resultados del Analisis *****\n";
   analisisS();
   
    //decimales(test);

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
	

	while(!archivo.eof()){
		
		getline(archivo,texto,'\n');
			
		for(i =0;i<texto.size();i++){
			
		 converso[k]=texto[i];	
		
		 //acumula la ultima posicion en el salto de liena
		 k++;
		 	
		}
		
		converso[k]=' ' ;
		 k++;
		cout<<"\t"<<texto<<endl<<endl;;
	}
	archivo.close();
}



//tokenizador de la cadena ingresada
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


//ciclos mientras
bool mientras(){
	contador++;
	palabra=buffer[contador];
	//si encuentra parectesis avanza
	if(palabra=="("){
		contador++;
	palabra=buffer[contador];
	// si encuentra una cadena avanza
	if(cadena(palabra)){
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
	               	// busca } si lo encuentra lo acepta
							 if(buffer[contador]=="}"){
								 	contador++;
								 	cout<<"\n\tcadena del mientras fue aceptada\n";
								 	//revisa si hay mas estructuras debajo
										 	if(buffer[contador]=="mientras"|| buffer[contador]=="para"||buffer[contador]=="si"){
											//Realiza la busqueda recursiva de estructuras	
											analisisS();	
						
											}else{
												
												//acepto porque no habias mas estructuras debajo
												cout<<"cadena  aceptada";
												return true;	
											}
				 
							 }	else{
							 		cout<<"cadena no aceptada";
							 		contador++;
							 		return false;
							 }
				}
		        	
		        
			}else{
				cout<<"cadena no aceptada";
				contador++;
				return false;
			}
		}else{
			cout<<"cadena no aceptada";
			contador++;
			return false;
		}
	}else{
		cout<<"cadena no aceptada";
		contador++;
		return false;
	}
}else{
		cout<<"cadena no aceptada";
		contador++;
		return false;
	}
	
	
}

//condicionales
bool si(){
	contador++;
	palabra=buffer[contador];
	//si encuentra parectesis avanza
	if(palabra=="("){
		contador++;
	palabra=buffer[contador];
	// si encuentra una cadena avanza
	if(cadena(palabra)){
	
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
               	 // busca } si lo encuentra lo acepta
				 if(buffer[contador]=="}"){
				 //busca la condicional sino despues del corchete de cierre del si
				 	if(buffer[contador+1]=="sino" ){
				 		
				 		if(buffer[contador+2]=="{"){
				 			  contador++;contador++;contador++;
		       				 //busca si las instrucciones estan correctas
								if(analisisS()){
									contador++;
						
            	 // busca } si lo encuentra lo acepta
				 }
			}
					 if(analisisS()){
				 			contador++;
				 			
						 }else{
						 	cout<<"cadena no  aceptada";
							 contador++;						 	
						 }
					 }else{
					 	contador++;
					 		cout<<"\n\tcadena del Si fue aceptada\n";
					 					 	
					 	if(buffer[contador]=="mientras"|| buffer[contador]=="para"||buffer[contador]=="si"){
						
						analisisS();	
						
						}else{
					
							return true;	
						}
					 	
					 }
					 
				 }	else {
				 	contador++;
				 		cout<<"cadena si fue aceptada";
				 	
				 	return false;
				 }
			   }
		        	
		        
			}else{
				cout<<"cadena no aceptada";
				contador++;
					return false;
			}
		}else{
			cout<<"cadena no aceptada";
			contador++;
			return false;
		}
	}else{
		cout<<"cadena no aceptada";
		contador++;
			return false;
	}
}else{
		cout<<"cadena no aceptada";
		contador++;
		return false;
	}
	
	
}

//ciclos para
bool para(){
	
	contador++;
	palabra=buffer[contador];
	//si encuentra parectesis avanza
	if(palabra=="("){
		contador++;
	palabra=buffer[contador];
	// si encuentra una cadena avanza
	 
	if(cadena(palabra)){
		
		contador++;	
		//si encuentra un caracter logico avanza
		
		if(buffer[contador]=="="&&numero(buffer[contador+1])&&palabra == buffer[contador+2]&&(buffer[contador+3]=="<"||buffer[contador+3]==">"||buffer[contador+3]=="<="||buffer[contador+3]==">=")
		&&(cadena(buffer[contador+4])||numero(buffer[contador+4]))&&buffer[contador+5]==palabra&&buffer[contador+6]=="="&&buffer[contador+7]==palabra&&buffer[contador+8]=="+"
		&&numero(buffer[contador+9])){
			contador += 10;
		  
			
			//si encuentra parentesis y luego cadena la acepta
			if(buffer[contador]==")"&&buffer[contador+1]=="{"){
				contador++;
				
		        //busca si las instrucciones estan correctas
		       
            	if(analisisS()){
            	 contador++;
				
				 if(buffer[contador]=="}"){
				 
				 
				 	cout<<"\n\tcadena del para fue aceptada\n ";
					contador++;
					if(buffer[contador]=="mientras"|| buffer[contador]=="para"||buffer[contador]=="si"){
						
					analisisS();	
						
					}else{
					
					return true;	
					}
				 	
				 
				 	
				 }else{
				 	return false;
				 }
			   }
		        	
		        
			}else{
				cout<<"cadena no aceptada";
				contador++;
				return false;
			}
		}else{
			cout<<"cadena no aceptada";
			contador++;
			return false;
		}
	}else{
		cout<<"cadena no aceptada";
		contador++;
		return false;
	}
}else{
		cout<<"cadena no aceptada";
		contador++;
		return false;
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


//analiza si es numero
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


//busca estructuras dentro de estructuras recursivamente
bool analisisS(){
		//analisis de palabras
	while(contador!=tamanioBuffer){
	// encuentra espacios vacios en el buffer
	while(buffer[contador]==""){
		contador++;
		
	}

	palabra=buffer[contador];
	
	if(palabra=="mientras"){
		if(mientras()){
		
			return true;
		}else {
			return false;
		}
		
	}else if(palabra == "si") {
		
		if(si()){
		
			return true;
		}else {
			return false;
		}
		
	}else if(palabra == "para"){
		
		if(para()){
		
			return true;
		}else {
			return false;
		}
		
	}else if(palabra == "declare"){
		
		if(declaracion()){
		
			return true;
		}else {
			return false;
		}
		
	}else{
	while(palabra !="para"&&palabra !="si"&&palabra !="mientras"&&palabra !="}"){
	    contador++;
	    palabra=buffer[contador];
	
		}contador--;
		return true;}
		
	
	contador++;
}
}


//analiza las declaraciones de variable
bool declaracion(){
	
	contador++;
	palabra=buffer[contador];
	
	int TamanioArreglo = sizeof TablaSimbolos/sizeof TablaSimbolos[0];
	int h;	
	
	//verifica que el nombre de la variable a declarar no sea una palabra reservada
		for(h=0;h<TamanioArreglo;h++){
			
			if(palabra.compare(TablaSimbolos[tamanioBuffer])==0){
				cout<<"\n\tSentencia Reservada para el sistema "<<palabra<<endl;
				return false;
			break;
			}
		}
	
	//verifica que el nombre no sea un numero 	
	if(!numero(palabra)){
		contador++;
		//verifica que reciba la clausula para asignacion
		if(buffer[contador]=="as"){
				contador++;
				//verifica si el tipo de dato es valido
			if(buffer[contador]=="entero"|| buffer[contador]=="decimal"||buffer[contador]=="booleano"|| buffer[contador]=="cadena"|| buffer[contador]=="caracter"){
				contador++;
				
				if(buffer[contador]=="="){
						contador++;
						
						//verifica se reciba numeros enteros para este tipo de dato
						if(buffer[contador-2]=="entero"){
							
							//verifica se le asigne signo al numero dado 
							if(buffer[contador]=="+"|| buffer[contador]=="-" ){
								contador++;
								//verifica que reciba un numero correctamente 
								if(numero(buffer[contador])){
								contador++;
								cout<<"\n\tAsignacion aceptada en la variable  "<<palabra<<endl;
								return true;
								
							}else{
								contador++;
								cout<<"\n\tSe esperaba un entero para la variable "<<palabra<<endl;
								return false;
								
							}
								
								
							}else{
								contador++;
								cout<<"\n\tSe esperaba un signo "<<endl;
								return false;
								
							}
							
						
							
						//se verifica que se reciban numeros con punto decimal correctamente	
						}else if(buffer[contador-2]=="decimal"){
							
							cout<<"\n\tTesteo "<<buffer[contador-2]<<endl;
							
							if(buffer[contador]=="+"|| buffer[contador]=="-" ){
									contador++;
							//verifica el numero tenga parte decimal 
							if(decimales(buffer[contador])){
								contador++;
								cout<<"\n\tAsignacion aceptada"<<palabra<<endl;
								return true;
								
							}else{
								contador++;
								cout<<"\n\tSe esperaba un numero decimal para la variable "<<palabra<<endl;
								return false;
								
							}	
								
								
							}else{
								
								contador++;
								cout<<"\n\tSe esperaba un signo "<<endl;
								return false;
							}
							
							
							
						}else if(buffer[contador-2]=="booleano"){
							
							
							//verifica que el valor sea booleano 
							if(buffer[contador]=="verdadero" || buffer[contador]=="falso"  ){
								contador++;
								cout<<"\n\tAsignacion aceptada "<<palabra<<endl;
								return true;
								
							}else{
								contador++;
								cout<<"\n\tSe esperaba un valor Booleano "<<palabra<<endl;
								return false;
								
							}
							
							
						}else if(buffer[contador-2]=="cadena"){
							
							
							//verifica que el valor sea una cadena valida de caracteres
							if(cadena(buffer[contador])){
								contador++;
								cout<<"\n\tAsignacion aceptada "<<palabra<<endl;
								return true;
								
							}else{
								contador++;
								cout<<"\n\tSe esperaba una Cadena de caracteres "<<palabra<<endl;
								return false;
								
							}
							
							
						}else if(buffer[contador-2]=="caracter"){
							
							
							//verifica si es un caracter del lenguaje 
							if(caracter(buffer[contador])){
								contador++;
								cout<<"\n\tAsignacion aceptada "<<palabra<<endl;
								return true;
								
							}else{
								contador++;
								cout<<"\n\tSe esperaba un Caracter valido del lenguaje "<<palabra<<endl;
								return false;
								
							}
							
							
						}else {
								contador++;
								cout<<"\n\tSe esperaba operador de asignacion"<<palabra<<endl;
								return false;
							
						}
					
					
				}else{
					contador++;
					cout<<"\n\tSe esperaba operador de asignacion"<<palabra<<endl;
					return false;
					
				}
			}else{
			
			contador++;
			cout<<"\n\tTipo de dato no Valido"<<palabra<<endl;
			return false;	
				
			}
			
			
			
		}else{
			contador++;
			cout<<"\n\tAsignacion Incorrecta "<<palabra<<endl;
			return false;
			
		}
		
		}else{
			contador++;
			cout<<"\n\tDeclaracion Incorrecta "<<palabra<<endl;
			return false;
		
	}
	
	
}

//verifica numeros con puntos decimales
bool decimales(string p){
	
	
	int i =0;
	Estado = qO;
	int longitud;
	
	longitud= p.size();
	
while (longitud > i and Estado !=qe){
	
	int Simbolo;
	Simbolo = p[i];
	
	
	
	switch(Estado){
		
		case qO:
				if(Simbolo>='0' && Simbolo <= '9'){
					Estado= q1;
		
				}else{
					
				Estado=qe;	
				}
		   		break;
		case q1:
				if(Simbolo>='0' && Simbolo <= '9'){
					Estado= q1;
		
				}else{
					if(Simbolo =='.'){
					Estado= q2;
		
					}else{
						Estado=qe;
					}
				}
		    	break;
		case q2:
				if(Simbolo>='0' && Simbolo <= '9'){
					Estado= q3;
		
				}else{
					Estado=qe;	
				}
		   		break;
        case q3:
				if(Simbolo>='0' && Simbolo <= '9'){
					Estado= q3;
		
				}else{
					Estado=qe;	
				}
		   		break;
			
	}
	
		i++;	
	}

		if(Estado==q3){
		
	
		return true;
			
		}else{
			
			return false;
		}
	
}


//verifica si son caracteres validos dentro del lenguaje
bool caracter( string p){
	int w =0;
	while(w<p.size()){
	
	if(p[w]>='a' && p[w] <= 'z'||p[w]>= 'A' && p[w] <= 'Z'||p[w] == '!' ||p[w] == '@'||p[w] == '%'||p[w] == '&'||p[w] == '_'||p[w] == '?' ||p[w] == '<'||p[w] == '>'||p[w] == ':'||p[w] == '['||p[w] == ']'){
			return true;
		
			}else{
				return false;
			}
		    w++;
			
	}	
	
	
	
}


