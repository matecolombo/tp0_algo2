#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "imagen.h"
#include "tp0_matrix.h"
#include "pixel.h"

//----- Carga un objeto imagen a partir del flujo de entrada
void imagen::cargar(istream & iss)
{
	string linea, token, delim = " ";
	size_t pos, n_linea = 1;

	//----- Procesamiento de las primeras lineas con inf	

	while(!(iss.eof())){
		pos = 0;
		getline(iss, linea);
		
		if(linea[0] == '#'){
			n_linea++;
			continue;
		}
		if(n_linea == 1){
			formato = linea;
		}			
		if(n_linea == 3){
			pos = linea.find(delim);
			token = linea.substr(0, pos);
			istringstream(token) >> ancho;
			linea.erase(0, pos + delim.length());
			token = linea.substr(0, pos);
			istringstream(token) >> alto;
		}		
		if(n_linea == 4){
			istringstream(linea) >> resolucion;
			break;	
		}
		n_linea++;
	}
	setPaso();
	matriz<double> m_aux(alto, ancho);
	uint i = 0, j = 0;
	double dato;

	//----- Procesamiento del resto de lineas
	
	while(!iss.eof() && i < alto)
	{
		getline(iss, linea);
		j = pos = 0; 
		while(j < ancho)
		{	
			pos = linea.find(delim);
			token = linea.substr(0, pos);
			if(istringstream(token) >> dato){	
				m_aux.fill_pos(i, j, dato);
				j++;
			}
			linea.erase(0, pos + delim.length());
		}
		i++;	
	}
	cargarMatriz(m_aux);
}

//----- Carga una matriz de pixeles a partir de una numerica
void imagen::cargarMatriz(matriz<double> & mi)
{	
	pixel<double> pix;
	m = new matriz<pixel<double>>(alto, ancho);
	
	for (uint i = 0; i < alto; ++i){
		for (uint j = 0; j < ancho; ++j){
			pix.setPos(-1 + j*paso_ancho, 1 - i*paso_alto);
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
	matriz<double> m_f(alto, ancho);
	//img_f.getMatriz() = new matriz<pixel<double>>(alto, ancho);
	img_f.setFormato(formato);
	img_f.setAncho(x);
	img_f.setAlto(alto);
	img_f.setRes(n);
	
	for (uint i = 0; i < alto; ++i)
	{
		for (uint j = 0; j < ancho; ++j)
		{
			z.setRe(-1 + j*paso_ancho); z.setIm(1 - i*paso_alto);
			//fz = f(z);			
			
			m_f.fill_pos(i, j, find_val_pos(z.getRe(), z.getIm()));
		}		
	}	
	//m_f.print_matriz();
	img_f.cargarMatriz(m_f);
}
*/
//----- Carga un objeto imagen a partir de otra imagen
void imagen::copiar(imagen & img_o)
{
	formato = img_o.getFormato();
	ancho = img_o.getAncho();
	alto = img_o.getAlto();
	resolucion = img_o.getRes();
	setPaso();
	m = new matriz<pixel<double>>(*(img_o.getMatriz()));	
}

//----- Transforma la imagen en base a una función
void imagen::transformar(Complejo (*f) (const Complejo &))
{	
	Complejo z, fz;
	double color = 0;
	matriz<double> m_f(alto, ancho);
	//m_f.print_matriz();
	
	for (uint i = 0; i < alto; ++i)
	{
		for (uint j = 0; j < ancho; ++j)
		{	
			z.setRe(-1 + j*paso_ancho); z.setIm(1 - i*paso_alto);
			fz = f(z);
			//fz = z;
			color = search_val_pos(fz);
			m_f.fill_pos(i, j, color);
		}
	}
	//m_f.print_matriz();
	cargarMatriz(m_f); 
	return;
}

//----- Busca un valor a partir de un complejo
double imagen::search_val_pos(const Complejo & fz)
{	
	double color = 0;
	double re = 0, im = 0;
	double re_o = fz.getRe();
	double im_o = fz.getIm();

	//cout << "(" << re_o << "," << im_o << ") ";

	for (uint i = 0; i < alto; ++i)
	{
		for (uint j = 0; j < ancho; ++j)
		{
			color = (m->get_val_xpos(i, j)).getVal();
			re = (m->get_val_xpos(i, j)).getX();
			im = (m->get_val_xpos(i, j)).getY();

			
			if((re_o > re-paso_ancho/2) && (re_o < re+paso_ancho/2))
				if((im_o > im-paso_alto/2) && (im_o < im+paso_alto/2))
					return color;
			/*
			if((re_o > re-ERROR) && (re_o < re+ERROR))
				if((im_o > im-ERROR) && (im_o < im+ERROR))
					return color;
			*/
			//cout << color << " ";
		}
		//cout << endl;
	}	
	return 0;
}

//----- Imprime la imagen en el flujo de salida
void imagen::imprimir(ostream & ofs)
{	
	ofs << endl;
	ofs << formato << endl;
	ofs << ancho << "x" << alto << endl;
	ofs << resolucion << endl;

	if(m != NULL){
		for(uint i = 0; i < alto; i++){
			for(uint j = 0; j < ancho; j++){
				ofs << (m->get_val_xpos(i,j)).getVal() << " ";
			}
			ofs << endl;
		}
	}
}
void imagen::imprimir_comp(ostream & ofs)
{	
	ofs << endl;
	for(uint i = 0; i < alto; i++){
		for(uint j = 0; j < ancho; j++)
			(m->get_val_xpos(i,j)).emitir();
		ofs << endl;
	}
}
imagen::~imagen()
{
	//m->~matriz();
}
Complejo expz(const Complejo & z)
{
	Complejo f_z;

	f_z.setRe(cos(z.getIm()));
	f_z.setIm(sin(z.getIm()));

	return f_z*pow(E, z.getRe());
}