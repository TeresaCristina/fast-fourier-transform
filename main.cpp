//g++ main.cpp --std=c++11 -lm

#include <iostream>
#include <iomanip>
#include <chrono>
#include <math.h>
#include <complex>
#include <cstddef>
#include <vector>
#include "dft.h"
#include "time.h"

using namespace std;
using namespace std::chrono;

int main()
{
	std::chrono::steady_clock::time_point ts, te;
	vector<complex<double>> input, output;
	input = toVector();
	int size = input.size();
	
	
		std::chrono::steady_clock::duration span{};
		for (int j = 0; j < 10; j++) {
			vector<complex<double>> in(input.begin(), input.begin() + i);
			ts = steady_clock::now();
			output = dft_naive(in);
			te = steady_clock::now();
			span = span + (te - ts);
		}
		std::cout << "Size: " << i << std::endl;
		reportTime("\nTime elapsed: ", span/10);	
	
	
	FILE *fout;
	fout = fopen("noise_output.txt", "w");
	for (int j = 0; j < size; j++) {
		fprintf(fout, "%.12lf   %.12lf\n", output[j].real(), output[j].imag()); // print output complex numbers
	}
	fclose(fout);
	
	return 0;
}
