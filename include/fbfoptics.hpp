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
/*
 * @file fbfoptics.hpp
 * @brief All the code required to do 4x4 optics on stratified media. Following the methods of Berreman. Can be used for both isotropic and aniostropic layers, but entry and exit media must be isotropic. isotropic layers tested, but aniostropic not yet tested
 * 
 * 
 * @author Jonathan Bramble
 * @date 25/06/2009
 */
class Fbfoptics {

public:
	/// The entrance matrix
	static void incmat(const double, const double, matrix<complex<double> >&);
	/// The exit matrix
	static void extmat(const double, const complex<double>, matrix<complex<double> >&);
	/// The dielectric tensor
	static void dietens(const double,const double,const double,const double,const double,const double, const double, matrix<double>&);
	/// The general transfer matrix for isotropic layers
	static void gtmiso(const complex<double>,const double,const double,const double, matrix<complex<double> >&);
	/// The general transfer matrix for anisotropic layers
	static void gtm(const matrix<double>& Delta, const double k0, const double h, matrix<complex<double> >& T);
	/// The differential propagation matrix Delta
	static void diffpropmat(const matrix<double> ep, const double eta, matrix<double>& Delta);
	/// Calculates from the total transfer matrix the rpp reflectivity co-efficient
	static double rpp(const matrix<complex<double> >& M);
	/// Returns the product of the sequence of transfer matricies
	static matrix<complex<double> > total_trans(std::vector<boost::numeric::ublas::matrix<complex<double> > > prod_seq);
};

#endif /* FBFOPTICS_H_ */




