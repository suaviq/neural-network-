#include <iostream>
#include<vector>
#include "matrices_vectors.h"
#include "layer.h"
#include "neural_network.h"
using namespace std;


int main()
{
	NeuralNetwork nn = NeuralNetwork(1, 1, 1, 2, 0.01);

	double raw_x[6][2] = { {1, 2}, {-1, -2}, {4, 1}, {1, 2}, {0, -1}, {1, 2} };
	double raw_y[6][1] = { {1}, {0}, {1}, {1}, {0}, {1} };
	double** X = new double* [6];
	double** y = new double* [6];

	for (int i = 0; i < 6; i++)
	{
		X[i] = new double[2];
		for (int j = 0; j < 2; j++)
		{
			X[i][j] = raw_x[i][j];
		}

		y[i] = new double[1];
		for (int j = 0; j < 1; j++)
		{
			y[i][j] = raw_y[i][j];
		}
	}

	nn.fit(1000, X, y, 6);
	nn.predict(X, 6);

	// cout_vector(10, multiply_matrix_by_vector(10, 10, initialize_layer_weights(10, 10), initialize_layer_bias(10)));
}

