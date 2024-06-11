#include <iostream>
#include <vector>
#include <cstdio>

enum class Status
{
	Zero = 0,
	One = 1,
	Infinity = 2,
	Visited = 3
};

struct Edge
{
	int end;
	int weight;
};

struct Vertex
{
	Status status;
	int outdegree;//����
	std::vector<Edge> edges;

	Vertex();
};

Vertex::Vertex()
{
	outdegree = 0;
	status = Status::Infinity;
};

int main()
{
	int n, m, s;
	std::cin >> n >> m >> s;
	s--;//����s��0��ʼ
	std::vector<Vertex> vertices(n);
	vertices[s].status = Status::Zero;
	for (int i = 0;i < m;i++)
	{
		int u, v, w;
		int ret = scanf("%d%d%d", &u, &v, &w);
		u--;//��Ŀ����u��v�Ǵ�1��ʼ��
		v--;
		vertices[u].outdegree++;
		vertices[u].edges.push_back({ v, w });
	}
	
	std::vector<int> Zero;
	std::vector<int> One;
	std::vector<int> dis(n, -1);//��s�����е�ľ��룬-1��������
	std::vector<int> precursor(n, -1);//ǰ����-1����û��
	dis[s] = 0;
	Zero.push_back(s);
	while (!Zero.empty() || !One.empty())
	{
		if (!Zero.empty())
		{
			int u = Zero.back();
			Zero.pop_back();
			if (vertices[u].status == Status::Visited)
			{
				//�õ���ʧЧ��ֻ��δ��ʱɾ��
				continue;
			}
			if (precursor[u] != -1)
			{
				dis[u] = dis[precursor[u]];
			}
			vertices[u].status = Status::Visited;
			for (int i = 0;i < vertices[u].outdegree;i++)
			{
				int v = vertices[u].edges[i].end;
				int weight = vertices[u].edges[i].weight;
				if (weight == 0)
				{
					if (vertices[v].status == Status::One || vertices[v].status == Status::Infinity)
					{
						vertices[v].status = Status::Zero;
						Zero.push_back(v);
						precursor[v] = u;
					}
				}
				else//weight = 1
				{
					if (vertices[v].status == Status::Infinity)
					{
						vertices[v].status = Status::One;
						One.push_back(v);
						precursor[v] = u;
					}
				}
			}
		}
		else
		{
			int u = One.back();
			One.pop_back();
			if (vertices[u].status == Status::Zero || vertices[u].status == Status::Visited)
			{
				//�õ���ʧЧ��ֻ��δ��ʱɾ��
				continue;
			}
			if (precursor[u] != -1)
			{
				dis[u] = dis[precursor[u]] + 1;
			}
			vertices[u].status = Status::Visited;
			for (int i = 0;i < vertices[u].outdegree;i++)
			{
				int v = vertices[u].edges[i].end;
				int weight = vertices[u].edges[i].weight;
				if (weight == 0)
				{
					if (vertices[v].status == Status::One || vertices[v].status == Status::Infinity)
					{
						vertices[v].status = Status::Zero;
						Zero.push_back(v);
						precursor[v] = u;
					}
				}
				else//weight = 1
				{
					if (vertices[v].status == Status::Infinity)
					{
						vertices[v].status = Status::One;
						One.push_back(v);
						precursor[v] = u;
					}
				}
			}
		}
	}
	for (int i = 0;i < n;i++)
	{
		printf("%d ", dis[i]);
	}

}