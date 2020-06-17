#ifndef _MATRIZ_H_INCLUDED_
#define _MATRIZ_H_INCLUDED_

#include <iostream>
#include <stdlib.h>

using namespace std;
typedef unsigned int uint;

template <class T>
class matriz {
    private:
        uint ancho;
        uint alto;
        T **m;

    public:
        matriz();
        matriz(int y, int x);
        matriz(const matriz &m);
        ~matriz();
        
        void setAncho(uint ancho_){ancho = ancho_;}
        void setAlto(uint alto_){alto = alto_;}
        void setM(T** m_){m = m_;}
        void setMatriz(uint alto, uint ancho);
        uint getAlto(){return alto;}
        uint getAncho(){return ancho;}
        T** getMatriz(){return m;};
        T getValPos(uint, uint);
        void cargarPos(int, int, T);
        void imprimirMatriz();
};

// Constructor por defecto
template<typename T> matriz<T>::matriz()
{
    alto = 4;
    ancho = 4;
}
 
// Constructor copia
template<typename T> matriz<T>::matriz(const matriz &m)
{
    setAlto(m.alto);
    setAncho(m.ancho);
    setM(m.m);
}
 
// Constructor por parámetro
template<typename T> matriz<T>::matriz(int y , int x)
{
    ancho = x;
    alto = y;
    m = new T*[alto];
 
    for (uint i = 0; i < alto; i++) {
        m[i] = new T[ancho];
    }
}

//  Crear matriz
template<typename T> void matriz<T>::setMatriz(uint alto_, uint ancho_)
{
  m = new T*[alto_];
 
    for (uint i = 0; i < alto_; i++) {
        m[i] = new T[ancho_];
    }  
}

// Llenar posicion especifica
template<typename T> void matriz<T>::cargarPos(int i, int j, T dato)
{
    m[i][j] = dato;
} 

// Retornar valor de una cierta posicion
template<typename T> T matriz<T>::getValPos(uint i, uint j)
{
    return m[i][j];
}

// Imprimir matriz
template<typename T> void matriz<T>::imprimirMatriz()
{
    for (uint i = 0; i < alto; i++) {
        for (uint j = 0; j < ancho; j++) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

// Destructor
template<typename T> matriz<T>::~matriz()
{
    for (uint i = 0; i < alto; i++) {
        delete[] m[i];
    }
    delete[] m;
}
#endif //_MATRIZ_H_INCLUDED_

