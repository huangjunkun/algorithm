#ifndef PROJECT_EULER_H_INCLUDED
#define PROJECT_EULER_H_INCLUDED

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <cassert>
#include <cstring>

using namespace std;



unsigned long long problem_8_2(unsigned arg)
{
    const char str_1000_digit_num[1001] = "73167176531330624919225119674426574742355349194934\
96983520312774506326239578318016984801869478851843\
85861560789112949495459501737958331952853208805511\
12540698747158523863050715693290963295227443043557\
66896648950445244523161731856403098711121722383113\
62229893423380308135336276614282806444486645238749\
30358907296290491560440772390713810515859307960866\
70172427121883998797908792274921901699720888093776\
65727333001053367881220235421809751254540594752243\
52584907711670556013604839586446706324415722155397\
53697817977846174064955149290862569321978468622482\
83972241375657056057490261407972968652414535100474\
82166370484403199890008895243450658541227588666881\
16427171479924442928230863465674813919123162824586\
17866458359124566529476545682848912883142607690042\
24219022671055626321111109370544217506941658960408\
07198403850962455444362981230987879927244284909188\
84580156166097919133875499200524063689912560717606\
05886116467109405077541002256983155200055935729725\
71636269561882670428252483600823257530420752963450";
    assert(arg <= 1000 && arg != 0);
    if (arg > 1000 || arg == 0)
        return -1;

    unsigned long long ret = 0;
    unsigned long long product = 0;
    std::string MAX_STR;
    unsigned long long MAX_RET = 1;
    for (size_t i = 0; i < arg; ++i)
    {
        MAX_STR.push_back('9');
        MAX_RET *= 9;
    }

    for(size_t i = 0; i < (1000 - arg); ++i)
    {
        if (strncmp(str_1000_digit_num+i, MAX_STR.c_str(), arg) == 0)
            return MAX_RET;

        size_t j;
        if (product == 0)
        {
            product = 1;
            j = 0;
        }
        else
        {
            j = arg-1;
        }

        for(; j < arg; ++j)
        {
            if (str_1000_digit_num[i+j] == '0')
            {
                // 遇到0，则直接停止计算，并且i跳至0后面。
                product = 0;
                i += j;
                break;
            }
            else
            {
                product *= (str_1000_digit_num[i+j]-'0');
            }
        }
        if(product > ret)
        {
            ret = product;
        }
        if (product != 0)
        {
            product /= (str_1000_digit_num[i]-'0');
            /// 为下一次计算做准备，只需除去首元素再乘上（下一次计算的）末元素。
        }
    }
    return ret;
}


unsigned long long problem_8(unsigned arg)
{
    const char str_1000_digit_num[1001] = "73167176531330624919225119674426574742355349194934\
96983520312774506326239578318016984801869478851843\
85861560789112949495459501737958331952853208805511\
12540698747158523863050715693290963295227443043557\
66896648950445244523161731856403098711121722383113\
62229893423380308135336276614282806444486645238749\
30358907296290491560440772390713810515859307960866\
70172427121883998797908792274921901699720888093776\
65727333001053367881220235421809751254540594752243\
52584907711670556013604839586446706324415722155397\
53697817977846174064955149290862569321978468622482\
83972241375657056057490261407972968652414535100474\
82166370484403199890008895243450658541227588666881\
16427171479924442928230863465674813919123162824586\
17866458359124566529476545682848912883142607690042\
24219022671055626321111109370544217506941658960408\
07198403850962455444362981230987879927244284909188\
84580156166097919133875499200524063689912560717606\
05886116467109405077541002256983155200055935729725\
71636269561882670428252483600823257530420752963450";
    assert(arg <= 1000 && arg != 0);
    if (arg > 1000 || arg == 0)
        return -1;

    unsigned long long ret = 0;
    std::string MAX_STR;
    unsigned long long MAX_RET = 1;
    for (size_t i = 0; i < arg; ++i)
    {
        MAX_STR.push_back('9');
        MAX_RET *= 9;
    }

    for(size_t i = 0; i < (1000 - arg); ++i)
    {
        if (strncmp(str_1000_digit_num+i, MAX_STR.c_str(), arg) == 0)
            return MAX_RET;

        unsigned long long product = 1;
        for(size_t j = 0; j < arg; ++j)
        {
            if (str_1000_digit_num[i+j] == '0')
            {
                // 遇到0，则直接停止计算，并且i跳至0后面。
                product = 0;
                i += j;
                break;
            }
            else
            {
                product *= (str_1000_digit_num[i+j]-'0');
            }
        }
        if(product > ret)
        {
            ret = product;
        }
    }
    return ret;
}

bool is_prime_number(unsigned long long n)
{
    if (n > 13)
    {
        if(n%2 == 0 || n%3 == 0 || n%5 == 0)
            return false;

        unsigned long long bound = std::sqrt(n);
        for(size_t i = 7; i<=bound; i+=2)
            if(n%i == 0)
                return false;
        return true;
    }
    else
    {
        return (n==2 || n==3 || n==5 || n==7 || n==11 || n==13);
    }
}

unsigned long long problem_7(unsigned arg)
{
    unsigned long long ret;
    if (arg > 1000)
    { ///brute force method
        ret = 2; // the first prime number
        for (size_t i = 0; i < arg;)
        {
            if (is_prime_number(ret))
            {
                ++i;
                if (i == arg)
                    break;
            }
            ++ret;
        }
    }
    else
    {
        ret = 13; // the first prime number
        for (size_t i = 6; i < arg;)
        {
            if (is_prime_number(ret))
            {
                ++i;
                if (i == arg)
                    break;
            }
            ret += 2;
        }
    }
    return ret;
}

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
    unsigned sqrt_value = sqrt(arg);
    for (size_t i = 2; i < sqrt_value; ++i)
    {
        if (arg % i == 0)
        {
            if (i > ret)
                ret = i;
            arg = arg / i;
            sqrt_value = sqrt(arg);
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

struct structA
{
    int32_t var1;
};

struct structB
{
    int32_t var1;
    int32_t var2;
    virtual void func() {}
};

struct structC : public structB
{
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
