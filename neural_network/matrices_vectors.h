#pragma once
#include<iostream>
#include<stdlib.h>
#include <cstdlib>
#include <ctime>

using namespace std;

double* multiply_mat_vec(int m, int n, double **matrix, double *vector)
{
	double *result = new double[m];
	for (int i = 0; i < m; i++)
	{
		result[i] = 0;
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			result[i] += (matrix[i][j] * vector[j]);
		}
	}
	
	for (int i = 0; i < m; i++)
	{
		cout << result[i] << endl;
	}
	return result;
}


double** initialize_layer_weights(int m, int n)
{
	srand(time(0));
	double** matrix = new double* [m];
	for (int i = 0; i < m; i++) {
		matrix[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			matrix[i][j] = double((rand() % 100) - 50)/double(100);
			cout << matrix[i][j] << endl;
		}
	}
	return matrix;

}
int main() 
{
	double matrix1[][3] = {{1, -1, 2}, {0, -3, 1}};
	double vector1[] = {2, 1, 0};

	double** matrix = new double*[2];
	for (int i = 0; i < 2; i++) {
		matrix[i] = new double[3];
		for (int j = 0; j < 3; j++) {
			matrix[i][j] = matrix1[i][j];
		}
	}

	double* vector = new double[3];
	for (int i = 0; i < 3; i++) {
		vector[i] = vector1[i];
	}

	double *result = multiply_mat_vec(2, 3, matrix, vector);
	double** c = initialize_layer_weights(3, 3);		
}
