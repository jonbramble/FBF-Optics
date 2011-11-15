/*
 * isolayer.hpp
 *
 *  Created on: 05-Nov-2011
 *      Author: Jonathan Bramble
 */

#ifndef ISOLAYER_H_
#define ISOLAYER_H_

#include <complex>
#include "Layer.hpp"

using namespace std;

class Isolayer: public Layer {	

	public:
		void seteps(complex<double> _eps);
		complex<double> geteps();
	private:
		complex<double> eps;
};

#endif
