#pragma once
#include<iostream>
#include<stdlib.h>
#include <cstdlib>
#include <ctime>
#include<cmath>

using namespace std;

// correct + print
double* multiply_matrix_by_vector(int m, int n, double **matrix, double *vector)
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
	
	//for (int i = 0; i < m; i++)
	//{
	//	cout << result[i] << '\t';
	//}
	return result;
}

//print
double** multiply_matrix_by_constant(int m, int n, double** matrix, double constant)
{
	double** R = new double* [m];
	for (int i = 0; i < m; i++)
	{
		R[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			R[i][j] = constant + matrix[i][j];
		}
	}
	return R;
}

//print 
double* multiply_vector_by_constant(int m, double* vector, double constant)
{
	double* R = new double[m];
	for (int i = 0; i < m; i++)
	{
		R[i] = constant * vector[i];
	}
	return R;
}
 
// repaired + print
double** add_matrices(int m, int n, double **A, double **B)
{
	int i, j;
	double** C = new double*[m];
	for (i = 0; i < m; i++)
	{
		C[i] = new double[n];
		for (j = 0; j < n; j++)
		{
			C[i][j] = A[i][j] + B[i][j];
		}
	}
	return C;
}

//repaired
double** substract_matrices(int m, int n, double** A, double** B)
{
	int i, j;
	double** C = new double* [m];
	for (i = 0; i < m; i++)
	{
		C[i] = new double[n];
		for (j = 0; j < n; j++)
		{
			C[i][j] = A[i][j] + (-1)*B[i][j];
		}
	}
	return C;
}

double* substract_constant_from_vector(int m, double constant, double* A)
{
	int i;
	double* result = new double[m];
	for (i = 0; i < m; i++)
	{
		result[i] = A[i] - constant;
	}
	return result;
}


double* substract_vectors(int m, double* A, double* B)
{
	int i;
	double* result = new double[m];
	for (i = 0; i < m; i++)
	{
		result[i] = A[i] - B[i];
	}
	return result;
}

double* add_vectors(int m, double* A, double* B)
{
	int i;
	double* result = new double[m];
	for (i = 0; i < m; i++)
	{
		result[i] = A[i] + B[i];
	}
	return result;
}

//repaired
double** multiply_vectorT_by_vector(int m, double* vecT, double* vec)
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

double multiply_vectorT_by_constant(int m, double* vecT, double constant)
{
	double sum = 0;
	for (int i = 0; i < m; i++)
	{
		sum += vecT[i] * constant;
	}
	return sum;
}

//repaired
double* element_wise_multiply(int m, double* vec1, double* vec2)
{
	double* R = new double[m];
	for (int i = 0; i < m; i++)
	{
		R[i] = vec1[i] * vec2[i];
	}
	return R;
}

//repaired
double* sigmoid_vector(int m, double *x)
{
	int i;
	double* Z = new double[m];
	for (i = 0; i < m; i++)
	{
		Z[i] = 1 / (1+ exp(-x[i]));
	}
	return Z;
}

//repaired
double* derivative_sigmoid_vector(int m, double* x)
{
	int i;
	double* R = new double[m];
	for (i = 0; i < m; i++)
	{
		//double e = exp(-x[i]);
		//double denominator = e + 1;
		//R[i] = e / (pow(denominator, 2)
		R[i] = exp(-x[i]) / ((exp(-x[i])+1)* (exp(-x[i]) + 1));
	}
	return R;
}

// MA BYĆ WEKTOREM
double* relu_vector(int m, double* x)
{
	int i, j;
	double* Z = new double [m];
	for (i = 0; i < m; i++)
	{
		if (x[i] >= 0)
		{
			Z[i] = x[i];
		}
		else
		{
			Z[i] = 0.0;
		}
	}
	return Z;
}

// DOBRZE
double* derivative_relu_vector(int m, double*x)
{
	int i;
	double* R = new double[m];
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

//repaired
double** initialize_layer_weights(int m, int n)
{
	srand(time(0));
	double** matrix = new double* [m];
	for (int i = 0; i < m; i++) {
		matrix[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			matrix[i][j] = double((rand() % 100) - 50)/double(100);
		}
	}
	return matrix;

}

//repaired
double* initialize_layer_bias(int m)
{
	srand(time(0));
	double* vector = new double[m];
	for (int i = 0; i < m; i++) 
	{
		vector[i] = double((rand() % 100) - 50) / double(100);
	}
	return vector;

}

//repaired
double* zeros_1d(int m)
{
	double* vector = new double[m];
	for (int i = 0; i < m; i++)
	{
		vector[i] = double(0);
	}
	return vector;

}

//repaired
double** zeros_2d(int m, int n)
{
	double** matrix = new double* [m];
	for (int i = 0; i < m; i++) {
		matrix[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			matrix[i][j] = double(0);
		}
	}
	return matrix;

}

void cout_matrix(int m, int n, double** M)
{
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
		{
			cout << M[i][j] << ' ';
		}
		cout << endl;
	}
}

void cout_vector(int m, double* V)
{
	for (int i = 0; i < m; i++) {
		
		cout << V[i] << ' ';
	}
	cout << endl;
}

// todo
double** transpose(int m, int n, double **M) 
{
	double** matrixT = new double* [n];
	for (int i = 0; i < n; i++) {
		matrixT[i] = new double[m];
		for (int j = 0; j < m; j++)
		{
			matrixT[i][j] = M[j][i];
		}
	}
	return matrixT;
}