// all we need to model a simple spr system

#ifndef SPR_H
#define SPR_H

#include "fbfoptics.hpp"
#include "isolayer.hpp"

class Spr {
		
	public:
	Spr();
	Spr(int N);
	
	void setstartangle(double _sangle);
	void setendangle (double _endangle);
	void setna( double _na);
	void setnf( double _nf);
	void setnlayers(double _size);
	void setlayers(std::vector<Isolayer> _layers);
	void setlambda(double _lambda);
	
	void run();
	void getdata(boost::numeric::ublas::vector<double>& ret_data);
	
	private:
		// layer class? good plan
	void setnpts(double _N);
	double na, nf,sangle, endangle, lambda;
	int N, size;

	
	boost::numeric::ublas::vector<double> data; // how can i pass the ref to the 'main' data allocation?
	std::vector<Isolayer> vlayers;
	std::vector<Isolayer>::iterator iso_it;
	std::vector<boost::numeric::ublas::matrix<complex<double> > >::reverse_iterator mat_it;
	std::vector<boost::numeric::ublas::matrix<complex<double> > > prod_seq;
	std::vector<boost::numeric::ublas::matrix<complex<double> > > prod_seq_temp;
	
	complex<double> eps;
	double d;
		
		

};



#endif
