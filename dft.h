// Naive algorithm for the calculation of a discrete fourier transform for complex numbers
// Teresa Costa   April/2021

#include <complex>
#include <cstddef>
#include <vector>

using namespace std;

// Calculates the DFT
vector<complex<double>> dft_naive(const vector<complex<double> > &input) {

	vector<complex<double>> output;
	
	int N = input.size();
	
	int k = 0;
	
	for (k = 0; k < N; k++) {  // For each output element, frequency bin
		complex<double> sum(0, 0);
		for (int n = 0; n < N; n++) {  // For each input element
			double angle = 2.0 * M_PI * n * k / N;	
			sum += input[n] * exp(complex<double>(0, -angle));
		}
		output.push_back(sum);
	}
	return output;
}
