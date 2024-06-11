#include <vector>
#include <iostream>
#include <tuple>
#include <iomanip> // ����setprecision������ͷ�ļ�

using db = long double;
// TODO: You need to set MAX_N properly
// n���20�����ϸ����������40��Լ���������40������Ŀ���Ż��������41��
const int MAX_N = 61;
const db EPS = 1e-8;

int var_n, cstr_n;
db eq[MAX_N][MAX_N], ans[MAX_N];
int id[MAX_N * 2];

std::vector<db> a;
std::vector<db> b;
std::vector<db> c;
std::vector<db> d;


void pivot(int r, int c)
{
    std::swap(id[r + var_n], id[c]);
    db tmp = -eq[r][c];
    eq[r][c] = -1;
    for (int i = 0; i <= var_n; ++i) eq[r][i] /= tmp;
    for (int i = 0; i <= cstr_n; ++i)
    {
        if (eq[i][c] == 0 || i == r) continue;
        tmp = eq[i][c];
        eq[i][c] = 0;
        for (int j = 0; j <= var_n; ++j) eq[i][j] += eq[r][j] * tmp;
    }
}
int initialize()
{
    for (int i = 1; i <= var_n; i++)
        id[i] = i;
    while (1)
    {
        int r = 0, c = 0;
        db tmp = -EPS;
        for (int i = 1; i <= cstr_n; ++i)
            if (eq[i][0] < tmp)
                tmp = eq[r = i][0];
        if (r == 0)
            return 1;//��������һ��ȫ�ǷǸ���������1
        for (int i = 1; i <= var_n; ++i)
        {
            if (eq[r][i] > EPS)
            {
                c = i;
                break;
            }
        }
        if (!c) return 0;
        pivot(r, c);
    }
}
int simplex()
{
    while (1)
    {
        int r = 0, c = 0;
        db tmp = EPS;
        for (int i = 1; i <= var_n; ++i)
            if (eq[0][i] > tmp)
            {
                c = i;
                break;
            }
        if (!c) return 1;
        tmp = 1e9;
        for (int i = 1; i <= cstr_n; ++i)
            if (eq[i][c] < -EPS && -eq[i][0] / eq[i][c] < tmp) r = i, tmp = -eq[i][0] / eq[i][c];
        if (!r) return 0;
        pivot(r, c);
    }
}


void build() {
    // TODO: You need to modify this part
    // - eq[0] stores the objective function
    // - eq[i] stores the i-th constraint, and eq[i][0] stores the right-hand side
    // Maximize: sum(eq[0][i] * x[i])
    // Subject to: sum(eq[i][j] * x[j]) <= eq[i][0]
    // the following is a sample to use this template

    // cin >> var_n >> cstr_n;
    // for (int i = 1; i <= var_n; ++i) cin >> eq[0][i];
    // for (int i = 1; i <= cstr_n; ++i) {
    //     for (int j = 1; j <= var_n; ++j) cin >> eq[i][j];
    //     cin >> eq[i][0];
    // }


    // ���¸����鶼��1-base�ģ��������������1��λ��0���ò���
    // eq�����ǰ1~n�д������y(x),n+1~2n�ж�Ӧ��������s(x),2n+1~3n��Ӧ��������t(x)

    int n, m;
    std::cin >> n >> m;
    var_n = 2*n;//ÿ����ʼ����y����һ����������t
    cstr_n = 2*n;

    //������ʾ��·ͨ�е�ͼ
    std::vector<std::vector<bool>> graph(n + 1, std::vector<bool>(n + 1, false)); 
    for (int i = 0; i < m; ++i)
    {
        int xx, yy; // ����yy��Ϊ�˱���Ϳ�������y�ظ�
        std::cin >> xx >> yy;
        graph[xx][yy] = true;
        graph[yy][xx] = true;
    }

    //��¼�����еķ�����Ϣ�����ǳ�����
    a.resize(n + 1);
    b.resize(n + 1);
    c.resize(n + 1);
    d.resize(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i] >> b[i] >> c[i] >> d[i];
    }

    // �����С���ַ����ʵ�Լ������ y(x)/(1+N(x)) >= d(x)
    for (int i = 1;i <= n;i++)
    {
        //�������x���ھ�����N(x)
        int N = 0;
        for (int j = 1;j <= n;j++)
        {
            if (graph[i][j] == true)
            {
                N++;
            }
        }
        db reciprocal = 1.0l / (N + 1);
        //������x�Ŀ�������y(x)���䵽�����ھӺ��Լ����Ӹ���ʹ���Ⱥŷ���
        for (int j = 1;j <= n;j++)
        {
            if (graph[i][j] == true)
            {
                eq[j][i] = -reciprocal;
            }
        }
        eq[i][i] = -reciprocal;
        eq[i][0] = -d[i];
    }

    //��Ӹ���Լ���� t(x) >= y(x) - c(x)
    for (int i = 1;i <= n;i++)
    {
        eq[n + i][i] = 1;
        eq[n + i][n + i] = -1;
        eq[n + i][0] = c[i];
    }

    //����Ŀ���Ż����� minimize{ ���{ a(x)*y(x) + [b(x)-a(x)]*t(x) } }
    //��maximize{ ���{ -a(x)*y(x) - [b(x)-a(x)]*t(x) } }
    for (int i = 1;i <= n;i++)
    {
        eq[0][i] = -a[i];
        eq[0][n + i] = -(b[i] - a[i]);
    }
    
}

/*
//test
void build()
{
    var_n = 2;
    cstr_n = 3;
    eq[0][1] = -1;
    eq[0][2] = 1;

    eq[1][0] = 0;
    eq[1][1] = 1;
    eq[1][2] = -1;

    eq[2][0] = 0;
    eq[2][1] = -1;
    eq[2][2] = 0;

    eq[3][0] = 1;
    eq[3][1] = -0.5;
    eq[3][2] = 1;

    var_n = 2;
    cstr_n = 3;
    eq[0][1] = 2;
    eq[0][2] = -1;

    eq[1][0] = -1;
    eq[1][1] = 1;
    eq[1][2] = -3;

    eq[2][0] = 9;
    eq[2][1] = 1;
    eq[2][2] = 2;

    eq[3][0] = -7;
    eq[3][1] = -3;
    eq[3][2] = -1;
}
*/

int main()
{
    build();
    for (int i = 1; i <= cstr_n; ++i)
        for (int j = 1; j <= var_n; ++j) eq[i][j] *= -1;

    int p1 = initialize();
    if (p1 == 0)
    {
        std::cout << "Infeasible" << std::endl;
        return 0;
    }
    int p2 = simplex();
    if (p2 == 0)
    {
        std::cout << "Unbounded" << std::endl;
        return 0;
    }
    std::cout << std::setprecision(9) << std::fixed;
    // TODO: You might need to modify this output part
    //std::cout << eq[0][0] << std::endl;

    for (int i = 1; i <= cstr_n; i++) ans[id[i + var_n]] = eq[i][0];
    for (int i = 1; i <= var_n; i++) std::cout << ans[i] << " ";
    std::cout << std::endl;

    //�ɵõ��Ķ��������С����
    db minCost = 0;
    for (int i = 1;i <= var_n / 2;i++)
    {
        if (ans[i] <= c[i])
        {
            minCost += ans[i] * a[i];
        }
        else
        {
            minCost += c[i] * a[i] + (ans[i] - c[i]) * b[i];
        }
    }

    std::cout << minCost << std::endl;

    return 0;
}