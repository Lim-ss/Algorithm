#include <iostream>
#include <vector>
#include <cstdio>

int main()
{
	int n;
	std::cin >> n;
	std::vector<int> A(n);//原序列
	std::vector<int> B;//用于寻找最长子序列
	for (int i = 0;i < n;i++)
	{
		scanf("%d", &A[i]);
	}
	//贪心算法
	B.push_back(A[0]);
	for (int i = 1;i < n;i++)
	{
		int a = A[i];
		if (a <= B.back())
		{
			B.push_back(a);
		}
		else
		{
			//二分查找
			int l = 0;
			int r = B.size() - 1;
			while (r - l > 1)
			{
				int m = (l + r) / 2;
				if (B[m] >= a)
				{
					l = m;
				}
				else
				{
					r = m;
				}
			}
			if (l != r)
			{
				if (B[l] >= a)
					B[r] = a;
				else
					B[l] = a;
			}
			else
			{
				if (B[l] >= a)
				{
					B[l + 1] = a;
				}
				else
				{
					B[l] = a;
				}
			}
		}
	}
	std::cout << B.size();
}