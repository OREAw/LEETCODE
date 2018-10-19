#include <iostream>
#include <vector>
#include<string>
#include<queue>
#include<unordered_set>
using namespace std;



//Strings A and B are K - similar(for some non - negative integer K) 
//if we can swap the positions of two letters in A exactly K times 
//so that the resulting string equals B.
//Given two anagrams A and B, return the smallest K for which A and B are K - similar.

class Solution {
public:
	int kSimilarity(string A, string B)
	{
		if (A == B) return 0;
		queue<pair<string, int>>  q; //��ʾstring��B֮�䲻��ͬ�ĵ�һ���ַ���λ��Ϊint��ֵ���������һ��Pair����ڶ�������
		unordered_set<string> visited; //s��ʾ�Ѿ����ʹ����ַ���
		int i = 0;
		for (; i<A.size(); i++)
		{
			if (A[i] != B[i])
				break;
		}
		//i��ʾA��B֮���һ������ͬ��λ���±ꡣ
		q.push(make_pair(A, i));
		visited.insert(A);//A���Ϊ�Ѿ�����
		int steps = 0; //��С��������
		while (!q.empty())
		{
			int n = q.size();
			for (int i = 0; i<n; i++)
			{
				string t = q.front().first;
				int index = q.front().second;
				q.pop();
				if (t == B) return steps; //����֮���t����B�����ҵ���̵Ľ�������������С�Ľ���������Ҳ����BFS�Ĳ��������أ�
				while (t[index] == B[index]) ++index;
				for (int i = index + 1; i<B.size(); i++) //�ӵ�һ������ͬ��λ�ÿ�ʼѰ�ҿ��Խ������ַ�
				{
					if (t[i] == B[index] && t[i] != B[i]) //�����������Ҫ��t[i]==B[i]��ʱ��Ҫ����Ҳ����ԭ���Ķ�λ��ͬ��λ�ò�Ҫ�������Խ�ʡʱ�䡣
					{
						swap(t[i], t[index]);//�������Խ������ַ�
						if (!visited.count(t))
						{
							q.push({ t, index + 1 });//����֮����ַ����Լ���һ������ͬ���ַ���λ�÷ŵ�������ȥ
							visited.insert(t);
						}
						swap(t[i], t[index]);
					}
				}
			}
			++steps;//��¼������
		}
		return steps;
	}
};
int main()
{

//Input : A = "ab", B = "ba"
//Output : 1
//
//Input : A = "abc", B = "bca"
//Output : 2
//
//Input : A = "abac", B = "baca" 
//Output : 2
//
//Input : A = "aabc", B = "abca"
//Output : 2


	//"aabbccddee"  "bdcebacdae" 5
	//"aabbccddee"  "dcacbedbae" 5
	//"aabbccddee"  "cbeddebaac" 6
	//"abccaacceecdeea"  bcaacceeccdeaae" 9
	Solution s;
	string word1 = "aabbccddee";
	string word2 = "bdcebacdae";
	cout << s.kSimilarity(word1, word2) << endl;



	system("pause");
	return 0;
}

