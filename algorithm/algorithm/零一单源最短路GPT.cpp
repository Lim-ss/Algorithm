#include <iostream>
#include <vector>
#include <deque>
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
    int outdegree;
    std::vector<Edge> edges;

    Vertex();
};

Vertex::Vertex()
{
    outdegree = 0;
    status = Status::Infinity;
}

int main()
{
    int n, m, s;
    std::cin >> n >> m >> s;
    s--; // ���� s �� 0 ��ʼ
    std::vector<Vertex> vertices(n);
    vertices[s].status = Status::Zero;

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        std::scanf("%d%d%d", &u, &v, &w);
        u--; // ��Ŀ���� u��v �Ǵ� 1 ��ʼ��
        v--;
        vertices[u].outdegree++;
        vertices[u].edges.push_back({ v, w });
    }

    std::deque<int> dq;
    std::vector<int> dis(n, -1); // �� s �����е�ľ��룬-1 ��������
    dis[s] = 0;
    dq.push_back(s);

    while (!dq.empty())
    {
        int u = dq.front();
        dq.pop_front();

        if (vertices[u].status == Status::Visited)
        {
            continue; // �õ���ʧЧ��ֻ��δ��ʱɾ��
        }

        vertices[u].status = Status::Visited;

        for (const auto& edge : vertices[u].edges)
        {
            int v = edge.end;
            int weight = edge.weight;

            if (weight == 0)
            {
                if (vertices[v].status == Status::One || vertices[v].status == Status::Infinity)
                {
                    vertices[v].status = Status::Zero;
                    if (dis[v] == -1 || dis[v] > dis[u])
                    {
                        dis[v] = dis[u];
                    }
                    dq.push_front(v);
                }
            }
            else // weight == 1
            {
                if (vertices[v].status == Status::Infinity)
                {
                    vertices[v].status = Status::One;
                    if (dis[v] == -1 || dis[v] > dis[u] + 1)
                    {
                        dis[v] = dis[u] + 1;
                    }
                    dq.push_back(v);
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        std::printf("%d ", dis[i]);
    }

    return 0;
}

