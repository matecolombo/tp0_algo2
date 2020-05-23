#ifndef _MATRIZ_H_INCLUDED_
#define _MATRIZ_H_INCLUDED_

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "pixel.h"
using namespace std;
 
template <class T>
class matriz {
    private:
        int m_cols;
        int m_rows;
        T **m_matriz;

    public:
        matriz();
        matriz(int i, int j);
        matriz(const matriz &m);
        ~matriz();
 
        int get_alto(){return m_rows;};
        int get_ancho(){return m_cols;};
        T get_val_xpos(int, int);
        void delete_matriz();
        void fill_pos(int, int, T);
        void print_matriz();
        void print_matriz_img();   
};

// Constructor por defecto
template<typename T> matriz<T>::matriz()
{
    m_rows = 4;
    m_cols = 4;
}
 
// Constructor copia
template<typename T> matriz<T>::matriz(const matriz &m)
{
    *this = m;
}
 
// Constructor por parámetro
template<typename T> matriz<T>::matriz(int rows , int cols)
{
    m_cols = cols;
    m_rows = rows;
    m_matriz = new T*[m_rows];
 
    for (int i = 0; i < m_rows; i++) {
        m_matriz[i] = new T[m_cols];
    }
}

// Llenar posicion especifica
template<typename T> void matriz<T>::fill_pos(int i, int j, T dato)
{
    m_matriz[i][j] = dato;
} 

// Retornar valor de una cierta posicion
template<typename T> T matriz<T>::get_val_xpos(int x, int y)
{
    for (int i = 0; i < m_rows; ++i)
        for (int j = 0; j < m_cols; ++j)
            if((i == x) && (j == y))
                return m_matriz[i][j];
    return m_matriz[0][0];
}

// Imprimir Matriz
template<typename T> void matriz<T>::print_matriz()
{
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            cout << m_matriz[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

// Arreglarrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
template<typename T> void matriz<T>::print_matriz_img()
{
    cout << endl;  
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            //cout << (m_matriz[i][j]).getVal() << " ";
            //cout << setprecision(2) << "(" << (m_matriz[i][j]).getX() << "," << (m_matriz[i][j]).getY() << ") ";
            (m_matriz[i][j]).emitir();
        }
        cout << endl;
    }
    cout << endl;  
}

// Destructor
template<typename T> matriz<T>::~matriz()
{
    for (int i = 0; i < m_rows; i++) {
        delete[] m_matriz[i];
    }
    delete[] m_matriz;
}

#endif //_MATRIZ_H_INCLUDED_

