#include <iostream>
#include <vector>
#include <string>

//// 计算前缀数组
//std::vector<int> computePrefixArray(const std::string& pattern) 
//{
//    int m = pattern.length();
//    std::vector<int> prefix(m, 0);
//    int k = 0;
//
//    for (int q = 1; q < m; ++q) 
//    {
//        while (k > 0 && pattern[k] != pattern[q]) 
//        {
//            k = prefix[k - 1];
//        }
//        if (pattern[k] == pattern[q]) 
//        {
//            k++;
//        }
//        prefix[q] = k;
//    }
//
//    return prefix;
//}

// 查找K模糊匹配的子串个数
int countKMatchingSubstrings(const std::string& s, const std::string& t, int k) 
{
    int n = s.length();
    int m = t.length();
    int count = 0;

    for (int i = 0; i <= n - m; ++i) 
    {
        int mismatchCount = 0;
        for (int j = 0; j < m; ++j) 
        {
            if (s[i + j] != t[j]) 
            {
                mismatchCount++;
                if (mismatchCount > k) 
                    break;
            }
        }
        if (mismatchCount <= k)
        {
            count++;
        }
    }
    return count;
}

int main() 
{
    int T;
    std::cin >> T;
    while (T--) 
    {
        int n, m, k;
        std::cin >> n >> m >> k;

        std::string s, t;
        std::cin >> s >> t;

        int result = countKMatchingSubstrings(s, t, k);
        std::cout << result << std::endl;
    }

    return 0;
}