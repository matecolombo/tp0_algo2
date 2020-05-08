#ifndef _COMPLEJO_H_INCLUDED_
#define _COMPLEJO_H_INCLUDED_

#include <iostream>

class Complejo {
	double re_, im_;
public:
	Complejo();
	Complejo(double);
	Complejo(double, double);
	Complejo(const Complejo &);
	Complejo const &operator=(Complejo const &);
	Complejo const &operator*=(Complejo const &);
	Complejo const &operator+=(Complejo const &);
	Complejo const &operator-=(Complejo const &);
	~Complejo();

	double re() const;
	double im() const;
	double abs() const;
	double abs2() const;
	Complejo const &conjugar();
	Complejo const conjugado() const;
	bool zero() const;

	friend Complejo const operator+(Complejo const &, Complejo const &);
	friend Complejo const operator-(Complejo const &, Complejo const &);
	friend Complejo const operator*(Complejo const &, Complejo const &);
	friend Complejo const operator/(Complejo const &, Complejo const &);
	friend Complejo const operator/(Complejo const &, double);

	friend bool operator==(Complejo const &, double);
	friend bool operator==(Complejo const &, Complejo const &);

    friend bool operator!=(Complejo const &, double);
	friend bool operator!=(Complejo const &, Complejo const &);

	friend std::ostream &operator<<(std::ostream &, const Complejo &);
	friend std::istream &operator>>(std::istream &, Complejo &);
};

#endif
