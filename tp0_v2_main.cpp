#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstring>

#include "tp0_v2_main.h"
#include "tp0_matrix.h"
#include "/home/alan/Documentos/Algo2/clases/cmdline.h"
#include "/home/alan/Documentos/Algo2/clases/imagen.h"

#include "/home/alan/Documentos/Algo2/clases/complejo.cpp"
#include "/home/alan/Documentos/Algo2/clases/imagen.cpp"
#include "/home/alan/Documentos/Algo2/clases/cmdline.cc"

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
	string param[4];
	imagen img_o;
	
	//----- Procesamiento de la linea de comando.
	cmdline cmdl(options);	
	cmdl.parse(argc, argv);

	//----- Procesamiento de las primeras lineas con inf	
	extraer_parametros(ifs, param);
	img_o.cargarParametros(param);
	//img.imprimirParametros();

	//----- Procesamiento del resto de lineas
	matriz<double> m(img_o.getAlto(), img_o.getAncho());
	crear_matriz(ifs, m);
	//m.print_matriz();

	//----- Creacion de la imagen inicial
	img_o.cargarMatriz(m);
	img_o.imprimir(*oss);		//Impresion comun
	img_o.imprimir_pos(*oss);	//impresion de posicion y valor

	//----- Creacion de imagen final
	//imagen img_f;
	//img_f.transformar(img_o, method);
	//img_f.imprimir(*oss);

	ifs.close();
	ofs.close();
	return 0;
}
void extraer_parametros(fstream & fin, string param[])
{	
	string linea, token, delim = " ";
	size_t pos, n_linea = 1;

	while(!(fin.eof())){
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

void crear_matriz(fstream & fin, matriz<double> & m)
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

