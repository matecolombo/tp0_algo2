#ifndef _IMAGEN_H_INCLUDED_
#define _IMAGEN_H_INCLUDED_

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "/home/alan/Documentos/Algo2/tp0/tp0_matrix.h"
#include "pixel.h"
#include "complejo.h"

using namespace std;
typedef unsigned int uint;

class imagen
{	
private:
	string nombre, formato;
	uint x, y, n;
	double paso_x, paso_y;
	
	matriz<pixel<double>> * m;
	
public:
	imagen():x(0), y(0), n(0), paso_x(0), paso_y(0), m(0){};
	imagen(uint x, uint y, uint n);
	~imagen();

	uint getAncho(){return x;};
	uint getAlto(){return y;};
	uint getRes(){return n;};
	matriz<pixel<double>>* & getMatriz(){return m;};
	void setFormato(string u){formato = u;};
	void setAncho(uint u){x = u;};
	void setAlto(uint u){y = u;};
	void setRes(uint u){n = u;};
	void setPaso(){paso_x = 2 / (double)x; paso_y = 2 / (double)y;};
	void cargarMatriz(matriz<double> & mi);
	void imprimir(ostream &);
	void imprimir_pos(ostream &);
	void cargarParametros(string*);
	//void transformar(imagen &, Complejo (*method) (const Complejo &));
	double find_val_pos(double x, double y);
};

#endif //_IMAGEN_H_INCLUDED_
