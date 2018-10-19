#include<iostream>
#include<vector>
#include<string>

using namespace std;


class Solution {
public:
// quick sort
	template<class T>
	int max_id(vector<T> v)
	{
		T max_value = v[0];
		int res_id = 0;
		for (int i = 1; i < v.size(); i++)
		{
			if (max_value < v[i])
			{
				max_value = v[i];
				res_id = i;
			}
		}
		return res_id;
	}
	template<class T>
	void quick_sort(vector<T> & vec, int left, int right)
	{
		if (left >= right)
		{
			return;
		}
		int left_cur = left;
		int right_cur = right + 1;
		T base = vec[left];
		while (true)
		{
			do
			{
				left_cur++;
			} while (vec[left_cur] < base);

			do
			{
				right_cur--;
			} while (vec[right_cur] > base);

			if (left_cur >= right_cur)
			{
				break;
			}
			swap(vec[left_cur], vec[right_cur]);
		}
		vec[left] = vec[right_cur];
		vec[right_cur] = base;

		quick_sort(vec, left, right_cur - 1);
		quick_sort(vec, right_cur + 1, right);

	}
	


};
int main()
{
	Solution s;
	int a[] = { 4,1,7,6,9,2,8,0,3,5 };
	//int a[] = { 4, 8, 3, 7, 1, 5, 6, 2 };
	vector<int> vec(a, a + 10);
	int id = s.max_id(vec);
	swap(vec[id], vec[9]);
	s.quick_sort(vec, 0, 9);

	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << endl;
	}
	system("pause");
	return 0;
}

