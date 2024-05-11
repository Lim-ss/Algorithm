#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

int main()
{
	int n, m;
	std::cin >> n >> m;
	std::vector<long double> p(m + 1);//1-base
	std::vector<long double> Sum1(m + 1);//1-base��Sum1[i]����� i ~ m �ĵ����͸��ʵĻ��ĺ�
	std::vector<long double> Sum2(m + 1);//1-base��Sum2[i]����� 1 ~ i �ĸ��ʵĺ�
	std::vector<long double> E(n + 1);//1-base��E[i]�����������i�����ӵ����Ų�������
	for (int i = 1;i <= m;i++)
	{
		std::cin >> p[i];
	}
	Sum1[m] = m * p[m];
	Sum2[1] = p[1];

	for (int i = m - 1;i >= 1;i--)
		Sum1[i] = Sum1[i + 1] + i * p[i];
	for (int i = 2;i <= m;i++)
		Sum2[i] = Sum2[i - 1] + p[i];

	E[1] = Sum1[1];
	for (int i = 2;i <= n;i++)
	{
		int j = std::floor(E[i - 1]);//��ȡ��
		E[i] = Sum1[j + 1] + E[i - 1] * Sum2[j];
	}

	double result = std::round(E[n] * 10) / 10;
	std::cout << std::setprecision(1) << std::fixed << result << std::endl;
}