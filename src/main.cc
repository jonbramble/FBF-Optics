#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "../include/spr.hpp"
#include "../include/isolayer.hpp"


using namespace boost::numeric::ublas;

int main(int argc, char* argv[]) {

	int N = 100;
	int nlayers = 1;

	boost::numeric::ublas::vector<double> result(N);
	std::vector<Isolayer> vlayers(nlayers);

	Isolayer gold;
	gold.seteps(complex<double>(-12.0,0.8));
	gold.setd(49e-9);

	vlayers.push_back(gold);


	Spr experiment(N);
	
	experiment.setstartangle(10); //not implemented yet
	experiment.setendangle(80);
	experiment.setna(1.85);
	experiment.setnf(1.33);
	experiment.setlayers(vlayers);
	
	experiment.setlambda(633e-9);
	
	experiment.run();  //error handling required
	experiment.getdata(result);
	
	cout << result << endl;
	
	// do something with data
	
	return 0;
}
