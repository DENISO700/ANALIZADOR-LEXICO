#include<iostream>
//Agregue librerias si es necesario
using namespace std;

# define max 10

//Escriba los prototipos de las funciones LeerArreglo, EscribirArreglo y Analisis

void LeerArreglo(int A[],int  tamA);
void Analisis(int A[],int  tamA,int B[],int tamB, char MayorEn[]);
void EscribirArreglo(int array[], int n);

int main( ) {
	
	int A[max], B[max],  tamA, tamB;
	char MayorEn[max];
	
	do{
		cout<<"Ingrese cantidad de elementos del arreglo A (maximo 10, min3):  ";
		cin>>tamA;
	}while (tamA>10 || tamA<3);
	cout<<"Ingrese elementos del arreglo A: ";
	LeerArreglo(A, tamA);
	cout<<endl<<endl;
	
	do{
		cout<<"Ingrese cantidad de elementos del arreglo B (maximo 10, min 3):  ";
		cin>>tamB;
	}while (tamB>10 || tamB<3);
	cout<<"Ingrese elementos del arreglo B: ";
	LeerArreglo(B, tamB);
	cout<<endl<<endl;
	
	Analisis(A, tamA, B, tamB, MayorEn);
	cout<<endl<<endl;

	cout<<"\nA: ";
	EscribirArreglo(A, tamA);
	
	cout<<"\nB: ";
	EscribirArreglo(B, tamB);
	
	cout<<"\nMayorEn: ";
	for(int i=0; MayorEn[i]!='\0';i++)
	cout<<MayorEn[i]<<"  ";
	

	return 0;
}




//Escriba la definición de la función leerArreglo. Esta función lee los elementos de un arreglo de enteros.

void LeerArreglo(int array[],int n){

    for (int j=0; j<n;j++){
       
        cin>>array[j];
     
    }

}


/*Escriba la definición de la función analisis. Esta funcion almacena en el arreglo de caracteres, 
el carácter A o B, según el vector donde se encuentra el número mayor en cada posición, 
en caso que los números en determinada posición sean iguales se almacenará el carácter =.
Recuerde que los arreglos de enteros pueden tener diferente tamaño. Ver Ejemplos.

*/
void Analisis(int A[],int  tamA,int B[],int tamB, char MayorEn[]){
	int mayor = 0;
	
if(tamB > tamA){
	mayor =tamB;
}else if(tamB < tamA){
	mayor =tamA;
}else{
	
	mayor = tamB;
}

MayorEn[mayor];
	
	for (int j=0; j<max-1;j++){
	
	if(A[j] != '\0'){
		
		if(B[j] != '\0'){
			
		if(A[j]==B[j]){
			
       	MayorEn[j] = '=';
       	
	   }else if (A[j] > B[j]){
	   	
	   	  	MayorEn[j] = 'A';
	   }else if (B[j] > A[j] ){
	   	
	   	  	MayorEn[j] = 'B';
	   }
	   
	}else{
			MayorEn[j] = 'A';
		}

	}else{
			MayorEn[j] = 'B';
}	
			
		
       
    }
    
    
	
	
}

/*Escriba la definición de la funcion EscribirArreglo. Esta función escribe los elementos
de un arreglo de enteros con una separación de dos espacios entre ellos.
*/
void EscribirArreglo(int array[], int n) {
   
   int fila=0;
  
    for( fila=0;fila<n;fila++) {
    
     cout<<array[fila]<<"  ";
              
    }
}



