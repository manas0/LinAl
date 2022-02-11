#include<bits/stdc++.h>
using namespace std;

void swapRows(vector<vector<double>> &matrix, int n, int row1 , int row2)
{
	double temp;
	for(int i = 0 ; i < n ; i++)
	{
		temp = matrix[row1][i];
		matrix[row1][i] = matrix[row2][i];
		matrix[row2][i] = temp;
	}
}

void findAndSwapWithNonZeroEntryRow(vector<vector<double>> &matrix, int n, int start)
{
	for(int i = start+1; i < n ; i++)
	{
		if(matrix[i][start] != 0)
		{
			swapRows(matrix, n , start , i);
			return ;
		}
	}
}

void makeCellOneAndRestEntriesZero(vector<vector<double>> &matrix, int n, int idx)
{
	double value = matrix[idx][idx];
	for(int i = idx ; i < n ; i++)
	{
		matrix[idx][i] /= value;
	}	

	for(int i = 0 ; i < n ; i++)
	{
		if(i == idx)
		{
			continue;
		}
		value = matrix[i][idx];
		for(int j = idx+1 ; j < n ; j++)
		{
			matrix[i][j] -= value*matrix[idx][j];
		}
	}
}

double calculateDeterminant(vector<vector<double>> matrix)
{
	int n = matrix.size();
	double determinant = 1;
	for(int i = 0 ; i < n ; i++)
	{
		if(matrix[i][i] == 0)
		{
			findAndSwapWithNonZeroEntryRow(matrix, n, i);
			determinant *= -1;
		}
		determinant *= matrix[i][i];
		if(determinant == 0)
		{
			return determinant;
		}
		makeCellOneAndRestEntriesZero(matrix, n, i);
	}
	return determinant;
}

int main()
{
	int n;
	cout<<"Determinant Calculator\n";
	cout<<"Enter the number of rows of matrix:\n";
	cin>>n;
	cout<<"Enter the matrix:\n";
	vector<vector<double>> matrix;
	double value;
	for(int i = 0; i < n ; i++)
	{
		vector<double> row;
		for(int j=0;j<n;j++)
		{
			cin>>value;
			row.push_back(value);
		}
		matrix.push_back(row);
	}
	double determinant = calculateDeterminant(matrix);
	cout<<"Determinant = "<< determinant<<endl;
	return 0;
}
