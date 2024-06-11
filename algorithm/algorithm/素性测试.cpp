
//#define INT128

#ifndef INT128

#include <iostream>
#include <random>

// 快速幂取模
long long powerMod(long long base, long long exponent, long long modulus)
{
    long long result = 1;
    base = base % modulus;

    while (exponent > 0)
    {
        if (exponent % 2 == 1)
        {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent = exponent / 2;
    }
    return result;
}

// Miller-Rabin素数测试
bool isPrimeMillerRabin(long long n, int iterations)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0)
        return false;

    // 将n-1分解为2^s * d
    long long s = 0;
    long long d = n - 1;
    while (d % 2 == 0)
    {
        d /= 2;
        s++;
    }

    // 执行Miller-Rabin测试
    std::random_device rd;
    std::mt19937_64 rng(rd());
    for (int i = 0; i < iterations; i++)
    {
        std::uniform_int_distribution<long long> dist(2, n - 2);
        long long a = dist(rng);
        long long x = powerMod(a, d, n);
        if (x == 1 || x == n - 1)
        {
            continue;
        }
        bool isPrime = false;
        for (long long r = 1; r < s; r++)
        {
            x = powerMod(x, 2, n);
            if (x == n - 1)
            {
                isPrime = true;
                break;
            }
        }
        if (!isPrime)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    long long n;
    int iterations = 10;
    long long last_n = -1;
    while (1)
    {
        std::cin >> n;
        if (n == last_n)
        {
            return 0;
        }
        if (isPrimeMillerRabin(n, iterations))
        {
            std::cout << "Y" << std::endl;
        }
        else
        {
            std::cout << "N" << std::endl;
        }
        last_n = n;
    }
    return 0;
}

#endif // !INT128

#ifdef INT128

#include <iostream>
#include <random>

// 快速幂取模
__int128 powerMod(__int128 base, __int128 exponent, __int128 modulus)
{
    __int128 result = 1;
    base = base % modulus;

    while (exponent > 0)
    {
        if (exponent % 2 == 1)
        {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent = exponent / 2;
    }
    return result;
}

// Miller-Rabin素数测试
bool isPrimeMillerRabin(__int128 n, int iterations)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0)
        return false;

    // 将n-1分解为2^s * d
    __int128 s = 0;
    __int128 d = n - 1;
    while (d % 2 == 0)
    {
        d /= 2;
        s++;
    }

    // 执行Miller-Rabin测试
    std::random_device rd;
    std::mt19937_64 rng(rd());
    for (int i = 0; i < iterations; i++)
    {
        std::uniform_int_distribution<long long> dist(2, n - 2);
        long long t = dist(rng);
        __int128 a = static_cast<__int128>(t);
        __int128 x = powerMod(a, d, n);
        if (x == 1 || x == n - 1)
        {
            continue;
        }
        bool isPrime = false;
        for (__int128 r = 1; r < s; r++)
        {
            x = powerMod(x, 2, n);
            if (x == n - 1)
            {
                isPrime = true;
                break;
            }
        }
        if (!isPrime)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int iterations = 10;
    __int128 n;
    long long t;
    long long last_t = -1;
    while (1)
    {
        std::cin >> t;
        n = static_cast<__int128>(t);
        if (t == last_t)
        {
            return 0;
        }
        last_t = t;


        if (isPrimeMillerRabin(n, iterations))
        {
            std::cout << "Y" << std::endl;
        }
        else
        {
            std::cout << "N" << std::endl;
        }
        
    }
    return 0;
}

#endif // INT128


