#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

int componentID = 0;
std::vector<int> component[10000]; // 最多有 10000 个强连通分量

struct Vertex {
    int componentID; // 连通分量 id，用于最后输出
    int outdegree;   // 出度
    std::vector<int> adjacent;

    Vertex();
};

Vertex::Vertex() 
{
    componentID = -1;
    outdegree = 0;
}

void Tarjan(int u, std::vector<Vertex>& vertices, std::vector<int>& dfn, std::vector<int>& low, std::vector<bool>& instack, std::stack<int>& stack, int& time) {
    time++;
    dfn[u] = low[u] = time;
    stack.push(u);
    instack[u] = true;
    for (int i = 0; i < vertices[u].outdegree; i++) 
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
        } while (v != u);
        componentID++;
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> dfn(n + 1, 0);    // 1-base 数组
    std::vector<int> low(n + 1, 0);    // 1-base 数组
    std::vector<bool> instack(n + 1, 0); // 1-base 数组
    std::vector<Vertex> vertices(n + 1); // 1-base 数组
    std::stack<int> stack;

    for (int i = 0; i < m; ++i) 
    {
        int u, v;
        std::cin >> u >> v;
        vertices[u].outdegree++;
        vertices[u].adjacent.push_back(v);
    }

    int time = 0;
    for (int i = 1; i <= n; ++i) 
    {
        if (dfn[i] == 0) 
        {
            Tarjan(i, vertices, dfn, low, instack, stack, time);
        }
    }

    std::cout << componentID << std::endl;
    std::vector<bool> printed(n + 1, false); // 记录每个节点是否已经输出

    for (int i = 1; i <= n; ++i) 
    {
        if (!printed[i]) 
        {
            int id = vertices[i].componentID;
            std::sort(component[id].begin(), component[id].end());
            for (int j = 0; j < component[id].size(); ++j) 
            {
                printed[component[id][j]] = true;
                std::cout << component[id][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}