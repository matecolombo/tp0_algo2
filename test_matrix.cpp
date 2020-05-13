#include <iostream>
#include "matrix.h"

#include "complejo.h" 

using namespace std;
 
int main()
{
    // Para no generar los mismos números aleatorios
    srand(time(NULL));
 
    int n_rows;
    int n_cols;
 
    int col_1;
    int col_2;
    int row_1;
    int row_2;
    int scalar;
 
    cout << "Ingresa nro de filas: " << endl;
    cin >> n_rows;
    cout << "Ingresa nro de columnas: " << endl;
    cin >> n_cols;
    cout << endl;
 
    Matrix<Complejo> a(n_rows, n_cols);
    Matrix<Complejo> b(n_rows, n_cols);
 
    // Matriz para almacenar el resultado de las operaciones
    Matrix<Complejo> c(n_rows, n_cols);
 
    a.fill_random();
    b.fill_random();
 
    cout << "********** Operaciones básicas con la Matriz A **********" << endl;
    cout << "Matriz A " << endl;
    a.print_matrix();
 
    //cout << "El mayor de la Matriz es: " << a.get_max() << endl;
    //cout << "El menor de la Matriz es: " << a.get_min() << endl;
    //cout << "La moda de la Matrix es: " << a.get_mode() << endl;
    cout << (a.isSymmetric() ? "" : "No") << " Es simétrica." << endl;
    cout << (a.isIdentity() ? "" : "No") << " Es identidad." << endl;
    cout << endl;
 
    cout << "Ingresa el escalar: " << endl;
    cin >> scalar;
    a.multiply_by_scalar(scalar);
    a.print_matrix();
 
    cout << "Intercambio: Ingresa 2 columnas del 1 al " << n_cols << endl;
    cout << "Columna 1: " << endl;
    cin >> col_1;
    cout << "Columna 2: " << endl;
    cin >> col_2;
    a.swap_cols(col_1, col_2);
    a.print_matrix();
 
    cout << "Intercambio: Ingresa 2 filas del 1 al " << n_rows << endl;
    cout << "Fila 1: " << endl;
    cin >> row_1;
    cout << "Fila 2: " << endl;
    cin >> row_2;
    a.swap_rows(row_1, row_2);
    a.print_matrix();
 
    cout << "Transpuesta de A " << endl;
    a.get_transpose();
 
    cout << "********** Operaciones con matrices **********" << endl;
    cout << "Matriz A " << endl;
    a.print_matrix();
 
    cout << "Matriz B " << endl;
    b.print_matrix();
 
    cout << "Matriz A + B " << endl;
    c = a + b;
    c.print_matrix();
 
    cout << "Matriz A - B " << endl;
    c = a - b;
    c.print_matrix();
 
    cout << "Matriz A * B " << endl;
    c = a * b;
    c.print_matrix();
 
    a.delete_matrix();
    b.delete_matrix();
    c.delete_matrix();
 
    return 0;
}