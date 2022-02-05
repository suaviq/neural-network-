#pragma once
#include <string>
#include "matrices_vectors.h"
#include "layer.h"
using namespace std;

//neural network as a list of layers 

class NeuralNetwork
{
private:
	int n_layers;
	int neurons_hidden;
	int output_size;
	int input_size;
	Layer* hidden_layers;
	OutputLayer output_layer;
public:
	NeuralNetwork(int n_layers, int neurons_hidden, int output_size, int input_size, double learning_rate = 0.01)
	{
		Layer* hidden_layers = new Layer[n_layers];
		hidden_layers[0] = Layer(neurons_hidden, input_size, "relu", learning_rate);
		for (int l = 1; l < n_layers; l++)
		{
			hidden_layers[l] = Layer(neurons_hidden, neurons_hidden, "relu", learning_rate);
		}
		OutputLayer output_layer = OutputLayer(output_size, neurons_hidden, "sigmoid", learning_rate);
		this->n_layers = n_layers;
		this->neurons_hidden = neurons_hidden;
		this->output_size = output_size;
		this->input_size = input_size;
		this->hidden_layers = hidden_layers;
		this->output_layer = output_layer;
	}

	void fit(int epochs, double** X, double** y, int m)			//
	{
		/*m -> wielkosc datasetu/ ilosc elementow w datasetcie
		n -> wielkosc jednego elementu w datasetcie, np X[0] = [1, 2, 3] --> n = 3*/

		for (int epoch = 0; epoch < epochs; epoch++)
		{
			for (int i = 0; i < m; i++) 
			{
				cout << "\r" << "epoch: " << epoch << " progress: " << i;
				// forward
				this->hidden_layers[0].forward(this->input_size, X[i]);
				for (int l = 1; l < this->n_layers; l++)
				{
					this->hidden_layers[l].forward(this->neurons_hidden, hidden_layers[l - 1].access_a());
				}
				this->output_layer.forward(this->neurons_hidden, hidden_layers[this->n_layers - 1].access_a());

				// backward

				this->output_layer.backward(y[i]);
				this->hidden_layers[this->n_layers - 1].backward(this->output_layer.access_neurons_curr(), this->output_layer.access_W(), this->output_layer.access_b(), this->output_layer.access_delta());
				for (int l = this->n_layers - 2; l > -1; l--)
				{
					this->hidden_layers[l].backward(this->hidden_layers[l+1].access_neurons_curr(), this->hidden_layers[l + 1].access_W(), this->hidden_layers[l + 1].access_b(), this->hidden_layers[l + 1].access_delta());
				}
				cout << endl;
			}
		}
	}

//fit: (forward + backward)*n 2 for
//predict: only forward 1 for
	double** predict(double** X, int m)
	{
		double** predicted = new double* [m];
		for (int i = 0; i < m; i++)
		{
			// forward
			this->hidden_layers[0].forward(this->input_size, X[i]);
			for (int l = 1; l < this->n_layers; l++)
			{
				this->hidden_layers[l].forward(this->neurons_hidden, hidden_layers[l - 1].access_a());
			}
			this->output_layer.forward(this->neurons_hidden, hidden_layers[this->n_layers - 1].access_a());
			
			// print results
			cout << "result for element " << i << ": ";
			predicted[i] = new double[this->output_size];
			for (int n = 0; n < this->output_size; n++)
			{
				if (output_layer.access_a()[n] >= 0.5)
					predicted[i][n] = 1;
				else
					predicted[i][n] = 0;
				cout << predicted[i][n] << " ";
			}
			cout << endl;
		}
		return predicted;
	}
};



