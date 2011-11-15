/*
 * anisolayer.hpp
 *
 *  Created on: 05-Nov-2011
 *      Author: Jonathan Bramble
 */

#ifndef ANISOLAYER_H_
#define ANISOLAYER_H_

#include "layer.hpp"

class Anisolayer: public Layer {	

	public:
		void setepsx(double _epsx);
		void setepsy(double _epsy);
		void setepsz(double _epsz);
		void settheta(double _theta);
		void setphi(double _phi);

		double getepsx();
		double getepsy();
		double getepsz();
		double gettheta();
		double getphi();

	private:
		double epsx, epsy, epsz, theta, phi;
};

#endif
