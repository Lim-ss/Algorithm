#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <utility>

class BellmanFord
{
	struct Edge;
public:
	int numsV;//点数量
	int numsE;//边数量
	std::vector<int> distance;//新增虚拟顶点到其他所有顶点的距离
	std::vector<Edge> edges;

public:
	BellmanFord(int numsV, int numsE);
};

struct BellmanFord::Edge
{
	int start;
	int end;
	int weight;
};

BellmanFord::BellmanFord(int numsV, int numsE)
{
	this->numsV = numsV;
	this->numsE = numsE;
	distance.resize(numsV, 0);
	edges.resize(numsE);
}

class Floyd
{
public:
	int size;//邻接矩阵的大小
	std::vector<std::vector<int>> distance;//邻接矩阵

public:
	Floyd(int size);
};

Floyd::Floyd(int size)
{
	this->size = size;
	distance.resize(size);
	for (int i = 0;i < size;i++)
	{
		distance[i].resize(size, 1e9);
		distance[i][i] = 0;
	}
}

class Johnson
{
	struct Vertex;
	struct Edge;
public:
	int numsV;//点数量
	int numsE;//边数量
	std::vector<std::vector<int>> distance;//邻接矩阵，仅用于存储结果
	std::vector<Vertex> vertices;//广义邻接表

public:
	Johnson(int numsV, int numsE);
};

struct Johnson::Vertex
{
	int outdegree;//出度
	std::vector<Edge> edges;

	Vertex();
};

Johnson::Vertex::Vertex()
{
	outdegree = 0;
}

struct Johnson::Edge
{
	int start;
	int end;
	int weight;
	int reweight;
};

Johnson::Johnson(int numsV, int numsE)
{
	this->numsV = numsV;
	this->numsE = numsE;
	distance.resize(numsV);
	for (int i = 0;i < numsV;i++)
	{
		distance[i].resize(numsV, 1e9);
		distance[i][i] = 0;
	}
	vertices.resize(numsV);
}

int main()
{
	int n, m;
	std::cin >> n >> m;
	BellmanFord bellmanFord(n, m);

	if (n <= 800)
	{
		Floyd floyd(n);
		for (int i = 0;i < m;i++)
		{
			int u, v, w;
			int ret = scanf("%d%d%d", &u, &v, &w);
			u--;//题目给的u、v是从1开始的
			v--;
			bellmanFord.edges[i].start = u;
			bellmanFord.edges[i].end = v;
			bellmanFord.edges[i].weight = w;
			floyd.distance[u][v] = floyd.distance[u][v] > w ? w : floyd.distance[u][v];
		}

		//使用BellmanFord判断是否存在负环，为了避免图不连通导致的错误，应该使用一个新的虚拟顶点来计算到所有点的最小距离
		{
			auto& d = bellmanFord.distance;
			for (int i = 0;i < n - 1;i++)
			{
				for (int j = 0;j < m;j++)
				{
					auto& e = bellmanFord.edges[j];
					if (d[e.end] > d[e.start] + e.weight && d[e.start] != 1e9)
					{
						d[e.end] = d[e.start] + e.weight;
					}
				}
			}
			for (int j = 0;j < m;j++)
			{
				auto& e = bellmanFord.edges[j];
				if (d[e.end] > d[e.start] + e.weight && d[e.start] != 1e9)
				{
					//存在负环
					std::cout << -1;
					return 0;
				}
			}
		}

		//使用Floyd计算全源最短路
		{
			auto& d = floyd.distance;
			for (int k = 0;k < n;k++)
			{
				for (int i = 0;i < n;i++)
				{
					for (int j = 0;j < n;j++)
					{
						if (d[i][j] > d[i][k] + d[k][j] && d[i][k] != 1e9 && d[k][j] != 1e9)
						{
							d[i][j] = d[i][k] + d[k][j];
						}
					}
				}
			}
			//打印结果
			for (int i = 0;i < n;i++)
			{
				long long sum = 0;
				for (int j = 0;j < n;j++)
				{
					long long t = (long long)d[i][j];
					sum += (j + 1) * t;
				}
				printf("%lld\n", sum);
			}
			return 0;
		}
	}
	else
	{
		Johnson johnson(n, m);
		for (int i = 0;i < m;i++)
		{
			int u, v, w;
			int ret = scanf("%d%d%d", &u, &v, &w);
			u--;//题目给的u、v是从1开始的
			v--;
			bellmanFord.edges[i].start = u;
			bellmanFord.edges[i].end = v;
			bellmanFord.edges[i].weight = w;
			johnson.vertices[u].outdegree++;
			johnson.vertices[u].edges.push_back({ u, v, w, 0});//reweight暂时未知
			johnson.distance[u][v] = johnson.distance[u][v] > w ? w : johnson.distance[u][v];
		}

		//使用BellmanFord判断是否存在负环，为了避免图不连通导致的错误，应该使用一个新的虚拟顶点来计算到所有点的最小距离
		{
			auto& d = bellmanFord.distance;
			for (int i = 0;i < n - 1;i++)
			{
				for (int j = 0;j < m;j++)
				{
					auto& e = bellmanFord.edges[j];
					if (d[e.end] > d[e.start] + e.weight && d[e.start] != 1e9)
					{
						d[e.end] = d[e.start] + e.weight;
					}
				}
			}
			for (int j = 0;j < m;j++)
			{
				auto& e = bellmanFord.edges[j];
				if (d[e.end] > d[e.start] + e.weight && d[e.start] != 1e9)
				{
					//存在负环
					std::cout << -1;
					return 0;
				}
			}
		}

		//重新赋权值，为johnson算法做准备
		for (int u = 0;u < n;u++)
		{
			auto& vertex = johnson.vertices[u];
			for (int j = 0;j < vertex.outdegree;j++)
			{
				int v = vertex.edges[j].end;
				vertex.edges[j].reweight = vertex.edges[j].weight + bellmanFord.distance[u] - bellmanFord.distance[v];
			}
		}

		//使用Johnson算法计算全源最短路
		{
			for (int i = 0;i < n;i++)
			{
				auto cmp = [](const std::pair<int, int>& a, const std::pair<int, int>& b) {if (a.first == b.first) return a.second > b.second; else return a.first > b.first;};
				std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)> residue(cmp);//还未加入已扩展区域的剩余顶点的{距离、id}，初始为空集
				std::vector<int> visited(n, 0);//用于判断该顶点是否已经加入已扩展区域
				std::vector<int> dis(n, 1e9);//顶点到已扩展区域的最小距离（reweight之后）
				dis[i] = 0;
				std::vector<int> precursor(n, -1);//距离某顶点最近的已扩展区域内的点的id
				for (int j = 0;j < n;j++)
				{
					residue.push({ dis[j],j });
				}

				while (!residue.empty())
				{
					int u = residue.top().second;
					residue.pop();
					if (visited[u] == 0)
					{
						visited[u] = 1;
						if (precursor[u] != -1)
						{
							johnson.distance[i][u] = johnson.distance[i][precursor[u]] + johnson.distance[precursor[u]][u];
						}
						//否则u一定为i，自动满足distance == 0
					}
					else
					{
						continue;
					}
					auto vertex_u = johnson.vertices[u];
					for (int j = 0;j < vertex_u.outdegree;j++)
					{
						int v = vertex_u.edges[j].end;
						int reweight = vertex_u.edges[j].reweight;
						if (dis[v] > reweight)
						{
							dis[v] = reweight;
							precursor[v] = u;
							residue.push({ reweight,v });
						}
					}
				}
			}
			//打印结果
			for (int i = 0;i < n;i++)
			{
				long long sum = 0;
				for (int j = 0;j < n;j++)
				{
					long long t = (long long)johnson.distance[i][j];
					sum += (j + 1) * t;
				}
				printf("%lld\n", sum);
			}
			return 0;
		}
	}
	
}