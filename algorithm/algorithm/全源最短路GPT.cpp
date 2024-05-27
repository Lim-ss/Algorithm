#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <climits>

class BellmanFord
{
    struct Edge;
public:
    int numsV; // ������
    int numsE; // ������
    std::vector<int> distance; // �������ⶥ�㵽�������ж���ľ���
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
    distance.resize(numsV + 1, INT_MAX); // Ϊ���ⶥ����һ���ռ�
    edges.resize(numsE);
}

class Floyd
{
public:
    int size;//�ڽӾ���Ĵ�С
    std::vector<std::vector<int>> distance;//�ڽӾ���

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
    int numsV; // ������
    int numsE; // ������
    std::vector<std::vector<int>> distance; // �ڽӾ��󣬽����ڴ洢���
    std::vector<Vertex> vertices; // �����ڽӱ�

public:
    Johnson(int numsV, int numsE);
};

struct Johnson::Vertex
{
    int outdegree; // ����
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
    for (int i = 0; i < numsV; i++)
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

    if (n < 800)
    {
        Floyd floyd(n);
        for (int i = 0;i < m;i++)
        {
            int u, v, w;
            int ret = scanf("%d%d%d", &u, &v, &w);
            u--;//��Ŀ����u��v�Ǵ�1��ʼ��
            v--;
            bellmanFord.edges[i].start = u;
            bellmanFord.edges[i].end = v;
            bellmanFord.edges[i].weight = w;
            floyd.distance[u][v] = floyd.distance[u][v] > w ? w : floyd.distance[u][v];
        }
        // ʹ��Bellman-Ford�ж��Ƿ���ڸ���
        {
            auto& d = bellmanFord.distance;
            d[n] = 0; // ���ⶥ�㵽�Լ��ľ���Ϊ0
            for (int i = 0; i < n; i++)
            {
                bellmanFord.edges.push_back({ n, i, 0 }); // �����ⶥ�㵽�������ж���ı�
            }

            for (int i = 0; i < n; i++)
            {
                for (const auto& e : bellmanFord.edges)
                {
                    if (d[e.start] != INT_MAX && d[e.end] > d[e.start] + e.weight)
                    {
                        d[e.end] = d[e.start] + e.weight;
                    }
                }
            }
            // ����Ƿ���ڸ���
            for (const auto& e : bellmanFord.edges)
            {
                if (d[e.start] != INT_MAX && d[e.end] > d[e.start] + e.weight)
                {
                    // ���ڸ���
                    std::cout << -1;
                    return 0;
                }
            }
        }
        //ʹ��Floyd����ȫԴ���·
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
            //��ӡ���
            for (int i = 0;i < n;i++)
            {
                long long sum = 0;
                for (int j = 0;j < n;j++)
                {
                    sum += (j + 1) * (long long)d[i][j];
                }
                printf("%lld\n", sum);
            }
            return 0;
        }
    }
    else
    {
        Johnson johnson(n, m);
        for (int i = 0; i < m; i++)
        {
            int u, v, w;
            int ret = scanf("%d%d%d", &u, &v, &w);
            u--; // ��Ŀ����u��v�Ǵ�1��ʼ��
            v--;
            bellmanFord.edges[i] = { u, v, w };
            johnson.vertices[u].outdegree++;
            johnson.vertices[u].edges.push_back({ u, v, w, 0 }); // reweight��ʱδ֪
            johnson.distance[u][v] = std::min(johnson.distance[u][v], w);
        }

        // ʹ��Bellman-Ford�ж��Ƿ���ڸ���
        {
            auto& d = bellmanFord.distance;
            d[n] = 0; // ���ⶥ�㵽�Լ��ľ���Ϊ0
            for (int i = 0; i < n; i++)
            {
                bellmanFord.edges.push_back({ n, i, 0 }); // �����ⶥ�㵽�������ж���ı�
            }

            for (int i = 0; i < n; i++)
            {
                for (const auto& e : bellmanFord.edges)
                {
                    if (d[e.start] != INT_MAX && d[e.end] > d[e.start] + e.weight)
                    {
                        d[e.end] = d[e.start] + e.weight;
                    }
                }
            }
            // ����Ƿ���ڸ���
            for (const auto& e : bellmanFord.edges)
            {
                if (d[e.start] != INT_MAX && d[e.end] > d[e.start] + e.weight)
                {
                    // ���ڸ���
                    std::cout << -1;
                    return 0;
                }
            }
        }

        // ���¸�Ȩֵ��ΪJohnson�㷨��׼��
        for (int u = 0; u < n; u++)
        {
            auto& vertex = johnson.vertices[u];
            for (auto& edge : vertex.edges)
            {
                int v = edge.end;
                edge.reweight = edge.weight + bellmanFord.distance[u] - bellmanFord.distance[v];
            }
        }

        // ʹ��Johnson�㷨����ȫԴ���·
        {
            for (int i = 0; i < n; i++)
            {
                auto cmp = [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                    return a.first > b.first;
                    };
                std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(cmp)> pq(cmp);
                std::vector<int> dis(n, INT_MAX);
                dis[i] = 0;
                pq.push({ 0, i });

                while (!pq.empty())
                {
                    int u = pq.top().second;
                    int d_u = pq.top().first;
                    pq.pop();

                    if (d_u > dis[u]) continue;

                    for (const auto& edge : johnson.vertices[u].edges)
                    {
                        int v = edge.end;
                        int weight = edge.reweight;
                        if (dis[v] > dis[u] + weight)
                        {
                            dis[v] = dis[u] + weight;
                            pq.push({ dis[v], v });
                        }
                    }
                }

                for (int j = 0; j < n; j++)
                {
                    if (dis[j] != INT_MAX)
                        johnson.distance[i][j] = dis[j] + bellmanFord.distance[j] - bellmanFord.distance[i];
                }
            }

            // ��ӡ���
            for (int i = 0; i < n; i++)
            {
                long long sum = 0;
                for (int j = 0; j < n; j++)
                {
                    sum += (j + 1) * (long long)(johnson.distance[i][j] == INT_MAX ? 1000000000 : johnson.distance[i][j]);
                }
                printf("%lld\n", sum);
            }
        }
        return 0;
    }
}