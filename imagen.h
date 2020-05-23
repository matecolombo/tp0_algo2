#ifndef _IMAGEN_H_INCLUDED_
#define _IMAGEN_H_INCLUDED_

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "tp0_matrix.h"
#include "pixel.h"
#include "complejo.h"

#define ERROR 0.01

using namespace std;
typedef unsigned int uint;

Complejo expz(const Complejo &);

class imagen
{	
private:
	string nombre, formato;
	uint ancho, alto, resolucion;
	double paso_ancho, paso_alto;
	
	matriz<pixel<double>> * m;
	
public:
	imagen():ancho(0), alto(0), resolucion(0), paso_ancho(0), paso_alto(0), m(0){};
	~imagen();

	string getFormato(){return formato;};
	uint getAncho(){return ancho;};
	uint getAlto(){return alto;};
	uint getRes(){return resolucion;};
	matriz<pixel<double>>* & getMatriz(){return m;};
	void setFormato(string u){formato = u;};
	void setAncho(uint u){ancho = u;};
	void setAlto(uint u){alto = u;};
	void setRes(uint u){resolucion = u;};
	void setPaso(){paso_ancho = 2 / (double)ancho; paso_alto = 2 / (double)alto;};
	void cargarMatriz(matriz<double> & mi);
	void cargar(istream &);
	void copiar(imagen &);
	void imprimir(ostream &);
	void imprimir_comp(ostream &);
	void transformar(Complejo (*method) (const Complejo &));
	double search_val_pos(const Complejo &);
};

#endif //_IMAGEN_H_INCLUDED_
