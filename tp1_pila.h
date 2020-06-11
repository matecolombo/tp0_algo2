#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

#include <iostream>
#include "/home/alan/Documentos/Algo2/clases/NodeT.h"

template <class T> class pila
{
private:
	template <class T1> class node
	{
	private:
		T info;
		node<T1> * next;
	
	public:
		node(){info = 0; next = NULL;};
		node(T1 x){info = x; next = NULL;};
		node(T1 x, node<T1> * p): info(x), next(p){}; 
		node(const node<T1> & n){info = n.info; next = n.next;};
		void setInfo(T1 x){info = x;};
		void setNext(node<T> * n){next = n;};
		T1 getInfo(){return info;};
		node<T1> * getNext(){return next;};
		void emit(){std::cout << info << "-> ";};
	};

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
