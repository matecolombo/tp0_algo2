#include <iostream>
#include <fstream>
#include <math.h>
#include <cstring>

#include "tp1.h"
#include "cmdline.h"
#include "tp1_imagen.h"

static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;			// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)
string funcion;

static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "f", "function", "-", opt_function, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
	};

int main(int argc, char * const argv[])
{	
	imagen img_o, img_f;

	//----- Procesamiento de la linea de comandos.

	cmdline cmdl(options);	
	cmdl.parse(argc, argv);
	cerr << MSJ_CMDLINE_OK << endl;

	//----- Creacion de la imagen inicial

	img_o.cargarPgm(ifs);
	cerr << MSJ_CARGA_OK << endl;

	img_o.imprimir(cout);				
	//img_o.imprimirPixel(cout);				

	//----- Creacion de imagen final

	img_f.copiar(img_o);
	cerr << MSJ_COPIADO_OK << endl;

	img_f.transformar(funcion);
	cerr << MSJ_TRANSFORMACION_OK << endl;

	img_f.imprimir(ofs);
	cerr << MSJ_IMPRESION_OK << endl;
	
	//----- Fin

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
	// Si el nombre del archivos es "-" entonces se arroja un error
	
	if (arg == "-") {
		iss = &cin;
	}
	else {
		ifs.open(arg.c_str(), ios::in); 	// c_str(): Returns a pointer to an array that contains a null-terminated
												// sequence of characters (i.e., a C-string) representing
		iss = &ifs;								// the current value of the string object.
		
		//Verificamos que el stream este OK.
		if (!iss->good()) {
			cerr << "cannot open " << arg << "." << endl;
			exit(1);
		}		
	}	
}

static void opt_output(string const &arg)
{
	// Si el nombre del archivos es "-", se arroja un error por cerr
	if (arg == "-") {
		oss = &cout;
		//exit(1);	// Establezco la salida estandar cout como flujo de salida
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}

	// Verificamos que el stream este OK.
	
	if (!oss->good()) {
		cerr << "cannot open " << arg << "." << endl;
		exit(1);		// EXIT: Terminaci�n del programa en su totalidad
	}
}

static void opt_help(string const &arg)
{
	cout << "cmdline -m function [-i file] [-o file]"
	     << endl;
	exit(0);
}


