#include <iostream>
#include <fstream>
#include <math.h>
#include <cstring>

#include "tp1_config.h"
#include "cmdline.h"
#include "tp1_imagen.h"

static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;			// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)
string funcion;

static option_t options[] = {
	{1, "i", "entrada", "-", opt_input, OPT_DEFAULT},
	{1, "o", "salida", "-", opt_output, OPT_DEFAULT},
	{1, "f", "funcion", "-", opt_function, OPT_DEFAULT},
	{0, "h", "ayuda", NULL, opt_help, OPT_DEFAULT},
	{0, },
	};

int main(int argc, char * const argv[])
{	
	imagen img_o, img_f;

	//----- Procesamiento de la linea de comandos -----

	cmdline cmdl(options);	
	cmdl.parse(argc, argv);
	cerr << MSJ_CMDLINE_OK << endl;

	//----- Creacion de la imagen inicial -----

	img_o.cargarPgm(ifs);
	cerr << MSJ_CARGA_OK << endl;

	cerr << img_o;				
	//img_o.imprimirPixel(cout);				

	//----- Creacion de imagen final -----

	img_f.copiar(img_o);
	cerr << MSJ_COPIADO_OK << endl;

	img_f.transformar(funcion);
	cerr << MSJ_TRANSFORMACION_OK << endl;

	cerr << img_f;				
	//img_f.imprimir(ofs);
	cerr << MSJ_IMPRESION_OK << endl;
	
	//----- Fin -----

	ifs.close();
	ofs.close();
	cerr << MSJ_FIN << endl;
	return 0;
}
static void opt_function(string const &arg)
{	
	funcion = arg.c_str();	
}

static void opt_input(string const &arg)
{
	
	if (arg == "-") {
		iss = &cin;
	}
	else {
		ifs.open(arg.c_str(), ios::in); 	
		iss = &ifs;										
		//Verificamos que el stream este OK.
		if (!iss->good()) {
			cerr << MSJ_ERROR_APERTURA << arg << "." << endl;
			exit(1);
		}		
	}	
}

static void opt_output(string const &arg)
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

static void opt_help(string const &arg)
{
	cout << MSJ_AYUDA << endl;
	exit(0);
}

#define MSJ_AYUDA "-h -i [entrada] -o [salida] -f [funcion]"
#define MSJ_ERROR_APERTURA "No se puede abrir el archivo: "

