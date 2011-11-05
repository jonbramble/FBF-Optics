// all we need to model a simple spr system

#ifndef SPR_H
#define SPR_H

#include "../include/fbfoptics.hpp"

class Spr {
		
	public:
	Spr(int N);
	
	void setstartangle(double _sangle);
	void setendangle (double _endangle);
	void setna( double _na);
	void setnf( double _nf);
	void setlayer( int _layers);
	void setlambda( double _lambda);
	void run();
	void getdata(boost::numeric::ublas::vector<double>& ret_data);
	
	private:
	
		// layer class? good plan
	void setnpts(double _N);
	double na, nf,sangle, endangle, lambda;
	int N, layers;
	boost::numeric::ublas::vector<double> data; // how can i pass the ref to the 'main' data allocation?
		
		

};



#endif
