/*
 * layer.hpp
 *
 *  Created on: 15-Nov-2011
 *      Author: Jonathan Bramble
 */

#ifndef LAYER_H_
#define LAYER_H_

using namespace std;

class Layer {

	public:
		void setname(char* _name);
		char* getname();
		void setd(double _d);
		double getd();

	private:
		char* name;
		double d;
};

#endif
