// runtest.cc - Infraestructura mínima para implementar un
// entorno primitivo de pruebas automáticas.
//
// El programa recibe como entrada el nombre de un archivo;
// cuyas líneas describen cada uno de los casos de prueba.
//
// Después de leer este archivo, este programa ejecuta caso
// por caso. Para cada caso, se debe proveer un archivo de
// referencia, conteniendo la salida esperada. Una vez que la
// ejecución del caso termina, nuestro programa compara la 
// salida generada, con la salida provista. Si resultan ser 
// iguales, pasamos al siguiente caso. De ser distintos, la 
// prueba no pasa.
//
// El formato del archivo de entrada, es simple: consiste de
// una seria de columnas, separadas por uno o más caracteres
// de espacio:
//
// nombre SP status SP input SP reference SP output SP command ...
//
// o nombre: es el nombre del caso de prueba. Obviamente, no
// puede contener espacios, ya que esto estaría introduciendo
// ambigüedad.
//
// o status: número entero, que indica el código de retorno
// esperado. Al terminar la ejecución del caso de prueba, se
// pasa a verificar dicho código. Si no coinciden, se considera
// un error.
//
// o input: nombre del archivo de entrada. Por el momento este
// parámetro debe figurar, pero no se usa para nada.
//
// o reference: nombre del archivo de referencia. El mismo debe
// contener la salida esperada de la ejecución del caso.
//
// o output: nombre del archivo de salida.
//
// o command: línea de comando a usar para invocar la ejecución
// del caso de prueba en cuestión. Aquí podremos usar espacios 
// y metacaracteres, ya que los programas se invocarán via el
// shell del sistema operativo.
//
// $Date: 2012/09/14 13:08:33 $
//
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Windows tiene system(3), pero no parece tener <sys/wait.h>, 
// WIFEXITED(), WEXITSTAT(), etc; así que tendremos que llenar 
// los agujeros nosotros mismos.
//
// DJGPP, por otra parte, viene con estas macros definidas en
// el header <sys/wait.h>, muy parecido a lo que pasa en UNIX.
//
#if defined(DJGPP) || defined(FREEBSD6)
#include <sys/wait.h>
#define DETECTED
#endif

#ifdef WIN32
#define WEXITSTATUS(w) ((w) & 0xff)
#define WIFEXITED(w)   (((w) & ~0xffUL) == 0)
#define DETECTED
#endif

#ifndef DETECTED
#include <sys/wait.h>
#endif

// Implementación de la clase status: permite manejar códigos
// de estado, devueltos por procesos usando std::exit(), por
// ejemplo.
//
// La clase provee un operador de entrada con formato, >>, que
// acepta dos tipos de sintaxis: código numérico (ejemplo, 1),
// o la negación de un código numérico (ejemplo, ~0). Esto 
// último es util para especificar portablemente casos de prueba
// de errores, en donde el programa termina abruptamente usando,
// por ejemplo, std::abort(). En esos casos, el código numérico
// retornado, puede variar de un sistema operativo a otro, pero
// siempre será no-nulo.
//
// 
class status {
	int status_;
	int negate_;
public:
	status();
	status(status const &);
	status const &operator=(status const &);
	friend bool operator==(status const &, int);
	friend bool operator==(int, status const &);
	friend bool operator!=(status const &, int);
	friend bool operator!=(int, status const &);
	friend istream &operator>>(istream &, status &);
	~status();
};

status::status() : status_(0), negate_(0)
{
}

status::status(status const &st) : status_(st.status_),
                                   negate_(st.negate_)
{
}

status const &
status::operator=(status const &st)
{
	if (this != &st) {
		status_ = st.status_;
		negate_ = st.negate_;
	}
	return *this;
}

bool
operator==(status const &st, int n)
{
	bool result(st.status_ == n);
	if (st.negate_)
		result = !result;
	return result;
}

bool
operator==(int code, status const &st)
{
	return st == code;
}

bool
operator!=(status const &st, int code)
{
	return !(st == code);
}

bool
operator!=(int code, status const &st)
{
	return !(code == st);
}

istream &
operator>>(istream &is, status &st)
{
	char ch;
	int code;
	int neg = 0;
	int okay = 0;

	if (is >> ch
	    && ch == '~') {
		neg = 1;
		if (is >> code
		    && code >= 0)
			okay = 1;
	} else {
		is.putback(ch);
		if (is >> code 
		    && code >= 0)
			okay = 1;
	}

	if (okay) {
		st.negate_ = neg;
		st.status_ = code;
	} else {
		is.clear(ios::badbit);
	}

	return is;
}

status::~status()
{
}

// Clase test: implementa la unidad de prueba.
//
class test {
	string in_;
	string out_;
	string ref_;
	string prog_;
	string name_;
	vector<string> args_;
	status stat_;

	test();
public:
	test(string const &,
	     string const &, 
	     string const &, 
	     string const &, 
	     string const &, 
	     vector<string> const &,
	     status const &);
	test(test const &);
	test const &operator=(test const &);
	~test();
	int run() const;
	int cmp(int) const;
	string name() const;
};

/*
 * Global state.
 */
vector<test> tests;

test::test()
{
	cerr << "Not implemented." << endl;
	abort();
}

test::test(string const &in,
           string const &out, 
           string const &ref,
           string const &prog,
           string const &name,
           vector<string> const &args,
           status const &stat)
	: in_(in), 
	  out_(out), 
	  ref_(ref), 
	  prog_(prog), 
	  name_(name), 
	  args_(args),
	  stat_(stat)
{
}

test::test(test const &t)
	: in_(t.in_), 
	  out_(t.out_), 
	  ref_(t.ref_), 
	  prog_(t.prog_), 
	  name_(t.name_), 
	  args_(t.args_),
	  stat_(t.stat_)
{
}

test::~test()
{
}

test const &
test::operator=(test const &t)
{
	if (&t != this) {
		in_ = t.in_;
		out_ = t.out_;
		ref_ = t.ref_;
		prog_ = t.prog_;
		name_ = t.name_;
		args_ = t.args_;
		stat_ = t.stat_;
	}

	return *this;
}

int
test::run() const
{
	string cmdline;
	int result;
	size_t i;

	cmdline = prog_;
	for (i = 0; i < args_.size(); ++i) {
		cmdline += " ";
		cmdline += args_[i];
	}

	if ((result = system(cmdline.c_str())) < 0) {
		cerr << "Cannot run "
		     << name_
		     << " (command line: "
		     << cmdline
		     << ")."
		     << endl;
		exit(1);
	}

	return result;
}

int
test::cmp(int exit_st) const
{
	string sos;
	string srs;
	int os_ok;
	int rs_ok;

	// Primero, nos aseguramos que el programa haya finalizado
	// de ejecutarse por voluntad propia. Es un error que esto
	// no suceda.
	//
	if (WIFEXITED(exit_st) == 0) {
		cerr << "Abnormal test case termination: "
		     << name_
		     << "."
		     << endl;
		exit(1);
	}

	// Ok. Habiendo finalizado por voluntad propia, pasamos a
	// verificar que el código de salida emitido por el programa
	// esté a la altura de las expectativas.
	//
	if (WEXITSTATUS(exit_st) != stat_)
		return 1;

	// Los códigos de salida coinciden. Para poder considerar a
	// la prueba como exitosa, necesitamos verificar que la salida
	// del programa sea lo que debería ser.
	//
	if (out_ != "n/a"
	    || ref_ != "n/a") {
		ifstream os(out_.c_str());
		ifstream rs(ref_.c_str());

		// Primero, chequeamos que los streams esten en buen estado.
		//
		if (!os.good()) {
			cerr << "Cannot open output stream "
			     << out_
			     << "."
			     << endl;
			exit(1);
		}
		if (!rs.good()) {
			cerr << "Cannot open reference stream "
			     << ref_
			     << "."
			     << endl;
			exit(1);
		}

		// Comparamos el contenido de los archivos de salida y de
		// referencia, ignorando diferencias de espacios entre palabras.
		//
		while (1) {
			os_ok = (os >> sos) ? 1 : 0;
			rs_ok = (rs >> srs) ? 1 : 0;

			if (os_ok && rs_ok) {
				if (sos == srs)
					continue;
				else
					return 1;
			}

			if (os.eof()
			    && rs.eof())
				break;

			return 1;
		}
	}

	// Ok ...
	//
	return 0;
}

string
test::name() const
{
	return name_;
}

int
read_line(istream &is, string &s)
{
	char c;

	s.clear();

	while (1) {
		if (!is.get(c)) {
			if (is.eof())
				return -1;
			cerr << "Cannot get line: stream error."
			     << endl;
			exit(1);
		}

		if (c == '\n')
			break;

		s.append(1, c);
	}

	return 0;
}

int
read_test(string const &line)
{
	string copy(line);
	istringstream iss;
	status stat;
	string in;
	string out;
	string ref;
	string prog;
	string name;
	string arg;
	vector<string> args;
	size_t i;
	char c;

	for (i = 0; i < copy.length(); ++i) {
		if (copy[i] == '#') {
			copy.erase(i);
			break;
		}
	}

	iss.str(copy);

	if (!(iss >> c))
		return 0;
	iss.putback(c);

	if (!(iss >> name)
	    || !(iss >> stat)
	    || !(iss >> in)
	    || !(iss >> out)
	    || !(iss >> ref)
	    || !(iss >> prog))
		return -1;
	while (iss >> arg)
		args.push_back(arg);
	tests.push_back(test(in, out, ref, prog, name, args, stat));

	return 0;
}

void
read_config(string const &path)
{
	ifstream ifs;
	istream *is;
	string line;
	int lnum;

	if (path != "-") {
		ifs.open(path.c_str(), ifstream::in);
		is = &ifs;
	} else {
		is = &cin;
	}

	if (!is->good()) {
		cerr << "Cannot open "
		     << path
		     << "."
		     << endl;
		exit(1);
	}

	for (lnum = 1; 1; ++lnum) {
		if (read_line(*is, line))
			return;
		if (read_test(line) < 0) {
			cerr << "Parse error at line "
			     << lnum
			     << "."
			     << endl;
			exit(1);
		}
	}
}

int
run_tests()
{
	int err = 0;
	int out;
	int st;
	size_t i;

	for (i = 0; i < tests.size(); ++i) {
		test &t = tests[i];

		st = t.run();
		out = t.cmp(st);
		err += out ? 1 : 0;
		cerr << "("
		     << i
		     << ") run test "
		     << t.name()
		     << ": "
		     << (out != 0 ? "error" : "ok")
		     << endl;
	}

	if (err)
		cerr << err
		     << " test"
		     << (err != 1 ? "s" : "")
		     << " failed."
		     << "\n";
	else
		cerr << "All tests ok."
		     << endl;

	return err != 0 ? 1 : 0;
}

int
main(int argc, char * const argv[])
{
	if (argc >= 2)
		read_config(argv[1]);
	if (run_tests() != 0)
		return 1;
	return 0;
}
