#include <iostream>
#include <iterator>

using namespace std;

int min(int a, int b)
{
	return a < b ? a : b;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

void knapsack(int v[], int w[], int c, int n, int m[][10])
{
	int jmax = min(w[n] - 1, c);
	for (int j = 0; j <= jmax; j++)
	{
		m[n][j] = 0;
	}
	for (int j = w[n]; j <= c; j++)
	{
		m[n][j] = v[n];
	}

	for (int i = n - 1; i > 1; i--)
	{
		jmax = min(w[i] - 1, c);
		for (int j = 0; j <= jmax; j++)
		{
			m[i][j] = m[i + 1][j];
		}
		for (int j = w[i]; j <= c; j++)
		{
			m[i][j] = max(m[i + 1][j], m[i + 1][j - w[i]] + v[i]);
		}
		m[1][c] = m[2][c];
		if (c >= w[1])
		{
			m[1][c] = max(m[1][c], m[2][c - w[1]] + v[1]);
		}
	}
}

void traceback(int m[][10], int w[], int c, int n, int x[])
{
	for (int i = 1; i < n; i++)
	{
		if (m[i][c] == m[i + 1][c])
		{
			x[i] = 0;
		}
		else
		{
			x[i] = 1;
			c = c - w[i];
		}
	}
	x[n] = (m[n][c]) ? 1 : 0;
}


int main()
{

	int c = 8;
	int v[] = { 0, 6, 3, 5, 4, 6 }, w[] = { 0, 2, 2, 6, 5, 4 };//下标从1开始  
	int N = 5;
	int *x = new int[N];
	int m[10][10];

	cout << "待装物品重量分别为：" << endl;
	for (int i = 1; i <= N; i++)
	{
		cout << w[i] << " ";
	}
	cout << endl;

	cout << "待装物品价值分别为：" << endl;
	for (int i = 1; i <= N; i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	knapsack(v, w, c, N, m);

	cout << "背包能装的最大价值为：" << m[1][c] << endl;

	traceback(m, w, c, N, x);
	cout << "背包装下的物品编号为：" << endl;
	for (int i = 1; i <= N; i++)
	{
		if (x[i] == 1)
		{
			cout << i << " ";
		}
	}
	cout << endl;


	system("pause");
	return 0;
}

