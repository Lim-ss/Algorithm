#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>


int componentID = 0;
std::vector<int> component[10000];//�����10000��ǿ��ͨ����

struct Vertex
{
	bool output;
	int componentID;//��ͨ����id������������
	int outdegree;//����
	std::vector<int> adjacent;

	Vertex();
};

Vertex::Vertex()
{
	output = false;
	componentID = -1;
	outdegree = 0;
};

void Tarjan(int u, std::vector<Vertex>& vertices, std::vector<int>& dfn, std::vector<int>& low, std::vector<bool>& instack, std::stack<int>& stack, int& time)
{
	time++;
	dfn[u] = low[u] = time;
	stack.push(u);
	instack[u] = true;
	for (int i = 0;i < vertices[u].outdegree;i++)
	{
		int v = vertices[u].adjacent[i];
		if (dfn[v] == 0)
		{
			Tarjan(v, vertices, dfn, low, instack, stack, time);
			low[u] = std::min(low[u], low[v]);
		}
		else if (instack[v])
		{
			low[u] = std::min(low[u], dfn[v]);
		}
	}
	if (dfn[u] == low[u])
	{
		int v;
		do
		{
			v = stack.top();
			stack.pop();
			instack[v] = false;
			component[componentID].push_back(v);
			vertices[v].componentID = componentID;
		} 
		while (v != u);
		componentID++;
	}
}

int main()
{
	int n, m;
	std::cin >> n >> m;
	std::vector<int> dfn(n + 1, 0);//1-base����
	std::vector<int> low(n + 1, 0);//1-base����
	std::vector<bool> instack(n + 1, 0);//1-base����
	std::vector<Vertex> vertices(n + 1);//1-base����
	std::stack<int> stack;
	for (int i = 1;i <= m;++i)
	{
		int u, v;
		std::cin >> u >> v;
		vertices[u].outdegree++;
		vertices[u].adjacent.push_back(v);
	}
	int time = 0;
	Tarjan(1, vertices, dfn, low, instack, stack, time);

	printf("%d\n", componentID);
	for (int i = 1;i <= n;i++)
	{
		if (vertices[i].output == true)
		{
			continue;
		}
		int id = vertices[i].componentID;
		std::sort(component[id].begin(), component[id].end());
		for (int j = 0;j < component[id].size();j++)
		{
			vertices[component[id][j]].output = true;
			printf("%d ", component[id][j]);
		}
		printf("\n");
	}

	return 0;
}
