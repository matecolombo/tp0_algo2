#ifndef _TP1_H_INCLUDED_
#define _TP1_H_INCLUDED_

#define MSJ_CMDLINE_OK "Procesamiento de cmdline: ok"
#define MSJ_CARGA_OK "Carga: ok"
#define MSJ_COPIADO_OK "Copiado: o"
#define MSJ_TRANSFORMACION_OK "Transformación: ok"
#define MSJ_IMPRESION_OK "Impresión: ok"
#define MSJ_FIN "Fin del programa."

#define MSJ_AYUDA "-h -i [entrada] -o [salida] -f [funcion]"
#define MSJ_ERROR_APERTURA "No se puede abrir el archivo: "

using namespace std;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_function(string const &);
static void opt_help(string const &);

#endif //_TP1_H_INCLUDED_