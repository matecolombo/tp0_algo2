#ifndef _IMAGEN_H_INCLUDED_
#define _IMAGEN_H_INCLUDED_

#include <iostream>
#include <iomanip>
#include "tp1_matrix.h"
#include "complejo.h" 	//Esto se deberia sacar luego de implementar el algoritmo flashero
						//al igual que el prototipo de exp abajo del todo
#define CHAR_COMENTARIO '#'
#define STR_DELIM " "
#define LINEA_FORMATO 1
#define LINEA_DIMENSION 3
#define LINEA_RESOLUCION 4
#define DOMX_PCOMP 2
#define DOMY_PCOMP 2


class imagen
{
private:

	class pixel
	{
	private:
		double x;
		double y;
		double val;

	public:
		pixel():x(0), y(0), val(0){};
		pixel(double x_, double y_, double val_):x(x_), y(y_), val(val_){};
		pixel(double x_, double y_):x(x_), y(y_){};
		pixel(double val_):val(val_){};
		~pixel(){};

		void setX(double x_){x = x_;}
		void setY(double y_){y = y_;}
		void setPos(double x_, double y_){x = x_; y = y_;}
		void setVal(double val_){val = val_;}
		double getX(){return x;}
		double getY(){return y;}
		double getVal(){return val;}
		//void operator<<();
		void emitir(){cout<<setprecision(2)<<"("<<x<<","<<y<<","<<val<<") ";}
	};

	string formato;
	uint alto, ancho;
	uint resolucion;
	double paso_alto;
 	double paso_ancho;
 	matriz<pixel> * m;

public:
	imagen():alto(0), ancho(0), resolucion(0), paso_alto(0), paso_ancho(0), m(0){};
	imagen(uint x, uint y, uint res){m = new matriz<pixel>(y, x); ancho = x; alto = y; resolucion = res;};
	~imagen();

	void setFormato(string formato_){formato = formato_;}
	void setResolucion(uint resolucion_){resolucion = resolucion_;}
	void setAlto(uint alto_){alto = alto_;}
	void setAncho(uint ancho_){ancho = ancho_;}
	void setPasoAlto(double paso_alto_){paso_alto = paso_alto_;}
	void setPasoAncho(double paso_ancho_){paso_ancho = paso_ancho_;}
	void setMatriz(matriz<pixel> * m_){m = m_;};
	string getFormato(){return formato;}
	uint getResolucion(){return resolucion;}
	uint getAlto(){return alto;}
	uint getAncho(){return ancho;}
	double getPasoAlto(){return paso_alto;}
	double getPasoAncho(){return paso_ancho;}
	matriz<pixel> * getMatriz(){return m;}	

	void cargarMatriz(matriz<double> & mi);
	void cargarPgm(istream & iss);
	void copiar(imagen &);
	void imprimir(ostream &);
	void imprimirPixel(ostream &);
	void transformar(string funcion);
	double buscarValor(const Complejo &);
	void calcularPaso(){paso_ancho = 2 / (double)ancho; paso_alto = 2 / (double)alto;};
	
};

Complejo exp(const Complejo &);

#endif //_IMAGEN_H_INCLUDED_