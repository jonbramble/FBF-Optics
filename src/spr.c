/*
 * spr.c
 *
 *  Created on: 25-Jun-2009
 *      Author: Jonathan Bramble
 */
#include "spr.h"

int main()
{
	double time;
	start_timer();
	gsl_matrix_complex * ILa = gsl_matrix_complex_alloc(4,4);
	gsl_matrix_complex * Lf = gsl_matrix_complex_alloc(4,4);
	gsl_matrix_complex * T = gsl_matrix_complex_alloc(4,4);
	gsl_matrix_complex * Temp = gsl_matrix_complex_alloc(4,4);
	gsl_matrix_complex * Tau = gsl_matrix_complex_alloc(4,4);

	gsl_complex one = gsl_complex_rect(1, 0);
	gsl_complex zero = gsl_complex_rect(0, 0);
	gsl_complex result;

	gsl_complex eau = gsl_complex_rect(-12.0,0.8);  // gold refractive index in permativitty form
	double dau = 49e-9; // au thickness

	double k0 = (2*M_PI)/633e-9; // laser wavevector

	double na = 1.85;  // prism index
	double nf = 1.333; // water index

	int k;

	for(k=0;k<1000;k++)
	{
		double phia = 0+k*((M_PI/2)/1000); //input angle
		double cphia = cos(phia); 
		double eta = na*sin(phia); // x comp of wavevector

		gsl_complex zcphif2 = gsl_complex_rect(1-pow((na/nf)*sin(phia),2),0); // snell
		gsl_complex cphif = gsl_complex_sqrt(zcphif2); 

		incmat(ILa,na,cphia); // entrance matrix
		extmat(Lf,nf,cphif);  // exit matrix
		gtmiso(Tau,eau,k0,eta,-dau);  // istropic matrix call
		//result = gsl_matrix_complex_get(Tau, 0,1);

		gsl_blas_zgemm(CblasNoTrans, CblasNoTrans, one, ILa, Tau, zero, Temp); // matrix multiplications
		gsl_blas_zgemm(CblasNoTrans, CblasNoTrans, one, Temp, Lf, zero, T);

		//rpp(T);
		//printf("%g + %gi\n",GSL_REAL(result),GSL_IMAG(result));
		//printf("%i %g+ %gi\n",k,GSL_REAL(result),GSL_IMAG(result));
		printf("%g , %g\n",phia,rpp(T));  // output result here

		gsl_matrix_complex_set_zero(T); // reset T for loop
	}
	gsl_matrix_complex_free(ILa);
	gsl_matrix_complex_free(Lf);
	gsl_matrix_complex_free(T);
	gsl_matrix_complex_free(Tau);
	gsl_matrix_complex_free(Temp);
	time = elapsed_time();

	printf("%g\n",time);
	return 0;
}
