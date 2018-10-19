#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<bitset>

using namespace std;


vector<vector<int>> vec;


// Or using function : next_permutation(begin, end), note that when using "next_permutation", 
// you need to sort(arr, arr+arr.size());
void perm(vector<int> & arr, int begin, int end)
{
	if (end == begin)
	{
		vec.push_back(arr);
		return;
	}
	else
	{
		for (int j = begin; j <= end; j++)
		{
			swap(arr[begin], arr[j]);
			perm(arr, begin + 1, end);
			swap(arr[begin], arr[j]);
		}
	}
}

int main()
{

	

	int a[] = { 1, 2, 3, 4 };
	vector<int> arr(a, a + 4);
	perm(arr, 0, arr.size() - 1);
	system("pause");
	return 0;
}

