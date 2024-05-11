#include <cstdio>
#include <iostream>
#include <vector>

int main()
{
	int m = 998244353;
	int n;
	std::cin >> n;
	
	std::vector<long long> a(n + 1);//a[i]��ʾ��i������������������1-base
	std::vector<long long> b(n + 1);//a[i]��ʾ��i�������������������1-base
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld%lld", &a[i], &b[i]);
	}

	//������ά���飬dp[i][j]��ʾ��ǰi�������У�ȡ��j������ķ�����
	//dp[n][k],k=0,...,n��Ϊ����
	int rows = n + 1; // ����
	int cols = n + 1; // ����
	long long** dp = new long long* [rows];
	for (int i = 0; i < rows; ++i) 
	{
		dp[i] = new long long[cols];
	}

	//��ʼ��dp�߽磬����dp[0][0]=1����û�����壬������Ҫ���ڵ��ƺ����ֵ
	dp[0][0] = 1;
	for (int k = 1; k <= n; k++)
	{
		dp[0][k] = 0;
		dp[k][0] = (dp[k - 1][0] * b[k]) % m;
	}
	//��̬�滮
	for (int i = 1;i <= n;i++)
	{
		for (int j = 1;j <= n;j++)
		{
			dp[i][j] = (dp[i - 1][j] * b[i] + dp[i - 1][j - 1] * a[i]) % m;
		}
	}

	for (int k = 0;k <= n;k++)
	{
		printf("%lld ", dp[n][k]);
	}

	//�ͷ��ڴ�
	for (int i = 0; i < rows; ++i)
	{
		delete[] dp[i];
	}
	delete[] dp;
}