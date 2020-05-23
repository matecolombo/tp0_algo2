#ifndef _PIXEL_H_INCLUDED_
#define _PIXEL_H_INCLUDED_

#include <iostream>
#include <iomanip>

using namespace std;
typedef unsigned int uint;

template <class T> class pixel{
private:	
	T x, y;
	T val;

public:
	pixel():x(0), y(0), val(0){};
	pixel(T x_, T y_):x(x_), y(y_), val(0){};
	pixel(T x_, T y_, T val_):x(x_), y(y_), val(val_){};
	~pixel(){};

	//ostream & operator<<(ostream & os)const{return os << "(" << x << "," << y << ") ";};
	
	void setPos(T x_, T y_){x = x_; y = y_;};
	void setVal(T x){val = x;};
	T getX(){return x;};
	T getY(){return y;};
	T & getVal(){return val;}
	
	void emitir(){cout<<setprecision(2)<<"("<<x<<","<<y<<","<<val<<") ";};
};

#endif //_PIXEL_H_INCLUDED_
