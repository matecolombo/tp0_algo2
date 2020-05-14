#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

#include "cmdline.h"
#include "matrix.h"
#include "complejo.h"

#define E 2.7172

using namespace std;

Complejo ide(const Complejo &);
Complejo exp(const Complejo &);

int main(int argc, char const *argv[])
{
	//Complejo z1(2,2);
	//Complejo z2 = exp(z1);
	//cout << endl << "f(z = " << z1 << ") = " << z2 << endl << endl;
	
	string delim = " ";
	string linea, token, formato;
	uint x, y, n, dato;
	size_t n_linea = 1;
	size_t pos = 0;
	
	ifstream fin("feep.txt");	//fin.open("feep.txt", ios::in) Se abre el archivo en modo lectura

	if(fin.bad())				//fin.fail()
	{
		cout << "fallo la apertura del archivo";
		cin.get();
		return 1;				//exit(1);
	}

	// Procesamiento de las primeras lineas con info
	while(!fin.eof()){
		pos = 0;
		getline(fin, linea);
		
		if(linea[0] == '#'){
			n_linea++;
			continue;
		}

		if(n_linea == 1)
			formato = linea;
			
		if(n_linea == 3){
			pos = linea.find(delim);
			token = linea.substr(0, pos);	
			x = stoi (token, 0, 10);		
			linea.erase(0, pos + delim.length());
			token = linea.substr(0, pos);
			y = stoi (token, 0, 10);					
		}
		
		if(n_linea == 4){
			n = stoi (linea, 0, 10);
			break;	
		}
		n_linea++;	
	}

	cout << formato << ", " << x << ", " << y << ", " << n << ", " << n_linea << endl << endl;

	//Procesamiento del resto de lineas
	Matrix<uint> img(y, x);
	uint i = 0, j = 0;
	while(!fin.eof() && i < y)
	{
		getline(fin, linea);
		j = pos = 0; 
		while(j<x)
		{	
			pos = linea.find(delim);
			token = linea.substr(0, pos);
			if(istringstream(token) >> dato){	
				img.fill_pos(i, j, dato);
				j++;
			}
			linea.erase(0, pos + delim.length());
		}
		i++;	
	}
	img.print_matrix();

	Matrix<uint> img2(img);

	
	img2.print_matrix();

	fin.close();
	
	return 0;
}


Complejo ide(const Complejo & z)
{
	return z;
}

//e^z = e^a.(cos b + j.sen b)
Complejo exp(const Complejo & z)
{
	Complejo f_z;

	f_z.setRe(cos(z.im()));
	f_z.setIm(sin(z.im()));

	return f_z*pow(E, z.re());
}
