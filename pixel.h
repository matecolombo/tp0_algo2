#ifndef _PIXEL_H_INCLUDED_
#define _PIXEL_H_INCLUDED_

#include <iostream>
#include "complejo.h"

using namespace std;
typedef unsigned int uint;

template <class T> class pixel{
private:
	Complejo pos;
	T val;

public:
	pixel():pos(0), val(0){};
	pixel(Complejo c):pos(c), val(0){};
	pixel(Complejo c, T x):pos(c), val(x){};
	~pixel(){};

	//ostream & operator<<(ostream & os, const pixel &){return os << pixel.pos << ":" << pixel.val;};
	void setPos(Complejo & c){pos = c;};
	void setPos(uint i, uint j){pos.setRe(i); pos.setIm(j);};
	void setVal(T x){val = x;};
	Complejo & getPos(){return pos;};
	T & getVal(){return val;}
	
	void emitir(){cout<<"("<<pos.getRe()<<","<<pos.getIm()<<","<<val<<")";};
};

#endif //_PIXEL_H_INCLUDED_
