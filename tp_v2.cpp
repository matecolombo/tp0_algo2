#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstring>

#include "complejo.h"
#include "complejo.cpp"
#include "array.h"
#include "cmdline.h"
#include "cmdline.cc"
#include "math_op.h"
#include "matrix.h"
#include "imagen.h"
#include "pixel.h"

#define E 2.7172

#define IDENTITY_METHOD "z"
#define EXP_METHOD "exp(z)"

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


using namespace std;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_method(string const &);
static void opt_help(string const &);

// Tabla de opciones de l�nea de comando. El formato de la tabla
// consta de un elemento por cada opci�n a definir. A su vez, en
// cada entrada de la tabla tendremos:
//
// o La primera columna indica si la opci�n lleva (1) o no (0) un
//   argumento adicional.
//
// o La segunda columna representa el nombre corto de la opci�n.
//
// o Similarmente, la tercera columna determina el nombre largo.
//
// o La cuarta columna contiene el valor por defecto a asignarle
//   a esta opci�n en caso que no est� expl�citamente presente
//   en la l�nea de comandos del programa. Si la opci�n no tiene
//   argumento (primera columna nula), todo esto no tiene efecto.
//
// o La quinta columna apunta al m�todo de parseo de la opci�n,
//   cuyo prototipo debe ser siempre void (*m)(string const &arg);
//
// o La �ltima columna sirve para especificar el comportamiento a
//   adoptar en el momento de procesar esta opci�n: cuando la
//   opci�n es obligatoria, deber� activarse OPT_MANDATORY.
//
// Adem�s, la �ltima entrada de la tabla debe contener todos sus
// elementos nulos, para indicar el final de la misma.
//


static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "m", "method", "-", opt_method, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;		// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)

static ifstream fin;


Complejo (*method) (const Complejo &);

/*****************************************************/

static void
opt_method(string const &arg)
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


static void
opt_input(string const &arg)
{
	// Si el nombre del archivos es "-" entonces se arroja un error
	//
	if (arg == "-") {
		cerr << "Input file not found"
			 << arg
			 << "."
			 << endl;
		exit(1);
	}
	else {
		fin.open("feep.txt");
		//fin.open(arg.c_str(), ios::in); // c_str(): Returns a pointer to an array that contains a null-terminated
										// sequence of characters (i.e., a C-string) representing
										// the current value of the string object.
		if(fin.bad())					
		{
			cout << "fallo la apertura del archivo";
			cin.get();
			return exit(1);					
		}
		//iss = &ifs;
	}

	// Verificamos que el stream este OK.
	//
	// if (!iss->good()) {
	// 	cerr << "cannot open "
	// 	     << arg
	// 	     << "."
	// 	     << endl;
	// 	exit(1);
	// }
}

static void
opt_output(string const &arg)
{
	// Si el nombre del archivos es "-", se arroja un error por cerr
	if (arg == "-") {
		oss = &cerr;
		//exit(1);	// Establezco la salida estandar cout como flujo de salida
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}

	// Verificamos que el stream este OK.
	//
	if (!oss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);		// EXIT: Terminaci�n del programa en su totalidad
	}
}

static void
opt_help(string const &arg)
{
	cout << "cmdline -m method [-i file] [-o file]"
	     << endl;
	exit(0);
}



void extraer_parametros(ifstream &, string*);
void crear_matriz(ifstream &, Matrix<double> &);
Complejo ide(const Complejo &);
Complejo exp(const Complejo &);

int main(int argc, char * const argv[])
{
	string linea;

	cmdline cmdl(options);	// Objeto con parametro tipo option_t (struct) declarado globalmente. Ver l�nea 51 main.cc
	cmdl.parse(argc, argv); // Metodo de parseo de la clase cmdline
	string param[4];
	imagen img;

	// ifstream fin("feep.txt");		
	// if(fin.bad())					
	// {
	// 	cout << "fallo la apertura del archivo";
	// 	cin.get();
	// 	return 1;					
	// }
	while(!fin.eof())
	{
		getline(fin, linea);
		cout<<linea<< endl;
	}
	//-----Procesamiento de las primeras lineas con inf
	extraer_parametros(fin, param);

	img.cargarParametros(param);
	
	//-----Procesamiento del resto de lineas
	Matrix<double> m(img.getAlto(), img.getAncho());
	crear_matriz(fin, m);
	//m.print_matrix();

	//-----Creacion de la imagen inicial
	img.cargarMatriz(m);
	img.imprimir();

	//-----Creacion de imagen final


	 fin.close();
	return 0;
}
void extraer_parametros(ifstream & fin, string param[])
{	
	string linea, token, delim = " ";
	size_t pos, n_linea = 1;

	while(!fin.eof()){
		pos = 0;
		getline(fin, linea);
		
		if(linea[0] == '#'){
			n_linea++;
			continue;
		}
		if(n_linea == 1){
			param[0] = linea;
		}			
		if(n_linea == 3){
			pos = linea.find(delim);
			token = linea.substr(0, pos);	
			param[1] = token;
			linea.erase(0, pos + delim.length());
			token = linea.substr(0, pos);
			param[2] = token;
		}		
		if(n_linea == 4){
			param[3] = linea;
			break;	
		}
		n_linea++;
	}
}
void crear_matriz(ifstream & fin, Matrix<double> & m)
{	
	string linea, token, delim = " ";
	int i = 0, j = 0, pos = 0;
	double dato;

	while(!fin.eof() && i < m.get_alto())
	{
		getline(fin, linea);
		//cout << linea << endl;
		j = pos = 0; 
		while(j < m.get_ancho())
		{	
			pos = linea.find(delim);
			token = linea.substr(0, pos);
			if(istringstream(token) >> dato){	
				m.fill_pos(i, j, dato);
				j++;
			}
			linea.erase(0, pos + delim.length());
		}
		i++;	
	}
}


