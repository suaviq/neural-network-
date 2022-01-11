#pragma once
#include <string>
#include "matrices_vectors.h"

using namespace std;

class Layer
{
private:
	double** weights; // Wn
	double* bias; // bn
	double* neuron_values; // An
	string activation_function;

public:

	Layer(int neurons_curr, int neurons_prev, string activation) {
		this->weights = initialize_layer_weights(neurons_curr, neurons_prev);
		//initialize bias weights 
	}
};

Layer test = Layer(4, 2, "sigmoid");