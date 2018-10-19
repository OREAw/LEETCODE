
//BY recursion
// linear equation solution, such as AX = B;
// note that, A is a coefficient vector, B is a constant, and X is an unknown vector.

void linear_solution(vector<int> vec_a, int sum_b, vector<vector<int>> & solutions, vector<int> & one_solution)
{
	if (vec_a.size() == 0)
	{
		if (sum_b == 0)
		{
			solutions.push_back(one_solution);
		}
	}
	else
	{
		int a_i = vec_a.front();
		vec_a.erase(vec_a.begin());
		if (a_i == 0)
		{
			return;
		}
		int sum_i;
		for (int i = 0; i <= sum_b / a_i; i++)
		{
			one_solution.push_back(i);
			sum_i = sum_b - i * a_i;
			linear_solution(vec_a, sum_i, solutions, one_solution);
			one_solution.pop_back();
		}
	}

}

void linear_solution(vector<int> vec_a, int sum_b, vector<vector<int>> & solutions)
{
	vector<int> one_solution;
	linear_solution(vec_a, sum_b, solutions, one_solution);
}

int main()
{
	vector<int> candidates;
	vector<vector<int>> vec;
	int target = 7;
	vector<int> one_solution;
	linear_solution(candidates, target, vec, one_solution);
}


