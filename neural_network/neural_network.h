#pragma once
#include <string>
#include "matrices_vectors.h"

using namespace std;

class NeuralNetwork 
{
private:
	double learning_rate;
public:
	void forward_propagation();
	void backward_propagation();
	void calculate_error();
	void update_weights();
	void train();

};