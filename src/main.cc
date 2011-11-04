#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "../include/fbfoptics.hpp"
using namespace boost::numeric::ublas;


int main(int argc, char* argv[]) {

	Fbfoptics spr;
	matrix<complex<double> > T(4,4), ILa(4,4), Lf(4,4), Temp(4,4), Tau(4,4);

	static const complex<double> one = complex<double>(1,0);
	static const complex<double> zero = complex<double>(0,0);
	complex<double>	result, zcphif2, cphif;

	zero_matrix<complex<double> > zmatrix(4,4);

	double phia, cphia, eta;

	static const complex<double> eau = complex<double>(-12.0,0.8);
	static const double dau = 49e-9;

	static const double s_pi = static_cast<double>(3.141592653589793238462643383279502884197L);

	double k0 = (2*s_pi)/633e-9; // laser wavevector

	double na = 1.85;  // prism index
	double nf = 1.333; // water index

	int k;

	static const int N = 10;

	//can we thread by breaking into parts
	for(k=0;k<10;k++)
	{
		phia = 0+k*((M_PI/2)/N); //input angle

		cphia = cos(phia); 
		eta = na*sin(phia); // x comp of wavevector
		zcphif2 = complex<double>(1-pow((na/nf)*sin(phia),2),0);

		cphif = sqrt(zcphif2);

		cout << cphif << endl;

		spr.incmat(na,cphia,ILa);
		spr.extmat(nf, cphif, Lf);

		spr.gtmiso(eau,k0,eta,-dau,Tau);
		
		

		Temp = prod(ILa,Tau);
		T = prod(Temp,Lf);

		cout << T << endl;
		
		//cout << phia << " " << spr.rpp(T) << endl;  // output result here

		T = zmatrix;// reset T for loop
	}

	return 0;
}
