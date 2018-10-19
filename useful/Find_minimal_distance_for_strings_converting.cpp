#include <iostream>
#include <vector>
#include<string>


using namespace std;

template<class T>
T min(T a, T b)
{
	return a < b ? a : b;
}

//Given two words word1 and word2, find the minimum number of steps required to 
//convert word1 to word2. (each operation is counted as 1 step.)
//
//You have the following 3 operations permitted on a word :
//a) Insert a character
//b) Delete a character
//c) Replace a character                                                             ���ĵ�ַ
//
//����������͵Ķ�̬�滮���⣬��dp[i][j]��ʾ��word1[0...i - 1]��word2[0...j - 1]�ı༭����, 
//��̬�滮�������£�
//��ʼ������dp[0][i] = i, dp[i][0] = i
//dp[i][j] = (word1[i - 1] == word2[j - 1]) ? 
//           dp[i - 1][j - 1] : 1 + min(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1])��
//���ͣ�����������ʵ����һ����ĸ��ͬ����ô�����ĸ���Բ��ñ仯���༭��������������ʶ�ȥ��
//���һ����ĸ��ı༭���룻������һ����ĸ��ͬ�����������ִ���ʽ��
//a����word1����һ����word2������ĸ��ͬ����ĸ����ʱword1��word2�����һ����ĸ��һ���ˣ�
//��ʱ�༭�������1����������� + ����ǰ��word1��word2ȥ�����һ����ĸ��ı༭���� 
//b��ɾ��word1�����һ����ĸ����ʱ�༭�������1��ɾ�������� + word1ȥ�����һ����ĸ��word2�ı༭���� 
//c ����word1�����һ����ĸ�滻��word2�����һ����ĸ��
//��ʱ�༭������� 1���滻������ + word1��word2ȥ�����һ����ĸ�ı༭���룬
//Ȼ��ȡ��������µ���С����
//dp[i][j]��ʾ��word[0...i-1]��word2[0...j-1]�ı༭����
class Solution {
public:
	int minDistance(string word1, string word2) {
		const int len1 = word1.size(), len2 = word2.size();
		int **dp = new int *[len1 + 1];
		for (int i = 0; i <= len1; i++)
		{
			dp[i] = new int[len2 + 1];
		}
		for (int i = 0; i <= len2; i++)dp[0][i] = i;
		for (int i = 0; i <= len1; i++)dp[i][0] = i;

		for (int i = 1; i <= len1; i++)
		{
			for (int j = 1; j <= len2; j++)
			{
				if (word1[i - 1] == word2[j - 1])
					dp[i][j] = dp[i - 1][j - 1];
				else dp[i][j] = 1 + min(dp[i][j - 1], min(dp[i - 1][j], dp[i - 1][j - 1]));
			}
		}
		return dp[len1][len2];
	}
};
int main()
{
//Input: word1 = "horse", word2 = "ros"
//Output : 3
//Input: word1 = "intention", word2 = "execution"
//Output : 5
	
	Solution s;
	string word1 = "horse";
	string word2 = "ros";
	cout << s.minDistance(word1, word2) << endl;

	system("pause");
	return 0;
}

