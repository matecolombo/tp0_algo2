
#include <iostream>
#include <cmath>
#include "complejo.h"


using namespace std;

Complejo::Complejo() : re_(0), im_(0)
{
}

Complejo::Complejo(double r) : re_(r), im_(0)
{
}

Complejo::Complejo(double r, double i) : re_(r), im_(i)
{
}

Complejo::Complejo(Complejo const &c) : re_(c.re_), im_(c.im_)
{
}

Complejo const &
Complejo::operator=(Complejo const &c)
{
	re_ = c.re_;
	im_ = c.im_;
	return *this;
}

Complejo const &
Complejo::operator*=(Complejo const &c)
{
	double re = re_ * c.re_
	         - im_ * c.im_;
	double im = re_ * c.im_
	         + im_ * c.re_;
	re_ = re, im_ = im;
	return *this;
}

Complejo const &
Complejo::operator+=(Complejo const &c)
{
	double re = re_ + c.re_;
	double im = im_ + c.im_;
	re_ = re, im_ = im;
	return *this;
}

Complejo const &
Complejo::operator-=(Complejo const &c)
{
	double re = re_ - c.re_;
	double im = im_ - c.im_;
	re_ = re, im_ = im;
	return *this;
}

Complejo::~Complejo()
{
}

double
Complejo::re() const
{
	return re_;
}

double Complejo::im() const
{
	return im_;
}

double
Complejo::abs() const
{
	return std::sqrt(re_ * re_ + im_ * im_);
}

double
Complejo::abs2() const
{
	return re_ * re_ + im_ * im_;
}

Complejo const &
Complejo::conjugar()
{
	im_*= -1;
	return *this;
}

Complejo const
Complejo::conjugado() const
{
	return Complejo(re_, -im_);
}

bool
Complejo::zero() const
{
#define ZERO(x) ((x) == +0.0 && (x) == -0.0)
	return ZERO(re_) && ZERO(im_) ? true : false;
}

Complejo const
operator+(Complejo const &x, Complejo const &y)
{
	Complejo z(x.re_ + y.re_, x.im_ + y.im_);
	return z;
}

Complejo const
operator-(Complejo const &x, Complejo const &y)
{
	Complejo r(x.re_ - y.re_, x.im_ - y.im_);
	return r;
}

Complejo const
operator*(Complejo const &x, Complejo const &y)
{
	Complejo r(x.re_ * y.re_ - x.im_ * y.im_,
	          x.re_ * y.im_ + x.im_ * y.re_);
	return r;
}

Complejo const
operator/(Complejo const &x, Complejo const &y)
{
	return x * y.conjugado() / y.abs2();
}

Complejo const
operator/(Complejo const &c, double f)
{
	return Complejo(c.re_ / f, c.im_ / f);
}

bool
operator==(Complejo const &c, double f)
{
	bool b = (c.im_ != 0 || c.re_ != f) ? false : true;
	return b;
}

bool
operator==(Complejo const &x, Complejo const &y)
{
	bool b = (x.re_ != y.re_ || x.im_ != y.im_) ? false : true;
	return b;
}

bool
operator!=(Complejo const &c, double f)
{
	bool b = (c.im_ != 0 || c.re_ != f) ? true : false;
	return b;
}

bool
operator!=(Complejo const &x, Complejo const &y)
{
	bool b = (x.re_ != y.re_ || x.im_ != y.im_) ? true : false;
	return b;
}

ostream &
operator<<(ostream &os, const Complejo &c)
{
	return os << "(" 
	          << c.re_
	          << ", " 
	          << c.im_
	          << ")";
}

istream &
operator>>(istream &is, Complejo &c)
{
	int good = false;
	int bad  = false;
	double re = 0;
	double im = 0;
	char ch = 0;

	if (is >> ch
	    && ch == '(') {
		if (is >> re
		    && is >> ch
		    && ch == ','
		    && is >> im
		    && is >> ch
		    && ch == ')')
			good = true;
		else
			bad = true;
	} else if (is.good()) {
		is.putback(ch);
		if (is >> re)
			good = true;
		else
			bad = true;
	}

	if (good)
		c.re_ = re, c.im_ = im;
	if (bad)
		is.clear(ios::badbit);
	
	return is;
}

