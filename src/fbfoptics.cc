/*
 * fbfoptics.c
 *
 *  Created on: 25-Jun-2009
 *      Author: Jonathan Bramble
 */

//gtm
//outs

#include "../include/fbfoptics.hpp"

Fbfoptics::Fbfoptics() {
	ILa = zero_matrix<complex<double> >(4,4); 
	Lf = zero_matrix<complex<double> >(4,4);
}

void Fbfoptics::incmat(double na, double cphia){
	ILa(0,2) = complex<double>(0.5,0);
	ILa(0,3) = complex<double>(1/(2*na*cphia),0);
	ILa(1,2) = complex<double>(0.5,0);
	ILa(1,3) = complex<double>(-1/(2*na*cphia),0);
	ILa(2,0) = complex<double>(1/(2*cphia),0);
	ILa(2,1) = complex<double>(1/(2*na),0);
	ILa(3,0) = complex<double>(-1/(2*cphia),0);
	ILa(3,1) = complex<double>(1/(2*na),0);	
}

void Fbfoptics::extmat(double nf, complex<double> cphif)
{
	complex<double> znf= complex<double>(nf,0.0);
	complex<double> zk = znf*cphif;
	
	Lf(0,2) = cphif;
	Lf(1,2) = znf;
	Lf(2,0) = complex<double>(1.0,0.0);
	Lf(3,0) = zk;
}


/*
#include "fbfoptics.h"

int extmat(gsl_matrix_complex * Lf, double nf, gsl_complex cphif)
{
	gsl_matrix_complex_set_zero(Lf);
	gsl_complex znf = gsl_complex_rect(nf,0);
	gsl_complex zk = gsl_complex_mul(znf,cphif);
	gsl_complex one = gsl_complex_rect(1,0);

	gsl_matrix_complex_set(Lf,0,2,cphif);
	gsl_matrix_complex_set(Lf,1,2,znf);
	gsl_matrix_complex_set(Lf,2,0,one);
	gsl_matrix_complex_set(Lf,3,0,zk);

	return 1;

}



int incmat(gsl_matrix_complex * ILa, double na, double cphia)
{
	gsl_complex zb[8];
	zb[0] = gsl_complex_rect(0.5,0);
	zb[1] = gsl_complex_rect(1/(2*na*cphia),0);
	zb[2] = gsl_complex_rect(0.5,0);
	zb[3] = gsl_complex_rect(-1/(2*na*cphia),0);

	zb[4] = gsl_complex_rect(1/(2*cphia),0);
	zb[5] = gsl_complex_rect(1/(2*na),0);
	zb[6] = gsl_complex_rect(-1/(2*cphia),0);
	zb[7] = gsl_complex_rect(1/(2*na),0);

	gsl_matrix_complex_set_zero(ILa);

	gsl_matrix_complex_set(ILa,0,2,zb[0]);
	gsl_matrix_complex_set(ILa,0,3,zb[1]);

	gsl_matrix_complex_set(ILa,1,2,zb[2]);
	gsl_matrix_complex_set(ILa,1,3,zb[3]);

	gsl_matrix_complex_set(ILa,2,0,zb[4]);
	gsl_matrix_complex_set(ILa,2,1,zb[5]);

	gsl_matrix_complex_set(ILa,3,0,zb[6]);
	gsl_matrix_complex_set(ILa,3,1,zb[7]);

	return 1;
}

int dietens(gsl_matrix * ep, double eav, double dem, double S, double stheta, double ctheta, double sphi, double cphi)
{
	gsl_matrix * A = gsl_matrix_alloc(3,3);
	gsl_matrix * epsilon = gsl_matrix_alloc(3,3);
	gsl_matrix * ea = gsl_matrix_alloc(3,3);

	gsl_matrix_set_zero(epsilon);

	gsl_matrix_set(A,0,0,cphi*ctheta);
	gsl_matrix_set(A,0,1,sphi);
	gsl_matrix_set(A,0,2,-cphi*stheta);

	gsl_matrix_set(A,1,0,-sphi*ctheta);
	gsl_matrix_set(A,1,1,cphi);
	gsl_matrix_set(A,1,2,sphi*stheta);

	gsl_matrix_set(A,2,0,stheta);
	gsl_matrix_set(A,2,1,0.0);
	gsl_matrix_set(A,2,2,ctheta);

	gsl_matrix_set(epsilon,0,0,eav-(1/3)*S*dem);
	gsl_matrix_set(epsilon,1,1,eav-(1/3)*S*dem);
	gsl_matrix_set(epsilon,2,2,eav+(2/3)*S*dem);

	gsl_blas_dgemm(CblasTrans, CblasTrans, 1.0, epsilon, A, 0.0, ea);
	gsl_matrix_transpose(A);//transpose A but dont need if eij=eji

	//LU solve here, could use a symmetrical eg Cholesky
	{
	gsl_matrix *K = gsl_matrix_alloc(4, 4);
	gsl_permutation *p = gsl_permutation_alloc(4);
	gsl_vector *x = gsl_vector_alloc(4);

	gsl_vector_view bp;
	double z;
	int i,j,s;

	gsl_matrix_memcpy(K,A);
	for (i = 0; i < 4; i++)
	{
		bp = gsl_matrix_column(ea, i);
		gsl_linalg_LU_decomp(A, p, &s);
		gsl_linalg_LU_solve(A, p, &bp.vector, x);
		for (j = 0; j < 4; j++)
		{
			z = gsl_vector_get(x, j);
			gsl_matrix_set(ep,i,j,z); //'through the looking glass' transpose
		}
		gsl_matrix_memcpy(A,K);
	}

	gsl_matrix_free(A);
	gsl_matrix_free(epsilon);
	gsl_matrix_free(ea);
	gsl_matrix_free(K);
	gsl_permutation_free(p);
	gsl_vector_free(x);

	}
	return 1;
}



void gtmiso(gsl_matrix_complex * Tiso, gsl_complex eiso, double k0, double eta, double diso)
{
	double eta2 = pow(eta,2);
	gsl_complex rb = gsl_complex_rect(eta2,0);

	gsl_complex za = gsl_complex_sub_real(eiso,eta2);
	gsl_complex qiso = gsl_complex_sqrt(za);
	gsl_complex zb = gsl_complex_mul_real(qiso,k0);
	gsl_complex zc = gsl_complex_mul_real(zb,diso);
	gsl_complex zd = gsl_complex_div(rb,eiso);

	gsl_complex carg = gsl_complex_cos(zc);
	gsl_complex sarg = gsl_complex_sin(zc);

	gsl_complex i = gsl_complex_rect(0,1);
	gsl_complex one = gsl_complex_rect(1,0);

	gsl_matrix_complex_set_zero(Tiso);

	gsl_matrix_complex_set(Tiso,0,0,carg);
	gsl_matrix_complex_set(Tiso,1,1,carg);
	gsl_matrix_complex_set(Tiso,2,2,carg);
	gsl_matrix_complex_set(Tiso,3,3,carg);

	gsl_complex zd1 = gsl_complex_sub(one,zd);
	gsl_complex zd2 = eiso;
	gsl_complex zd3 = one;
	gsl_complex zd4 = gsl_complex_sub_real(eiso,eta2);

	gsl_complex zmult1 = gsl_complex_mul(zd1,i);
	gsl_complex zmult2 = gsl_complex_mul(zd2,i);
	gsl_complex zmult3 = gsl_complex_mul(zd3,i);
	gsl_complex zmult4 = gsl_complex_mul(zd4,i);

	gsl_complex zdiv1 = gsl_complex_div(zmult1,qiso);
	gsl_complex zdiv2 = gsl_complex_div(zmult2,qiso);
	gsl_complex zdiv3 = gsl_complex_div(zmult3,qiso);
	gsl_complex zdiv4 = gsl_complex_div(zmult4,qiso);

	gsl_complex zmult5 = gsl_complex_mul(zdiv1,sarg);
	gsl_complex zmult6 = gsl_complex_mul(zdiv2,sarg);
	gsl_complex zmult7 = gsl_complex_mul(zdiv3,sarg);
	gsl_complex zmult8 = gsl_complex_mul(zdiv4,sarg);

	gsl_matrix_complex_set(Tiso,0,1,zmult5);
	gsl_matrix_complex_set(Tiso,1,0,zmult6);
	gsl_matrix_complex_set(Tiso,2,3,zmult7);
	gsl_matrix_complex_set(Tiso,3,2,zmult8);

}

void diffpropmat(gsl_matrix * Delta, gsl_matrix * ep, double eta)
{
		double zb[10];
		double eta2 = pow(eta,2);

		double ep31,ep33,ep32,ep13,ep22,ep11,ep12,ep21,ep23;

		ep11 = gsl_matrix_get(ep,0,0);
		ep12 = gsl_matrix_get(ep,0,1);
		ep13 = gsl_matrix_get(ep,0,2);
		ep21 = gsl_matrix_get(ep,1,0);
		ep22 = gsl_matrix_get(ep,1,1);
		ep23 = gsl_matrix_get(ep,1,2);
		ep31 = gsl_matrix_get(ep,2,0);
		ep32 = gsl_matrix_get(ep,3,1);
		ep33 = gsl_matrix_get(ep,3,2);

		zb[0] = -eta*ep31/ep33;
		zb[1] = 1-eta2/ep33;
		zb[2] = -eta*ep32/ep33;
		zb[3] = ep11-(ep13*ep31)/ep33;
		zb[4] = -eta*ep13/ep33;
		zb[5] = ep11-(ep12*ep32)/ep33;
		zb[6] = 1.0;
		zb[7] = ep21-(ep31*ep23)/ep33;
		zb[8] = -eta*ep23/ep33;
		zb[9] = ep11-(ep13*ep31)/ep33-eta2;

		gsl_matrix_set_zero(Delta);

		gsl_matrix_set(Delta,0,0,zb[0]);
		gsl_matrix_set(Delta,0,1,zb[1]);
		gsl_matrix_set(Delta,0,2,zb[2]);
		gsl_matrix_set(Delta,1,0,zb[3]);
		gsl_matrix_set(Delta,1,1,zb[4]);
		gsl_matrix_set(Delta,1,2,zb[5]);
		gsl_matrix_set(Delta,2,3,zb[6]);
		gsl_matrix_set(Delta,3,0,zb[7]);
		gsl_matrix_set(Delta,3,1,zb[8]);
		gsl_matrix_set(Delta,3,2,zb[9]);
}

double rpp(gsl_matrix_complex * M)
{
	gsl_complex t11, t43, t41, t13, t33, t31, mul1, mul2, mul3, mul4, sub1, sub2, div1;
	t11 = gsl_matrix_complex_get(M,0,0);
	t43 = gsl_matrix_complex_get(M,3,2);
	t41 = gsl_matrix_complex_get(M,3,0);
	t13 = gsl_matrix_complex_get(M,0,2);
	t33 = gsl_matrix_complex_get(M,2,2);
	t31 = gsl_matrix_complex_get(M,2,0);

	mul1 = gsl_complex_mul(t11,t43);
	mul2 = gsl_complex_mul(t41,t13);
	mul3 = gsl_complex_mul(t11,t33);
	mul4 = gsl_complex_mul(t13,t31);

	sub1 = gsl_complex_sub(mul1,mul2);
	sub2 = gsl_complex_sub(mul3,mul4);

	div1 = gsl_complex_div(sub1,sub2);

	return gsl_complex_abs2(div1);
}

void gtm(gsl_matrix_complex * T, gsl_matrix * Delta, double k0, double h)
{
	gsl_complex t = gsl_complex_rect(0,-h*k0);
	expm(T,t,Delta);
}

void expm(gsl_matrix_complex * L, gsl_complex t, gsl_matrix * m)
     {
    int i,j,s;
	gsl_vector_complex *eval = gsl_vector_complex_alloc(4);
	gsl_matrix_complex *evec = gsl_matrix_complex_alloc(4, 4);
	gsl_eigen_nonsymmv_workspace * w = gsl_eigen_nonsymmv_alloc(4);
	gsl_matrix_complex *evalmat = gsl_matrix_complex_alloc(4, 4);
	gsl_matrix_complex *vd = gsl_matrix_complex_alloc(4, 4);
	gsl_complex one = gsl_complex_rect(1, 0);
	gsl_complex zero = gsl_complex_rect(0, 0);

	gsl_matrix_complex *K = gsl_matrix_complex_alloc(4, 4);
	gsl_permutation *p = gsl_permutation_alloc(4);
	gsl_vector_complex *x = gsl_vector_complex_alloc(4);

	gsl_vector_complex_view bp;
	gsl_complex z;

	gsl_eigen_nonsymmv(m, eval, evec, w);
	gsl_eigen_nonsymmv_sort(eval, evec, GSL_EIGEN_SORT_ABS_DESC);

	gsl_eigen_nonsymmv_free(w); // clear workspace

	for (i = 0; i < 4; i++)
	{
		gsl_complex eval_i = gsl_vector_complex_get(eval, i);
		gsl_complex expeval = gsl_complex_mul(eval_i,t);
		expeval = gsl_complex_exp(expeval);
		gsl_matrix_complex_set(evalmat, i, i, expeval);
	}

	gsl_vector_complex_free(eval); // clear vector for eigenvalues

	// v'L'=De'v'
	gsl_blas_zgemm(CblasTrans, CblasTrans, one, evalmat, evec, zero, vd);
	gsl_matrix_complex_transpose(evec);//transpose v

	gsl_matrix_complex_memcpy(K,evec);

	for (i = 0; i < 4; i++)
	{
		bp = gsl_matrix_complex_column(vd, i);
		gsl_linalg_complex_LU_decomp(evec, p, &s);
		gsl_linalg_complex_LU_solve(evec, p, &bp.vector, x);
			for (j = 0; j < 4; j++)
			{
				z = gsl_vector_complex_get(x, j);
				gsl_matrix_complex_set(L,i,j,z); //'through the looking glass' transpose
			}
		gsl_matrix_complex_memcpy(evec,K);
	}


	gsl_permutation_free(p);
	gsl_vector_complex_free(x);
	gsl_matrix_complex_free(vd);
	gsl_matrix_complex_free(evec);
	gsl_matrix_complex_free(evalmat);
	gsl_matrix_complex_free(K);
}

*/

