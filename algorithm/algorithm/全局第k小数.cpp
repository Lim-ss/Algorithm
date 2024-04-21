#include <cstdio>
#include <iostream>

//从A[l~r]中选出第k小的数，k = 0，1，2，...，r - l.
int QSelect(int l, int r, int k, int* A)
{
	if (l == r)
	{
		return A[l];
	}

	int m = (l + r) / 2;
	int pivot = A[m];
	{
		//将pivot放在最后一个位置
		A[m] = A[r];
		A[r] = pivot;
	}
	int i = l;
	int j = r - 1;
	while (i < j)
	{
		while (A[i] < pivot)
		{
			i++;
		}
		while (A[j] > pivot && j > 0)
		{
			j--;
		}
		if (i < j)
		{
			int t = A[i];
			A[i] = A[j];
			A[j] = t;
			i++;
			j--;
		}
	}
	//此时 i = j 或 i = j + 1;
	if (A[i] >= pivot)
	{
		A[r] = A[i];
		A[i] = pivot;
	}
	else
	{
		i++;
		A[r] = A[i];
		A[i] = pivot;
	}
	//此时 i 为 pivot的位置
	
	if (i - l > k)
	{
		// 第k小的值在左侧区间内，仍然排升序第k位
		return QSelect(l, i - 1, k, A);
	}
	else if (i - l < k)
	{
		// 第k小的值在右侧区间内，排升序第 k - (i - l + 1) 位，因为减掉了左区间加上pivot本身
		return QSelect(i + 1, r, k - (i - l + 1), A);
	}
	else //(i - l == k)
	{
		// A[i] 即为所求的第k小的值
		return A[i];
	}
}

int main()
{
	int k, n;
	std::cin >> n >> k;
	int* A = new int[n];
	for (int i = 0;i < n;i++)
	{
		scanf("%d", &A[i]);
	}

	int ans = QSelect(0, n - 1, k - 1, A);
	std::cout << ans << std::endl;
	delete[] A;
	return 0;
}