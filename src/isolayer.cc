/*
 * Isolayer.cc
 *
 *  Created on: 05-Nov-2011
 *      Author: Jonathan Bramble
 */

#include "../include/isolayer.hpp"


void Isolayer::seteps(complex<double> _eps){ eps = _eps; }
std::complex<double> Isolayer::geteps(){ return eps; }
void Isolayer::setd(double _d){ d = _d; }
double Isolayer::getd(){ return d; }
