#include <iostream>
#include <vector>

using namespace std;

class solve_maze
{
public:
	// û���ϰ�������ϵ����£�ֻ�����»������ƶ��� ����·����
	//����ʽ��res[i][j] = res[i-1][j] + res[i][j-1];  
	//��ʼ����ʱ��res��ά����ĵ�һ�е�һ�ж���Ϊ1���������
	int maze1(int m, int n) 
	{
		vector<vector<int>> vec(m, vector<int>(n, 1));
		for (int i = 1; i < m; i++)
		{
			for (int j = 1; j < n; j++)
			{
				vec[i][j] = vec[i - 1][j] + vec[i][j - 1];
			}
		}
		return vec[m - 1][n - 1];
	}
	//���ȳ�ʼ����ʱ��Ե�һ�е�һ����������ϰ���ĵط���path[i][0]  
	//��path[0][i]����Ϊ0.Ȼ�����ǻ�����������ĵ���ʽ���м��㣺
	//res[i][j] = res[i-1][j] + res[i][j-1]��
	//ѭ�������ʱ����������ϰ���ͽ�path[i][j]��Ϊ0.
	//ֻ�����ϻ������ƶ�
	int maze2(vector<vector<int>> &obstacleGrid)
	{
		int rows = obstacleGrid.size();
		int cols = obstacleGrid[0].size();
		vector<vector<int>> vec(rows, vector<int>(cols, 0));

		int sign = rows + 1;
		for (int i = 0; i < rows; i++)
		{
			if (obstacleGrid[i][0] == 1)
			{
				sign = i;	
			}
			if (i >= sign)
			{
				vec[i][0] = 0;
			}
			else
			{
				vec[i][0] = 1;
			}
		}

		sign = cols + 1;
		for (int j = 0; j < cols;j++)
		{
			if (obstacleGrid[0][j] == 1)
			{
				sign = j;
			}
			if (j >= sign)
			{
				vec[0][j] = 0;
			}
			else
			{
				vec[0][j] = 1;
			}
		}

		for (int i = 1; i < rows; i++)
		{
			for (int j = 1; j < cols; j++)
			{
				if (obstacleGrid[i][j] == 1)
				{
					vec[i][j] = 0;
				}
				else
				{
					vec[i][j] = vec[i - 1][j] + vec[i][j - 1];
				}
			}
		}
		return vec[rows - 1][cols - 1];
	}
};


int main()
{
	
	vector<vector<int>> grids;
	vector<int> v;
	v.push_back(1);
	v.push_back(0);

	grids.push_back(v);

	solve_maze s;
	cout << s.maze2(grids) << endl;


	system("pause");
	return 0;
}

