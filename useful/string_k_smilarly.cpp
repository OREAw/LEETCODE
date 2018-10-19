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
		queue<pair<string, int>>  q; //表示string和B之间不相同的第一个字符的位置为int的值，他们组成一个Pair存放在队列里面
		unordered_set<string> visited; //s表示已经访问过的字符串
		int i = 0;
		for (; i<A.size(); i++)
		{
			if (A[i] != B[i])
				break;
		}
		//i表示A和B之间第一个不相同的位置下标。
		q.push(make_pair(A, i));
		visited.insert(A);//A标记为已经访问
		int steps = 0; //最小交换步数
		while (!q.empty())
		{
			int n = q.size();
			for (int i = 0; i<n; i++)
			{
				string t = q.front().first;
				int index = q.front().second;
				q.pop();
				if (t == B) return steps; //交换之后的t等于B，则找到最短的交换次数，将最小的交换次数（也就是BFS的层数）返回，
				while (t[index] == B[index]) ++index;
				for (int i = index + 1; i<B.size(); i++) //从第一个不相同的位置开始寻找可以交换的字符
				{
					if (t[i] == B[index] && t[i] != B[i]) //这个条件很重要，t[i]==B[i]的时候不要动，也就是原本的对位相同的位置不要动，可以节省时间。
					{
						swap(t[i], t[index]);//交换可以交换的字符
						if (!visited.count(t))
						{
							q.push({ t, index + 1 });//交换之后的字符串以及下一个不相同的字符的位置放到队列中去
							visited.insert(t);
						}
						swap(t[i], t[index]);
					}
				}
			}
			++steps;//记录层数。
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

