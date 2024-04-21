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

std::vector<Point> points;//全局数组(

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

	//寻找中间条带的范围，设分界线为Mid所在位置
	//注意这里的l和r是中间带状区域的左右边界
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

	std::vector<int>* region = new std::vector<int>();//区间内所有点的index；以y升序排序；由子问题归并获得
	std::vector<int> band;//带状区域内所有点的index；以y升序排序；求region时顺便获得
	auto it1 = return_1.region->begin();
	auto it2 = return_2.region->begin();

	//归并获得region和band
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

	//合并
	long long min = d2;
	for (int i = 0;i < band.size();i++)
	{
		//对于band中每个点，检查上方0 <= delta_y < h范围内的点，这样可以保证每个点对最多被检查一次
		//(实际上是检查排序靠后的顶点，如果 == 0，不一定能检查到，但是该点对会被另一个点检查到)
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
	//令所有点对依照x进行升序排序，O(nlogn)
	std::sort(points.begin(), points.end(), [](Point p1, Point p2) {return p1.x < p2.x;});
	auto returnvalue = MinDistance(0, n - 1);
	long long min = returnvalue.d2;
	std::cout << min << std::endl;
}