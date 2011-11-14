#include "../include/spr.hpp"
#include "../include/isolayer.hpp"
#include <boost/math/complex/asin.hpp>

Spr::Spr(){
	data = boost::numeric::ublas::vector<double>(100);
	setnpts(100);
	// set defaults
}

Spr::Spr(int N){
	data = boost::numeric::ublas::vector<double>(N);
	setnpts(N);
}

void Spr::setnpts(double _N){N = _N;}
void Spr::setna(double _na){na = _na;}
void Spr::setstartangle(double _sangle){sangle = _sangle;}
void Spr::setendangle (double _endangle){endangle = _endangle;}
void Spr::setnf(double _nf){nf = _nf;}
void Spr::setnlayers(double _size){size = _size;}
void Spr::setlayers(std::vector<Isolayer> _layers){   // must check these have been called
	vlayers = _layers;
}		
	
void Spr::setlambda(double _lambda){lambda = _lambda;}

void Spr::getdata(boost::numeric::ublas::vector<double>& ret_data){
	ret_data=data;
}

void Spr::run()
{
	//make tests
	static const double s_pi = static_cast<double>(3.141592653589793238462643383279502884197L);

	matrix<complex<double> > T(4,4), ILa(4,4), Lf(4,4), Temp(4,4), Tli(4,4);
	identity_matrix<complex<double> > Id(4,4);

	complex<double>	result, zcphif2, phif, cphif;

	double phia, cphia, eta;
	double k0 = (2*s_pi)/lambda; // laser wavevector
	int k;
	
	// need some kind of generalised loop
	for(k=0;k<N;k++)
	{
		double radrng = ((endangle-sangle)*s_pi)/180;	
		phia = sangle+k*(radrng/N); //input angle

		cphia = cos(phia); 
		eta = na*sin(phia); // x comp of wavevector
		zcphif2 = complex<double>(1-pow((na/nf)*sin(phia),2),0);  // this always picks the correct sector
		cphif = sqrt(zcphif2);
		
		Fbfoptics::incmat(na,cphia,ILa);
		Fbfoptics::extmat(nf,cphif,Lf);
		
		prod_seq.push_back(ILa); 
		for ( iso_it=vlayers.begin() ; iso_it<vlayers.end(); iso_it++ ){//iterate over elements
			eps = iso_it->geteps();
			d = iso_it->getd();
			Fbfoptics::gtmiso(eps,k0,eta,-1*d,Tli);
			prod_seq.push_back(Tli);
		}
		prod_seq.push_back(Lf); //add at end

		Temp = Id; // resets temp

		for ( mat_it=prod_seq.rbegin() ; mat_it<prod_seq.rend(); mat_it++ ){//iterate over elements
			T = prod(*mat_it,Temp);
			Temp = T;
		}
	
		prod_seq.clear();

		data(k) = Fbfoptics::rpp(T);    // need to choose data rpp rps etc
		std::cout << phia << "	" << Fbfoptics::rpp(T) << std::endl;
	}
}
