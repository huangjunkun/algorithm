#ifndef PROJECT_EULER_H_INCLUDED
#define PROJECT_EULER_H_INCLUDED

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <cassert>
#include <cstring>

using namespace std;

bool is_palindromic_number(unsigned long value);
long long gcd(long long m, long long n);
long long lcm(long long m, long long n);
bool is_prime_number(unsigned long long n);


unsigned long problem_11(unsigned arg)
{
    if (arg > 20)
    {
        return -1;
    }
    const unsigned grid_num[20][20] = {{8, 2, 22, 97, 38, 15, 0, 40, 0, 75, 4, 5, 7, 78, 52, 12, 50, 77, 91, 8}, \
{49, 49, 99, 40, 17, 81, 18, 57, 60, 87, 17, 40, 98, 43, 69, 48, 4, 56, 62, }, \
{81, 49, 31, 73, 55, 79, 14, 29, 93, 71, 40, 67, 53, 88, 30, 3, 49, 13, 36, 65}, \
{52, 70, 95, 23, 4, 60, 11, 42, 69, 24, 68, 56, 1, 32, 56, 71, 37, 2, 36, 91}, \
{22, 31, 16, 71, 51, 67, 63, 89, 41, 92, 36, 54, 22, 40, 40, 28, 66, 33, 13, 80}, \
{24, 47, 32, 60, 99, 3, 45, 2, 44, 75, 33, 53, 78, 36, 84, 20, 35, 17, 12, 50}, \
{32, 98, 81, 28, 64, 23, 67, 10, 26, 38, 40, 67, 59, 54, 70, 66, 18, 38, 64, 70}, \
{67, 26, 20, 68, 2, 62, 12, 20, 95, 63, 94, 39, 63, 8, 40, 91, 66, 49, 94, 21}, \
{24, 55, 58, 5, 66, 73, 99, 26, 97, 17, 78, 78, 96, 83, 14, 88, 34, 89, 63, 72}, \
{21, 36, 23, 9, 75, 0, 76, 44, 20, 45, 35, 14, 0, 61, 33, 97, 34, 31, 33, 95}, \
{78, 17, 53, 28, 22, 75, 31, 67, 15, 94, 3, 80, 4, 62, 16, 14, 9, 53, 56, 92}, \
{16, 39, 5, 42, 96, 35, 31, 47, 55, 58, 88, 24, 0, 17, 54, 24, 36, 29, 85, 57}, \
{86, 56, 0, 48, 35, 71, 89, 7, 5, 44, 44, 37, 44, 60, 21, 58, 51, 54, 17, 58}, \
{19, 80, 81, 68, 5, 94, 47, 69, 28, 73, 92, 13, 86, 52, 17, 77, 4, 89, 55, 40}, \
{4, 52, 8, 83, 97, 35, 99, 16, 7, 97, 57, 32, 16, 26, 26, 79, 33, 27, 98, 66}, \
{88, 36, 68, 87, 57, 62, 20, 72, 3, 46, 33, 67, 46, 55, 12, 32, 63, 93, 53, 69}, \
{4, 42, 16, 73, 38, 25, 39, 11, 24, 94, 72, 18, 8, 46, 29, 32, 40, 62, 76, 36}, \
{20, 69, 36, 41, 72, 30, 23, 88, 34, 62, 99, 69, 82, 67, 59, 85, 74, 4, 36, 16}, \
{20, 73, 35, 29, 78, 31, 90, 1, 74, 31, 49, 71, 48, 86, 81, 16, 23, 57, 5, 54}, \
{1, 70, 54, 71, 83, 51, 54, 69, 16, 92, 33, 48, 61, 43, 52, 1, 89, 19, 67, 48}};
    // left, right
    unsigned long max_product = 0;
    unsigned long product = 0;
    for (size_t i = 0; i < 20; ++i)
    {
        product = 0;
        for (size_t j = 0; j < 20 - arg; ++j)
        {
            size_t z;
            if (product == 0)
            {
                product = 1;
                z = 0;
            }
            else
            {
                z = arg-1;
            }
            for (; z < arg; ++z)
            {
                if (grid_num[i][j+z] == 0)
                {
                    // 遇到0，则直接停止计算，并且跳至0后面。
                    product = 0;
                    j += z;
                    break;
                }
                else
                {
                    product *= (grid_num[i][j+z]);
                }
            }
            if(product > max_product)
            {
                max_product = product;
            }
            if (product != 0)
            {
                product /= (grid_num[i][j]);
                /// 为下一次计算做准备，只需除去首元素再乘上（下一次计算的）末元素。
            }
        }
    }
    // up, down
    for (size_t i = 0; i < 20; ++i)
    {
        product = 0;
        for (size_t j = 0; j < 20 - arg; ++j)
        {
            size_t z;
            if (product == 0)
            {
                product = 1;
                z = 0;
            }
            else
            {
                z = arg-1;
            }
            for (; z < arg; ++z)
            {
                if (grid_num[j+z][i] == 0)
                {
                    // 遇到0，则直接停止计算，并且跳至0后面。
                    product = 0;
                    j += z;
                    break;
                }
                else
                {
                    product *= (grid_num[j+z][i]);
                }
            }
            if(product > max_product)
            {
                max_product = product;
            }
            if (product != 0)
            {
                product /= (grid_num[j][i]);
                /// 为下一次计算做准备，只需除去首元素再乘上（下一次计算的）末元素。
            }
        }
    }
    // 1. diagonally
   for (size_t i = (arg-1); i < 20; ++i)
    {
        product = 0;
        size_t dec_i = i;
        for (size_t j = 0; j <= (i-(arg-1)); ++j, --dec_i)
        {
            size_t z;
            if (product == 0)
            {
                product = 1;
                z = 0;
            }
            else
            {
                z = arg-1;
            }
            for (; z < arg; ++z)
            {
                if (grid_num[dec_i-z][j+z] == 0)
                {
                    // 遇到0，则直接停止计算，并且跳至0后面。
                    product = 0;
                    dec_i -= z;
                    j += z;
                    break;
                }
                else
                {
                    product *= (grid_num[dec_i-z][j+z]);
                }
            }
            if(product > max_product)
            {
                max_product = product;
            }
            if (product != 0)
            {
                product /= (grid_num[dec_i][j]);
                /// 为下一次计算做准备，只需除去首元素再乘上（下一次计算的）末元素。
            }
        }
    }
    // 2. diagonally
    for (size_t i = (arg-1); i < 20; ++i)
    {
        product = 0;
        size_t dec_i = i;
        for (size_t j = 0; j <= (i-(arg-1)); ++j, --dec_i)
        {
            size_t z;
            if (product == 0)
            {
                product = 1;
                z = 0;
            }
            else
            {
                z = arg-1;
            }
            for (; z < arg; ++z)
            {
                if (grid_num[j+z][dec_i-z] == 0)
                {
                    // 遇到0，则直接停止计算，并且跳至0后面。
                    product = 0;
                    dec_i -= z;
                    j += z;
                    break;
                }
                else
                {
                    product *= (grid_num[j+z][dec_i-z]);
                }
            }
            if(product > max_product)
            {
                max_product = product;
            }
            if (product != 0)
            {
                product /= (grid_num[j][dec_i]);
                /// 为下一次计算做准备，只需除去首元素再乘上（下一次计算的）末元素。
            }
        }
    }
    // 3. diagonally
    for (size_t i = 0; i < (20 - arg); ++i)
    {
        product = 0;
        size_t inc_i = i;
        for (size_t j = 0; j < (20-i-arg); ++j, ++inc_i)
        {
            size_t z;
            if (product == 0)
            {
                product = 1;
                z = 0;
            }
            else
            {
                z = arg-1;
            }
            for (; z < arg; ++z)
            {
                if (grid_num[inc_i+z][j+z] == 0)
                {
                    // 遇到0，则直接停止计算，并且跳至0后面。
                    product = 0;
                    inc_i += z;
                    j += z;
                    break;
                }
                else
                {
                    product *= (grid_num[inc_i+z][j+z]);
                }
            }
            if(product > max_product)
            {
                max_product = product;
            }
            if (product != 0)
            {
                product /= (grid_num[inc_i][j]);
                /// 为下一次计算做准备，只需除去首元素再乘上（下一次计算的）末元素。
            }
        }
    }
    // 4. diagonally
    for (size_t i = 0; i < (20 - arg); ++i)
    {
        product = 0;
        size_t inc_i = i;
        for (size_t j = 0; j < (20-i-arg); ++j, ++inc_i)
        {
            size_t z;
            if (product == 0)
            {
                product = 1;
                z = 0;
            }
            else
            {
                z = arg-1;
            }
            for (; z < arg; ++z)
            {
                if (grid_num[j+z][inc_i+z] == 0)
                {
                    // 遇到0，则直接停止计算，并且跳至0后面。
                    product = 0;
                    inc_i += z;
                    j += z;
                    break;
                }
                else
                {
                    product *= (grid_num[j+z][inc_i+z]);
                }
            }
            if(product > max_product)
            {
                max_product = product;
            }
            if (product != 0)
            {
                product /= (grid_num[j][inc_i]);
                /// 为下一次计算做准备，只需除去首元素再乘上（下一次计算的）末元素。
            }
        }
    }
    return max_product;
}
unsigned long long problem_10(unsigned arg)
{
    if (arg < 2)
        return 0;

    unsigned long long sum = 2;// 2 the first prime
    for (size_t i = 3; i < arg; i += 2)// 3 the secpnd prime
    {
        if (is_prime_number(i))
        {
            sum += i;
        }
    }
    return sum;
}

unsigned long problem_9(unsigned arg)
{
////Without programming:
////
////a= 2mn; b= m^2 -n^2; c= m^2 + n^2;
////a + b + c = 1000;
////
////2mn + (m^2 -n^2) + (m^2 + n^2) = 1000;
////2mn + 2m^2 = 1000;
////2m(m+n) = 1000;
////m(m+n) = 500;
////
////m>n;
////
////m= 20; n= 5;
////
////a= 200; b= 375; c= 425;
    assert(arg != 0);
    unsigned a = 1, b = 1, c = 1;
    unsigned max_a = arg / 3, max_b = 2* arg / 3, max_c = arg;
    for (a = 1; a < max_a; ++a)
    {
        for (b = a + 1; b < max_b; ++b)
        {
            for (; ; )
            {
                unsigned long value = a*a + b*b;
                c = sqrt(value);
                if (c*c == value && (a + b + c) == arg)
                {
                    cout << "relust a=" << a << ", b=" << b << ", c=" << c << "\n";
                    return (a * b * c);
                }
                else
                {
                    break;
                }
            }

        }
    }
    cout << "none result.\n";
    return 0;
}
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

    unsigned long long max_product = 0;
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
                // 遇到0，则直接停止计算，并且跳至0后面。
                product = 0;
                i += j;
                break;
            }
            else
            {
                product *= (str_1000_digit_num[i+j]-'0');
            }
        }
        if(product > max_product)
        {
            max_product = product;
        }
        if (product != 0)
        {
            product /= (str_1000_digit_num[i]-'0');
            /// 为下一次计算做准备，只需除去首元素再乘上（下一次计算的）末元素。
        }
    }
    return max_product;
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
long long gcd(long long m, long long n)
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
    return (m*n/gcd(m, n));
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
