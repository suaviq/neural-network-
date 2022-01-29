#pragma once
#include <string>
#include "matrices_vectors.h"

using namespace std;

class Layer
{
private:
	double** W; // weights
	double* b; // bias
	double* z; // neuron value
	double* a; // neuron value after activation
	double* a_prev; // neuron value after activation
	double* delta_w; // delta
	double* error_w; // error
	double* delta_b; // delta
	double* error_b; // error
	double learning_rate;
	string activation_function;

public:

	Layer(int neurons_curr, int neurons_prev, string activation, double learning_rate) 
	{
		this->W = initialize_layer_weights(neurons_curr, neurons_prev);
		this->b = initialize_layer_bias(neurons_curr);
		this->z = zeros_1d(neurons_curr);
		this->a = zeros_1d(neurons_curr);
		this->a_prev = zeros_1d(neurons_curr);
		this->delta_w = zeros_1d(neurons_curr);
		this->delta_b = zeros_1d(neurons_curr);
		this->error_w = zeros_1d(neurons_curr);
		this->error_b = zeros_1d(neurons_curr);
		this->activation_function = activation;
	}

	double* forward(double* a_prev) {
		// z -> a_prev * W + b
		// a -> activation(z)
		return this->a;
	}
	double* backward(double** W_next, double* delta_w_next, double* b_next, double delta_b_next) {
		// error_w = W_next * delta_w_next
		// delta_w -> error_w . activation_derivative(a) . -> element wise multiplications [1, 2, 3] . [2, 2, 2] = [1*2, 2*2, 3*2=
		// W -> W - learning_rate * a_prev.T * delta  -> [1, 2].T * [1, 2] = matrix
		// error_b = b_next * delta_b_next
		// delta_b = error_b * activation_derivative(a)
		// b -> b - learning_rate * delta_b
	}
	~Layer() {
		delete this->W;
		delete this->b;
		delete this->z;
		delete this->a;
		delete this->a_prev;
		delete this->delta_w;
		delete this->error_w;
		delete this->delta_b;
		delete this->error_b;

	}
};

class OutLayer: public Layer
{
	double* backward(double* y) {
		// error_w -> a - y
		// delta_w -> error_w*derivative(a)
		// error_w -> a - y
		// delta_w -> error_w*derivative(a)
	}
}
// X = [[1, 2], [4, 20]]
// y = [0, 1]
// Layer test_1 = Layer(2, 2, "sigmoid");
// Layer test_2 = OutLayer(2, 2, "sigmoid");
// test.forward_pass({ 0, 1 });