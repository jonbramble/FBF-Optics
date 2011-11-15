/*
 * isolayer.hpp
 * Copyright (C) Jonathan Bramble 2011
 * 
FBF-Optics is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gtk-testrun is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef ISOLAYER_H_
#define ISOLAYER_H_

#include <complex>
#include "layer.hpp"

using namespace std;

class Isolayer: public Layer {	

	public:
		void seteps(complex<double> _eps);
		complex<double> geteps();
	private:
		complex<double> eps;
};

#endif
