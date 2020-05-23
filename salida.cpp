
void imagen::imprimirImagen(ofstream &ofs, Matrix<double> & mi){
	ofs << formato << endl;
	ofs << x" " << y << endl;
	cout << n << endl;

	for(size_t i = 0; i < mi.get_alto(); i++){
		for(size_t j = 0; j < mi.get_ancho(); j++){
			ofs << m.get_val_xpos(i,j) << " ";
		}
		ofs << endl
	}
}