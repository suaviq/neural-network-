#pragma once
#include <string>
#include "matrices_vectors.h"

using namespace std;

class Layer
{
protected:
	int neurons_curr;
	int neurons_prev;
	double** W; // weights
	double* b; // bias
	double* z; // neuron value
	double* a; // neuron value before activation ?? bylo napisane after zgupialam
	double* a_prev; // neuron value after activation
	double* delta; // delta
	double* error; // error
	double learning_rate;
	string activation_function;

public:

	Layer(int neurons_curr, int neurons_prev, string activation, double learning_rate) 
	{
		this->neurons_curr;
		this->neurons_prev;
		this->W = initialize_layer_weights(neurons_curr, neurons_prev);
		this->b = initialize_layer_bias(neurons_curr);
		this->z = zeros_1d(neurons_curr);
		this->a = zeros_1d(neurons_curr);
		this->a_prev = zeros_1d(neurons_curr);
		this->delta = zeros_1d(neurons_curr);
		this->error = zeros_1d(neurons_curr);
		this->learning_rate = learning_rate;
		this->activation_function = activation;
	}

	//check
	double* forward(int neurons_curr, int neurons_prev, double* a_prev) {
		this->z = multiply_matrix_by_vector(neurons_curr, neurons_prev, W, a_prev);
		if (this->activation_function == "sigmoid") {
			this->a = sigmoid_vector(neurons_curr, z);  
		}
		else if (this->activation_function == "relu") {
			this->a = relu_vector(neurons_curr, z); 
		}
		else {
			throw invalid_argument("Activation function must be either 'sigmoid' or 'relu'");
		}
		this->a_prev = a_prev;
		// z -> a_prev * W + b
		// a -> activation(z)
		return this->a;
	}

	// SPRAWDZIC OBLICZENIA 
	// UPDATE BIOS MOŻE NIE DZIAŁAĆ
	double* backward(int neurons_next, double** W_next, double* delta_w_next, double* b_next, double* delta_next) {
		// error_w = W_next * delta_w_next
		// delta_w -> error_w . activation_derivative(a) . -> element wise multiplications [1, 2, 3] . [2, 2, 2] = [1*2, 2*2, 3*2]
		// W -> W - learning_rate * a_prev.T * delta  -> [1, 2].T * [1, 2] = matrix
		// error_b = b_next * delta_b_next
		// 
		// delta_b = error_b (vec) * activation_derivative(a)
		// 
		// b -> b - learning_rate * delta_b

		//weight
		this->error = add_vectors(this->neurons_curr, multiply_matrix_by_vector(neurons_next, this->neurons_curr, W_next, delta_w_next), element_wise_multiply(this->neurons_curr, b_next, delta_next));
 
		if (this->activation_function == "sigmoid") {
			this->delta = element_wise_multiply(this->neurons_curr, this->error, derivative_sigmoid_vector(this->neurons_curr, this->a)); 
		}
		else if (this->activation_function == "relu") {
			this->delta = element_wise_multiply(this->neurons_curr, this->error, derivative_relu_vector(this->neurons_curr, this->a));
		}
		else {
			throw invalid_argument("Activation function must be either 'sigmoid' or 'relu'");
		}
	
		double** w = multiply_vectorT_by_vector(this->neurons_curr, this->a_prev, this->delta);
		double** w1 = multiply_matrix_by_constant(this->neurons_curr, this->neurons_prev, w, this->learning_rate);
		this->W = substract_matrices(this->neurons_curr, this->neurons_prev, this->W, w1);
		//bias
		this->b = substract_vectors(neurons_curr, this->b, element_wise_multiply(this->neurons_curr, this->b, this->delta));
	}
	~Layer() {
		delete this->W;
		delete this->b;
		delete this->z;
		delete this->a;
		delete this->a_prev;
		delete this->delta;
		delete this->error;
	}
};

class Output_Layer : public Layer
{
	double* backward(double* y) {
		// error_w -> a - y									wektor
		// delta_w -> error_w* activation_derivative(a)		probably element wise multiply
		// error_b -> a - y
		// delta_b -> error_b*derivative(a)
		// 
		//weight
		this->error = substract_vectors(this->neurons_curr, this->a, y);
		if (this->activation_function == "sigmoid") {
			this->delta = element_wise_multiply(neurons_curr, error, derivative_sigmoid_vector(this->neurons_curr, this->a));
		}
		else if (this->activation_function == "relu") {
			this->delta = element_wise_multiply(neurons_curr, error, derivative_relu_vector(this->neurons_curr, this->a));
		}
		else {
			throw invalid_argument("Activation function must be either 'sigmoid' or 'relu'");
		}
	}
};
