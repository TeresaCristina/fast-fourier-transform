// Iterative algorithm for the calculation of a fast fourier transform for complex numbers
// Teresa Costa   April/2021

#include <complex>
#include <cstddef>
#include <vector>
#include <algorithm>
#include "bit_reversal.h"

using namespace std;

std::vector<complex<double>> fft_iterative(const vector<complex<double>> &input)
{

  // Bit Reversal
  int size = input.size();
   std::cout << size << std::endl;
  int stages = log2(size);
   std::cout << stages << std::endl;
  std::vector<complex<double>> output(size, 0);

  for (int i = 0; i < size; i++)
  { // 0 to 7 (8 elements)
    int out = bitReverse(i, stages);
    output[out] = input[i];
   //  std::cout << i << std::endl;
   // std::cout << output[out] << std::endl;
  }

  int leafs = 1;
  complex<double> imag(0, 1);

  for (int s = 1; s <= stages; s++) //stages
  {
    int half = leafs;
    leafs *= 2; // chunks

    complex<double> real(1, 0);
    complex<double> angle = exp(-imag * (M_PI / half));

    for (int j = 0; j < half; j++)
    {
      for (int k = j; k < size; k = k + leafs)
      {

        complex<double> odd = real * output[k + half];
        complex<double> even = output[k];

        output[k] = even + odd;
        output[k + half] = even - odd;
      }
      real = real * angle;

    }
  
  }
 
  return output;
}
