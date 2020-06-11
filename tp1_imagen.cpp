#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "tp1_imagen.h"
#include "tp1_pila.h"


//----- Carga un objeto imagen a partir del flujo de entrada
void imagen::cargarPgm(istream & ifs)
{
	string linea, token, delim = STR_DELIM;
	size_t i = 0, j = 0; 
	size_t pos = 0, n_linea = 1;
	double dato;
	matriz<double> m_aux;

	while(!ifs.eof()){
		j = pos = 0;
		getline(ifs, linea);

		if(linea[0] == CHAR_COMENTARIO){
			n_linea++;
			continue;
		}
		if(n_linea == LINEA_FORMATO){
			//Validar
			formato = linea;
			n_linea++;
			continue;
		}			
		if(n_linea == LINEA_DIMENSION){
			pos = linea.find(delim);
			token = linea.substr(0, pos);			
			istringstream(token) >> ancho;
			//Validar
			m_aux.setAncho(ancho);

			linea.erase(0, pos + delim.length());
			token = linea.substr(0, pos);
			istringstream(token) >> alto;
			//Validar
			m_aux.setAlto(alto);

			m_aux.setMatriz(alto, ancho);
			n_linea++;
			continue;
		}	
		if(n_linea == LINEA_RESOLUCION){
			istringstream(linea) >> resolucion;
			//Validar
			n_linea++;
			continue;	
		}
		while(j < ancho && i < alto)
		{	
			pos = linea.find(delim);
			token = linea.substr(0, pos);
			if(istringstream(token) >> dato){
				m_aux.cargarPos(i, j, dato);
				j++;

			}
			linea.erase(0, pos + delim.length());
		}
		i++;	
	}
	calcularPaso();
	cargarMatriz(m_aux);		
}

//----- Carga una matriz de pixeles a partir de una numerica
void imagen::cargarMatriz(matriz<double> & mi)
{	
	pixel pix;
	double x, y;
	m = new matriz<pixel>(alto, ancho);
	
	//Validar

	for (uint i = 0; i < alto; ++i){
		for (uint j = 0; j < ancho; ++j){
			x = -DOMX_PCOMP/2 + j*paso_ancho;
			y = DOMY_PCOMP/2 - i*paso_alto;
	
			pix.setPos(x, y);
			pix.setVal(mi.getValPos(i, j));
			m->cargarPos(i, j, pix);	
		}
	}
}

//----- Carga un objeto imagen a partir de otra imagen
void imagen::copiar(imagen & img_o)
{
	formato = img_o.getFormato();
	ancho = img_o.getAncho();
	alto = img_o.getAlto();
	paso_ancho = img_o.getPasoAncho();
	paso_alto = img_o.getPasoAlto();
	resolucion = img_o.getResolucion();
	m = new matriz<pixel>(*(img_o.getMatriz()));	
}

//----- Transforma la imagen en base a una función
void imagen::transformar(string funcion)
{	
	Complejo z, fz;
	double color = 0;
	double x, y;
	matriz<double> m_f(alto, ancho);
	//cout << funcion << endl;

	//transformacion del formato de la funcion

	//prueva de la pila
	pila<char> p;
	p.push('a');
	p.push('b');
	p.push('c');
	cout << p.pop() << endl;
	cout << p.pop() << endl;
	cout << p.pop() << endl;
	

	for (uint i = 0; i < alto; ++i)
	{
		for (uint j = 0; j < ancho; ++j)
		{	
			x = -DOMX_PCOMP/2 + j*paso_ancho;
			y = DOMY_PCOMP/2 - i*paso_alto;
	
			z.setRe(x); z.setIm(y);
			//fz = z;
			fz = exp(z);
			color = buscarValor(fz);
			m_f.cargarPos(i, j, color);
		}
	}
	cargarMatriz(m_f); 
	return;
}
//e^z = e^a.(cos b + j.sen b)
Complejo exp(const Complejo & z)
{
	Complejo f_z;

	f_z.setRe(cos(z.getIm()));
	f_z.setIm(sin(z.getIm()));

	return f_z*exp(z.getRe());
}

//----- Busca un valor a partir de un complejo
double imagen::buscarValor(const Complejo & fz)
{	
	double color = 0;
	double re = 0, im = 0;
	double re_o = fz.getRe();
	double im_o = fz.getIm();

	for (uint i = 0; i < alto; ++i)
		for (uint j = 0; j < ancho; ++j)
		{
			color = (m->getValPos(i, j)).getVal();
			re = (m->getValPos(i, j)).getX();
			im = (m->getValPos(i, j)).getY();

			
			if((re_o > re-paso_ancho/2) && (re_o < re+paso_ancho/2))
				if((im_o > im-paso_alto/2) && (im_o < im+paso_alto/2))
					return color;
		}	
	return 0;
}

//----- Imprime la imagen en el flujo de salida
void imagen::imprimir(ostream & ofs)
{	
	ofs << formato << endl;
	ofs << ancho << " " << alto << endl;
	ofs << resolucion << endl;
		
	if(m != NULL){
		for(uint i = 0; i < alto; i++){
			for(uint j = 0; j < ancho; j++){
				ofs << (m->getValPos(i,j)).getVal() << " ";
			}
			ofs << endl;
		}
	}
	ofs << endl;
}

//----- Imprime la imagen con toda la informacion del pixel en el flujo de salida
void imagen::imprimirPixel(ostream & ofs)
{	
	ofs << endl;
	for(uint i = 0; i < alto; i++){
		for(uint j = 0; j < ancho; j++)
			(m->getValPos(i,j)).emitir();
		ofs << endl;
	}
}

//----- Destructor
imagen::~imagen()
{	
	m->borrarMatriz();
}
