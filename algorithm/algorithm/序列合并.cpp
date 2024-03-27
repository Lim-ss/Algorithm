#include <cstdio>
#include <utility>
//使用的是小根堆
class Heap
{
public:
	Heap(int MaxSize);
	~Heap();
	void Push(int n, int index);
	std::pair<int, int> Pop();
	int GetSize() const;
	void PrintHeap();//use for debug
private:
	void ShiftUp();
	void ShiftDown();

	std::pair<int,int>* tree;//first->sum, second->index
	int size;
};

Heap::Heap(int MaxSize)
	:size(0)
{
	tree = new std::pair<int, int>[MaxSize];
}

Heap::~Heap()
{
	delete[] tree;
}

void Heap::Push(int n,int index)
{
	//为了运行效率没有检测是否越界
	tree[size].first = n;
	tree[size].second = index;
	size++;
	ShiftUp();
}

std::pair<int, int> Heap::Pop()
{
	//为了运行效率没有检测是否empty
	std::pair<int, int> root = tree[0];
	tree[0] = tree[size - 1];
	size--;
	ShiftDown();
	return root;
}

int Heap::GetSize() const
{
	return(size);
}

void Heap::PrintHeap()
{
	for (int i = 0;i < size;i++)
	{
		printf("%d ", tree[i].first);
	}
	printf("\n");
}

void Heap::ShiftUp()
{
	int current = size - 1;
	int parent = (current - 1) / 2;
	while (current != 0 && tree[current].first < tree[parent].first)
	{
		std::pair<int, int> t = tree[current];
		tree[current] = tree[parent];
		tree[parent] = t;

		current = parent;
		parent = (current - 1) / 2;
	}
}

void Heap::ShiftDown()
{
	int current = 0;
	int lchild = current * 2 + 1;
	int rchild = current * 2 + 2;
	while (rchild < size)//如果current没有右孩子，退出（要么是叶节点，要么是叶节点的父节点）
	{
		if (tree[current].first < tree[lchild].first)
		{
			if (tree[current].first < tree[rchild].first)
			{
				return;
			}
			std::pair<int, int> t = tree[current];
			tree[current] = tree[rchild];
			tree[rchild] = t;

			current = rchild;
			lchild = current * 2 + 1;
			rchild = current * 2 + 2;
		}
		else if (tree[current].first < tree[rchild].first)
		{
			std::pair<int, int> t = tree[current];
			tree[current] = tree[lchild];
			tree[lchild] = t;

			current = lchild;
			lchild = current * 2 + 1;
			rchild = current * 2 + 2;
		}
		else
		{
			if (tree[lchild].first > tree[rchild].first)
			{
				std::pair<int, int> t = tree[current];
				tree[current] = tree[rchild];
				tree[rchild] = t;

				current = rchild;
				lchild = current * 2 + 1;
				rchild = current * 2 + 2;
			}
			else
			{
				std::pair<int, int> t = tree[current];
				tree[current] = tree[lchild];
				tree[lchild] = t;

				current = lchild;
				lchild = current * 2 + 1;
				rchild = current * 2 + 2;
			}
		}
	}
	if (lchild < size && tree[current].first > tree[lchild].first)
	{
		//最后一个左孩子
		std::pair<int, int> t = tree[current];
		tree[current] = tree[lchild];
		tree[lchild] = t;
	}
}

int main()
{
	int n, t;
	int output = 0;
	scanf_s("%d", &n);
	Heap heap(n);
	int* a = new int[n];
	int* b = new int[n];
	int* p = new int[n];
	for (int i = 0;i < n;i++)
	{
		scanf_s("%d", &t);
		a[i] = t;
	}
	for (int i = 0;i < n;i++)
	{
		scanf_s("%d", &t);
		b[i] = t;
	}
	for (int i = 0;i < n;i++)
	{
		p[i] = 0;
	}

	for (int i = 0;i < n;i++)
	{
		heap.Push(a[i] + b[0], i);
	}

	while (output < n)
	{
		std::pair<int, int> top = heap.Pop();
		output++;
		printf("%d ", top.first);
		p[top.second]++;
		if (p[top.second] < n)
		{
			heap.Push(a[top.second] + b[p[top.second]], top.second);
		}
	}

	delete[] a;
	delete[] b;
	delete[] p;
}

