#ifndef COMPLEX_METHODS_HPP
#define COMPLEX_METHODS_HPP
 
// names are taken to match those in gsl library for convenience 

#include <complex>

template <class T> std::complex<T> complex_sub_real(const std::complex<T>& a, const T& b){
	return std::complex<T>(real(a)-b,imag(a));	
 }
 
 #endif //COMPLEX_METHODS_HPP
