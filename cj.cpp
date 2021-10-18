#include <iostream>
#include <stdlib.h>
#include <conio.h> // Para usar 'getch()'
#include <locale.h>
#define MAX 50
using namespace std;


struct fechaNac{ // Maneja las fechas del usuario, asi como el año de creacion
	int dia;
	int mes;
	int anio;
	int anioExpi;
};

struct Cliente{ // Datos del cliente
	char nombre[MAX];
	char apellido[MAX];
	int pin; // contrasenia
	int NPI; // codigo de usuario, se usara para retirar dinero
	struct fechaNac fn;
	
}cl[MAX];

struct Ingresar{ // maneja los datos para ingresar y retirar datos
	double cantidad;
	double sumar; // sumatoria del ingreso de dinero
	double totalD;
	
}ig[MAX];

// Funciones
void menu();
void capturarDatos();
void almacenarDatos();
void procesarDatos();
void consultarDatos();
void imprimirDatos();
void banco(int i); // Administra el ingreso y egreso del dinero
void creditos();

// 	Variables globales
int cont=0; // Conteo en el dato de los usarios, reemplaza a i a grandes rasgos
int start=0; // Si esta en cero, significa que ningun usuario ha sido creado
int DinIngre=0; // Si esta en cero, significa que no se ha realizado ningun retiro
double limite = 5000; // Limite para retirar dinero diario
int anioActual = 2021; // Año del banquero, deicde si la cuenta es invalida o no
double retirar = 0; // El retiro del dinero

int main(){
	setlocale(LC_ALL, "spanish"); // Permite usar "ñ" y acento sin errores
	menu();	
}


void menu(){
	int opc;
	
	do{
		// Un menu simple
		cout<<"\t    ----=== [CAJERO AUTOMATICO] ===----\n"<<endl;
		cout<<"\t\t*************************"<<endl;
		cout<<"\t\t* 1. Crear cliente	*"<<endl;
		cout<<"\t\t* 2. Procesar Datos	*"<<endl;
		cout<<"\t\t* 3. Consultar Datos	*"<<endl;
		cout<<"\t\t* 4. Imprimir Datos	*"<<endl;
		cout<<"\t\t* 5. Creditos		*"<<endl;
		cout<<"\t\t* 6. Salir		*"<<endl;
		cout<<"\t\t*************************"<<endl;
		cout<<"\t\tOpcion: ";
		cin>>opc;
		cout<<endl;
		
		switch(opc){
			
			case 1:
			capturarDatos();
			getch();
			system("cls");
			break;
			
			case 2:
			procesarDatos();
			getch();
			system("cls");
			break;
			
			case 3: 
			consultarDatos();
			getch();
			system("cls");
			break;
			
			case 4: 
			imprimirDatos();
			getch();
			system("cls");
			break;
			
			case 5:
			creditos();
			getch();
			system("cls"); 
			break;
			
			case 6: 
			cout<<"\n\t\tHasta la proxima :D\n";
			exit(0);
			break;
			
			default: cout<<"\t\tError, ingrese otra opcion\n\n";
			getch();
			system("cls");
		}
		
	}while(opc!=6);
	
}

void capturarDatos(){
	// Pedir los datos al usario
	cout<<"\t\t=== DATOS GENERALES ==="<<endl;
	
	cout<<"\t\tIngrese su Nombre: ";		
	cin>> cl[cont].nombre,MAX;
	
	cout<<"\t\tIngrese su Apellido: ";
	cin>> cl[cont].apellido,MAX;
	
	cout<<"\t\tIngrese su pin (4 digitos): ";
	cin>>cl[cont].pin;
	
	if(cl[cont].pin < 999 || cl[cont].pin > 9999 ){ // Limita los digitos de la PIN
		cout<<"\t\tSolo puede tener 4 digitos positivos, intente de nuevo";
		getch();
		system("cls");
		menu();
	}
	
	for(int i = 0;i<cont;i++){
		if(cl[cont].pin == cl[i].pin){ // Permite que los Pines no se repita entre usuarios
			cout<<"\n\t\tError, no se pueden repetir el PIN, intente de nuevo";
			getch();
			system("cls");
			menu();
		}
	}
	
	cout<<"\t\tIngrese su codigo de usuario (4 digitos): ";
	cin>>cl[cont].NPI;
	
	if(cl[cont].NPI < 999 || cl[cont].NPI > 9999 ){ // Limita los digitos del NPI
		cout<<"\n\t\tSolo puede tener 4 digitos positivos, intente de nuevo";
		getch();
		system("cls");
		menu();
	}
	
	for(int i =0;i<cont;i++){
		if(cl[cont].NPI == cl[i].NPI){ // Ya fue planteado
			cout<<"\n\t\tError, no se pueden repetir el NPI";
			getch();
			capturarDatos();
		}
	}
	
	cout<<"\n\t\t=== FECHAS  ==="<<endl;
	
	cout<<"\t\tIngrese el dia: ";
	cin>>cl[cont].fn.dia;
	
	if(cl[cont].fn.dia < 1 || cl[cont].fn.dia > 31){ // Los meses tendran todos 31 dias
		cout<<"\t\t\nInvalido, el mes no tiene "<< cl[cont].fn.dia <<" dias, intente de nuevo";
		getch();
		system("cls");
		menu();
	} 
	
	cout<<"\t\tIngrese el mes (solo numero): ";
	cin>>cl[cont].fn.mes;
	
	if(cl[cont].fn.mes < 1 || cl[cont].fn.mes > 12){ // No existe un 13, verdad?
		cout<<"\t\t\nInvalido, No sabia que el año tiene "<< cl[cont].fn.mes <<" meses, intente de nuevo";
		getch();
		system("cls");
		menu();
	}
	
	cout<<"\t\tIngrese el año: ";
	cin>>cl[cont].fn.anio;
	
	if(cl[cont].fn.anio > anioActual){ //Permite limitar el año de nacimiento a antes del 2021
		cout<<"\n\t\tError, año mayor a 2021, intente de nuevo";
		getch();
		system("cls");
		menu();
	}
	
	
	cout<<"\t\tIngrese el año de la expiracion de su cuenta: "; // Una cuenta expirada no puede retirar dinero, 1 de las 5 condiciones para el retiro
	cin>>cl[cont].fn.anioExpi;
	
	if(cl[cont].fn.anioExpi < anioActual){ // Una cuenta no puede expirar antes del año actual
		cout<<"\t\tError, el año ingresado esta vencido, no se puede realizar la cuenta debe ser menor a "<<anioActual<<"\n\t\tIntente hacer la cuenta de nuevo";
		getch();
		system("cls");
		menu();
	
	}
	
	cout<<"\n\t\tCliente ingresado :D";
	
	cont++;
	start++;
}

void procesarDatos(){
	int pin=0; // Pin ingresado por el usario
	int opc=0; // Opcion del para el switch
	int npi=0; // NPI ingresado por el usario
	int n=3; // Numero de intentos
	
	if(start == 0){
		
		cout<<"\t\tNo hay clientes creados\n\n"; // Si no hay clientes regresa al menu;
	}
	
	else{
		
		cout<<"\t\tIngrese el PIN de su cuenta: ";
		cin>>pin;
		
		for(int i = 0;i<cont;i++){
			if(pin == cl[i].NPI){ // Si el usario se confunde
				cout<<"\n\t\tHa confundido su PIN con NIP, intente de nuevo";
				getch();
				system("cls");
				menu();
			}
		}
		
		
		for(int i = 0;i<cont;i++){
			
			if(pin == cl[i].pin){ //Manda el iterado con el cliente correcto a la funcion 'banco' cumpliendo la 2 condiciones del retiro, ademas de la 3 pues el numero de intentos fue cero
				banco(i);
			}
			
			else{	
		
				do{// Comprueba los numeros de intento, del NPI si la Pin es incorrecto
					cout<<"\t\tError, ingrese su NPI (Quedan "<<n<<" intentos): ";
					cin>> npi;
					
					if(npi == cl[i].NPI){
						banco(i);
					}		
					n--;	
					
				}while(n != 0 ); // Si es incorrecto, se devuelve al menu
					cout<<"\t\tNPI incorrecto, vuela a intentar"<<endl;
					getch();
					system("cls");
					menu();
			}
			
		}
		
			
	}
		
}

void consultarDatos(){
	
	if(start == 0){ // Ya fue explicado
		
		cout<<"\t\tNo hay clientes creados\n\n";
		
	}else{
		int pin=0;
		
		cout<<"\t\tIngrese el Pin del usuario: "; 
		cin>> pin;
		
		for(int i = 0;i<cont;i++){
			
			if(pin == cl[i].pin){ // Si el pin es correcto mostrara la consulta del cliente con el pin
				
				cout<<"\t\tPIN: "<<cl[i].pin<<"\n"<<endl;
				
				cout<<"\t\tNombre: "<<cl[i].nombre<<endl;
				cout<<"\t\tApellido: "<<cl[i].apellido<<endl;
				cout<<"\t\tNPI: "<<cl[i].NPI<<endl;
				cout<<"\t\tFecha de nacimiento: "<<cl[i].fn.dia<<"/"<<cl[i].fn.mes<<"/"<<cl[i].fn.anio<<endl;
				cout<<"\t\tDinero en cuenta: "<<ig[i].totalD<<endl;
				cout<<"\t\tDinero ingresado: "<<ig[i].sumar<<endl;
				cout<<"\t\tDinero retirado: "<<retirar<<endl;
				cout<<"\t\tFecha de expiracion: "<<cl[i].fn.anioExpi;
			
			}else{
				
				cout<<"\t\tPin incorrecto o usuario inexsistente"<<endl;
				
			}
			
		}
	}

}

void imprimirDatos(){ // Reporte de los cuentas agregadas
	
	if(start == 0){
		
		cout<<"\t\tNo hay clientes creados\n\n";
		
	}
	
	else{
		
		for(int i = 0;i<cont;i++){
			cout<<"\t\t***************************************"<<endl;
			cout<<"\t\t* Nombres #"<<i+1<<": "<<cl[i].nombre<<"		      *"<<endl;
			cout<<"\t\t* Apellido #"<<i+1<<": "<<cl[i].apellido<<"		      *"<<endl;
			cout<<"\t\t* Pin #"<<i+1<<": "<<cl[i].pin<<"				*"<<endl;
			cout<<"\t\t* NPI #"<<i+1<<": "<<cl[i].NPI<<"			      *"<<endl;
			cout<<"\t\t* Fecha de nacimiento #"<<i+1<<": "<<cl[i].fn.dia<<"/"<<cl[i].fn.mes<<"/"<<cl[i].fn.anio<<"  *"<<endl;
			cout<<"\t\t* Dinero en la cuenta #"<<i+1<<": "<<ig[i].totalD<<"	      *"<<endl;
			cout<<"\t\t* Año de expiracion de la cuenta: "<<cl[i].fn.anioExpi<<" *"<<endl;
			cout<<"\t\t***************************************"<<endl;
		}
		
		start++;
	}
	
}

void banco(int i){ // Funcion propia que se encarga del ingreso y retiro del dinero
	int opc = 0; //Para el switch
				
				
			do{//Enviado desde procesar datos muentra esta pantalla al usuario
				cout<<"\n\t\tHola usuario "<<cl[i].nombre<<endl;
				cout<<"\t\t¿Que accion desdea realizar?\n\n";
				
				cout<<"\t\t1. Agregar dinero a la cuenta"<<endl;
				cout<<"\t\t2. Retirar dinero a la cuenta"<<endl;
				cout<<"\t\t3. Dinero total en cuenta"<<endl;
				cout<<"\t\t4. Salir"<<endl;
				cout<<"\t\tOpcion: ";
				cin>>opc;
									
				switch(opc){
						
					case 1: 
						cout<<"\t\tIngrese la cantidad de dinero agregar a tu cuenta: "; // Para poder retirar dinero se necesita tener dinero en la cuenta, 5 de 6 condicion
						cin>> ig[i].cantidad;
						
						ig[i].sumar += ig[i].cantidad;
						ig[i].totalD = ig[i].sumar;
						cout<<"\n"; 
						
						cout<<"\t\tDinero ingresado :D";
						DinIngre++;
						getch();
						system("cls");
					break;
						
					case 2: 
						
						if(DinIngre == 0 || ig[i].totalD < 0){ 
							cout<<"\t\tNo hay dinero disponible para retirar";
						}
							
						else{
							cout<<"\t\tSolo puedes retirar un maximo de 5000 al dia, ademas de que obviamente\n\t\tno puedes retirar de lo habeis ingresado\n"<<endl;						 	
						 	cout<<"\t\tPuedes retirar aun: "<< limite - retirar; // Limite diario
						 	
						 	cout<<"\n\t\tIngrese la cantidad a retirar: ";
						 	cin>>retirar; //Lo que se retirara
						 	
						 	if(retirar <= ig[i].sumar && retirar < limite){ // Compruba si el limite no se ha superado y si balance es menor, la 4 y 5  condicion del retiro
							 	
							 	ig[i].totalD = ig[i].sumar - retirar;
								 
								cout<<"\n\t\tRetiro completado :D"<<endl;  
							 	getch();
								system("cls");
							 }else{
							 	cout<<"\n\t\tError, limite superado, transaccion cancelada"; // si el limite es superado
							 	getch();
								system("cls");
							 }
						 	
						}
						
						break;
						
					case 3:
						
						if(ig[i].sumar < 0){
							cout<<"\t\tNo hay dinero ingresado"<<ig[i].sumar<<endl;
							getch();
							system("cls");
						}
	
						else{
						
							cout<<"\t\tDinero en cuenta: "<<ig[i].sumar<<endl;
							getch();
							system("cls");
						}
					break; 
						
					case 4: 
						system("cls");
						menu(); 
					break;
				}
						
				}while(opc != 4);	
	
}

void creditos(){
	//Creditos :D
	cout<<"\t\t*********************************"<<endl;
	cout<<"\t\t* Creado por: 		        *"<<endl;
	cout<<"\t\t*  Leo  Corea             	*"<<endl;
	cout<<"\t\t*  Roire Villacencio	        *"<<endl;
	cout<<"\t\t*                               *"<<endl;
	cout<<"\t\t* Docente:	                *"<<endl;
	cout<<"\t\t*  César Marín López 		*"<<endl;
	cout<<"\t\t*                               *"<<endl;
	cout<<"\t\t*         Año 2021 		*"<<endl;
	cout<<"\t\t*********************************"<<endl;
	

}

