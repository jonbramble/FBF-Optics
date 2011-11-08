/*
 * fbfoptics.c
 *
 *  Created on: 25-Jun-2009
 *      Author: Jonathan Bramble
 */

//gtm
//outs

#include "../include/fbfoptics.hpp"

void Fbfoptics::incmat(const double na, const double cphia, matrix<complex<double> >& ILa){
	ILa(0,0) = complex<double>(0,0);
	ILa(0,1) = complex<double>(0,0);
	ILa(0,2) = complex<double>(0.5,0);
	ILa(0,3) = complex<double>(1/(2*na*cphia),0);

	ILa(1,0) = complex<double>(0,0);
	ILa(1,1) = complex<double>(0,0);
	ILa(1,2) = complex<double>(0.5,0);
	ILa(1,3) = complex<double>(-1/(2*na*cphia),0);

	ILa(2,0) = complex<double>(1/(2*cphia),0);
	ILa(2,1) = complex<double>(1/(2*na),0);
	ILa(2,2) = complex<double>(0,0);
	ILa(2,3) = complex<double>(0,0);

	ILa(3,0) = complex<double>(-1/(2*cphia),0);
	ILa(3,1) = complex<double>(1/(2*na),0);	
	ILa(3,2) = complex<double>(0,0);
	ILa(3,3) = complex<double>(0,0);
}

void Fbfoptics::extmat(const double nf, const complex<double> cphif, matrix<complex<double> >& Lf)
{
	complex<double> znf= complex<double>(nf,0.0);
	complex<double> zk = znf*cphif;
	
	Lf(0,0) = complex<double>(0,0);
	Lf(0,1) = complex<double>(0,0);
	Lf(0,2) = cphif;
	Lf(0,3) = complex<double>(0,0);

	Lf(1,0) = complex<double>(0,0);
	Lf(1,1) = complex<double>(0,0);
	Lf(1,2) = znf;
	Lf(1,3) = complex<double>(0,0);

	Lf(2,0) = complex<double>(1.0,0.0);
	Lf(2,1) = complex<double>(0,0);
	Lf(2,2) = complex<double>(0,0);
	Lf(2,3) = complex<double>(0,0);

	Lf(3,0) = zk;
	Lf(3,1) = complex<double>(0,0);
	Lf(3,2) = complex<double>(0,0);
	Lf(3,3) = complex<double>(0,0);
}

void Fbfoptics::dietens(double eav, double dem, double S, double stheta, double ctheta, double sphi, double cphi, matrix<double>& ep)
{
	matrix<double> A (3,3), ea(3,3), Ap(3,3), inverse(3,3);
	matrix<double> epsilon (3,3);
	
	A(0,0) = cphi*ctheta;
	A(0,1) = sphi;
	A(0,2) = -cphi*stheta;
	A(1,0) = -sphi*ctheta;
	A(1,1) = cphi;
	A(1,2) = sphi*stheta;
	A(2,0) = stheta;
	A(2,1) = 0;
	A(2,2) = ctheta;

	epsilon(0,0)=eav-(1/3)*S*dem;
	epsilon(1,1)=eav-(1/3)*S*dem;
	epsilon(2,2)=eav+(2/3)*S*dem;

	ea = prod(A,epsilon);

	// move to external implementation for clarity

	//inverse http://www.crystalclearsoftware.com/cgi-bin/boost_wiki/wiki.pl?LU_Matrix_Inversion
	typedef permutation_matrix<std::size_t> pmatrix;
 	matrix<double> wc(A); // create a working copy of the input
 	pmatrix pm(wc.size1()); // create a permutation matrix for the LU-factorization
 	int res = lu_factorize(wc,pm); // perform LU-factorization
        //if( res != 0 ) return false;
 	inverse.assign(identity_matrix<double>(wc.size1())); // create identity matrix of "inverse"
 	lu_substitute(wc, pm, inverse); // backsubstitute to get the inverse

	ep = prod(ea,inverse);
}

void Fbfoptics::gtmiso(const complex<double> eiso, const double k0, const double eta, const double diso, matrix<complex<double> >& Tiso)
{
	double eta2 = pow(eta,2);
	complex<double> rb, za, qiso, zb, zc, zd, carg, sarg;

	rb = complex<double>(eta2,0);

	za = eiso-eta2;
	//za = complex_sub_real(eiso,eta2);
	qiso = sqrt(za);
	zb = qiso*k0;
	zc = zb*diso;
	zd= rb/eiso;

	carg = cos(zc);
	sarg = sin(zc);

	static const complex<double> zero = complex<double>(0.0,0.0);
	static const complex<double> i = complex<double>(0.0,1.0);
	static const complex<double> one = complex<double>(1.0,0.0);
	
	matrix<complex<double> > T(4,4);

	T(0,2) = zero;
	T(0,3) = zero;
	T(1,2) = zero;
	T(1,3) = zero;
	T(2,0) = zero;
	T(2,1) = zero;	
	T(3,0) = zero;
	T(3,1) = zero;
	
	T(0,0) = carg; 
	T(1,1) = carg; 
	T(2,2) = carg; 
	T(3,3) = carg; 

	T(0,1) = ((i*(one-zd))/qiso)*sarg; 
	T(1,0) = ((i*eiso)/qiso)*sarg; 
	T(2,3) = ((i*one)/qiso)*sarg; 
	T(3,2) = ((i*(eiso-eta2))/qiso)*sarg; 

	Tiso = T;
}

void Fbfoptics::diffpropmat(const matrix<double> ep, const double eta, matrix<double>& Delta)
{
	double zb[10];
	double eta2 = pow(eta,2);

	double ep31,ep33,ep32,ep13,ep22,ep11,ep12,ep21,ep23;

	ep11 = ep(0,0);
	ep12 = ep(0,1);
	ep13 = ep(0,2);
	ep21 = ep(1,0);
	ep22 = ep(1,1);
	ep23 = ep(1,2);
	ep31 = ep(2,0);
	ep32 = ep(3,1);
	ep33 = ep(3,2);

	Delta(0,0)=-eta*ep31/ep33;
	Delta(0,1)=1-eta2/ep33;
	Delta(0,2)=-eta*ep32/ep33;
	Delta(0,3)=0;
	Delta(1,0)=ep11-(ep13*ep31)/ep33;
	Delta(1,1)=-eta*ep13/ep33;
	Delta(1,2)=ep11-(ep12*ep32)/ep33;
	Delta(1,3)=0;
	Delta(2,0)=0;
	Delta(2,1)=0;
	Delta(2,2)=0;
	Delta(2,3)=1.0;
	Delta(3,0)=ep21-(ep31*ep23)/ep33;
	Delta(3,1)=-eta*ep23/ep33;
	Delta(3,2)=ep11-(ep13*ep31)/ep33-eta2;
	Delta(3,3)=0;
}

double Fbfoptics::rpp(const matrix<complex<double> >& M)
{
	complex<double> zr;
	zr = ((M(0,0)*M(3,2))-(M(3,0)*M(0,2)))/((M(0,0)*M(2,2))-(M(0,2)*M(2,0)));
	double r = pow(abs(zr),2);
	return r;
}

void Fbfoptics::gtm(const matrix<double>& Delta, const double k0, const double h, matrix<complex<double> >& T)
{
	matrix<complex<double> > Tw = Delta;
	for (unsigned i = 0; i < 4; ++ i)
        	for (unsigned j = 0; j < 4; ++ j)
            		Tw(i,j)=complex<double>(0,-h*k0*Delta(i,j));
	T = expm_pad(Tw); 
}

