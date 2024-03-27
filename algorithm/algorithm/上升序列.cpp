#include<cstdio>
#include<vector>
#include<cmath>

//��״���飨Binary Index Tree, BIT��
//ע��:��������1-base�ģ�Ҳ����˵�±��1��ʼ
class BIT
{
public:
	BIT(int size_);
	inline void Add(int position, int value);
	inline void Revise(int position, int newValue);//�޸�
	inline long long Sum(int position);
	inline long long Sum(int left, int right);
	inline int Visit(int position);//����
	inline void Print();

private:
	inline int Lowbit(int x);

	std::vector<int> tree;//ע��Ϊ�˷����Ӧ�����Ʊ�ʾ��tree[0]����ʹ��
	int size;
	int n;//size <= 2^n
	int realsize;//2^n + 1
};

BIT::BIT(int size_)
{
	size = size_;//�洢�������õĿռ�
	n = log(size)/log(2) + 1;//�ڲ�ʵ������Ĵ�С��ȡΪ2^n + 1
	realsize = pow(2, n) + 1;//�ڲ������ʵ�ʴ�С
	tree.resize(realsize, 0);
}

//����A[position]��ֵ
void BIT::Add(int position, int value)
{
	for (int i = position; i < realsize; i += Lowbit(i))
		tree[i] += value;
}

//�޸�A[position]��ֵ
void BIT::Revise(int position, int newValue)
{
	int oldValue = Visit(position);
	int AddValue = newValue - oldValue;
	Add(position, AddValue);
}

//���A[1~position]�ĺ�
long long BIT::Sum(int position)
{
	long long sum = 0;
	for (int i = position; i > 0; i -= Lowbit(i))
		sum += (long long)tree[i];
	return sum;
}

//���A[left~right]�ĺ�
long long BIT::Sum(int left, int right)
{
	return Sum(right) - Sum(left - 1);
}

//����A[position]��ֵ
int BIT::Visit(int position)
{
	return (int)(Sum(position) - Sum(position - 1));
}

//��ö��������λһ��1����֮���0��ʾ��ֵ����01001100�õ�00000100
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
	int* A = new int[n + 1];//A[0]����
	for (int i = 1;i <= n;i++)
	{
		scanf("%d", &A[i]);
	}

	BIT B(n);//B��ʼȫΪ0����������A����A[i]=x,��B[x] = 1
	for (int i = 1;i <= n;i++)
	{
		long long low = B.Sum(A[i] - 1);//����A[i]֮ǰ���ұ���С��Ԫ�ظ���
		long long high = n - A[i] - i + 1 + low;//����A[i]֮���ұ������Ԫ�ظ���
		num += low * high;//low * highΪ��A[i]Ϊ���ĵ�������Ԫ�������
		B.Revise(A[i], 1);
	}
	printf("%lld", num);
}