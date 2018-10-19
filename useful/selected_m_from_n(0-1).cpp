
//调用  vector<vector<int>> vec = combine(4, 2)

//本程序的思路是开一个数组，其下标表示1到n个数，数组元素的值为1表示其代表的数被选中，为0则没选中。
//
//首先初始化，将数组前n个元素置1，表示第一个组合为前n个数。
//
//然后从左到右扫描数组元素值的“10”组合，找到第一个“10”组合后将其变为“01”组合，
//同时将其左边的所有“1”全部移动到数组的最左端。
//
//当第一个“1”移动到数组的n - m的位置，即n个“1”全部移动到最右端时，就得到了最后一个组合。


vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> vec, vvec;
	if (n < k)
	{
		return vec;
	}
	vector<int> v, v_one;
	for (int i = 1; i <= n; i++)
	{
		v.push_back(i);
		if (i <= k)
		{
			v_one.push_back(1);
		}
		else
		{
			v_one.push_back(0);
		}
	}

	if (n == k)
	{
		vec.push_back(v);
		return vec;
	}
	vvec.push_back(v_one);
	bool b = true;
	for (int i = 1; i <= k; i++)
	{
		b = b && (v_one[n - i]);
	}
	while(b == false)
	{
		int i;
		for (i = 0; i < n - 1; i++)
		{
			if ((v_one[i] == 1) && (v_one[i + 1] == 0))
			{
				int temp = v_one[i + 1];
				v_one[i + 1] = v_one[i];
				v_one[i] = temp;
				break;
			}
			
		}
		int count_one = 0;
		for (int j = i; j >= 0; j--)
		{
			if (v_one[j] == 1)
			{
				count_one = count_one + 1;
			}
		}
		for (int t = 0; t < i; t++)
		{
			if (t < count_one)
			{
				v_one[t] = 1;
			}
			else
			{
				v_one[t] = 0;
			}
			
		}

		vvec.push_back(v_one);
		b = true;
		for (int h = 1; h <= k; h++)
		{
			b = b && (v_one[n - h]);
		}
	}
	for (int i = 0; i < vvec.size(); i++)
	{
		vector<int> temp;
		for (int j = 0; j < n; j++)
		{
			if (vvec[i][j] == 1)
			{
				temp.push_back(v[j]);
			}
		}
		vec.push_back(temp);
	}

	return vec;
    }
