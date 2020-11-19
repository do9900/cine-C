/*      SISTEMA CINE
Este proyecto está basado en una representación de un cine, 
en donde, en un principio, se debe registrar la cartelera (listado de peliculas), cada cual
con un precio unitario y el número de peliculas que dispone la cartelera, 
esta lista de peliculas se guarda utilizando archivos para asi utilizarla en 
cada una de las ventas posteriores generadas por cada cliente. Además estos
productos incluidos en la lista, pueden ser eliminados, y/o modificados,
según sea deseado.
En cada compra se deberá ingresar el nombre del cliente.Luego de esta acción se 
procederá a escoger la opción de mostrar el reporte de compra, que asemeja a
una boleta; aquí se muestra el código de la pelicula, su nombre, la cantidad 
de boletos comprados, el precio unitario, el costo total de
toda la operación, incluyendo el IGV, además el nombre del cliente y se 
solicita que el cliente firme la boleta.

AUTOR: DIEGO JAVIER HUAREZ AREVALO

*/
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <iomanip> 
#include <string.h> 
using namespace std;
#define archivo "c:Datos.dat"
#define temporal "c:temporal.dat"

struct Pelicula
{
  char name[30];
  int codigo; //codigo de la sala en la que se proyectara la pelicula
  char sinopsis[100];
  char genero[15];
  int duracion; //en minutos
  float precio=0;
  int capacidad=0;
  float total=0;
};
struct Fecha{
	int dia;
	int mes;
	int anio;
};
struct persona
{ int dni;
  char nombre[30];
  char apellidoPaterno[15];
  char apellidoMaterno[15];
  char correo[25];
  Fecha fecha_nac;
};

persona data,t;
Pelicula datos,temp[50];
FILE *f;
FILE *g;
FILE *temprl;
//========================================================= INTRODUCCION =========================================================
void intro(char mensaje[])
{
 cout<<"\n\n\n\n\n\n\n\n\n\t\t\t\t ********** "<<mensaje<<" **********\n\n"<<endl; 
system("pause"); 
system("cls"); 
}

//========================================================= SALIDA =========================================================
void salida(char mensaje[])
{
 cout<<"\n\n\n\n\n\n\n\n\n\     ******************** "<<mensaje<<" ********************\n"<<endl;
system("pause");
system("cls");
}
//========================================================= RESPUESTA =========================================================
char continuar(char mensaje[])
{char opcion;
do
{cout<<mensaje;
cin>>opcion;
if(opcion!='S'&& opcion!='N')
  cout<<"RESPUESTA NO VALIDA, POR FAVOR INGRESE DE NUEVO SU RESPUESTA";
}while(opcion!='S'&& opcion!='N');
return opcion;
}

//========================================================= REPORTE INDIVIDUAL =========================================================
void mostrarpel()
{cout<<"\n\t   |CODIGO ==> "<<setw(44)<<datos.codigo<<"|"<<endl;
cout<<"\t   |NOMBRE ==> "<<setw(44)<<datos.name<<"|"<<endl;
cout<<"\t   |SINOPSIS ==> "<<setw(42)<<datos.sinopsis<<"|"<<endl;
cout<<"\t   |GENERO  ==> "<<setw(42)<<datos.genero<<"|"<<endl;
cout<<"\t   |DURACION ==> "<<setw(42)<<datos.duracion<<"|"<<endl;
cout<<"\t   |CANTIDAD ==> "<<setw(42)<<datos.capacidad<<"|"<<endl;
cout<<"\t   |PRECIO ==> "<<setw(44)<<datos.precio<<"|"<<endl;
}

//========================================================= MENU Pelicula =========================================================
int menu()
{int op4;
do
{system("cls");
cout<<"\n\t\t ____________________________________"<<endl;
cout<<"\t\t|====================================|"<<endl;
cout<<"\t\t|**********    PELICULA    **********|"<<endl;
cout<<"\t\t|====================================|"<<endl;
cout<<"\t\t|INGRESAR DATOS de la Pelicula   [1] |"<<endl;
cout<<"\t\t|====================================|"<<endl;
cout<<"\t\t|CONSULTA de la Pelicula         [2] |"<<endl;
cout<<"\t\t|====================================|"<<endl;
cout<<"\t\t|MODIFICAR DATOS de la Pelicula  [3] |"<<endl;
cout<<"\t\t|====================================|"<<endl;
cout<<"\t\t|ELIMINAR Pelicula               [4] |"<<endl;
cout<<"\t\t|====================================|"<<endl;
cout<<"\t\t|REPORTE (CARTELERA)             [5] |"<<endl;
cout<<"\t\t|====================================|"<<endl;
cout<<"\t\t|SALIR                           [6] |"<<endl;
cout<<"\t\t|====================================|"<<endl;
cout<<"\t\t|____________________________________|"<<endl;

cout<<"\n\n\n\t\t ____________________________________"<<endl;
cout<<"\t\t|INGRESE SU OPCION ==>            [ ]|\b\b\b";cin>>op4;
cout<<"\t\t|                                    |";
}while(op4<1||op4>6);
return op4;
}

//========================================================= MENU CLIENTE=========================================================
int menu2()
{int op3;
do
{system("cls");
cout<<"\n\t\t ____________________________________"<<endl;
cout<<"\t\t|====================================|"<<endl;
cout<<"\t\t|********** MENU PRINCIPAL **********|"<<endl;
cout<<"\t\t|====================================|"<<endl;
cout<<"\t\t|INGRESAR DATOS DEL CLIENTE      [1] |"<<endl;
cout<<"\t\t|====================================|"<<endl;
cout<<"\t\t|Peliculas EN LA CARTELERA       [2] |"<<endl;
cout<<"\t\t|====================================|"<<endl;
cout<<"\t\t|COMPRAR                         [3] |"<<endl;
cout<<"\t\t|====================================|"<<endl;
cout<<"\t\t|LISTA DE COMPRA                 [4] |"<<endl;
cout<<"\t\t|====================================|"<<endl;
cout<<"\t\t|FACTURAR                        [5] |"<<endl;
cout<<"\t\t|====================================|"<<endl;
cout<<"\t\t|____________________________________|"<<endl;

cout<<"\n\n\t\t ____________________________________"<<endl;
cout<<"\t\t|INGRESE SU OPCION ==>            [ ]|\b\b\b";cin>>op3;
cout<<"\t\t|                                    |";
}while(op3<1||op3>5);
return op3;
}

//========================================================= LECTURA =========================================================
void insertar()
{system("cls");
char resp;
int cod;
 
do
{system("cls");
cout<<"\t\t********** INGRESO DE DATOS **********"<<endl;
cout<<"\t\t======================================"<<endl;

cout<<"CODIGO: ";
cin>>cod;
f=fopen(archivo,"a+");

if (f==NULL)
{cout<<"\n\n ERROR: EL ARCHIVO NO EXISTE\n";
system("pause");
exit(1);
}
fread(&datos,sizeof(datos),1,f);

while(!feof(f))
{if(datos.codigo==cod)
   {cout << "\n\n REGISTRO DUPLICADO"<<endl;
     fclose(f);
     system("pause");
     return;
    }
fread(&datos,sizeof(datos),1,f);
}
datos.codigo=cod; //Guarda el valor del codigo ingresado en el struct datos
cout<<"NOMBRE de la Pelicula: ";
fflush(stdin);
gets(datos.name);
cout<<"SIPNOSIS: ";
gets(datos.sinopsis);
cout<<"GENERO: ";
fflush(stdin);
gets(datos.genero);
cout<<"DURACION: ";
cin>>datos.duracion;
do
{cout<<"PRECIO de la Pelicula: ";
cin>>datos.precio;
if(datos.precio<0)
  cout<<"ERROR!!!! PRECIO NO VALIDO, POR FAVOR INGRESE OTRO"<<endl;
}while(datos.precio<0);

do
{cout<<"Capacidad de la Pelicula: ";
cin>>datos.capacidad;
if(datos.capacidad<0)
  cout<<"ERROR!!!! CAPACIDAD NO VALIDA, POR FAVOR INGRESE OTRA"<<endl;
}while(datos.capacidad<0);

fwrite(&datos,sizeof(datos),1,f);
cout<<"\n\n\t--- REGISTRO ARCHIVADO CON EXITO --- \n";
fclose(f);
      
resp=continuar("\nDESEA INGRESAR otra Pelicula (S/N) ==> ");

}while(resp=='S');
}

//========================================================= REPORTE =========================================================
void reporte()
{system("cls");

cout<<"\t\t******************** REPORTE ********************"<<endl;
cout<<"\t\t================================================="<<endl<<endl;
f=fopen(archivo,"r");

if(f==NULL)
{cout<<"\n\n ERROR: EL ARCHIVO NO EXISTE"<<endl;
 system("pause");
 exit(1); 
}
cout<<" _____________________________________________________________________________"<<endl;
cout<<setw(30)<<"|=============================================================================|"<<endl;
cout<<"|"<<setw(10)<<"CODIGO "<<setw(20)<<" NOMBRE"<<setw(20)<<"CAPC."<<setw(10)<<"PRECIO"<<"       |"<<endl;
cout<<setw(30)<<"|=============================================================================|"<<endl;

fread(&datos,sizeof(datos),1,f);
while(!feof(f))
    {
	if(datos.codigo!=0){
	cout<<"|"<<setw(10)<<datos.codigo<<setw(20)<<datos.name<<setw(20)<<datos.capacidad<<setw(10)<<datos.precio<<"       |"<<endl;		
	}
	fread(&datos,sizeof(datos),1,f);
    }
cout<<setw(30)<<"|=============================================================================|"<<endl;
cout<<"|_____________________________________________________________________________|"<<endl;

fclose(f);
cout<<"\n";
system("pause");
}

//========================================================= CONSULTA (BUSQ. POR CODIGO) =========================================================
void consulta()
{int bcod;
char resp;
int enc=0;

do
{system("cls");
cout<<"\t\t********** BUSQUEDA POR CODIGO **********"<<endl;
cout<<"\t\t========================================="<<endl;
f=fopen(archivo,"r+");

if(f==NULL)
{cout<<"\n\n ERROR: EL ARCHIVO NO EXISTE\n";
system("pause");
exit(1);
}
  
cout<<"INGRESE UN CODIGO VALIDO PARA SU BUSQUEDA: ";
cin>>bcod;

cout<<"\n\n\t\t********** DATOS DE LA BUSQUEDA **********"<<endl;
cout<<"\t\t=========================================="<<endl;
fread(&datos,sizeof(datos),1,f);

cout<<"\t    _______________________________________________________"<<endl;
cout<<setw(30)<<"\t   |=======================================================|"; 
while(!feof(f))
{if((datos.codigo==bcod)&&enc!=1)
   {mostrarpel();
    enc=1;
   }
fread(&datos,sizeof(datos),1,f);
}
cout<<setw(30)<<"\t   |=======================================================|"; 
cout<<"\n\t   |_______________________________________________________|"<<endl;

if(enc==0)
cout<<"\n\t--- NO EXISTE una Pelicula REGISTRADA CON ESTE CODIGO ---"<<endl;

fclose(f);

resp=continuar("\nDESEA REALIZAR OTRA BUSQUEDA (S/N) ==> ");
enc=0;
}while(resp=='S');

cout<<"\n --- FIN DE LA BUSQUEDA ---"<<endl;
system("pause");
return;
}


//========================================================= MODIFICAR =========================================================
void modificar()
{int op1;
int cod;
char resp;
int enc=0;
system("cls");

cout<<"\t\t********** MODIFICAR DATOS **********"<<endl;
cout<<"\t\t====================================="<<endl<<endl;

f=fopen(archivo,"r+");  
if(f==NULL)
{cout<<"\n\n ERROR: EL ARCHIVO NO EXISTE"<<endl;
 system("pause");
 exit(1); 
}

g=fopen(temporal,"a+");
if(g==NULL)
{cout<<"\n\n ERROR: EL ARCHIVO NO EXISTE"<<endl;
exit(1); 
system("pause");
}

cout<<"INGRESE UN CODIGO VALIDO PARA SU BUSQUEDA: ";
cin>>cod;
fread(&datos,sizeof(datos),1,f);

cout<<"\t    _______________________________________________________"<<endl;
cout<<setw(30)<<"\t   |=======================================================|";
while(!feof(f))
{if(datos.codigo==cod)
    {mostrarpel();
    cout<<setw(30)<<"\t   |=======================================================|"; 
    cout<<"\n\t   |_______________________________________________________|"<<endl;
    system("pause");

    do
    {do
    {system("cls");
    cout<<"\n\t\t __________________________________________"<<endl;
    cout<<"\t\t|==========================================|"<<endl;
    cout<<"\t\t|********** ¿QUE DESEA MODIFICAR **********|"<<endl;
    cout<<"\t\t|==========================================|"<<endl;
    cout<<"\t\t|CODIGO                                [1] |"<<endl;
    cout<<"\t\t|==========================================|"<<endl;
    cout<<"\t\t|NOMBRE                                [2] |"<<endl;
    cout<<"\t\t|==========================================|"<<endl;
    cout<<"\t\t|CAPACIDAD                             [3] |"<<endl;
    cout<<"\t\t|==========================================|"<<endl;
    cout<<"\t\t|PRECIO                                [4] |"<<endl;
    cout<<"\t\t|==========================================|"<<endl;
    cout<<"\t\t|__________________________________________|"<<endl;

    cout<<"\n\n\n\t\t ____________________________________"<<endl;
    cout<<"\t\t|INGRESE SU OPCION ==>            [ ]|\b\b\b";cin>>op1;
    cout<<"\t\t|                                    |";
    }while(op1<1||op1>4);
	switch(op1)
    {case 1: system("cls");
	         cout<<"\n\nNUEVO CODIGO: ";
             cin>>cod;
             f=fopen(archivo,"a+");

            if (f==NULL)
            {cout<<"\n\n ERROR: EL ARCHIVO NO EXISTE\n";
             system("pause");
            exit(1);
            }
            fread(&datos,sizeof(datos),1,f);

            while(!feof(f))
            {if(datos.codigo==cod)
            {cout << "\n\n REGISTRO DUPLICADO"<<endl;
            fclose(f);
            system("pause");
             return;
            }
            fread(&datos,sizeof(datos),1,f);
            }
            datos.codigo=cod;
			break;
					
    case 2:system("cls");
	       cout<<"\n\nNUEVO NOMBRE: ";
           fflush(stdin);
           gets(datos.name);
		   break;
		   

    case 3:do
            {system("cls");
			cout<<"\n\nACTUALIZAR CAPACIDAD: ";
            cin>>datos.capacidad;
            }while(datos.capacidad<0);
			break;

    case 4:do
            {system("cls");
			cout<<"\n\nNUEVO PRECIO: ";
            cin>>datos.precio;
            }while(datos.precio<0);
			break;
          }
          resp=continuar("\n\nDESEA MODIFICAR OTRO CAMPO (S/N) ==> ");
		 }while(resp=='S');     
		 enc=1;       
      fwrite(&datos,sizeof(datos),1,g);  
    }
	else
      fwrite(&datos,sizeof(datos),1,g);
      fread(&datos,sizeof(datos),1,f);
}
fclose(f);
fclose(g);
remove(archivo);
rename(temporal, archivo);

if(enc==0)
    cout<<"\n\t--- NO EXISTE una Pelicula REGISTRADA CON ESTE CODIGO ---"<<endl;
else
	cout<<"\n\t--- REGISTRO ACTUALIZADO CON EXITO ---"<<endl;
system("pause");
}

//========================================================= ELIMINAR =========================================================
void eliminar()
{system("cls");
int cod;
char resp;
 
cout<<"\t\t********** ELIMINACION **********"<<endl;
cout<<"\t\t================================="<<endl;
 
f=fopen(archivo,"r+");  
if(f==NULL)
{cout<<"\n\n ERROR: EL ARCHIVO NO EXISTE"<<endl;
 system("pause");
 exit(1); 
}

cout<<"INGRESE UN CODIGO VALIDO PARA SU BUSQUEDA: ";
cin>>cod;
fread(&datos,sizeof(datos),1,f);

cout<<"\t    _______________________________________________________"<<endl;
cout<<setw(30)<<"\t   |=======================================================|";
while(!feof(f))
{if(datos.codigo==cod) 
    {mostrarpel();
cout<<setw(30)<<"\t   |=======================================================|"; 
cout<<"\n\t   |_______________________________________________________|"<<endl;
system("pause");
  
datos.codigo=0;
strcpy(datos.name,"");
datos.capacidad=0;
datos.precio=0;
                          
resp=continuar("\nESTA SEGURO DE QUE DESEA ELIMINAR ESTE REGISTRO (S/N) ==> ");                       

if(resp=='S')
    {fseek(f,ftell(f)-sizeof(datos),SEEK_SET);
    fwrite(&datos,sizeof(datos),1,f);
    cout<<"\n\t--- REGISTRO ELIMINADO CON EXITO ---"<<endl;
    }
    fclose(f);

    system("pause");
    return;                               
    }        
fread(&datos,sizeof(datos),1,f);
}

cout <<"\n\rNO SE ENCUENTRA REGISTRO!!!\n";
fclose(f);
system("pause");
return;
}     


//========================================================= CINE =========================================================
void cine()
{Pelicula datos[50];
int n=0,op;

system("cls");
intro("ADMINISTRACION: CINE X");

do
{op=menu();

switch(op)
{case 1:insertar();
        break;
       
 case 2:consulta();
        break;
   
 case 3:modificar();
        break;
         
 case 4:eliminar();
        break;
        
 case 5:reporte();
        break;
       
}
}while(op!=6);
system("cls");
salida("REGISTRO COMPLETO");
}

//========================================================= DATOS DEL CLIENTE =========================================================
void informacion(int &num)
{system("cls");
char resp;

system("cls");
cout<<"\t\t********** INGRESO DE DATOS DEL CLIENTE **********"<<endl;
cout<<"\t\t=================================================="<<endl;
cout<<"DNI: ";
cin>>data.dni;
cout<<"NOMBRE DEL CLIENTE: ";
fflush(stdin);
gets(data.nombre);
cout<<"APELLIDO PATERNO: ";
gets(data.apellidoPaterno);
cout<<"APELLIDO PATERNO: ";
gets(data.apellidoMaterno);
cout<<"CORREO: ";
fflush(stdin);
gets(data.correo);
cout<<"FECHA DE NACIMIENTO:\n";
do{
	cout<<"Dia: "; cin>>data.fecha_nac.dia;
}while(data.fecha_nac.dia<1||data.fecha_nac.dia>31);
do{
	cout<<"Mes: "; cin>>data.fecha_nac.mes;
}while(data.fecha_nac.mes<1||data.fecha_nac.mes>12);
do{
	cout<<"Anio: "; cin>>data.fecha_nac.anio;
}while(data.fecha_nac.anio<1900);

cout<<"\n\n\t--- YA PUEDE PROCEDER --- \n";
num=1; //puntero que varia su valor con cada cliente q se registre
system("pause");
}

//========================================================= COMPROBADOR =========================================================
int comp(int cantd,char nom[30])
{int dat=0;
int ind;
int enc;
f=fopen(archivo,"r+");

enc=0;
if(f==NULL)
{cout<<"\n\n ERROR: EL ARCHIVO NO EXISTE";
system("pause");
exit(1);
}

fread(&datos,sizeof(datos),1,f);
while(!feof(f))
{if(strcmp(nom,datos.name)==0&&enc!=1)
  {dat=datos.capacidad;
  enc=1;
  }
fread(&datos,sizeof(datos),1,f);
}
fclose(f);

if(enc==0)
{cout<<"\n\t--- NO EXISTE UN PRODUCTO REGISTRADO CON ESTE NOMBRE ---"<<endl;
return 2;
}

if(dat<cantd)
{ind=0;
}
else
ind=1;
return ind;
}

//========================================================= COMPRAR =========================================================
void comprar(int &cont,float &tototal)
{char bname[30];
char resp;
int enc,ind;
int cantd;
int i;

do
{system("cls");
cout<<"\t\t********** COMPRAR **********"<<endl;
cout<<"\t\t============================="<<endl;
enc=0;

cout<<"INGRESE EL NOMBRE de la Pelicula: ";
fflush(stdin);
gets(bname);

do
{cout<<"INGRESE LA CANTIDAD QUE DESEA COMPRAR: ";
cin>>cantd;
}while(cantd<0);

ind=comp(cantd,bname);
if(ind==0)
{cout<<"\n\nLO SENTIMOS, NO CONTAMOS CON SUFICIENTES Entradas"<<endl;
 cout<<"POR FAVOR REVISE LA OPCION [2] PARA MAS INFORMACION\n"<<endl;
 system("pause");
return;
}

if(ind==2)
{return;
}

f=fopen(archivo,"r+");

if(f==NULL)
{cout<<"\n\n ERROR: EL ARCHIVO NO EXISTE\n";
system("pause");
exit(1);
}

fread(&datos,sizeof(datos),1,f);
while(!feof(f))
{if((strcmp(bname,datos.name)==0)&&enc!=1) //Almacena los datos del archivo en un array local para trabajar con la cantidad de entradas
    {
	 temp[cont]=datos;
	 temp[cont].capacidad=0;
     temp[cont].capacidad=temp[cont].capacidad+cantd;
     temp[cont].total=0;
     temp[cont].total=temp[cont].total+temp[cont].capacidad*temp[cont].precio;
     cont++;
     enc=1;
	}  
fread(&datos,sizeof(datos),1,f);
}
fclose(f);

f=fopen(archivo,"r+");  
if(f==NULL)
{cout<<"\n\n ERROR: EL ARCHIVO NO EXISTE"<<endl;
 system("pause");
 exit(1); 
}

g=fopen(temporal,"a+");
if(g==NULL)
{cout<<"\n\n ERROR: EL ARCHIVO NO EXISTE"<<endl;
exit(1); 
system("pause");
}

fread(&datos,sizeof(datos),1,f);
while(!feof(f))
{if(strcmp(datos.name,bname)==0)
    {
	{datos.capacidad=datos.capacidad-cantd; 
	}
     fwrite(&datos,sizeof(datos),1,g);       
    }
	else
      fwrite(&datos,sizeof(datos),1,g);
      fread(&datos,sizeof(datos),1,f);
}
fclose(f);
fclose(g);
remove(archivo);
rename(temporal, archivo);

  
if(enc==0)
cout<<"\n\t--- NO EXISTE una Pelicula CON ESTE NOMBRE en la TAQUILLA ---"<<endl;
fclose(f);

resp=continuar("\nDESEA REALIZAR OTRA COMPRA (S/N) ==> ");
}while(resp=='S');

cout<<"\n --- FIN DE LA COMPRA ---"<<endl;
system("pause");
return;
}

//=========================================================  LISTA COMPRAS =========================================================
void lista(char mensaje[50],int cont,float tototal,float &tot,float &igv)
{system("cls");
int i;

for(i=0;i<cont;i++)
{tototal=tototal+temp[i].total;
}

cout<<"\t******************** "<<mensaje<<" ********************"<<endl;
cout<<"\t=========================================================="<<endl<<endl;


cout<<" _____________________________________________________________________________"<<endl;
cout<<setw(30)<<"|=============================================================================|"<<endl;
cout<<"|"<<setw(10)<<"CODIGO "<<setw(20)<<" NOMBRE"<<setw(20)<<"CANT."<<setw(10)<<"PRECIO"<<setw(10)<<"TOTAL"<<"       |"<<endl;
cout<<setw(30)<<"|=============================================================================|"<<endl;

for(i=0;i<cont;i++)
{
cout<<"|"<<setw(10)<<temp[i].codigo<<setw(20)<<temp[i].name<<setw(20)<<temp[i].capacidad<<setw(10)<<temp[i].precio<<setw(10)<<temp[i].total<<setw(8)<<"|"<<endl;
}
cout<<setw(30)<<"|=============================================================================|"<<endl;
cout<<"|"<<setw(10)<<"TOTAL: "<<setw(60)<<tototal<<"       |"<<endl;
cout<<"|_____________________________________________________________________________|"<<endl;
system("pause");

tot=tototal;
igv=tot*0.18;
}

//========================================================= VERIFICA =========================================================
int ver(int num)
{system("cls");
if(num==0)
{cout<<"\n\n\nPOR FAVOR INSERTE SU INFORMACION EN LA CASILLA [1], PARA CONTINUAR\n"<<endl;
 system("pause");
}
return num;
}


//========================================================= FACTURA =========================================================
void factura(int cont,float tototal,float tot,float igv,int num,int &op)
{system("cls");
int n;

lista("  FACTURA",cont,tototal,tot,igv);

cout<<setw(30)<<"|=============================================================================|"<<endl;
cout<<setw(30)<<"|================================= CINE TECHIES :v ================================|"<<endl;
cout<<setw(30)<<"|=============================================================================|"<<endl;
cout<<"|"<<setw(8)<<"NOMBRE: "<<setw(69)<<data.nombre<<"|"<<endl;
cout<<"|"<<setw(8)<<"A. PATERNO: "<<setw(66)<<data.apellidoPaterno<<"|"<<endl;
cout<<"|"<<setw(8)<<"A. MATERNO: "<<setw(66)<<data.apellidoMaterno<<"|"<<endl;
cout<<"|"<<setw(10)<<"FIRMA: ........................."<<setw(46)<<"|"<<endl;
cout<<"|"<<setw(7)<<"CORREO: "<<setw(70)<<data.correo<<"|"<<endl;
cout<<"|"<<setw(5)<<"IGV: "<<setw(66)<<igv<<" SOLES"<<"|"<<endl;
cout<<"|"<<setw(10)<<"TOTAL A PAGAR: "<<setw(56)<<tot+igv<<" SOLES"<<"|"<<endl;
cout<<"|_____________________________________________________________________________|"<<endl;
system("pause");
op=6;
}

//========================================================= CLIENTE =========================================================
void cliente()
{persona data[50];
Pelicula datos[50];
int op;
int cont=0;
float tototal=0;
float igv=0,tot=0;
int num=0;
int n=0;


system("cls");
intro("BIENVENIDO AL CINE X");

do
{op=menu2();

switch(op)
{case 1:informacion(num);
        break;
      
 case 2:reporte();
        break;

 case 3:comprar(cont,tototal);
        break;
             
 case 4:lista("LISTA DE COMPRAS",cont,tototal,tot,igv);
        break;
case 5:n=ver(num);
       if(n==0)
	   break;
	   factura(cont,tototal,tot,igv,num,op);
}
}while(op!=6);

system("cls");
salida("GRACIAS POR SU PREFERENCIA");
}

//========================================================= SELECCION =========================================================
int seleccion(int &n)
{int op;

{if(n==0)
intro("PROYECTO DE CINE");
n++;
}

do
{system("cls");
cout<<"\n\n\n\t\t ____________________________________"<<endl;
cout<<"\t\t|====================================|"<<endl;
cout<<"\t\t|********** MENU PRINCIPAL **********|"<<endl;
cout<<"\t\t|====================================|"<<endl;
cout<<"\t\t|MODO ADMINISTRACION             [1] |"<<endl;
cout<<"\t\t|====================================|"<<endl;
cout<<"\t\t|MODO CLIENTE                    [2] |"<<endl;
cout<<"\t\t|====================================|"<<endl;
cout<<"\t\t|SALIR                           [3] |"<<endl;
cout<<"\t\t|====================================|"<<endl;
cout<<"\t\t|____________________________________|"<<endl;

cout<<"\n\n\n\t\t ____________________________________"<<endl;
cout<<"\t\t|INGRESE SU OPCION ==>            [ ]|\b\b\b";cin>>op;
cout<<"\t\t|                                    |";
}while(op<1||op>3);
return op;
}

//========================================================= PRINCIPAL =========================================================
int main()
{Pelicula datos[50];
int n=0,op,tam,sel;
float comp,total;

do
{sel=seleccion(n);



switch(sel)
{case 1:cine();
        break;
        
 case 2:cliente();
        break;
}
}while(sel!=3);
system("cls");
salida("GRACIAS POR USAR EL PROGRAMA");
return 0;
}


