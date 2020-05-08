#ifndef ARRAYTEMP_H
#define ARRAYTEMP_H

//Template para clase Array

//Declaraciones

template <class T>
class Array
{
    public:
        Array(); // constructor
        Array( const Array<T> & );
        Array(size_t);
        ~Array( );
        size_t getSize( ) const;
        Array <T> &operator=( const Array<T> & );
        bool operator==( const Array<T> & ) const;
        T &operator[ ]( size_t ) const;
        Array<T>& expand(size_t x);
        void emitir();

    private:
        size_t size;
        T *ptr;
};

//Definiciones

template <class T>
Array<T>::Array()
{
    size=10;
    ptr = new T[10];
}

template <class T>
Array<T>::Array(size_t x)
{
    if ((x<1)) size=10; else size=x;   
    ptr = new T[size];
}

template <class T>
Array<T>::Array( const Array<T> &init )
{
    size=init.size ;
    ptr = new T[ size ];
    for ( int i = 0; i < size; i++ )
    ptr[ i ] = init.ptr[ i ];
}

template <class T>
Array<T>::~Array()
{
    if (ptr)
    delete [ ] ptr;
}

template <class T>
size_t Array<T>::getSize() const { return size; }

template <class T>
Array<T>& Array<T>::operator=( const Array<T> &rigth )
{
    if ( &rigth != this )
    {
        if ( size != rigth.size )
        {
            T *aux;
            aux=new T[ rigth.size ];
            delete [] ptr;
            size =rigth.size ;
            ptr=aux;
            for ( int i = 0; i < size; i++ )
            {   
                ptr[ i ] = rigth.ptr[ i ];
            }
                return *this;
            }
        else
        {
            for ( int i = 0; i < size; i++ )
            {       
                ptr[ i ] = rigth.ptr[ i ];
            }
            return *this; // al retornar una referencia permite x = y = z;
        }
    }
    return *this;
}

template <class T>
bool Array<T>::operator==( const Array<T> &rigth ) const
{
    if ( size != rigth.size )
        return false;
    else
    for ( int i = 0; i < size; i++ )
        if ( ptr[ i ] != rigth.ptr[ i ] )
            return false;
    return true;
}

template <class T>
T& Array<T>::operator [ ]( size_t subscript ) const
{
    
    return ptr[ subscript ]; // retorna referencia
  
}

template <class T>
Array<T>& Array<T>::expand(size_t j)
{
    T * aux = new T[j];
    size_t i;
    for ( i = 0; i < size; i++ )
    {   
        aux[ i ] = ptr[ i ];
    }
    delete [] ptr;
    size = j;
    ptr = aux;
    return *this;
}

#endif