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
	std::vector<Monster> positive;//总体效果为加血的怪(或者不加不减)
	std::vector<Monster> negative;//总体效果为减血的怪
	std::vector<int> order;//用于输出打怪的顺序
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
	//加血怪按照a从小往大排序
		std::sort(positive.begin(), positive.end(), [](Monster m1, Monster m2) {return m1.a < m2.a;});
	//减血怪按照b从大往小排序
		std::sort(negative.begin(), negative.end(), [](Monster m1, Monster m2) {return m1.b > m2.b;});
	//先打加血怪
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