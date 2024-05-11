#include <iostream>
#include <vector>
#include <algorithm>

struct Monster
{
	int a;
	int b;
	int id;
};

int main()
{
	int n;
	long long h;
	std::cin >> n >> h;
	std::vector<Monster> positive;//����Ч��Ϊ��Ѫ�Ĺ�(���߲��Ӳ���)
	std::vector<Monster> negative;//����Ч��Ϊ��Ѫ�Ĺ�
	std::vector<int> order;//���������ֵ�˳��
	for (int i = 0;i < n;i++)
	{
		Monster m;
		m.id = i + 1;
		std::cin >> m.a >> m.b;
		if (m.b >= m.a)
			positive.push_back(m);
		else
			negative.push_back(m);
	}
	//��Ѫ�ְ���a��С��������
		std::sort(positive.begin(), positive.end(), [](Monster m1, Monster m2) {return m1.a < m2.a;});
	//��Ѫ�ְ���b�Ӵ���С����
		std::sort(negative.begin(), negative.end(), [](Monster m1, Monster m2) {return m1.b > m2.b;});
	//�ȴ��Ѫ��
	for (int i = 0;i < positive.size();i++)
	{
		if (h <= positive[i].a)
		{
			std::cout << "-1";
			return 0;
		}
		h = h - positive[i].a + positive[i].b;
		order.push_back(positive[i].id);
	}
	for (int i = 0;i < negative.size();i++)
	{
		if (h <= negative[i].a)
		{
			std::cout << "-1";
			return 0;
		}
		h = h - negative[i].a + negative[i].b;
		order.push_back(negative[i].id);
	}
	for (int i = 0;i < order.size();i++)
	{
		std::cout << order[i] << " ";
	}
	return 0;
}