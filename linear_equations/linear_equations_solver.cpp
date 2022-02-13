#include<bits/stdc++.h>
using namespace std;

void swapRows(vector<vector<double>> &A, vector<double> &B, int n, int row1 , int row2)
{
	double temp;
	for(int i = 0 ; i < n ; i++)
	{
		temp = A[row1][i];
		A[row1][i] = A[row2][i];
		A[row2][i] = temp;
	}
    temp = B[row1];
    B[row1] = B[row2];
    B[row2] = temp;
}

void findAndSwapWithNonZeroEntryRow(vector<vector<double>> &A, vector<double> &B, int n, int start)
{
	for(int i = start+1; i < n ; i++)
	{
		if(A[i][start] != 0)
		{
			swapRows(A, B, n, start, i);
			return ;
		}
	}
}

void makeCellOneAndRestEntriesZero(vector<vector<double>> &A, vector<double> &B, int n, int idx)
{
	double value = A[idx][idx];
	for(int i = 0 ; i < n ; i++)
	{
		A[idx][i] /= value;
	}	
    B[idx] /= value;

	for(int i = 0 ; i < n ; i++)
	{
		if(i == idx)
		{
			continue;
		}
		value = A[i][idx];
		for(int j = 0 ; j < n ; j++)
		{
			A[i][j] -= value*A[idx][j];
			
		}
        B[i] -= value*B[idx];
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

vector<double> linearEquationsSolver(vector<vector<double>> A, vector<double> B)
{
	int n = A.size();
	for(int i = 0 ; i < n ; i++)
	{
		if(A[i][i] == 0)
		{
			findAndSwapWithNonZeroEntryRow(A, B , n, i);
		}
		if(A[i][i] == 0)
		{
			return B;
		}
		makeCellOneAndRestEntriesZero(A, B, n, i);
	}
	return B;
}

int main()
{
	int n;
	cout<<"Linear Equations Solver\n";
	cout<<"Enter the number of equations:\n";
	cin>>n;
    cout<<"Format AX=B\n";
	cout<<"Enter the A matrix:\n";
	vector<vector<double>> A;
	double value;
	for(int i = 0; i < n ; i++)
	{
		vector<double> row;
		for(int j=0;j<n;j++)
		{
			cin>>value;
			row.push_back(value);
		}
		A.push_back(row);
	}
    cout<<"Enter the B vector:\n";
	vector<double> B;
	for(int i = 0; i < n ; i++)
	{
		cin>>value;
		B.push_back(value);
	}
	vector<double> solution = linearEquationsSolver(A, B);
	if(true)
	{
		cout<<"Solution is:\n";
		for(int i = 0 ; i < n ; i++)
		{
			cout<<"x"<<i+1<<" = "<<solution[i]<<"\n";
		}
	}
	return 0;
}