#include <iostream> 
#include <iomanip>  
#include <chrono>
#include <math.h>
#include <complex>
#include <cstddef>
#include <vector>

using namespace std;
using namespace std::chrono;

// Gets time of computation
void reportTime(const char* msg, std::chrono::steady_clock::duration span) {
     auto ms = duration_cast<microseconds>(span);
     std::cout << msg << ms.count() << " microseconds" << std::endl;
 }
 
// Convert from document input to vector 
 vector<complex<double>> toVector() {
 	int size;
 	FILE *fin;
 	vector<complex<double>> input;
       // open file
	fin = fopen("speech_noised.txt", "r");
	fscanf(fin, "%d", &size);
	// get input
	double temp;
	for (int i = 0; i < size; i++)
	{
		std::complex<double> tempComplex;
		fscanf(fin, "%lf", &temp);
		tempComplex.real(temp);
		input.push_back(tempComplex);
	}
	fclose(fin);
	return input;
 }
 
// Calculate desviation
 double RMSE(vector<double> vector1, vector<double> vector2) {
	
	double sum_square_error = 0.;
	int length = vector1.size();

	//printf("length = %d\n", length);

	if (length != vector2.size()) {
		// invalid arguments sizes so return absurd output
		return -1.;

	} else {

		double residual;
		auto it1 = vector1.begin();
		auto it2 = vector2.begin();
		
		while (it1 != vector1.end() || it2 != vector2.end()) {
			residual = *it1 - *it2;
			//printf("v1:%f v2:%f residual:%f\n", *it1, *it2, residual);
			sum_square_error += residual * residual;
			it1++;
			it2++;
		}
		sum_square_error = sqrt(sum_square_error / length);
	}

	return sum_square_error;
}
