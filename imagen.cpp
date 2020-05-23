#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <math.h>
#include "imagen.h"
#include "/home/alan/Documentos/Algo2/tp0/tp0_matrix.h"
#include "pixel.h"

imagen::imagen(uint ancho, uint alto, uint resolucion)
{
	x = ancho;
	y = alto;	
	n = resolucion;
	setPaso();
	m = NULL;
}

void imagen::cargarParametros(string param[])
{
	formato = param[0];
	istringstream(param[1]) >> x;
	istringstream(param[2]) >> y;
	istringstream(param[3]) >> n;
	setPaso();
}

void imagen::cargarMatriz(matriz<double> & mi)
{	
	pixel<double> pix;
	m = new matriz<pixel<double>>(y, x);
	
	for (uint i = 0; i < y; ++i){
		for (uint j = 0; j < x; ++j){
			pix.setPos(-1 + j*paso_x, 1 - i*paso_y);
			pix.setVal(mi.get_val_xpos(i, j));			
			m->fill_pos(i, j, pix);			
		}
	}
}
/*
void imagen::transformar(imagen & img_f, Complejo (*f) (const Complejo &))
{
	Complejo z, fz;
	//pixel<double> pix;
	matriz<double> m_f(y, x);
	//img_f.getMatriz() = new matriz<pixel<double>>(y, x);
	img_f.setFormato(formato);
	img_f.setAncho(x);
	img_f.setAlto(y);
	img_f.setRes(n);
	
	for (uint i = 0; i < y; ++i)
	{
		for (uint j = 0; j < x; ++j)
		{
			z.setRe(-1 + j*paso_x); z.setIm(1 - i*paso_y);
			//fz = f(z);			
			
			m_f.fill_pos(i, j, find_val_pos(z.getRe(), z.getIm()));
		}		
	}	
	//m_f.print_matriz();
	img_f.cargarMatriz(m_f);
}

void imagen::transformar(imagen & img_f, Complejo (*f) (const Complejo &))
{
	return;
}*/
double imagen::find_val_pos(double u, double v)
{	
	//uint auxi, auxj;
	//double aux;
	//double errx = 10, erry = 10;
	/*
	for (uint i = 0; i < y; ++i)
	{
		for (uint j = 0; j < x; ++j)
		{
			aux = (m->get_val_xpos(i, j)).getX();			
			if(abs(aux-u) < errx){
				errx = abs(aux-u);
				auxi = i;
			}
			aux = (m->get_val_xpos(i, j)).getY();			
			if(abs(aux-v) < erry){
				erry = abs(aux-v);
				auxj = j;
			}			
		}
	}	
	return (m->get_val_xpos(auxi, auxj)).getVal();
	*/
	return 0;//(m->get_val_xpos(auxi, auxj)).getVal();
	
}

void imagen::imprimir(ostream & ofs)
{	
	ofs << endl;
	ofs << formato << endl;
	ofs << x << "x" << y << endl;
	ofs << n << endl;

	for(uint i = 0; i < y; i++){
		for(uint j = 0; j < x; j++){
			ofs << (m->get_val_xpos(i,j)).getVal() << " ";
		}
		ofs << endl;
	}
	ofs << endl;
}
void imagen::imprimir_pos(ostream & ofs)
{	
	ofs << endl;
	for(uint i = 0; i < y; i++){
		for(uint j = 0; j < x; j++)
			(m->get_val_xpos(i,j)).emitir();
		ofs << endl;
	}
	ofs << endl;
}
imagen::~imagen()
{
	m->~matriz();
}