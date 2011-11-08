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
	complex<double> eps;
	double d;
	
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

		if( size == 0 )
		{
			//cout << "size = 0" << endl;
			T = prod(ILa,Lf);
			
		}

		else if ( size == 1 )
		{
			cout << "size = 1" << endl;
			eps = vlayers[0].geteps();
			d = -1*vlayers[0].getd();
			cout << eps << endl;
			cout << d << endl;
			Fbfoptics::gtmiso(eps,k0,eta,d,Tli);
			Temp = prod(Tli,Lf);
			T = prod(ILa,Temp);
			
		}
		else if (size > 1 )
		{
			//cout << "size > 1" << endl;
			int pen = (size-1);
			
			eps = vlayers[pen].geteps();
			d = -1*vlayers[pen].getd(); // -ve sign is for optics reasons see shubert paper
			Fbfoptics::gtmiso(eps,k0,eta,d,Tli); // could change gtmiso to take vlayer as argument - for iso or no iso layers
			Temp = prod(Tli,Lf);

			for( unsigned int i=(pen-1); i==0; --i)  //better with reverse iterator
			{
				eps = vlayers[i].geteps();
				d = -1*vlayers[i].getd(); 

				Fbfoptics::gtmiso(eps,k0,eta,d,Tli);
				T = prod(Tli,Temp);
				Temp = T;  // not sure if Temp = Tli*Temp will work
			}

			T = prod(ILa,Temp);
		}

		data(k) = Fbfoptics::rpp(T);    // need to choose data
		std::cout << phia << "	" << Fbfoptics::rpp(T) << std::endl;
	}
}



