
/* PROYECTO ANALIZADOR LEXICO  GRUPO 6

%INTEGRANTES:
	Keren Eunice Ramos Sauceda 20161002793
	Lesly Mabely Argueta Aguilar 20142030185
	Deiby Benigno Lopez Ramirez  20151030486
	Cristhopher Isaac Andino Garmendia 20151003402
	Denis Alejandro Ordoñez Sevilla 20171002520
ATENCION AL CLIENTE
SI TIENE ALGUN PROBLEMA MANDE WHATSAPP A +504 8996-0147 PREGUNTE POR DENIS ORDOÑEZ 


       ######CONSIDERACIONES DE USO######
  
 1).El archivo a usar debe llamarse test.txt.
 2).Cada palabra debe ir seprada por espacios, en el codifo fuente de prueba.
 3).Al inicio de cada cambio de linea debe ir un espacio.
 
 ****EJEMPLO****
 
 mientras ( i = 9 ) {
 
	}
	
	operar - 4 / + 5
	
	declare test as decimal = + 12.45 

 	
*/

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
bool operaciones();
bool interruptor();
bool interruptorCaso();
bool imprimir();
bool leer();
bool comentar();
bool asignacion();
bool analisisS();
	
	char *token;
	 string test;
	string dividido;
	string texto;
	
	char converso[200];
	
	
	string TablaSimbolos[21] = {"mientras","si","sino","para","as","interruptor","leer","imprimir","operar","declare","decimal","booleano","caracter","entero","cadena","asignar","##","caso","descanso","defecto"};
	
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
  
  
   
   test="' hola '";
   
  
    cout<<"\n\t\t\t***** Resultados del Analisis *****\n";
   	analisisS();
   
    //imprimir();

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
							 		cout<<"\n\tEstructura de Repeticion While Aceptada\n";
							 		
								 	contador++;
								     
								 	//revisa si hay mas estructuras debajo
								 
										 	if(buffer[contador]=="mientras"|| buffer[contador]=="para"||buffer[contador]=="si" ||buffer[contador]=="interruptor"||buffer[contador]=="imprimir"||buffer[contador]=="leer"||buffer[contador]=="operar"||buffer[contador]=="asignar"||buffer[contador]=="declare" ){
											//Realiza la busqueda recursiva de estructuras
												
											
											analisisS();	
						
											}else{
											
											 contador++;
											return true;	
											}
				 
							 }	else{
							 	cout<<"\n\tError de sintaxis se esperaba llave de cierre de bloque";
									contador++;
									return false;
							 }
								}else{
					
									contador++;
									//verifica llave de cierre
									if(buffer[contador]=="}"){
									cout<<"\n\tEstructura condicional mientras aceptada";
									contador++;
															
									}else{
									cout<<"\n\tError de sintaxis se esperaba llave de cierre de bloque";
									contador++;
									return false;							
				                   }
					
					
				}
		        	
		        
			}else{
				cout<<"Error de Sintaxis se esperaba llave de inicio de bloque";
				contador++;
				return false;
			}
		}else{
			cout<<"Error de sintaxis se esperaba un operador relacional";
			contador++;
			return false;
		}
	}else{
		cout<<"Error de Sintaxis se esperaba una cadena valida";
		contador++;
		return false;
	}
}else{
		cout<<"Error de Sintaxis se esperaba ( de apertura para la condicion";
		contador++;
		return false;
	}
	
	
}

//condicionales
bool si(){
	contador++;
	palabra=buffer[contador];
		cout<<"\n\tEstructura Condicional "<<buffer[contador-1]<<" encontrada "<<endl;
	//verifica que este el parentesis de apertura
	if(palabra=="("){
			contador++;	
			
			if(cadena(buffer[contador])){
				contador++;
			//verifica que este el operador relacional para la condicion
			if(buffer[contador]=="<"||buffer[contador]==">"||buffer[contador]=="="||buffer[contador]=="!="){
				contador++;
				//verifica sil otro lado de la igualdad es valido 
				if(cadena(buffer[contador])||numero(buffer[contador])){
						contador++;
						//verifica si se agrega el parentesis de cierre de la condicion 
						if(buffer[contador]==")"){
							contador++;
							//Verifica si se agrega la llave de apertura de bloque
							if(buffer[contador]=="{"){
								contador++;
								
								//verifica si hay algo en el bloque
								if(buffer[contador]=="mientras"|| buffer[contador]=="para"||buffer[contador]=="si" ||buffer[contador]=="interruptor"||buffer[contador]=="imprimir"||buffer[contador]=="leer"||buffer[contador]=="operar"||buffer[contador]=="asignar"||buffer[contador]=="declare" ){
									cout<<"\n\tEstructura "<<buffer[contador]<<" anidada \n"<<endl;
									analisisS();
									
								}else{
								
									//verifica si existe la llave de cierre
									if(buffer[contador]=="}" ){
										contador++;
										cout<<"\n\tEstructura condicional Si aceptada";
										contador++;
										return true;
										
									}else{
										//verifica si es un sino 
										if(buffer[contador]=="}" and buffer[contador+1]=="sino"){
											contador++;
											contador++;
											//verifica llave de apertura del sino 
											
											if(buffer[contador]=="{"){
												contador++;
												//verificar si hay mas estructuras
		
													if(buffer[contador]=="mientras"|| buffer[contador]=="para"||buffer[contador]=="si" ||buffer[contador]=="interruptor"||buffer[contador]=="imprimir"||buffer[contador]=="leer"||buffer[contador]=="operar"||buffer[contador]=="asignar"||buffer[contador]=="declare" ){
														cout<<"\n\tEstructura "<<buffer[contador]<<" anidada \n"<<endl;
														
														analisisS();
									                     contador++;
														}else{
															contador++;
															//verifica llave de cierre
															if(buffer[contador]=="}"){
																cout<<"\n\tEstructura condicional SiNo aceptada";
															contador++;
															
															}else{
																
																cout<<"\n\tError de sintaxis se esperaba llave de cierre de bloque";
																contador++;
																return false;
																
																
															}
												
															}
												
											}else{
												
												cout<<"\n\tError de sintaxis se esperaba llave de inicio de bloque";
												contador++;
												return false;
												
												
											}
											
											
										}else{
											cout<<"\n\tError de sintaxis se esperaba llave de cierre de bloque";
											contador++;
											return false;
											
										}
										
									}
									
									
								}
								
							}else{
								cout<<"\n\tError de sintaxis se esperaba llave de apertura de bloque";
								contador++;
								return false;	
							}
		
						}else{
							cout<<"\n\tError de sintaxis se esperaba un valor valido para comparar";
							contador++;
							return false;					
						}
	
				}else{
					cout<<"\n\tError de sintaxis se esperaba un valor valido para comparar";
					contador++;
					return false;
				}
				
				
				
			}else{
			cout<<"\n\tError de sintaxis se esperaba un operador relacional";
			contador++;
			return false;	
				
			}
			
			}else{
				cout<<"\n\tCadena invalida para una variable";
			contador++;
			return false;
				
			}
		
		
	}else{
		
		cout<<"\n\tError sintaxis falta el caracter (";
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
		       cout<<buffer[contador]<<endl;
            	if(analisisS()){
            	 contador++;
				
				 if(buffer[contador]=="}"){
				 
				 
				       
				 		cout<<"\n\tEstructura de Repeticion Para aceptada\n ";
						contador++;
						
							if(buffer[contador]=="mientras"|| buffer[contador]=="para"||buffer[contador]=="si" ||buffer[contador]=="interruptor"||buffer[contador]=="imprimir"||buffer[contador]=="leer"||buffer[contador]=="operar"||buffer[contador]=="asignar"||buffer[contador]=="declare" ){
											//Realiza la busqueda recursiva de estructuras	
								analisisS();	
						
							}else{
												
								
								return true;	
								}
				 	
				 
				 	
				 }else{
				 	cout<<"Error de Sintaxis se esperaba } como operador de cierre";
					contador++;
					return false;
				 
				 }
			   }else{
			   	
			   	cout<<"No hay Estructuras anidadas ";
				contador++;
				return false;
			   
			   }
		        	
		        
			}else{
				cout<<"Error de Sintaxis se esperaba operadores de cierre";
				contador++;
				return false;
			}
		}else{
			cout<<"\n\tError de Sintaxis argumentos no validos";
			contador++;
			return false;
		}
	}else{
		cout<<"\n\tError de Sintaxis cadena no valida";
		contador++;
		return false;
	}
}else{
		cout<<"\n\tError de Sintaxis se esperaba ( de apertura";
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
		
	}else if(palabra == "imprimir"){
		
		if(imprimir()){
		
			return true;
		}else {
			return false;
		}
		
	}else if(palabra == "leer"){
		
		if(leer()){
		
			return true;
		}else {
			return false;
		}
		
	}else if(palabra == "asignar"){
		
		if(asignacion()){
			
	
			return true;
		}else {
			return false;
		}
		
	}else if(palabra == "interruptor"){
		
		if(interruptor()){
			
			return true;
		}else {
			return false;
		}
		
	}else if(palabra == "operar"){
		
		if(operaciones()){
			
			return true;
		}else {
			return false;
		}
		
	}else if(palabra == "##"){
		
		if(comentar()){
			
			return true;
		}else{
			return false;
		}
		}
	else{
		 cout<<"\n\tprobandooo "<<buffer[contador--]<<"\n";
	while(palabra !="para"&&palabra !="si"&&palabra !="mientras"&&palabra !="asignar"&&palabra !="}"&&palabra !="imprimir"&&palabra !="leer"&&palabra !="operar"&& contador<tamanioBuffer){
	    contador++;
	    palabra=buffer[contador];
	    cout<<"\n\tpalabra no declarada correctamente "<<buffer[contador]<<"\n";
		}contador--;
		
		return false;}
		
	
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
									if(buffer[contador]=="mientras"|| buffer[contador]=="para"||buffer[contador]=="si" ||buffer[contador]=="interruptor"||buffer[contador]=="imprimir"||buffer[contador]=="leer"||buffer[contador]=="operar"||buffer[contador]=="asignar"||buffer[contador]=="declare" ){
											//Realiza la busqueda recursiva de estructuras	
											analisisS();	
						
											}else{
												
											    contador--;
												cout<<"\n\tDeclaracion correcta de la variable "<<palabra<<endl;
												return true;	
											}
								
								
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
							
						//verifica que el numero tenga signo							
							if(buffer[contador]=="+"|| buffer[contador]=="-" ){
									contador++;
							//verifica el numero tenga parte decimal 
							if(decimales(buffer[contador])){
								contador++;
									if(buffer[contador]=="mientras"|| buffer[contador]=="para"||buffer[contador]=="si" ||buffer[contador]=="interruptor"||buffer[contador]=="imprimir"||buffer[contador]=="leer"||buffer[contador]=="operar"||buffer[contador]=="asignar"||buffer[contador]=="declare" ){
											//Realiza la busqueda recursiva de estructuras	
											analisisS();	
						
											}else{
												cout<<"\n\tAsignacion aceptada en la variable  "<<palabra<<endl;
												return true;	
											}
								
								
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
									if(buffer[contador]=="mientras"|| buffer[contador]=="para"||buffer[contador]=="si" ||buffer[contador]=="interruptor"||buffer[contador]=="imprimir"||buffer[contador]=="leer"||buffer[contador]=="operar"||buffer[contador]=="asignar"||buffer[contador]=="declare" ){
											//Realiza la busqueda recursiva de estructuras	
											analisisS();	
						
											}else{
												cout<<"\n\tAsignacion aceptada en la variable  "<<palabra<<endl;
												return true;	
											}
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
								
								
								//verificar mas estreucturas abajo
								
									contador++;
									if(buffer[contador]=="mientras"|| buffer[contador]=="para"||buffer[contador]=="si" ||buffer[contador]=="interruptor"||buffer[contador]=="imprimir"||buffer[contador]=="leer"||buffer[contador]=="operar"||buffer[contador]=="asignar"||buffer[contador]=="declare" ){
											//Realiza la busqueda recursiva de estructuras	
											analisisS();	
						
											}else{
												cout<<"\n\tAsignacion aceptada en la variable  "<<palabra<<endl;
												return true;	
											}
								
								
								
								
								
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


//verifica la sintaxis de impresion en pantalla
bool imprimir(){
	
	contador++;
	palabra=buffer[contador];
	cout<<"\n\t nota:asegurese de poner $ al inicio y final, si no lo reconocera todo como impresion \n"<<endl;
	if(palabra == "$"){
		contador++;
		while(buffer[contador] != "$"){
			
			contador++;
			
		}
		
		
	  cout<<"\tImpresion  exitosa "<<endl;
		
			contador++;
		
		if(buffer[contador]=="mientras"|| buffer[contador]=="para"||buffer[contador]=="si" ||buffer[contador]=="interruptor"||buffer[contador]=="imprimir"||buffer[contador]=="leer"||buffer[contador]=="operar"||buffer[contador]=="asignar"||buffer[contador]=="declare" ){
							
									//Realiza la busqueda recursiva de estructuras	
									
								analisisS();	
						
							}else{
								contador--;		
								//acepto porque no habias mas estructuras debajo
							    
							return true;	
								}
	
	}else{
		
		contador++;
		cout<<"\n\tSe esperaba un indicador de inicio de impresion"<<palabra<<endl;
		
		return false;
		
	}
	
}


//funciona para ller valores 
bool leer(){
	
		contador++;
	palabra=buffer[contador];
	
	if(palabra == "%"){
		
		contador++;
		while(buffer[contador] != "%"){
			
			contador++;
			
		}
		
			cout<<"\tLectura  exitosa "<<endl;
			contador++;
			cout<<"\tLectura  exitosa "<<buffer[contador];
		
		if(buffer[contador]=="mientras"|| buffer[contador]=="para"||buffer[contador]=="si" ||buffer[contador]=="interruptor"||buffer[contador]=="imprimir"||buffer[contador]=="leer"||buffer[contador]=="operar"||buffer[contador]=="asignar"||buffer[contador]=="declare" ){
								
									//Realiza la busqueda recursiva de estructuras	
									
								analisisS();	
						
							}else{	
								//acepto porque no habias mas estructuras debajo
							    contador--;
							return true;	
								}
		
	
	
		
		
	}else{
		
		contador++;
		cout<<"\n\tSe esperaba un indicador de inicio de lectura"<<palabra<<endl;
		return false;
		
	}
	
	
	
}

//funcion para verificar asignacion de valores 
bool asignacion (){
	
	contador++;
	palabra=buffer[contador];
	
	if(cadena(palabra)){
		
		contador++;
		if(buffer[contador]=="="){
			
			contador++;
			
			if(buffer[contador]=="("){
				
				while(buffer[contador] != ")"){
					
							
					contador++;
			
					}
					
		        	contador++;
					if(buffer[contador+1]=="mientras"|| buffer[contador]=="para"||buffer[contador]=="si" ||buffer[contador]=="interruptor"||buffer[contador]=="imprimir"||buffer[contador]=="leer"||buffer[contador]=="operar"||buffer[contador]=="asignar"||buffer[contador]=="declare" ){
							//Realiza la busqueda recursiva de estructuras	
					
						analisisS();	
						
							}else{
								cout<<"\n\tAsignacion aceptada en la variable  "<<palabra<<endl;
								return true;	
							}	
					
				
				
			}else{
				
				cout<<"\n\tSe esperaba el delimitador del valor"<<buffer[contador]<<endl;
				contador++;
				return false;
				
			}
			
			
			
			
		}else{
			
		cout<<"\n\tSe esperaba el operador de asignacion"<<buffer[contador]<<endl;
		contador++;
		return false;	
			
		}
		
		
	}else{
		
		contador++;
		cout<<"\n\tSe esperaba un nombre de variable valido"<<palabra<<endl;
		return false;
		
		
	}
	
	
}

//funcion verificadora de la estructura del interurptor

bool interruptor(){

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
		if(buffer[contador]==")"&&buffer[contador+1]=="{"){
			
			contador++;
			
			//si encuentra parentesis y luego cadena la acepta
			if(buffer[contador+1]=="caso"&&(numero(buffer[contador+2])||cadena(buffer[contador+2]))&&buffer[contador+3]==":"&&buffer[contador+4]=="descanso"){
				
								contador += 5;
								     
								 	//revisa si hay mas estructuras debajo
								 
							 	if(buffer[contador]=="mientras"|| buffer[contador]=="para"||buffer[contador]=="si" ||buffer[contador]=="interruptor"||buffer[contador]=="imprimir"||buffer[contador]=="leer"||buffer[contador]=="operar"||buffer[contador]=="asignar"||buffer[contador]=="declare" ){
								//Realiza la busqueda recursiva de estructuras
										analisisS();	
						
											}else{
											if(buffer[contador]!="}"){
            	                                 
							            	 	if(interruptorCaso()){
							            	 		contador++;
							            	 		if(buffer[contador]=="}"){
											 	
											 	cout<<"\n\t Estructura de seleccion del interruptor fue aceptada";
										     	return true;
											 	
											 	
											 }	
												 }
											 }
											 
											 else if(buffer[contador]=="}"){
											 	
											 	cout<<"\n\t Estructura de seleccion del interruptor fue aceptada";
										     	return true;
											 	contador++;
											 	
											 }	else{
											 	return false;
											 }
											 	
											}
            	
            	 
            	 
				 
			   }else{
			   	cout<<"rechazada por mala declaracion de caso";
			   	return false;
		      	
			
			
	}
}else{
		cout<<"no aceptada por falta de ')' o '{' en interruptor";
		contador++;
		return false;
	}
	
	
} else{
	
		cout<<"nombre variable no valida en declaracion interruptor";
		contador++;
		return false;
}
}else{
cout<<"no aceptada por falta de '(' en interruptor";
		contador++;
		return false;
}
}

bool interruptorCaso(){
	int bandera = true;
	
	while(bandera){
	
		if(buffer[contador]=="caso"&&numero(buffer[contador+1])&&buffer[contador+2]==":"&&buffer[contador+3]=="descanso"){
		contador+=3;
		bandera = false;
		return true;
		}else if(buffer[contador]=="defecto"&&buffer[contador+1]==":"&&buffer[contador+2]=="descanso"){
			
			contador+3;
			bandera = false;
			return true;
						
		}else{
			
			bandera = false;
			
		}
		
	}
		
}


//funcion para operaciones aritmeticas

bool operaciones(){
	

	contador++;
	palabra=buffer[contador];
	//verifica que lleve signo
	if(buffer[contador] == "+" || buffer[contador] == "-"){
		contador++;
		//verifica que sea un numero 
			if(numero(buffer[contador])){
					contador++;
					//verificamos el operador aritmetico
					if(buffer[contador] == "+" || buffer[contador] == "-" || buffer[contador] == "*" || buffer[contador] == "/"){
					   contador++;
					   
					   //verificamos el signo del segundo numero 
					   
					   	if(buffer[contador] == "+" || buffer[contador] == "-"){
							contador++;
					   
					   	if(numero(buffer[contador])){
					   		cout<<"\n\t Operacion arismetica Exitosa"<<endl;
					   		contador++;
				         
				         	
				         	if(buffer[contador]=="mientras"|| buffer[contador]=="para"||buffer[contador]=="si" ||buffer[contador]=="interruptor"||buffer[contador]=="imprimir"||buffer[contador]=="leer"||buffer[contador]=="operar"||buffer[contador]=="asignar"||buffer[contador]=="declare" ){
								
									//Realiza la busqueda recursiva de estructuras	
										
								analisisS();	
						
							}else{
								 contador--;
 	
								//acepto porque no habias mas estructuras debajo
							    
							return true;	
								}
					      
						
							
								
			        		}else{
						    contador++;
							cout<<"\n\tSe esperaba un numero "<<palabra<<endl;
							return false;
								
							}
						
					}else{
					
						contador++;
						cout<<"\n\tSe esperaba un signo "<<endl;
						return false;
					}
					 	
						
					}else{
						
					  contador++;
				 	  cout<<"\n\tSe esperaba un operador aritmetico "<<palabra<<endl;
					  return false;
								
						
						
					}			
								
				}else{
					contador++;
					cout<<"\n\tSe esperaba un numero "<<palabra<<endl;
					return false;
								
				}
		
		
		
	}else{
		
			contador++;
			cout<<"\n\tSe esperaba un signo "<<endl;
			return false;
		
		
	}	
	
	
	
	
	
}

//funciona para ller valores 
bool comentar(){
	
		contador++;
	palabra=buffer[contador];
	
		cout<<"\n\tNota: asegurese de terminar comentario ## sino detectara todo como comentario";
		contador++;
		while(buffer[contador] != "##"){
			
			contador++;
			
		}
		
			cout<<"\n\t Comenteario  exitoso "<<endl;
			contador++;
		
		if(buffer[contador]=="mientras"|| buffer[contador]=="para"||buffer[contador]=="si" ||buffer[contador]=="interruptor"||buffer[contador]=="imprimir"||buffer[contador]=="leer"||buffer[contador]=="operar"||buffer[contador]=="asignar"||buffer[contador]=="declare" ){
								
									//Realiza la busqueda recursiva de estructuras	
									
								analisisS();	
						
							}else{	
								//acepto porque no habias mas estructuras debajo
							    contador--;
							return true;	
								}
	
	
	
}


