#include <cstdio>
#include <queue>

int main()
{
	int n;
	long long result = 0;
	scanf("%d", &n);
	std::priority_queue<long long, std::vector<long long>, std::greater<long long>> heap;
	for (int i = 0;i < n;i++)
	{
		long long t;
		scanf("%lld", &t);
		heap.push(t);
	}
	if (n == 0)
	{
		printf("0");
		return 0;
	}
	if (n == 1)
	{
		result += heap.top();
		printf("%lld", result);
		return 0;
	}
	if (n == 2)
	{
		result += heap.top();
		heap.pop();
		result += heap.top();
		printf("%lld", result);
		return 0;
	}

	if ((n - 3) % 3 == 1)
	{
		heap.push(0);
	}

	while (1)
	{
		if (heap.size() == 3)
		{
			long long sum = 0;
			while (heap.size() != 0)
			{
				sum += heap.top();
				heap.pop();
			}
			result += sum;
			printf("%lld", result);
			return 0;
		}
		else if(heap.size() > 3)
		{
			long long sum = 0;
			sum += heap.top();
			heap.pop();
			sum += heap.top();
			heap.pop();
			sum += heap.top();
			heap.pop();
			heap.push(sum);
			result += sum;
		}
		else
		{
			return -1;
		}
	}
}