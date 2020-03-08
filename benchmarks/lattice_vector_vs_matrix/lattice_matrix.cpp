template<typename Node, int nomial>
std::ostream& operator << (std::ostream& os, Lattice_matrix<Node, nomial>& lattice){
	for(int i = 0; i < lattice.size1(); i++){
		os << '[';
		for(int j = 0; j <= i; j++){
			os << lattice(i, j);
			if(j != i) os << ", ";
		}
		os << ']';
	}
	return os;
};
