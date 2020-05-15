#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "imagen.h"
#include "matrix.h"
#include "pixel.h"


/*
imagen::imagen(string nombre_archivo)
{
	uint pos, i, j, n_linea;
	string linea, token, delim = " ";
	pixel<double> pix;
	double dato;
	
	ifstream fin(nombre_archivo);	

	if(!fin.bad())				
	{
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
	Matrix<pixel<double>> m(y, x);
	i = j = 0;
	while(!fin.eof() && i < y)
	{
		getline(fin, linea);
		cout << linea << endl;
		j = pos = 0; 
		while(j<x)
		{	
			pos = linea.find(delim);
			token = linea.substr(0, pos);
			if(istringstream(token) >> dato){
				pix.setPos(i, j);
				pix.setVal(dato);
				m.fill_pos(i, j, pix);
				j++;
			}
			linea.erase(0, pos + delim.length());
		}
		i++;	
	}
	}
	else
		cout << "fallo la apertura del archivo";	

	m.print_matrix();
}
*/
void imagen::cargarMatriz(Matrix<double> & mi)
{	
	uint i, j;
	pixel<double> pix;
	Complejo c;
	m = new Matrix<pixel<double>>(mi.get_alto(), mi.get_ancho());
	for (i = 0; i < y; ++i)
		for (j = 0; j < x; ++j)
		{		
			c.setRe(i);
			c.setIm(j);
			pix.setPos(c);
			pix.setVal(mi.get_val_xpos(i, j));
			m->fill_pos(i, j, pix);
		}
}
void imagen::imprimir()
{	
	imprimirParametros();
	m->print_matrix_img();
}

void imagen::cargarParametros(string param[])
{
	formato = param[0];
	istringstream(param[1]) >> x;
	istringstream(param[2]) >> y;
	istringstream(param[3]) >> n;
}

void imagen::imprimirParametros()
{
	cout << endl << "Formato: " << formato << endl;
	cout << "Dimension: " << x << "x" << y << endl;
	cout << "Resolucion: " << n << endl << endl;
}
