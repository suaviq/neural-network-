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
	double* a; // neuron value before activation ?? bylo napisane after zgupialam
	double* a_prev; // neuron value after activation
	double* delta_w; // delta
	double* error_w; // error
	double** delta_b; // delta TU WYCHODZI ZE DELTA JEST MNOŻENIEM DWÓCH WEKTORÓW WIEC ZAŁOŻYŁAM ŻE BĘDZIE vecT * vec ALE ??????????
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
		this->delta_b = zeros_2d(neurons_curr, neurons_prev); // ????????? CO Z TĄ DELTĄ B?????
		this->error_w = zeros_1d(neurons_curr);
		this->error_b = zeros_1d(neurons_curr);
		this->activation_function = activation;
	}

	//check
	double* forward(int neurons_curr, int neurons_prev, double* a_prev) {
		this->z = multiply_mat_vec(neurons_curr, neurons_prev, W, a_prev);
		this->a = sigmoid_vec(neurons_curr, neurons_prev, z);
		// z -> a_prev * W + b
		// a -> activation(z)
		return this->a;
	}

	// SPRAWDZIC OBLICZENIA 
	double* backward(int neurons_curr, int neurons_prev, double** W_next, double* delta_w_next, double* b_next, double delta_b_next) {
		// error_w = W_next * delta_w_next
		// delta_w -> error_w . activation_derivative(a) . -> element wise multiplications [1, 2, 3] . [2, 2, 2] = [1*2, 2*2, 3*2]
		// W -> W - learning_rate * a_prev.T * delta  -> [1, 2].T * [1, 2] = matrix
		// error_b = b_next * delta_b_next
		// 
		// delta_b = error_b (vec) * activation_derivative(a)
		// 
		// b -> b - learning_rate * delta_b

		//weight
		this->error_w = multiply_mat_vec(neurons_curr, neurons_prev, W_next, delta_w_next);
		this->a = derivative_sigmoid_vec(neurons_curr, a_prev);			//?????? vector
		this->delta_w = element_wise_multiply(neurons_curr, error_w, a); 
		double** w = multiply_vecT_vec(neurons_curr, a_prev, delta_w);
		double** w1 = multiply_matrix_by_constant(neurons_curr, neurons_prev, learning_rate, w);
		this->W = substract_matrices(neurons_curr, neurons_prev, W, w1);
		//bias
		this->error_b = multiply_vector_by_constant(neurons_curr, delta_b_next, b_next);
		this->delta_b = multiply_vecT_vec(neurons_curr, error_b, a);
		double** B = multiply_matrix_by_constant(neurons_curr, neurons_prev, learning_rate, delta_b);
		// TU COŚ NIE GRA BO NIE MOGĘ ODJĄC MACIERZY OD WEKTORA A BIAS NA 100% JEST WEKTOREM A NIE MACIERZĄ 


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
//Layer test_1 = Layer(2, 2, "sigmoid");
// test_1.forward(2, 2, "sigmoid", 1)
// Layer test_2 = OutLayer(2, 2, "sigmoid");
