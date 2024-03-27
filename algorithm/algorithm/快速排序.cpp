#include <cstdio>
#include <cstdlib>

void QSort(int* a, int l, int r)
{
	int m = (l + r) / 2;
	int pivot = a[m];
	{
		//将pivot放在最后一个位置
		a[m] = a[r];
		a[r] = pivot;
	}
	int i = l;
	int j = r - 1;
	while (i < j)
	{
		while (a[i] < pivot)
		{
			i++;
		}
		while (a[j] > pivot)
		{
			j--;
		}
		if (i < j)
		{
			int t = a[i];
			a[i] = a[j];
			a[j] = t;
			i++;
			j--;
		}
	}
	//此时 i = j 或 i = j + 1;
	if (a[i] >= pivot)
	{
		a[r] = a[i];
		a[i] = pivot;
	}
	else
	{
		i++;
		a[r] = a[i];
		a[i] = pivot;
	}
	//此时 i 为 pivot的位置
	if (l < i - 1)
		QSort(a, l, i - 1);
	if (i + 1 < r)
		QSort(a, i + 1, r);
	return;
}

int main()
{
	int n;
	scanf_s("%d", &n);
	int* a = new int[n];
	for (int i = 0;i < n;i++)
	{
		scanf_s("%d", &a[i]);
	}
	QSort(a, 0, n - 1);
	for (int i = 0;i < n;i++)
	{
		printf("%d", a[i]);
		if (i != n - 1)
		{
			printf(" ");
		}
	}
	delete[] a;
}