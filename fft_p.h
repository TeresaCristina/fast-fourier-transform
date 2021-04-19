// Parallel algorithm for the calculation of a fast fourier transform for complex numbers
// Teresa Costa   April/2021

#include <omp.h>
#include <math.h>
#include <complex>
#include <vector>
#include "bit_reversal.h"

std::vector<complex<double>> fft_iterative(const vector<complex<double>> &input)
{
  int size = input.size();
  std::cout << size<< std::endl;
  std::vector<complex<double>> output(size, 0);

  int stages = log2(size);
   std::cout <<stages<< std::endl;

  // Bit Reversal
#pragma omp parallel num_threads(4)
  {
    int thisThread = omp_get_thread_num();
    int nt = omp_get_num_threads();
   // #pragma omp for
    for (int i = thisThread; i < size; i = i + nt)
    {
      int out = bitReverse(i, stages);
      output[out] = input[i];
    }
  }

  int leafs = 1;
  complex<double> imag(0, 1);

  // FFT Calculation
  for (int s = 1; s <= stages; s++)
  {
    int half = leafs;
    leafs = leafs * 2;
    complex<double> real(1, 0);
    complex<double> angle = exp(-imag * (M_PI / half));
    int j = 0;
    int k = 0;

#pragma omp parallel for private(j, k)
    for (j = 0; j < half; j++)
    {
      complex<double> real = complex<double>(1, 0) * pow(angle, j);
      for (int k = j; k < size; k = k + leafs)
      {
        complex<double> odd = real * output[k + half];
        complex<double> even = output[k];
        // Butterfly Exchange
        output[k] = even + odd;
        output[k + half] = even - odd;
      }
    }
  }

  return output;
}
