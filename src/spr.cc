#include "../include/spr.hpp"

Spr::Spr(int N){
	data = boost::numeric::ublas::vector<double>(N);
	setnpts(N);
}

void Spr::setnpts(double _N){N = _N;}
void Spr::setna(double _na){na = _na;}
void Spr::setstartangle(double _sangle){sangle = _sangle;}
void Spr::setendangle (double _endangle){endangle = _endangle;}
void Spr::setnf(double _nf){nf = _nf;}
void Spr::setlayer(int _layers){layers = _layers;}
void Spr::setlambda(double _lambda){lambda = _lambda;}

void Spr::getdata(boost::numeric::ublas::vector<double>& ret_data){
	ret_data=data;

}

void Spr::run()
{
	//make tests
	
	
	Fbfoptics spr;  //replace with class methods
	
	static const complex<double> one = complex<double>(1,0); // can I define these elsewhere
	static const complex<double> zero = complex<double>(0,0);

	static const complex<double> eau = complex<double>(-12.0,0.8);
	static const double dau = 49e-9;
	static const double s_pi = static_cast<double>(3.141592653589793238462643383279502884197L);

	matrix<complex<double> > T(4,4), ILa(4,4), Lf(4,4), Temp(4,4), Tau(4,4);
	
	complex<double>	result, zcphif2, cphif;

	zero_matrix<complex<double> > zmatrix(4,4);

	double phia, cphia, eta;
	double k0 = (2*s_pi)/lambda; // laser wavevector

	//double na = 1.85;  // prism index
	//double nf = 1.333; // water index

	int k;

	//can we thread by breaking into parts
	for(k=0;k<N;k++)
	{
		phia = 0+k*((s_pi/2)/N); //input angle

		cphia = cos(phia); 
		eta = na*sin(phia); // x comp of wavevector
		zcphif2 = complex<double>(1-pow((na/nf)*sin(phia),2),0);

		cphif = sqrt(zcphif2);

		spr.incmat(na,cphia,ILa);
		spr.extmat(nf, cphif, Lf);

		spr.gtmiso(eau,k0,eta,-dau,Tau);

		Temp = prod(ILa,Tau);
		T = prod(Temp,Lf);
	
		// need to choose data
		data(k) = spr.rpp(T);
		//cout << phia << " " << spr.rpp(T) << endl;  // output result here
		T = zmatrix; // reset T for loop
	}
}



