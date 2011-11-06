/*
 * fbfoptics.h
 *
 *  Created on: 25-Jun-2009
 *      Author: Jonathan Bramble
 */

#ifndef FBFOPTICS_H_
#define FBFOPTICS_H_

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>

#include <complex>
#include "complex_methods.hpp"
#include "expm.hpp"

using namespace boost::numeric::ublas;
using namespace std;

class Fbfoptics {

public:
	static void incmat(const double, const double, matrix<complex<double> >&);
	static void extmat(const double, const complex<double>, matrix<complex<double> >&);
	static void dietens(const double,const double,const double,const double,const double,const double, const double, matrix<double>&);
	static void gtmiso(const complex<double>,const double,const double,const double, matrix<complex<double> >&);
	static void diffpropmat(const matrix<double> ep, const double eta, matrix<double>& Delta);
	static double rpp(const matrix<complex<double> >& M);
	static void gtm(const matrix<double>& Delta, const double k0, const double h, matrix<complex<double> >& T);
};

#endif /* FBFOPTICS_H_ */




