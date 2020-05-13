#include <iostream>
#include <math.h>
#include "cmdline.h"
#include "matrix.h"
#include "complejo.h"

#define E 2.7172

using namespace std;

Complejo ide(const Complejo &);
Complejo exp(const Complejo &);

int main(int argc, char const *argv[])
{
	Complejo z1(2,2);
	Complejo z2 = exp(z1);

	cout << endl << "f(z = " << z1 << ") = " << z2 << endl << endl;


	return 0;
}

//e^z = e^a.(cos b + j.sen b)
Complejo ide(const Complejo & z)
{
	return z;
}

Complejo exp(const Complejo & z)
{
	Complejo f_z;

	f_z.setRe(cos(z.im()));
	f_z.setIm(sin(z.im()));

	return f_z*pow(E, z.re());
}
