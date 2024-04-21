#include <cstdio>
#include <iostream>

//��A[l~r]��ѡ����kС������k = 0��1��2��...��r - l.
int QSelect(int l, int r, int k, int* A)
{
	if (l == r)
	{
		return A[l];
	}

	int m = (l + r) / 2;
	int pivot = A[m];
	{
		//��pivot�������һ��λ��
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
	//��ʱ i = j �� i = j + 1;
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
	//��ʱ i Ϊ pivot��λ��
	
	if (i - l > k)
	{
		// ��kС��ֵ����������ڣ���Ȼ�������kλ
		return QSelect(l, i - 1, k, A);
	}
	else if (i - l < k)
	{
		// ��kС��ֵ���Ҳ������ڣ�������� k - (i - l + 1) λ����Ϊ���������������pivot����
		return QSelect(i + 1, r, k - (i - l + 1), A);
	}
	else //(i - l == k)
	{
		// A[i] ��Ϊ����ĵ�kС��ֵ
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