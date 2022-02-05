#include <iostream>
#include<vector>
#include "matrices_vectors.h"
#include "layer.h"
#include "neural_network.h"
using namespace std;


int main()
{
	NeuralNetwork nn = NeuralNetwork(1, 1, 1, 2, 0.01);

	double** X_train = read_matrix_txt(6, 2, "D:/neural_network/neural-network-/raw_matrix_x.txt");
	double** y_train = read_matrix_txt(6, 1, "D:/neural_network/neural-network-/raw_matrix_y.txt");

	double** X_test = read_matrix_txt(6, 3, "D:/neural_network/neural-network-/matrix_train.txt");

	nn.fit(1000, X_train, y_train, 6);
	nn.predict(X_test, 6);
	
}

