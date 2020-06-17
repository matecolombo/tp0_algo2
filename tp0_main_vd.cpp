#include <iostream>
#include <fstream>
#include <math.h>
#include <cstring>

#include "tp0_config_vd.h"
#include "tp0_imagen_vd.h"
#include "cmdline.h"

static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;			// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)

static opcion_t opciones[] = {
	{1, "i", "entrada", "-", opc_entrada, OPT_DEFAULT},
	{1, "o", "salida", "-", opc_salida, OPT_DEFAULT},
	{1, "f", "funcion", "-", opc_funcion, OPT_DEFAULT},
	{0, "h", "ayuda", NULL, opc_ayuda, OPT_DEFAULT},
	{0, },
};

int main(int argc, char * const argv[])
{	
	imagen img_o, img_f;

	//----- Procesamiento de la linea de comandos -----

	cmdline cmdl(opciones);	
	cmdl.parse(argc, argv);
	cerr << MSJ_CMDLINE_OK << endl;

	//----- Creacion de la imagen inicial -----

	img_o.cargarPgm(*iss);
	cerr << MSJ_CARGA_OK << endl;

	//----- Creacion de imagen final -----

	img_f.copiar(img_o);
	cerr << MSJ_COPIADO_OK << endl;

	img_f.transformar(funcion);
	cerr << MSJ_TRANSFORMACION_OK << endl;

	img_f.imprimir(*oss);
	cerr << MSJ_IMPRESION_OK << endl;
	
	//----- Fin -----

	ifs.close();
	ofs.close();
	cerr << MSJ_FIN << endl;
	return 0;
}
static void opc_funcion(string const &arg)
{
	if(arg == FUNCION_IDENTIDAD)
	{
		funcion = ide;
	}
	else if(arg == FUNCION_EXPONENCIAL)
	{
		funcion = exp;
	}
	else if (arg.c_str() == NULL)
	{
		funcion = ide;
	}
	else{
		cerr << MSJ_FUNCION_DESCONOCIDA << arg << endl;
		exit(1);
	}
}

static void opc_entrada(string const &arg)
{
	// Si el nombre del archivos es "-" entonces se arroja un error
	
	if (arg == "-") {
		iss = &cin;
	}
	else {
		ifs.open(arg.c_str(), ios::in); 		// c_str(): Returns a pointer to an array that contains a null-terminated
												// sequence of characters (i.e., a C-string) representing
		iss = &ifs;								// the current value of the string object.
		
		//Verificamos que el stream este OK.
		if (!iss->good()) {
			cerr << MSJ_ERROR_APERTURA << arg << "." << endl;
			exit(1);
		}		
	}	
}

static void opc_salida(string const &arg)
{
	// Si el nombre del archivos es "-", se arroja un error por cerr
	if (arg == "-") {
		oss = &cout;
		
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}

	// Verificamos que el stream este OK.
	
	if (!oss->good()) {
		cerr << MSJ_ERROR_APERTURA << arg << "." << endl;
		exit(1);		// EXIT: Terminaci�n del programa en su totalidad
	}
}

static void opc_ayuda(string const &arg)
{
	cout << MSJ_AYUDA
	     << endl;
	exit(0);
}

Complejo ide(const Complejo & z)
{
	return z;
}

//e^z = e^a.(cos b + j.sen b)
Complejo exp(const Complejo & z)
{
	Complejo f_z;

	f_z.setRe(cos(z.getIm()));
	f_z.setIm(sin(z.getIm()));

	return f_z*exp(z.getRe());
}


