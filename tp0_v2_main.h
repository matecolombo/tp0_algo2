#ifndef _MAIN_H_INCLUDED_
#define _MAIN_H_INCLUDED_

#include "/home/alan/Documentos/Algo2/clases/matrix.h"

#define IDENTITY_METHOD "z"
#define EXP_METHOD "exp(z)"
#define E 2.7172

using namespace std;

Complejo (*method) (const Complejo &);

void extraer_parametros(fstream &, string*);
void crear_matriz(fstream &, Matrix<double> &);
static void opt_input(string const &);
static void opt_output(string const &);
static void opt_method(string const &);
static void opt_help(string const &);
Complejo ide(const Complejo &);
Complejo exp(const Complejo &);

#endif