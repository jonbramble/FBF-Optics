#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "../include/fbfoptics.hpp"
using namespace boost::numeric::ublas;


int main(int argc, char* argv[]) {

	Fbfoptics test;

	/*
	matrix<double> m1 (3, 3), m2 (3, 3), m3(3,3), Ap(3,3);
    	for (unsigned i = 0; i < std::min (m1.size1 (), m2.size1 ()); ++ i)
        for (unsigned j = 0; j < std::min (m1.size2 (), m2.size2 ()); ++ j)
            m1 (i, j) = m2 (i, j) = 3 * i + j;

	cout << m2 << endl;

	bool a = InvertMatrix(m2,Ap);
	
	cout << a << endl;

    	cout << Ap << endl;
	cout << prod(Ap,m2) << endl;

	//m3 = prod (m1, m2);

	//std::cout << m3 << std::endl;
    	//std::cout << prod (m1, m2) << std::endl;*/

	matrix<complex<double> > R(4,4), ILa(4,4), Lf(4,4); 

	test.incmat(2.0,5.0,ILa);
	test.extmat(2.0,5.0,Lf);

	R = prod (ILa, Lf);
	
	std::cout << ILa << std::endl;	
	std::cout << Lf << std::endl;
	
	std::cout << R << std::endl;
	std::cout << prod(ILa,Lf) << std::endl;
	
	return 0;

}
