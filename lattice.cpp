template<typename Node, int nomial>
Lattice<Node, nomial>::Lattice(const int N): tree(N)
{
	for(size_t i = 0; i < N; i++){
		tree[i] = std::vector<Node>(i + 1);
	}
};
	
template<typename Node, int nomial>
std::vector<Node>& Lattice<Node, nomial>::operator [] (const int i){
	return tree[i];
};

template<typename Node, int nomial>
typename Lattice<Node, nomial>::iterator Lattice<Node, nomial>::begin() const{
	return tree.begin();
};

template<typename Node, int nomial>
typename Lattice<Node, nomial>::iterator Lattice<Node, nomial>::end() const{
	return tree.end();
};

template<typename Node, int nomial>
std::size_t Lattice<Node, nomial>::size() const{
	return tree.size();
};

template<typename Node, int nomial>
std::size_t Lattice<Node, nomial>::maxIndex() const{
	return tree.size() - 1;
};

template<typename Node, int nomial>
std::ostream& operator << (std::ostream& os, const Lattice<Node, nomial>& lattice){
	for(auto& v : lattice){
		os << '\n';
		for(auto& n : v){
			os << n << ", ";
		}
	}
	return os;
};
