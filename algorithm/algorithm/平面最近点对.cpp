#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#include <cmath>

struct Point
{
	int x;
	int y;
};

struct ReturnValue
{
	std::vector<int>* region;
	long long d2;
};

std::vector<Point> points;//ȫ������(

static long long Distance2(Point a, Point b)
{
	return pow((a.x - b.x), 2) + pow((a.y - b.y), 2);
}

static ReturnValue MinDistance(int Left, int Right)
{
	if (Right == Left)
	{
		std::vector<int>* region = new std::vector<int>();
		region->push_back(Left);
		ReturnValue rt = { region, std::numeric_limits<long long>::max() };
		return rt;
	}

	int Mid = (Left + Right) / 2;
	auto return_1 = MinDistance(Left, Mid);
	auto return_2 = MinDistance(Mid + 1, Right);
	long long d2 = return_1.d2 < return_2.d2 ? return_1.d2 : return_2.d2;
	long long d = sqrt(d2) + 1;

	//Ѱ���м������ķ�Χ����ֽ���ΪMid����λ��
	//ע�������l��r���м��״��������ұ߽�
	int l = Mid;
	int r = Mid;
	while (l != Left)
	{
		if (points[l - 1].x > points[Mid].x - d)
			l--;
		else
			break;
	}
	while (r != Right)
	{
		if (points[r + 1].x < points[Mid].x + d)
			r++;
		else
			break;
	}

	std::vector<int>* region = new std::vector<int>();//���������е��index����y����������������鲢���
	std::vector<int> band;//��״���������е��index����y����������regionʱ˳����
	auto it1 = return_1.region->begin();
	auto it2 = return_2.region->begin();

	//�鲢���region��band
	while (it1 != return_1.region->end() && it2 != return_2.region->end())
	{
		if (points[*it1].y < points[*it2].y)
		{
			region->push_back(*it1);
			if (*it1 >= l && *it1 <= r)
				band.push_back(*it1);
			it1++;
		}
		else
		{
			region->push_back(*it2);
			if (*it2 >= l && *it2 <= r)
				band.push_back(*it2);
			it2++;
		}
	}
	while (it1 != return_1.region->end())
	{
		region->push_back(*it1);
		if (*it1 >= l && *it1 <= r)
			band.push_back(*it1);
		it1++;
	}
	while (it2 != return_2.region->end())
	{
		region->push_back(*it2);
		if (*it2 >= l && *it2 <= r)
			band.push_back(*it2);
		it2++;
	}
	delete return_1.region;
	delete return_2.region;

	//�ϲ�
	long long min = d2;
	for (int i = 0;i < band.size();i++)
	{
		//����band��ÿ���㣬����Ϸ�0 <= delta_y < h��Χ�ڵĵ㣬�������Ա�֤ÿ�������౻���һ��
		//(ʵ�����Ǽ�����򿿺�Ķ��㣬��� == 0����һ���ܼ�鵽�����Ǹõ�Իᱻ��һ�����鵽)
		for (int j = i + 1;j < band.size();j++)
		{
			if (points[band[j]].y - points[band[i]].y < d)
			{
				long long _d2 = Distance2(points[band[j]], points[band[i]]);
				min = _d2 < min ? _d2 : min;
			}
			else
			{
				break;
			}
		}
	}
	ReturnValue rt = { region, min };
	return rt;
}

int main()
{
	int n;
	std::cin >> n;
	for (int i = 1;i <= n;i++)
	{
		Point newPoint;
		std::cin >> newPoint.x >> newPoint.y;
		points.push_back(newPoint);
	}
	//�����е������x������������O(nlogn)
	std::sort(points.begin(), points.end(), [](Point p1, Point p2) {return p1.x < p2.x;});
	auto returnvalue = MinDistance(0, n - 1);
	long long min = returnvalue.d2;
	std::cout << min << std::endl;
}