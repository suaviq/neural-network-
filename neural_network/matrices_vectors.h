#pragma once
#include<iostream>
#include<stdlib.h>
#include <cstdlib>
#include <ctime>
#include<cmath>

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

double** add_matrices(int m, int n, double **A, double **B, double **C)
{
	int i, j;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			C[i][j] = A[i][j] + B[i][j];
			cout << C[i][j] << endl;
		}
	}
	return C;
}

double** substract_matrices(int m, int n, double** A, double** B, double** C)
{
	int i, j;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			C[i][j] = A[i][j] + (-1)*B[i][j];
			cout << C[i][j] << endl;
		}
	}

	return C;
}

double** multiply_vecT_vec(int m, double* vecT, double* vec, double** R)
{
	double** R = new double* [m];
		for (int i = 0; i < m; i++)
		{
			R[i] = new double[m];
			for (int j = 0; j < m; j++)
			{
				R[i][j] = vecT[i] * vec[j];
			}
		}
		return R;
}
double* element_wise_multiply(int m, double* vec1, double* vec2, double* R)
{
	for (int i = 0; i < m; i++)
	{
		R[i] = vec1[i] * vec2[i];
	}
	return R;
}
double** sigmoid_matrix(int m, int n, double **x, double** Z)
{
	int i, j;

	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			Z[i][j] = 1 / (1+ exp(-x[i][j]));
			cout << Z[i][j]<<endl;
		}
	}
	return Z;
}

double* derivative_sigmoid_vec(int m, double* x, double* R)
{
	int i;
	for (i = 0; i < m; i++)
	{
		//double e = exp(-x[i]);
		//double denominator = e + 1;
		//R[i] = e / (pow(denominator, 2)
		R[i] = exp(-x[i]) / ((exp(-x[i])+1)* (exp(-x[i]) + 1));
	}
	return R;
}

double** relu_matrix(int m, int n, double** x, double** Z)
{
	int i, j;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (x[i][j] >= 0)
			{
				Z[i][j] = x[i][j];
			}
			else Z[i][j] = 0.0;

			cout << Z[i][j]<<endl;
		}
	}
	return Z;
}

double* derivative_relu_vec(int m, double*x, double* R)
{
	int i;
	for (i = 0; i < m; i++)
	{
		if (x[i] < 0)
		{
			R[i] = 0.0;
		}
		else
		{
			R[i] = 1.0;
		}
	}
	return R;
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
double* initialize_layer_bias(int m)
{
	srand(time(0));
	double* vector = new double[m];
	for (int i = 0; i < m; i++) 
	{
		vector[i] = double((rand() % 100) - 50) / double(100);
		cout << vector[i] << endl;
	}
	return vector;

}

double* zeros_1d(int m)
{
	srand(time(0));
	double* vector = new double[m];
	for (int i = 0; i < m; i++)
	{
		vector[i] = double(0);
		cout << vector[i] << endl;
	}
	return vector;

}
//pochodne dla funkcji aktywacyjnej obu
double** zeros_2d(int m, int n)
{
	double** matrix = new double* [m];
	for (int i = 0; i < m; i++) {
		matrix[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			matrix[i][j] = double(0);
			cout << matrix[i][j] << endl;
		}
	}
	return matrix;

}

int main() 
{
	double matrix1[2][3] = {{1, -1, 2}, {0, -3, 0}};
	double matrix2[2][3]= {{1, -1, 2}, {0, -3, 1}};
	double c_matrix[2][3];
	double vector1[] = {2, 1, 0};
	

	double** matrix = new double*[2];
	for (int i = 0; i < 2; i++) {
		matrix[i] = new double[3];
		for (int j = 0; j < 3; j++) {
			matrix[i][j] = matrix1[i][j];
		}
	}
	double** matrix_sum1 = new double* [2];
	for (int i = 0; i < 2; i++) {
		matrix_sum1[i] = new double[3];
		for (int j = 0; j < 3; j++) {
			matrix_sum1[i][j] = matrix1[i][j];
		}
	}
	double** matrix_sum2 = new double* [2];
	for (int i = 0; i < 2; i++) {
		matrix_sum2[i] = new double[3];
		for (int j = 0; j < 3; j++) {
			matrix_sum2[i][j] = matrix2[i][j];
		}
	}
	double** matrix_result = new double* [2];
	for (int i = 0; i < 2; i++) {
		matrix_result[i] = new double[3];
		for (int j = 0; j < 3; j++) {
			matrix_result[i][j] = c_matrix[i][j];
		}
	}

	sigmoid_matrix(2, 3, matrix_sum1, matrix_result);
	//add_matrices(2, 3, matrix_sum1, matrix_sum2, matrix_result);
	cout << endl;
	//substract_matrices(2, 3, matrix_sum1, matrix_sum2, matrix_result);

	double* vector = new double[3];
	for (int i = 0; i < 3; i++) {
		vector[i] = vector1[i];
	}

	//double *result = multiply_mat_vec(2, 3, matrix, vector);
	//double** c = initialize_layer_weights(3, 3);		
}
