
void imagen::imprimirImagen(ofstream &ofs){
	ofs << formato << endl;
	ofs << x" " << y << endl;
	cout << n << endl;

	for(size_t i = 0; i < x; i++){
		for(size_t j = 0; j < y; j++){
			ofs << m.get_val_xpos(i,j) << " ";
		}
		ofs << endl
	}
}
