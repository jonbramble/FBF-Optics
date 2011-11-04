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

using namespace boost::numeric::ublas;
using namespace std;

class Fbfoptics {

public:
	Fbfoptics();
	void incmat(const double, const double, matrix<complex<double> >&);
	void extmat(const double, const complex<double>, matrix<complex<double> >&);
	void dietens(const double,const double,const double,const double,const double,const double, const double, matrix<double>&);
	void gtmiso(const complex<double>,const double,const double,const double, matrix<complex<double> >&);
};








/*
#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>

int incmat(gsl_matrix_complex * ILa, double na, double cphia);
int extmat(gsl_matrix_complex * Lf, double nf, gsl_complex cphif);
int dietens(gsl_matrix * ep, double eav, double dem, double S, double stheta, double ctheta, double sphi, double cphi);
void diffpropmat(gsl_matrix * Delta, gsl_matrix * ep, double eta);
double rpp(gsl_matrix_complex * M);
void gtmiso(gsl_matrix_complex * Tiso, gsl_complex eiso, double k0, double eta, double diso);
void gtm(gsl_matrix_complex * T, gsl_matrix * Delta, double k0, double h);
void expm(gsl_matrix_complex * L, gsl_complex t, gsl_matrix * m);
*/
#endif /* FBFOPTICS_H_ */




