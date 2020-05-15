#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

//#include "/home/alan/Documentos/Algo2/clases/cmdline.h"
#include "/home/alan/Documentos/Algo2/clases/matrix.h"
#include "/home/alan/Documentos/Algo2/clases/complejo.h"
#include "/home/alan/Documentos/Algo2/clases/imagen.h"
//#include "/home/alan/Documentos/Algo2/clases/pixel.h"

#define E 2.7172

using namespace std;

void extraer_parametros(ifstream &, string*);
void crear_matriz(ifstream &, Matrix<double> &);
Complejo ide(const Complejo &);
Complejo exp(const Complejo &);

int main(int argc, char const *argv[])
{
	string param[4];
	imagen img;

	ifstream fin("feep.txt");		
	if(fin.bad())					
	{
		cout << "fallo la apertura del archivo";
		cin.get();
		return 1;					
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
