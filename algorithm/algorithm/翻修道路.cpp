#include <vector>
#include <iostream>

class Edge
{
public:
	//无向边，虽然叫做start和end，实际上不区分
	int start;
	int end;
	int weight;
};

class Vertex
{
public:
	std::vector<int> adjacentEdges;
};

int DFS(int x, int y, std::vector<bool>& visited, std::vector<Vertex>& vertices, std::vector<Edge>& edges)
{
	int sum = 1;
	visited[x] = true;
	for (int& e : vertices[x].adjacentEdges)
	{
		int v = edges[e].start == x ? edges[e].end : edges[e].start;
		int w = edges[e].weight;
		if (w >= y && visited[v] == false)
		{
			sum += DFS(v, y, visited, vertices, edges);
		}
	}
	return sum;
}

int main()
{
	int n, m, q;
	std::cin >> n >> m >> q;
	std::vector<Vertex> vertices(n + 1);//1-base
	std::vector<Edge> edges(m + 1);//1-base
	std::vector<int> answers;//存储答案
	for (int i = 1;i <= m;i++)
	{
		int u, v, w;
		std::cin >> u >> v >> w;
		edges[i].start = u;
		edges[i].end = v;
		edges[i].weight = w;
		vertices[u].adjacentEdges.push_back(i);
		vertices[v].adjacentEdges.push_back(i);
	}

	for (int i = 1;i <= q;i++)
	{
		int decision;
		std::cin >> decision;
		if (decision == 1)
		{
			int p, k;
			std::cin >> p >> k;
			edges[p].weight = k;
		}
		else if (decision == 2)
		{
			int x, y;
			std::cin >> x >> y;
			std::vector<bool> visited(n, false);
			int sum = DFS(x, y, visited, vertices, edges);
			answers.push_back(sum);
		}
		else
		{
			return -1;
		}
	}

	for (int& num : answers)
	{
		std::cout << num << std::endl;
	}
}