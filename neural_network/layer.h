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
		this->neurons_curr = neurons_curr;
		this->neurons_prev = neurons_prev;
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
	double* forward(int neurons_prev, double* a_prev) {
		// z -> a_prev * W + b
		// a -> activation(z)
		cout << "calculate z" << endl;
		this->z = multiply_matrix_by_vector(this->neurons_curr, neurons_prev, this->W, a_prev);
		cout_vector(this->neurons_curr, this->z);
		cout << endl;

		cout << "calculate a" << endl;
		if (this->activation_function == "sigmoid") {
			this->a = sigmoid_vector(this->neurons_curr, this->z);
			cout_vector(this->neurons_curr, this->a);
		}
		else if (this->activation_function == "relu") {
			this->a = relu_vector(this->neurons_curr, this->z);
			cout_vector(this->neurons_curr, this->a);
		}
		else {
			throw invalid_argument("Activation function must be either 'sigmoid' or 'relu'");
		}

		this->a_prev = a_prev;
		cout << endl << endl;
		return this->a;
	}


	double* backward(int neurons_next, double** W_next, double* b_next, double* delta_next) {
		// error = W_next * delta_next + b_next * delta_next
		// delta -> error . activation_derivative(a) . -> element wise multiplications [1, 2, 3] . [2, 2, 2] = [1*2, 2*2, 3*2]
		// W -> W - learning_rate * a_prev.T * delta  -> [1, 2].T * [1, 2] = matrix
		// error_b = b_next * delta_b_next
		// 
		// delta_b = error_b (vec) * activation_derivative(a)
		// 
		// b -> b - learning_rate * delta_b

		//weight
		cout << "calculate error" << endl;
		double **W_nextT = transpose(neurons_next, this->neurons_curr, W_next);
		this->error = multiply_matrix_by_vector(this->neurons_curr, neurons_next, W_nextT, delta_next);
		cout_vector(this->neurons_curr, this->error);

		//delta
		cout << "calculate delta" << endl;
		if (this->activation_function == "sigmoid") {
			this->delta = element_wise_multiply(this->neurons_curr, this->error, derivative_sigmoid_vector(this->neurons_curr, this->a)); 
			cout_vector(this->neurons_curr, this->delta);
		}
		else if (this->activation_function == "relu") {
			this->delta = element_wise_multiply(this->neurons_curr, this->error, derivative_relu_vector(this->neurons_curr, this->a));
			cout_vector(this->neurons_curr, this->delta);
		}
		else {
			throw invalid_argument("Activation function must be either 'sigmoid' or 'relu'");
		}
		
		//update weights
		cout << "update weights" << endl;
		double** w = multiply_vectorT_by_vector(this->neurons_curr, this->a_prev, this->delta);
		double** w1 = multiply_matrix_by_constant(this->neurons_curr, this->neurons_prev, w, this->learning_rate);
		this->W = substract_matrices(this->neurons_curr, this->neurons_prev, this->W, w1);
		cout_matrix(this->neurons_curr, this->neurons_prev, this->W);

		//update bias
		cout << "update bias" << endl;
		this->b = substract_vectors(neurons_curr, this->b, element_wise_multiply(this->neurons_curr, this->b, this->delta));
		cout_vector(this->neurons_curr, this->b);
	}

	double* access_a()
	{
		return this->a;
	}

	double* access_delta()
	{
		return this->delta;
	}

	double* access_b()
	{
		return this->b;
	}

	double** access_W()
	{
		return this->W;
	}

	int access_neurons_curr()
	{
		return this->neurons_curr;
	}
};

class OutputLayer : public Layer
{
public:
	using Layer::Layer;
	using Layer::forward;
	double* backward(double* y) {
		// error -> a - y									wektor
		// delta -> error_w* activation_derivative(a)		probably element wise multiply
		// 
		//weight
		this->error = substract_vectors(this->neurons_curr, this->a, y);
		if (this->activation_function == "sigmoid") {
			this->delta = element_wise_multiply(this->neurons_curr, this->error, derivative_sigmoid_vector(this->neurons_curr, this->a));
		}
		else if (this->activation_function == "relu") {
			this->delta = element_wise_multiply(this->neurons_curr, this->error, derivative_relu_vector(this->neurons_curr, this->a));
		}
		else {
			throw invalid_argument("Activation function must be either 'sigmoid' or 'relu'");
		}

		//update weights
		cout << "update weights" << endl;
		double** w = multiply_vectorT_by_vector(this->neurons_curr, this->a_prev, this->delta);
		double** w1 = multiply_matrix_by_constant(this->neurons_curr, this->neurons_prev, w, this->learning_rate);
		this->W = substract_matrices(this->neurons_curr, this->neurons_prev, this->W, w1);
		cout_matrix(this->neurons_curr, this->neurons_prev, this->W);

		//update bias
		cout << "update bias" << endl;
		this->b = substract_vectors(neurons_curr, this->b, element_wise_multiply(this->neurons_curr, this->b, this->delta));
		cout_vector(this->neurons_curr, this->b);
	
	}


};

void test_layer() {
	double x_raw[2] = { 1, 2};
	double y_raw[1] = { 0.5 };

	double* x = new double[2];
	double* y = new double[1];

	for (int i = 0; i < 2; i++) {
		x[i] = x_raw[i];
	}

	for (int i = 0; i < 1; i++) {
		y[i] = y_raw[i];
	}

	Layer hidden_layer = Layer(2, 2, "relu", 0.01);
	OutputLayer out_layer = OutputLayer(1, 2, "sigmoid", 0.01);

	hidden_layer.forward(2, x);
	out_layer.forward(2, hidden_layer.access_a());

	out_layer.backward(y);
	hidden_layer.backward(out_layer.access_neurons_curr(), out_layer.access_W(), out_layer.access_b(), out_layer.access_delta());
	
	delete x, y;
	/*double* x = new double[5];
	for (int i = 0; i < 5; i++) {
		x[i] = x_raw[i];
	}
	Layer test1 = Layer(4, 4, "sigmoid", 0.1);
	test1.forward(3, 4, x);
	
	double W_next_raw[4][3] = { { 1, 4, 7}, {3, 5, 6},{4, 6, 3}, {4, 6, 3}};
	double** W_next = new double* [4];
	for (int i = 0; i < 4; i++) {
		W_next[i] = new double[3];
		for (int j = 0; j < 3; j++) {
			W_next[i][j] = W_next_raw[i][j];
		}
	}

	double b_next_raw[4] = { 3, 8, 6, 3 };
	double* b_next = new double[4];
	for (int i = 0; i < 4; i++) {
		b_next[i] = b_next_raw[i];
	}

	double delta_next_raw[4] = { 3, 8, 9, 7 };
	double* delta_next = new double[4];
	for (int i = 0; i < 4; i++) {
		delta_next[i] = delta_next_raw[i];
	}*/

	/*test1.backward(4, W_next, b_next, delta_next);
	test1.backward(4, W_next, b_next, delta_next);*/

}

int main()
{
	test_layer();
	// cout_matrix(2, 3, zeros_2d(2, 3));
	// cout_matrix(3, 2, transpose(2, 3, zeros_2d(2, 3)));
}
