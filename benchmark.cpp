
template<class duration_unit>
void Benchmark<duration_unit>::start()
{
	t0 = std::chrono::system_clock::now();
	started = true;
};

template<class duration_unit>
int Benchmark<duration_unit>::stop()
{
	if(!started){
		std::cerr << "Benchmark wasn't started \n";
		return -1;
	}
	
	t1 = std::chrono::system_clock::now();
	return std::chrono::duration_cast<duration_unit>(t1 - t0).count();
};