#include <iostream>
#include <math.h>
#include <cstring>

#include "tp0.h"
#include "cmdline.h"
#include "imagen.h"

#include "complejo.cpp"
#include "imagen.cpp"
#include "cmdline.cc"

static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;			// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)

static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "m", "method", "-", opt_method, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
	};

int main(int argc, char * const argv[])
{	

	//----- Procesamiento de la linea de comandos.

	cmdline cmdl(options);	
	cmdl.parse(argc, argv);

	//----- Creacion de la imagen inicial

	imagen img_o;
	img_o.cargar(*iss);//cargar_pgm();
	//img_o.imprimir(*oss);				

	//----- Creacion de imagen final

	imagen img_f;
	img_f.copiar(img_o);
	img_f.transformar(method);
	img_f.imprimir(*oss);

	//----- Fin

	ifs.close();
	ofs.close();
	return 0;
}

static void opt_method(string const &arg)
{
	if (!strcmp(IDENTITY_METHOD, arg.c_str()))
	{
		method = ide;
	}
	else if (!strcmp(EXP_METHOD, arg.c_str()))
	{
		method = exp;
	}
	else if (arg.c_str() == NULL)
	{
		method = ide;
	}
	else{
		exit(1);
	}
}

static void opt_input(string const &arg)
{
	// Si el nombre del archivos es "-" entonces se arroja un error
	
	if (arg == "-") {
		cerr << "Input file not found" << arg << "." << endl;
		exit(1);
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
	cout << "cmdline -m method [-i file] [-o file]"
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

	return f_z*pow(E, z.getRe());
}

