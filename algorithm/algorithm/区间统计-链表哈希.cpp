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
	struct listNode;
	std::vector<listNode*> arr;
};

struct HashMap::listNode
{
	int key;
	int value;
	HashMap::listNode* next;

	listNode(int key, int value);
};

HashMap::listNode::listNode(int key, int value)
{
	this->key = key;
	this->value = value;
	this->next = nullptr;
}

HashMap::HashMap(int size)
{
	//暂时没写扩容机制，只能初始确定大小
	arr.resize(size, nullptr);
}

void HashMap::Edit(int key, int value)
{
	int hash = Hash(key);
	if (arr[hash] == nullptr)
	{
		arr[hash] = new listNode(key, value);
		return;
	}

	listNode* p = arr[hash];
	listNode* previous = nullptr;
	while (p != nullptr)
	{
		if (p->key == key)
		{
			p->value = value;
			return;
		}
		previous = p;
		p = p->next;
	}
	//没找到，新增一个
	previous->next = new listNode(key, value);
	return;
}

void HashMap::Add(int key)
{
	int hash = Hash(key);
	if (arr[hash] == nullptr)
	{
		arr[hash] = new listNode(key, 1);
		return;
	}

	listNode* p = arr[hash];
	listNode* previous = nullptr;
	while (p != nullptr)
	{
		if (p->key == key)
		{
			p->value++;
			return;
		}
		previous = p;
		p = p->next;
	}
	//没找到，新增一个
	previous->next = new listNode(key, 1);
	return;
}

int HashMap::Find(int key)
{
	listNode* p = arr[Hash(key)];
	while (p != nullptr)
	{
		if (p->key == key)
		{
			return p->value;
		}
		else
		{
			p = p->next;
		}
	}
	return 0;//没找到
}

int HashMap::Hash(int key)
{
	return key % arr.size();
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
	HashMap map(10000);
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
