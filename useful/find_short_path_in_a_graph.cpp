#include<iostream>
#include<vector>

using namespace std;
template<class T>
T max(T a, T b)
{
	return a > b ? a : b;
}
template<class T>
T min(T a, T b)
{
	return a < b ? a : b;
}
void output_matrix(int **matrix, int start, int end)
{
	for (int i = start; i < end; i++)
	{
		for (int j = start; j < end; j++)
		{
			cout << matrix[i][j] << ",";
		}
		cout << endl;
	}
}

void output_path(int **kay, int i, int j)
{
	if (i == j)
	{
		return;
	}
	if (kay[i][j] == 0)
	{
		cout << j << ",";
		return;
	}
	output_path(kay, i, kay[i][j]);
	output_path(kay, kay[i][j], j);
}

void find_path(int **a, int **c, int **kay, int n)
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			c[i][j] = a[i-1][j-1];
			kay[i][j] = 0;
		}
	}
	bool b;
	for (int k = 1; k <= n; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				b = c[i][k] != INT_MAX && c[k][j] != INT_MAX && (c[i][j] == INT_MAX || c[i][j] >(c[i][k] + c[k][j]));
				if (b)
				{
					c[i][j] = c[i][k] + c[k][j];
					kay[i][j] = k;
				}
			}
		}
	}
}

void output_path(int **c, int **kay, int i, int j)
{
	if (c[i][j] == INT_MAX)
	{
		cout << "there is no path !" << endl;
	}
	else
	{
		cout << "The path from " << i << " to " << j << " is:" << endl;
		cout << i << ",";
		output_path(kay, i, j);
	}
}



int main()
{
	int n = 5;
	int **a = new int *[n];
	int a1[] = { 0, 1, 4, 4, 8 };
	int a2[] = { 3, 0, 1, 5, 9 };
	int a3[] = { 2, 2, 0, 1, 8 };
	int a4[] = { 8, 8, 9, 0, 1 };
	int a5[] = { 8, 8, 2, 9, 0 };
	a[0] = a1;
	a[1] = a2;
	a[2] = a3;
	a[3] = a4;
	a[4] = a5;
	cout << "a:" << endl;
	output_matrix(a, 0, n);
	int **c = new int *[n+1];
	int **kay = new int *[n+1];
	for (int i = 0; i <= n; i++)
	{
		c[i] = new int[n + 1];
		kay[i] = new int[n + 1];
	}
	find_path(a, c, kay, n);
	cout << "c:" << endl;
	output_matrix(c, 1, n+1);
	cout << "kay:" << endl;
	output_matrix(kay, 1, n + 1);

	output_path(c, kay, 1, 5);

	cout << endl;
	system("pause");
	return 0;
}

