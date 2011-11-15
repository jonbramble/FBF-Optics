/*
 * layer.cc
 *
 *  Created on: 15-Nov-2011
 *      Author: Jonathan Bramble
 */

#include "../include/layer.hpp"

void Layer::setd(double _d){ d = _d; }
double Layer::getd(){ return d; }
void Layer::setname(char* _name){ name = _name; }
char* Layer::getname(){ return name; }
