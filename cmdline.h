#ifndef _CMDLINE_H_INCLUDED_
#define _CMDLINE_H_INCLUDED_

#include <string>
#include <iostream>

#define OPT_DEFAULT   0
#define OPT_SEEN      1
#define OPT_MANDATORY 2

#define MSJ_ARGUMENTO_REQUERIDO "Se requiere un argumento para: "
#define MSJ_OPCION_DESCONOCIDA "Opcion desconocida: "
#define MSJ_OPCION "Opcion: "
#define MSJ_OBLIGATORIO "es obligatorio."
struct opcion_t {
	int has_arg;
	const char *short_name;
	const char *long_name;
	const char *def_value;
	void (*parse)(std::string const &); // Puntero a función de opciones
	int flags;
};

class cmdline {
	opcion_t *option_table;
	
	cmdline();
	
	int do_long_opt(const char *, const char *);
	int do_short_opt(const char *, const char *);
public:
	cmdline(opcion_t *);
	void parse(int, char * const []);
};

#endif
