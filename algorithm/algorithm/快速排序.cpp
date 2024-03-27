#include <cstdio>
#include <cstdlib>

void QSort(int* a, int l, int r)
{
	int m = (l + r) / 2;
	int pivot = a[m];
	{
		//��pivot�������һ��λ��
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
	//��ʱ i = j �� i = j + 1;
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
	//��ʱ i Ϊ pivot��λ��
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