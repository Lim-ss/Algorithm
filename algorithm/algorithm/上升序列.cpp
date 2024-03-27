#include<cstdio>
#include<vector>
#include<cmath>

//树状数组（Binary Index Tree, BIT）
//注意:该数组是1-base的，也就是说下标从1开始
class BIT
{
public:
	BIT(int size_);
	inline void Add(int position, int value);
	inline void Revise(int position, int newValue);//修改
	inline long long Sum(int position);
	inline long long Sum(int left, int right);
	inline int Visit(int position);//访问
	inline void Print();

private:
	inline int Lowbit(int x);

	std::vector<int> tree;//注意为了方便对应二进制表示，tree[0]不作使用
	int size;
	int n;//size <= 2^n
	int realsize;//2^n + 1
};

BIT::BIT(int size_)
{
	size = size_;//存储数据所用的空间
	n = log(size)/log(2) + 1;//内部实际数组的大小将取为2^n + 1
	realsize = pow(2, n) + 1;//内部数组的实际大小
	tree.resize(realsize, 0);
}

//增加A[position]的值
void BIT::Add(int position, int value)
{
	for (int i = position; i < realsize; i += Lowbit(i))
		tree[i] += value;
}

//修改A[position]的值
void BIT::Revise(int position, int newValue)
{
	int oldValue = Visit(position);
	int AddValue = newValue - oldValue;
	Add(position, AddValue);
}

//输出A[1~position]的和
long long BIT::Sum(int position)
{
	long long sum = 0;
	for (int i = position; i > 0; i -= Lowbit(i))
		sum += (long long)tree[i];
	return sum;
}

//输出A[left~right]的和
long long BIT::Sum(int left, int right)
{
	return Sum(right) - Sum(left - 1);
}

//访问A[position]的值
int BIT::Visit(int position)
{
	return (int)(Sum(position) - Sum(position - 1));
}

//获得二进制最低位一个1及其之后的0表示的值，如01001100得到00000100
int BIT::Lowbit(int x)
{
	return (x) & (-x);
}

void BIT::Print()
{
	for (int i = 1;i <= size;i++)
	{
		printf("%d ", Visit(i));
	}
	printf("\n");
}

int main()
{
	//test
	/*BIT bit(10);
	bit.Revise(2, 4);
	bit.Revise(5, 20);
	bit.Revise(10, 10);
	bit.Revise(10, -199);
	bit.Print();*/

	long long num = 0;
	int n;
	scanf("%d", &n);
	int* A = new int[n + 1];//A[0]不用
	for (int i = 1;i <= n;i++)
	{
		scanf("%d", &A[i]);
	}

	BIT B(n);//B初始全为0，遍历数组A，若A[i]=x,则将B[x] = 1
	for (int i = 1;i <= n;i++)
	{
		long long low = B.Sum(A[i] - 1);//排在A[i]之前，且比它小的元素个数
		long long high = n - A[i] - i + 1 + low;//排在A[i]之后，且比它大的元素个数
		num += low * high;//low * high为以A[i]为中心的升序三元组的数量
		B.Revise(A[i], 1);
	}
	printf("%lld", num);
}