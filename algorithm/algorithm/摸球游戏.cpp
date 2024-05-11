#include <cstdio>
#include <iostream>
#include <vector>

int main()
{
	int m = 998244353;
	int n;
	std::cin >> n;
	
	std::vector<long long> a(n + 1);//a[i]表示第i个袋子里红球的数量，1-base
	std::vector<long long> b(n + 1);//a[i]表示第i个袋子里蓝球的数量，1-base
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld%lld", &a[i], &b[i]);
	}

	//创建二维数组，dp[i][j]表示在前i个袋子中，取出j个红球的方案数
	//dp[n][k],k=0,...,n即为所求
	int rows = n + 1; // 行数
	int cols = n + 1; // 列数
	long long** dp = new long long* [rows];
	for (int i = 0; i < rows; ++i) 
	{
		dp[i] = new long long[cols];
	}

	//初始化dp边界，其中dp[0][0]=1本身没有意义，但是需要用于递推后面的值
	dp[0][0] = 1;
	for (int k = 1; k <= n; k++)
	{
		dp[0][k] = 0;
		dp[k][0] = (dp[k - 1][0] * b[k]) % m;
	}
	//动态规划
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

	//释放内存
	for (int i = 0; i < rows; ++i)
	{
		delete[] dp[i];
	}
	delete[] dp;
}