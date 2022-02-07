#include <iostream>
#include<vector>
#include "matrices_vectors.h"
#include "layer.h"
#include "neural_network.h"
using namespace std;


int main()
{
	// task for neural network is simple
	// so we don't need many layer because neural network won't train 
	// vanishing gradients - gradients becomes so smalll that it keeps weights from changing their values
	// in worst case, it can stop neural network from futher training
	NeuralNetwork nn = NeuralNetwork(1, 1, 1, 2, 0.01);

	double** X_train = read_matrix_txt(6, 2, "D:/neural_network/neural-network-/raw_matrix_x.txt");
	double** y_train = read_matrix_txt(6, 1, "D:/neural_network/neural-network-/raw_matrix_y.txt");

	double** X_test = read_matrix_txt(6, 3, "D:/neural_network/neural-network-/matrix_train.txt");

	nn.fit(1000, X_train, y_train, 6);
	nn.predict(X_test, 6);
	
}

