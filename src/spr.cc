#include "../include/spr.hpp"
#include "../include/isolayer.hpp"

Spr::Spr(){
	data = boost::numeric::ublas::vector<double>(100);
	setnpts(100);
	// set defaults
}


Spr::Spr(int N){
	data = boost::numeric::ublas::vector<double>(N);
	setnpts(N);
	// set defaults
}

void Spr::setnpts(double _N){N = _N;}
void Spr::setna(double _na){na = _na;}
void Spr::setstartangle(double _sangle){sangle = _sangle;}
void Spr::setendangle (double _endangle){endangle = _endangle;}
void Spr::setnf(double _nf){nf = _nf;}
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
	static const complex<double> one = complex<double>(1,0); // can I define these elsewhere
	static const complex<double> zero = complex<double>(0,0);

	static const complex<double> eau = complex<double>(-12.0,0.8);
	static const double dau = 49e-9;
	static const double s_pi = static_cast<double>(3.141592653589793238462643383279502884197L);

	matrix<complex<double> > T(4,4), ILa(4,4), Lf(4,4), Temp(4,4), Tli(4,4);
	
	complex<double>	result, zcphif2, cphif;

	double phia, cphia, eta;
	double k0 = (2*s_pi)/lambda; // laser wavevector

	int k;

	for(k=0;k<N;k++)
	{
		phia = 0+k*((s_pi/2)/N); //input angle

		cphia = cos(phia); 
		eta = na*sin(phia); // x comp of wavevector
		zcphif2 = complex<double>(1-pow((na/nf)*sin(phia),2),0);

		cphif = sqrt(zcphif2);

		Fbfoptics::incmat(na,cphia,ILa);
		Fbfoptics::extmat(nf,cphif,Lf);

		std::vector<Isolayer>::size_type size = vlayers.size();

		if( size == 0 )
		{
			T = prod(ILa,Lf);
		}

		else if ( size == 1 )
		{
			Fbfoptics::gtmiso(vlayers[0].geteps(),k0,eta,-1*vlayers[0].getd(),Tli);
			Temp = prod(Tli,Lf);
			T = prod(Temp,Lf);
		}
		else 
		{
			int pen = (size-1);
			Fbfoptics::gtmiso(vlayers[pen].geteps(),k0,eta,-1*vlayers[pen].getd(),Tli);
			
			
			for( unsigned int i=(size-1); i==0; --i)  //better with reverse iterator
			{
				Fbfoptics::gtmiso(vlayers[i].geteps(),k0,eta,-1*vlayers[i].getd(),Tli);
				if(i==(size-1))
				{
					Temp = prod(Tli,Lf);
				}
				else 
				{
					Temp = prod(Temp,Tli);
				}
			}
		}

		data(k) = Fbfoptics::rpp(T);    // need to choose data
	}
}



