#include "time.h"
#include "stdio.h"
#include "conio.h"
#include "cstdlib"
#include "string.h"
#include "ctype.h"
//-----------------------FECHA DEL SISTEMA------
time_t t; 
struct tm *ahora; 
//----------------------------------------------

struct FECHA {
	int dd,mm,aaa;
	int h,m,s;
};
struct datos {
	char nombre[50];
	char ciudad[40];
	char direccion[70];
	int telefon;
	int edad;
	char email[40];
	struct FECHA fec_nacimiento;	//Validado
	struct FECHA fec_ingreso;	  //Sistema
};
typedef struct datos DATO;

bool logica=false;				// Variable Global
char menu_principal();			// 
char menu_tipo();

int consultar();

int ingresar();
int modificar();
int eliminar();
void salir();
int presentar();

int Val_fecha(int &anio, int &mes);
int validar_num(char cad[50]);
int validar_cad(char cad[50]);

int main(void){
	char op,op2;
	int pass;
	do{
		op=menu_principal();
		switch(op){
			case '1':
				printf("\n\tPara acceder a esta Opcion, Se necesita Autenticacion: ");
				printf("\n Ingrese Codigo de acceso:  ");
				scanf("%d",&pass);
				if(pass == 2016||pass==1991){
					do{
						op2=menu_tipo();
						switch(op2){
							case '1':	system("cls");	ingresar();		op2='5';	break;
							case '2':	system("cls");	modificar();	op2='5';	break;
							case '3':	system("cls");	eliminar();		op2='5';	break;
							case '4':	system("cls");	presentar();	op2='5';	break;
						}
					}while(op2!='5');	
				}else{
					system("cls");
					printf("\n\n\n\t Acceso denegado!");
					getch();
				}
			break;
			case '2':
				system("cls");
				consultar();
			break;
			case '3':
				system("cls");
				salir();
			break;
			default:
				printf("\n\n\n\t\t\tOpcion [%c] invalido !",op); getch();
			break;
		}
	}while(op!='3');
	
	return 0;
}
char menu_principal(){
	char op;
	system("cls");
	printf("\n* * Menu Principal * *\n");
	printf("\n (1)AGENDA VIRTUAL.:");
	printf("\n (2)CONSULTAR......:");
	printf("\n (3)SALIR..........:");
	printf("\n Opcion --> ");fflush(stdin);
	op = getch();
	return op;
}
char menu_tipo(){
	char op;
	system("cls");
	printf("\n* * Menu de Administrador * *\n");
	printf("\n (1)Registro.............:");
	printf("\n (2)Modificacion.........:");
	printf("\n (3)Eliminacion..........:");
	printf("\n (4)Todos Los Contactos..:");
	printf("\n (5)Salir................:");
	printf("\n Opcion --> ");fflush(stdin);
	op = getch();
	return op;
}
	/* VALIDA INT */
int validar_num(char num[50]){
	int i=0,error=0,j;
	j=strlen(num);
	while(i<j && error==0)
	{
		if(isdigit(num[i])!=0)
		{
			i++;
		}
		else
		{
			error=1;
		}
	}
	return error;
}
/* VALIDA STRING */
int validar_cad(char cad[50]){
	int i=0,error=0,j;
	j=strlen(cad);
	while(i<j && error==0)
	{
		if(isalpha(cad[i]) == 13){ error = 1; return error;}
		if(isalpha(cad[i]) != 0  || cad[i] == 32)
		{
			i++;
		}
		else
		{
			error=1;
		}
	}
	return error;
}
int Val_fecha(int &anio, int &mes){
	switch(mes)
	{
		case 1: return 31; break;
		case 2: 
			if (anio%400 == 0 || (anio%4==0 && anio%100!=0)){
            return 29;
            }else{
            return 28;
           	}	
		break;
		case 3: return 31; break;	case 4: return 30; break;	case 5: return 31; break;	case 6: return 30; break;
		case 7: return 31; break;	case 8: return 31; break;	case 9: return 30; break;	case 10: return 31; break;
		case 11: return 30; break;	case 12: return 31; break;
	}
}
int ingresar(){
	FILE *fich; int val_fec;
	DATO e;
	printf("\n\t\t * REGISTRAR Numero. *");
	//-----------------------FECHA DEL SISTEMA-------
	time(&t); 
	ahora = localtime(&t);
	//-----------------------------------------------
if ((fich = fopen("ADMINISTRACION.dat", "a")) == NULL)  { 
	printf ("Fichero no existe\n");
}  
else {
	printf("\n\n");;
	do{
		printf("Ingrese Numero : ");fflush(stdin);
	}while(!scanf("%d",&e.telefon));
	
	do{
		printf("Ingrese Nombres : ");fflush(stdin);
		gets(e.nombre);
	}while(validar_cad(e.nombre)==1);
	printf("\n\tDireccion vivienda: \n");
		printf("   Direccion de vivienda : ");	fflush(stdin);
		gets(e.direccion);
	printf("\n\tFecha Nacimiento \n");
	do{
		printf("   A%co: ",164);	fflush(stdin);
	}while(!scanf("%i",&e.fec_nacimiento.aaa)||e.fec_nacimiento.aaa<=1900||e.fec_nacimiento.aaa>2016);
	do{
		printf("   Mes: ");	fflush(stdin);
	}while(!scanf("%i",&e.fec_nacimiento.mm)||e.fec_nacimiento.mm<=0||e.fec_nacimiento.mm>12);
	do{
		printf("   Dia: ");	fflush(stdin);
	}while(!scanf("%i",&e.fec_nacimiento.dd)||e.fec_nacimiento.dd<=0||e.fec_nacimiento.dd>Val_fecha(e.fec_nacimiento.aaa,e.fec_nacimiento.mm));
	//-----------------------FECHA DEL SISTEMA--------------
	e.fec_ingreso.dd = ahora->tm_mday;
	e.fec_ingreso.mm = ahora->tm_mon + 1;
	e.fec_ingreso.aaa = ahora->tm_year +1900;
	//------------------------------------------------------
	e.edad = (ahora->tm_year +1900)-(e.fec_nacimiento.aaa);
	if(e.edad<18){
		printf("\n\n\t Por motivo de ser Menor de edad es imposible registrar su E-MAIL\n");
		printf("\n\t La edad minima es de [18 a%cos].. .\n",164);
	}else{
		printf("Ingrese E-mail : ");fflush(stdin);
		gets(e.email);
	}
	
	fwrite(&e, sizeof(e), 1, fich);
  	fclose(fich);
}
	getch();
}
int modificar(){
	FILE *fich , *fich2;
	int op;
	DATO m,e;
	printf("\n\t\t * MODIFICAR Contacto. *\n");
	if ((fich = fopen("ADMINISTRACION.dat", "r")) == NULL ) { 
		printf("Fichero no existe\n " );
		getch();
		return 0;
	} else 
	if ((fich2 = fopen("aux_.dat", "a")) == NULL ) { 
		printf("Fichero no existe\n " );
		fclose(fich);
	} else {
		printf("\n N. de Telefono que desea Modificar: ");
		scanf("%d",&m.telefon);
		fread (&e, sizeof(e), 1, fich);
		while (! feof(fich)) { 
			if(m.telefon==e.telefon){
			//-------------------------------------------------------------------------------------------------
			printf("\n(1) -> Nombre............: %s ",e.nombre);
			printf("\n(2) -> Direccion.........: %s",e.direccion);
			printf("\n(3) -> Telefono..........: %d",e.telefon);
			printf("\n(4) -> REGRESAR AL MENU\n\n");
	do{
				do{
					printf(" Que campo desea modificar: ");	fflush(stdin);
				}while(!scanf("%d",&op));
			switch(op){
				case 1:
					do{
					printf("\n Nuevo Nombre: ");	fflush(stdin);
					gets(e.nombre);
					}while(validar_cad(e.nombre)==1);
					op=4;
					logica=true;
				break;
				case 2:
					printf("\n Nuevo DIRECCION: \n");
					printf("\n\tDireccion de vivienda: ");	fflush(stdin);
					gets(e.direccion);
					op=4;
					logica=true;
				break;
				case 3:
					do{
						printf("\n Nuevo Telefono: ");	fflush(stdin);
					}while(!scanf("%d",&e.telefon));
					op=4;
					logica=true;
				break;
				case 4:
					printf("\n\n\t\t No se ah Modificado ningun Campo. . ."); break;
				break;
			}
	}while(op!=4);
		fwrite(&e, sizeof(e), 1, fich2);//-----------------------------------
	}
	else{//-----------------------------------
		fwrite(&e, sizeof(e), 1, fich2);//-----------------------------------
	}//-----------------------------------
	fread (&e, sizeof(e), 1, fich);
	}
		fclose (fich);
		fclose (fich2);
		remove("ADMINISTRACION.dat");//-----------------------------
		rename("aux_.dat","ADMINISTRACION.dat");
	}
if(logica!=true){  getch();	}else{	printf("\n\n\n\t\t Contacto Modificado correctamente . ."); logica=false;getch();}
}
int eliminar(){
	FILE *fich,*fich2;
	DATO e,elim;
	printf("\n\t\t * ELIMINAR Nro. *\n");
	if ((fich = fopen("ADMINISTRACION.dat", "r")) == NULL)  { 
		printf("Fichero no existe\n " );
		getch();
		return 0;
	} else 
	if ((fich2 = fopen("aux_.dat", "a")) == NULL)  { 
		printf("Fichero no existe\n " );
		fclose(fich);
	} else {
		do{
		printf("\n\n Ingrese No. Celular. : ");fflush(stdin);
		}while(!scanf("%d",&elim.telefon));
		fread (&e, sizeof(e), 1, fich);
		while (! feof(fich)) { 
			if(elim.telefon==e.telefon){
				logica=true;
			}else{
				fwrite(&e, sizeof(e), 1, fich2);//-----------------------------------
			}
		fread (&e, sizeof(e), 1, fich);
	}
		fclose (fich);
		fclose (fich2);
		remove("ADMINISTRACION.dat");//-----------------------------
		rename("aux_.dat","ADMINISTRACION.dat");
	}
	if(logica!=true){	printf("\n\tNumero no existe!");	getch();	}else{	printf("\n\tNo. [0%d] Eliminado",elim.telefon);	logica=false;	getch();	}
}
int consultar(){
	FILE *fich; DATO e,consul;
	int num;
	printf("\n\t\t * CONSULTAR Numero. *\n");
	if ((fich = fopen("ADMINISTRACION.dat", "r")) == NULL)  { 
		printf("Fichero no existe\n " );
		getch();
		return 0;
	} else {
	do{
		printf("\n\n Ingrese No. Telefono : ");fflush(stdin);
	}while(!scanf("%d",&consul.telefon));
	fread(&e,sizeof(e),1,fich);
	while(! feof(fich)){
		if(consul.telefon == e.telefon){
			printf("\n___________________________");
			printf("\n Nombre..............: %s",e.nombre);
			printf("\n Direccion...........: %s",e.direccion);
			printf("\n No. Telefono........: 0%d",e.telefon);
			if(e.edad>=18){
				printf("\n E-mail..............: %s",e.email);
			}
			printf("\n EDAD................: %d",e.edad);
			printf("\n Fecha de Nacimiento.: %i/%i/%i",e.fec_nacimiento.dd,e.fec_nacimiento.mm,e.fec_nacimiento.aaa);
			printf("\n Fecha de Registro...: %i/%i/%i",e.fec_ingreso.dd,e.fec_ingreso.mm,e.fec_ingreso.aaa);
			printf("\n___________________________");
			logica=true;
		}
		fread(&e,sizeof(e),1,fich);
	}
	fclose(fich);
}
	if(logica!=true){	printf("\n\tContacto no Existe");	getch();	}else{	getch();	logica=false;	}
}

void salir(){
	system("color 2");system("cls");
	printf("\n\n\n\n\t\t UNIVERSIDAD DE GUAYAQUIL ");
	printf("\n\t   FAC - CIENCIAS MATEMATICAS Y FISICAS \n");
	printf("\n\tCARRERA........: INGENIERIA EN SISTEMAS COMPUTACIONALES ");
	printf("\n\tCURSO..........: S3D ");
	printf("\n\tMATERIA........: ESTRUCTURA DE DATOS ");
	printf("\n\n\t\t\t* * INTEGRANTES * *\n \n\t\t\t * Matute Ronny\n\t\t\t * Vallejo Felix\n\n\n\n");getch();
}

int presentar(){
	FILE *fich;DATO e;
	printf("\n\t* Listado de todos los Contactos Guardados . *\n\n");
	if ((fich = fopen("ADMINISTRACION.dat", "r")) == NULL)  { 
		printf("Fichero no existe\n " );
		getch();
		return 0;
	} else {
	fread(&e,sizeof(e),1,fich);
	while(! feof(fich)){
			printf("\n_____________________________________________");
			printf("\n Nombre..............: %s",e.nombre);
			printf("\n Direccion...........: %s",e.direccion);
			printf("\n No. Telefono........: 0%d",e.telefon);
			if(e.edad>=18){
				printf("\n E-mail..............: %s",e.email);
			}
			printf("\n EDAD................: %d",e.edad);
			printf("\n Fecha de Nacimiento.: %i/%i/%i",e.fec_nacimiento.dd,e.fec_nacimiento.mm,e.fec_nacimiento.aaa);
			printf("\n Fecha de Registro...: %i/%i/%i",e.fec_ingreso.dd,e.fec_ingreso.mm,e.fec_ingreso.aaa);
			printf("\n_____________________________________________");
		fread(&e,sizeof(e),1,fich);
	}
}
	fclose(fich);
	getch();
}

