#include <iostream>
#include <vector>

using namespace std;

class solve_maze
{
public:
	// 没有障碍物，从左上到右下，只能向下或向上移动， 返回路径数
	//递推式：res[i][j] = res[i-1][j] + res[i][j-1];  
	//初始化的时候将res二维数组的第一行第一列都置为1，方便计算
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
	//首先初始化的时候对第一行第一列上面出现障碍物的地方将path[i][0]  
	//和path[0][i]都置为0.然后我们还是利用上面的递推式进行计算：
	//res[i][j] = res[i-1][j] + res[i][j-1]。
	//循环计算的时候如果碰到障碍物，就将path[i][j]置为0.
	//只能向上或向下移动
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

