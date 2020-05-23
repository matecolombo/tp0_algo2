#ifndef _TP0_H_INCLUDED_
#define _TP0_H_INCLUDED_

#include "complejo.h"

#define IDENTITY_METHOD "z"
#define EXP_METHOD "exp(z)"
#define E 2.7172

using namespace std;

Complejo (*method) (const Complejo &);
static void opt_input(string const &);
static void opt_output(string const &);
static void opt_method(string const &);
static void opt_help(string const &);
Complejo ide(const Complejo &);
Complejo exp(const Complejo &);

#endif