// MKL for the calculation of a discrete fourier transform for complex numbers
// Teresa Costa   April/2021

// g++ -DMKL_ILP64 -m64 -I/opt/intel/mkl/include main.cpp -L/opt/intel/mkl/lib/intel64 -Wl,--no-as-needed -lmkl_intel_ilp64 -lmkl_gnu_thread -lmkl_core -lgomp -lpthread -lm -ldl -o test

#include "mkl_dfti.h"
#include <ostream>
#include <iostream>
#include <complex>
#include <cstddef>
#include <vector>
#include "mkl.h"
#include <iomanip>  
#include <chrono>
#include <math.h>

std::vector<std::complex<double>> fft_mkl(std::vector<std::complex<double>>& in){
    	
    	std::vector<std::complex<double>> out(in.size(), 0);
    	
    	int size = in.size();
	
	mkl_set_num_threads (4);
    	
    	DFTI_DESCRIPTOR_HANDLE descriptor;
    	MKL_LONG status;

    	status = DftiCreateDescriptor(&descriptor, DFTI_DOUBLE, DFTI_COMPLEX, 1, in.size()); //Specify size and precision
    	status = DftiSetValue(descriptor, DFTI_PLACEMENT, DFTI_NOT_INPLACE); //Out of place FFT
	status = DftiSetValue(descriptor, DFTI_CONJUGATE_EVEN_STORAGE, DFTI_COMPLEX_COMPLEX);
	status = DftiSetValue(descriptor, DFTI_PACKED_FORMAT, DFTI_CCE_FORMAT);
    	status = DftiCommitDescriptor(descriptor); //Finalize the descriptor
    	status = DftiComputeForward(descriptor, in.data(), out.data()); //Compute the Forward FFT
    
    	status = DftiFreeDescriptor(&descriptor); //Free the descriptor

    	return out;
}
