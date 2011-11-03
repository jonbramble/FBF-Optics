#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "../include/fbfoptics.hpp"
using namespace boost::numeric::ublas;


int main(int argc, char* argv[]) {

	Fbfoptics test;

	/*matrix<double> m1 (3, 3), m2 (3, 3), m3(3,3);
    	for (unsigned i = 0; i < std::min (m1.size1 (), m2.size1 ()); ++ i)
        for (unsigned j = 0; j < std::min (m1.size2 (), m2.size2 ()); ++ j)
            m1 (i, j) = m2 (i, j) = 3 * i + j;

	m3 = prod (m1, m2);

	std::cout << m3 << std::endl;
    	std::cout << prod (m1, m2) << std::endl;*/

	test.incmat(2.0,5.0);
	test.extmat(2.0,5.0);

	matrix<complex<double> > R(4,4); 

	R = prod (test.ILa, test.Lf);
	
	std::cout << test.ILa << std::endl;	
	std::cout << test.Lf << std::endl;
	
	std::cout << R << std::endl;
	std::cout << prod(test.ILa,test.Lf) << std::endl;
	
	return 0;

}
