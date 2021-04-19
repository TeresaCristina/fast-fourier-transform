// Recursive algorithm for the calculation of a fast fourier transform for complex numbers
// Teresa Costa   April/2021


#include <complex>
#include <cstddef>
#include <vector>
#include <algorithm>

using namespace std;


// Calculates the FFT
void fft_recursive(vector<complex<double>> &input) {

  double N = input.size();
  double half = N / 2.0;
  
  if (N > 1)
  {

    vector<complex<double>> even;
    vector<complex<double>> odd;
    for (int i = 0; i < N; i++)
    {
      even.push_back(input[i]);
      odd.push_back(input[++i]);
    }

    // conquer
    fft_recursive(even);
    fft_recursive(odd);

    // combine
    for (double k = 0; k < half; ++k)
    {
      double angle = 2.0 * M_PI * k / N;
      complex<double> sum = odd[k] * exp(complex<double>(0, -angle));
      complex<double> temp = even[k];

      input[k] = temp + sum;
      input[k + half] = temp - sum;
    }
  }
  	
}
