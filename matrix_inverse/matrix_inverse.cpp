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

void findAndSwapWithNonZeroEntryRow(vector<vector<double>> &matrix, vector<vector<double>> &inverseMatrix, int n, int start)
{
	for(int i = start+1; i < n ; i++)
	{
		if(matrix[i][start] != 0)
		{
			swapRows(matrix, n, start, i);
			swapRows(inverseMatrix, n, start, i);
			return ;
		}
	}
}

void makeCellOneAndRestEntriesZero(vector<vector<double>> &matrix, vector<vector<double>> &inverseMatrix, int n, int idx)
{
	double value = matrix[idx][idx];
	for(int i = 0 ; i < n ; i++)
	{
		matrix[idx][i] /= value;
		inverseMatrix[idx][i] /= value;
	}	

	for(int i = 0 ; i < n ; i++)
	{
		if(i == idx)
		{
			continue;
		}
		value = matrix[i][idx];
		for(int j = 0 ; j < n ; j++)
		{
			matrix[i][j] -= value*matrix[idx][j];
			inverseMatrix[i][j] -= value*inverseMatrix[idx][j];
		}
	}
}

vector<vector<double>> initializeIdentityMatrix(int n)
{
	vector<vector<double>> identityMatrix;
	for(int i = 0 ; i < n ; i++)
	{
		vector<double> row;
		for(int j = 0 ; j < n ; j++)
		{
			if(i == j)
			{
				row.push_back(1);
			}
			else
			{
				row.push_back(0);
			}
		}
		identityMatrix.push_back(row);
	}
	return identityMatrix;
}

pair<bool, vector<vector<double>>> findMatrixInverse(vector<vector<double>> matrix)
{
	int n = matrix.size();
	vector<vector<double>> inverseMatrix = initializeIdentityMatrix(n);
	for(int i = 0 ; i < n ; i++)
	{
		if(matrix[i][i] == 0)
		{
			findAndSwapWithNonZeroEntryRow(matrix, inverseMatrix , n, i);
		}
		if(matrix[i][i] == 0)
		{
			return {false, inverseMatrix};
		}
		makeCellOneAndRestEntriesZero(matrix, inverseMatrix, n, i);
	}
	return {true, inverseMatrix};
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
	pair<bool , vector<vector<double>>> matrixInverse = findMatrixInverse(matrix);
	bool doesMatrixInverseExist = matrixInverse.first;
	vector<vector<double>> inverseMatrix = matrixInverse.second;
	if(doesMatrixInverseExist)
	{
		cout<<"Inverse of the matrix is:\n";
		for(int i = 0 ; i < n ; i++)
		{
			for(int j = 0 ; j < n ; j++)
			{
				cout<<inverseMatrix[i][j]<<" ";
			}
			cout<<'\n';
		}
	}
	else
	{
		cout<<"Inverse of the matrix does not exist.\n";
	}
	return 0;
}