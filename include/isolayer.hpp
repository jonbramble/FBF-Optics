/*
 * isolayer.hpp
 *
 *  Created on: 05-Nov-2011
 *      Author: Jonathan Bramble
 */

#ifndef ISOLAYER_H_
#define ISOLAYER_H_

#include <complex>

using namespace std;

class Isolayer {
		
	public:
	
		void seteps(complex<double> _eps);
		complex<double> geteps();

		void setd(double _d);
		double getd();
	
	private:

		complex<double> eps;
		double d; 

};

#endif
