#ifndef _TP0_CONFIG_H_INCLUDED_
#define _TP0_CONFIG_H_INCLUDED_

#include "complejo.h"

#define MSJ_CMDLINE_OK "Procesamiento de cmdline: ok"
#define MSJ_CARGA_OK "Carga: ok"
#define MSJ_COPIADO_OK "Copiado: ok"
#define MSJ_TRANSFORMACION_OK "Transformación: ok"
#define MSJ_IMPRESION_OK "Impresión: ok"
#define MSJ_FIN "Fin del programa."

#define MSJ_FUNCION_DESCONOCIDA "Funcion desconocida: "
#define FUNCION_IDENTIDAD "z"
#define FUNCION_EXPONENCIAL "exp(z)"
#define MSJ_ERROR_APERTURA "No se puede abrir el archivo: "
#define MSJ_AYUDA "-i [entrada] -o [salida] -f [funcion]"

Complejo (*funcion) (const Complejo &);

using namespace std;

static void opc_entrada(string const &);
static void opc_salida(string const &);
static void opc_funcion(string const &);
static void opc_ayuda(string const &);
Complejo ide(const Complejo &);
Complejo exp(const Complejo &);

#endif //_TP0_CONFIG_H_INCLUDED_