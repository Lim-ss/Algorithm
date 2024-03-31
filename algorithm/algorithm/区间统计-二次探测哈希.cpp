#include "cstdio"
#include "vector"

class HashMap
{
public:
	HashMap(int size);
	void Edit(int key, int value);
	void Add(int key);
	int Find(int key);
private:
	int Hash(int key);
	struct Map;
	std::vector<Map*> arr;
};

struct HashMap::Map
{
	int key;
	int value;

	Map(int key, int value);
};

HashMap::Map::Map(int key, int value)
{
	this->key = key;
	this->value = value;
}

HashMap::HashMap(int size)
{
	//暂时没写扩容机制，只能初始确定大小
	arr.resize(size, nullptr);
}

void HashMap::Edit(int key, int value)
{
	int hash = Hash(key);
	int t = 1;
	while (arr[hash] != nullptr)
	{
		if (arr[hash]->key == key)
		{
			arr[hash]->value = value;
			return;
		}
		else
		{
			hash = Hash(hash);
		}
	}
	arr[hash] = new Map(key, value);
	return;
}

void HashMap::Add(int key)
{
	int hash = Hash(key);
	int t = 1;
	while (arr[hash] != nullptr)
	{
		if (arr[hash]->key == key)
		{
			arr[hash]->value++;
			return;
		}
		else
		{
			hash = Hash(hash);
		}
	}
	arr[hash] = new Map(key, 1);
	return;
}

int HashMap::Find(int key)
{
	int hash = Hash(key);
	int t = 1;
	while (arr[hash] != nullptr)
	{
		if (arr[hash]->key == key)
		{
			return arr[hash]->value;
		}
		else
		{
			hash = Hash(hash);
		}
	}
	return 0;//没找到
}

int HashMap::Hash(int key)
{
	unsigned int hash = key;
	hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
	hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
	hash = (hash >> 16) ^ hash;
	return hash % arr.size();
}

int main()
{
	//输入
	int n;
	scanf("%d", &n);
	int* A = new int[n];
	for (int i = 0;i < n;i++)
	{
		scanf("%d", &A[i]);
	}
	//长度和数组
	//n * max{A[i]} = 1.5 x 10^9 可以用int表示
	int* B = new int[n];
	for (int i = 0;i < n;i++)
	{
		B[i] = A[i];
	}
	for (int i = 1;i < n;i++)
	{
		B[i] = B[i - 1] + B[i];
	}

	//统计
	long long num = 0;
	HashMap map(1000000);
	map.Add(B[0]);
	for (int l2 = 1;l2 < n;l2++)
	{
		for (int r2 = l2;r2 < n;r2++)
		{
			num += (long long)map.Find(B[r2] - B[l2 - 1]);
		}
		for (int i = l2;i >= 1;i--)
		{
			map.Add(B[l2] - B[i - 1]);
		}
		map.Add(B[l2]);
	}
	printf("%lld", num);
}
