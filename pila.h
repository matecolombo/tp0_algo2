#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

#include <iostream>
#include "/home/alan/Documentos/Algo2/clases/NodeT.h"

template <class T> class pila
{
private:
	node<T> * cima;

public:
	pila():cima(0){};
	~pila();

	void push(T);		//Agrega elemento en el tope
	T pop();			//Extrae elemento del tope
	T tope();			//Muestra el elemento del tope
	bool esta_vacia();
};
template <class T> bool pila<T>::esta_vacia()
{
	return (!cima)? true: false;
}
template <class T> void pila<T>::push(T dato)
{
	cima = new node<T>(dato, cima);
}
template <class T> T pila<T>::pop()
{
	T dato = cima->getInfo();
	node<T> * aux = cima;
	cima = cima->getNext();
	delete aux;
	return dato;
}
template <class T> T pila<T>::tope()
{
	return cima->getInfo();
}
template <class T> pila<T>::~pila()
{
	while(cima)
		pop();
}

#endif //PILA_H_INCLUDED
