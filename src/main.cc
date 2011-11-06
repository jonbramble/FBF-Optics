#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "../include/spr.hpp"
#include "../include/isolayer.hpp"


using namespace boost::numeric::ublas;

int main(int argc, char* argv[]) {

	const int N = 5000;
	int nlayers = 2;

	boost::numeric::ublas::vector<double> result(N);
	std::vector<Isolayer> vlayers(nlayers);

	Isolayer gold, SAM;
	gold.seteps(complex<double>(-12.0,0.8));
	gold.setd(49e-9);

	SAM.seteps(complex<double>(2.10,0));
	SAM.setd(20e-9);

	vlayers.push_back(gold);
	vlayers.push_back(SAM);

	Spr experiment(N);
	
	experiment.setstartangle(10); //not implemented yet
	experiment.setendangle(80);
	experiment.setna(1.85);
	experiment.setnf(1.33);
	experiment.setlambda(633e-9);
	experiment.setnlayers(nlayers);

	experiment.setlayers(vlayers);
	experiment.run();  //error handling required
	experiment.getdata(result);
	
	//cout << result << endl;
	
	return 0;
}
