
//����  vector<vector<int>> vec = combine(4, 2)

//�������˼·�ǿ�һ�����飬���±��ʾ1��n����������Ԫ�ص�ֵΪ1��ʾ����������ѡ�У�Ϊ0��ûѡ�С�
//
//���ȳ�ʼ����������ǰn��Ԫ����1����ʾ��һ�����Ϊǰn������
//
//Ȼ�������ɨ������Ԫ��ֵ�ġ�10����ϣ��ҵ���һ����10����Ϻ����Ϊ��01����ϣ�
//ͬʱ������ߵ����С�1��ȫ���ƶ������������ˡ�
//
//����һ����1���ƶ��������n - m��λ�ã���n����1��ȫ���ƶ������Ҷ�ʱ���͵õ������һ����ϡ�


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
