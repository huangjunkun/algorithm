#ifndef PROJECT_EULER_H_INCLUDED
#define PROJECT_EULER_H_INCLUDED

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <cassert>

using namespace std;



unsigned long long problem_6(unsigned arg)
{
    unsigned long long sum1 = 0, sum2 = 0;
    for (size_t i = 1; i <= arg; ++i)
    {
        sum1 += i * i;
    }
//    for (size_t i = 1; i <= arg; ++i)
//    {
//        sum2 += i;
//    }
    sum2 = (arg * (arg+1)) >> 1;
    sum2 *= sum2;
    cout << "sum1=" << sum1 << ", sum2=" << sum2 << "\n";
    return std::abs(sum2 - sum1);
}
//  求两数的最大公约数
long long gcd1(long long m, long long n)
{
    assert (m>0 && n>0);
    if (m < n)
    {
        int tmp = m;
        m = n;
        n = tmp;
    }

    while (0 !=n)
    {
        int r = m % n;
        m = n;
        n = r;
    }
    return m;
}
// 求两数的最小公倍数
// 公式法： 最小公倍数 × 最大公约数 = 乘积
long long lcm(long long m, long long n)
{
    return (m*n/gcd1(m, n));
}

unsigned long long problem_5(unsigned arg)
{
    assert(arg > 2);
    vector<size_t> num;
    num.resize(arg);
    for (size_t i = 0; i < num.size(); ++i)
    {
        num[i] = i+1;
    }
    unsigned long long ret = lcm(num[0], num[1]);
    for (size_t i = 2; i < num.size(); ++i)
    {
        ret = lcm(ret, num[i]);
    }
    return ret;
}
bool is_palindromic_number(unsigned long value)
{
    char buffer[32];
    itoa(value, buffer, 10);
    string s(buffer);
    size_t i = 0, j = s.size()-1;
    while (j > i)
    {
        if (s[i] != s[j])
            break;
        ++i;
        --j;
    }
    return (i >= j);
}
unsigned long problem_4(unsigned arg)
{
    size_t i, min_i = arg/10;
    size_t j, min_j = arg/10;
    unsigned long ret = 0;
    for(i = arg; i > min_i; --i)
    {
        for (j = arg; j >= i; --j)
        {
            unsigned long value = i * j;
            if (ret >= value)
                break;
            if (is_palindromic_number(value))
            {
                ret = value;
            }
        }
    }
    cout << "" << i << " " << j << "\n";

    return ret;
}

unsigned problem_3(unsigned long long arg)
{
    unsigned ret = 0;
    //unsigned sqrt_value = sqrt(arg);
    for (size_t i = 2; i < sqrt(arg); ++i)
    {
        if (arg % i == 0)
        {
            if (i > ret)
                ret = i;
            arg = arg / i;
            i = 1;
        }
    }
    if (arg > ret)
        ret = arg;
    return ret;
}
unsigned long problem_2(unsigned arg)
{
    unsigned long sum = 0, ret = 0;
    unsigned long value1 = 1, value2 = 2;
    //sum = value1 + value2;
    unsigned long next = 0;
    while (next <= arg)
    {
        if (!(value2 & 1)) //value2 % 2 == 0
        {
            ret += value2;
        }
        next = value1 + value2;
        value1 = value2;
        value2 = next;
        //sum += next;
    }
    return ret;
}
unsigned long problem_1(unsigned arg)
{
    unsigned long ret = 0;
    for (size_t i = 1; i < arg; ++i)
    {
        if (i % 3 == 0 || i % 5 == 0)
            ret += i;
    }
    return ret;
}


/// test case ...
#define MY_DEFINE(structure, member) ((int) &((structure *)0)->member)

struct structA {
    int32_t var1;
};

struct structB {
    int32_t var1;
    int32_t var2;
    virtual void func() {}
};

struct structC : public structB {
    int32_t var3;
};

void test_MY_DEFINE()
{
    cout << MY_DEFINE(structA, var1) << ", " << MY_DEFINE(structB, var2) << ", " << MY_DEFINE(structC, var3)<<  "\n";
}

void find_difference_from_two_files()
{
/***
    ifstream fin_all("all.txt");
    ifstream fin_some("some.txt");
    set<string> set_some;
    string item;
    while (fin_some >> item)
    {
        if (item.empty())
        {
            continue;
        }
        set_some.insert(item);
        item.clear();

    }
    cout << "some.txt item count=" << set_some.size() << "\n";
    ofstream fout_diff("difference.txt");
    size_t all_count = 0, diff_count = 0;

    while (fin_all >> item)
    {
        if (set_some.find(item) == set_some.end()) {
            ++diff_count;
            fout_diff << item << "\n";
        }
        ++all_count;
        item.clear();
    }
    cout << "all.txt item count=" << all_count << "\n";
    cout << "difference.txt item count=" << diff_count << "\n";
    ***/
}
#endif // PROJECT_EULER_H_INCLUDED
