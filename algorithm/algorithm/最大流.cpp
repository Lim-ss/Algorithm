#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cstring>

long long capacity[500][500];
int parent[500];
long long max_capacity[500];
bool visited[500];

//�����������·��
bool BFS(int source, int sink, int n)
{
    memset(visited, 0, sizeof(visited));
    std::queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v = 1; v <= n; v++)
        {
            if (!visited[v] && capacity[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
                if (v == sink)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

//̰�ķ�һ��ÿ������̵�����·��
long long edmonds_karp(int n, int source, int sink)
{
    long long max_flow = 0;

    while (BFS(source, sink, n))
    {
        long long path_flow = std::numeric_limits<int>::max();
        for (int v = sink; v != source; v = parent[v])
        {
            int u = parent[v];
            path_flow = std::min(path_flow, capacity[u][v]);
        }

        for (int v = sink; v != source; v = parent[v])
        {
            int u = parent[v];
            capacity[u][v] -= path_flow;
            capacity[v][u] += path_flow;
        }
        max_flow += (long long)path_flow;
    }
    return max_flow;
}

//dijkstra�ĸİ棬ÿ����չ�����Ե�����������һ����
//�ҵ�����������������·����
bool dijkstra(int source, int sink, int n)
{
    memset(max_capacity, 0, sizeof(max_capacity));
    memset(visited, false, sizeof(visited));
    std::priority_queue<std::pair<long long, int>> pq;
    pq.push({ std::numeric_limits<long long>::max(), source });
    max_capacity[source] = std::numeric_limits<long long>::max();
    visited[source] = true;
    parent[source] = -1;

    while (!pq.empty()) 
    {
        long long flow = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        visited[u] = true;
        for (int v = 1; v <= n; v++)
        {
            if (visited[v] == false && std::min(flow, capacity[u][v]) > max_capacity[v])
            {
                max_capacity[v] = std::min(flow, capacity[u][v]);
                parent[v] = u;
                pq.push({ max_capacity[v], v });
            }
        }
    }
    return max_capacity[sink] > 0;
}

//̰�ķ�����ÿ������������·��
long long ford_fulkerson_max_capacity(int n, int source, int sink)
{
    long long max_flow = 0;
    while (dijkstra(source, sink, n))
    {
        //��parent�������ǰ�ҵ�������·��������
        long long path_flow = std::numeric_limits<int>::max();
        for (int v = sink; v != source; v = parent[v])
        {
            int u = parent[v];
            path_flow = std::min(path_flow, capacity[u][v]);
        }
        //�޸�parent���ϱߵ�����
        for (int v = sink; v != source; v = parent[v])
        {
            int u = parent[v];
            capacity[u][v] -= path_flow;
            capacity[v][u] += path_flow;
        }
        max_flow += path_flow;
    }

    return max_flow;
}

int main() {
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    if (n > 500)
    {
        return -1;
    }
    memset(capacity, 0, sizeof(capacity));
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        capacity[u][v] += w;
    }
    //std::cout << ford_fulkerson_max_capacity(n, s, t) << std::endl;
    std::cout << edmonds_karp(n, s, t) << std::endl;
    return 0;
}
