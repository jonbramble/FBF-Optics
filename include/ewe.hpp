/*
 * ewe.hpp
 * Copyright (C) Jonathan Bramble 2011
 * 
FBF-Optics is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FBF-Optics is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef EWE_H
#define EWE_H

#include "fbfoptics.hpp"
#include "isolayer.hpp"

class Ewe: public Fbfoptics {
		
 public:
	Ewe();
	
	void setstartangle(double _sangle);
	void setendangle (double _endangle);
	void setna( double _na);
	void setnf( double _nf);
	void setnlayers(double _size);
	void setlayers(std::vector<Isolayer> _layers);
	void setlambda(double _lambda);
	
	void run();
	void getdata(boost::numeric::ublas::vector<double>& ret_data);
 
		

};

#endif
