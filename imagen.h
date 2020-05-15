#ifndef _IMAGEN_H_INCLUDED_
#define _IMAGEN_H_INCLUDED_

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "matrix.h"
#include "pixel.h"
#include "complejo.h"

using namespace std;
typedef unsigned int uint;

class imagen
{	
private:
	string nombre, formato;
	uint x, y, n;
	Matrix<pixel<double>> * m;
	
public:
	imagen(){};
	~imagen(){};

	uint getAncho(){return x;};
	uint getAlto(){return y;};
	void getDim(uint* i, uint*j){*i = x; *j = y;};
	void cargarMatriz(Matrix<double> & mi);
	void imprimir();
	void cargarParametros(string*);
	void imprimirParametros();

};


#endif //_IMAGEN_H_INCLUDED_
