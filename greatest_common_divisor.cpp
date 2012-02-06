
#include <iostream>
#include <vector>
#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cassert>
#include <limits.h>

using namespace std;


/**
** 源文件： greatest_common_divisor.cpp
** 功能说明：
** 测试程序，计算两个数的最小公约数，不同解法：
	a. 欧几里得算法 gcd1.
	b. 计算gcd(m, n)的连续整数检测算法gcd2.
	c. 中学里的计算方法gcd3, 相对最复杂的办法,但是有效的.
		1 找到m的所有质数prime1；
		2 找到n的所有质数prime2；
		3 从prime1和prime2中找出所有的公因数com_prime。
		注意：如果p是其中一个公因数，而且在prime1和prime2中分别出现Pm，Pn次
		那么应该将p重复min{Pm, Pn}次；
		4 将com_prime的所有质因数相乘，结果即m, n最大公约数。
		（gcd3解法O_o 够折腾的求解过程吧。）

** 作者：junkun huang  e-mail：huangjunkun@gmail.com
** 创建日期：2008-11 /
*/

int gcd1(int m, int n)
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


int gcd2(int m, int n)
{
    assert (m>0 && n>0);
    int min = (m > n ? n : m);

    for (; ; --min)
    {
        if (0 == m % min && 0 == n % min)
            break;
    }
    return min;
}


typedef	struct	prime_factor
{
    int 	digit;
    int 	num;
} prime_factor;

void sieve(int n, vector<int>& return_vec)
{
    vector<int>	int_vec;

    for (int i=2; i<=n; i++)
        int_vec.push_back(i);
    for (int i=2; i<=sqrt(double(n)); i++)
    {
        int j = i * i;
        while(j<=n)
        {
            int_vec[j-2] = 0;
            j += i;
        }
    }

    for (int i=0; i<int_vec.size(); i++)
    {
        if (int_vec[i]!=0)
            return_vec.push_back(int_vec[i]);
    }
}

void find_prime_factors(int n, vector<prime_factor>& prime_factor_vec)
{
    vector<int>		prime_vec;
    sieve(n, prime_vec);
    prime_factor	prime_factor_temp;
    bool	factor_exist_flag = false;

    for (int i=0; i<=n && n!=1; i++)
    {
        if ((n%prime_vec[i])==0)
        {
            int j=0;
            for (; j<prime_factor_vec.size(); j++)
            {
                if (prime_factor_vec[j].digit==prime_vec[i])
                {
                    factor_exist_flag = true;
                    break;
                }
            }
            if (factor_exist_flag==true)
                prime_factor_vec[j].num++;
            else
            {
                prime_factor_temp.digit = prime_vec[i];
                prime_factor_temp.num = 1;
                prime_factor_vec.push_back(prime_factor_temp);
            }

            n /= prime_vec[i];
            i--;//继续在改位置判断、、、抵消i++
        }
        factor_exist_flag = false;
    }
}

void find_commom_factors(int m, int n, vector<prime_factor>& common_factors_vec)
{
    vector<prime_factor>	m_factor_vec, n_factor_vec ;//, common_factors_vec
    prime_factor	common_factor;

    find_prime_factors(m, m_factor_vec);
    find_prime_factors(n, n_factor_vec);

    for (int i=0; i<m_factor_vec.size(); i++)
        for (int j=0; j<n_factor_vec.size(); j++)
        {
            if (m_factor_vec[i].digit==n_factor_vec[j].digit)
            {
                common_factor.digit = m_factor_vec[i].digit;
                common_factor.num =  m_factor_vec[i].num > n_factor_vec[j].num ?
                                     n_factor_vec[j].num : m_factor_vec[i].num;
                common_factors_vec.push_back(common_factor);
            }
        }
}

int gcd3(int m, int n)
{
    assert (m>0 && n>0);
    vector<prime_factor>	common_factors_vec;
    find_commom_factors(m, n, common_factors_vec);
    int 	ret = 1;
    for (int i=0; i<common_factors_vec.size(); i++)
        for (int j=0; j<common_factors_vec[i].num; j++)
        {
            ret *= common_factors_vec[i].digit;
        }

    return	ret;
}

int main()
{
    char c;
    do
    {
        int 	m, n;
        cout << "	请输入你要求其最大公约数的两个数（M，N）\n	M : ";
        cin	 >> m;
        cout << "	N : ";
        cin  >> n;

        cout << "	gcd1(m, n) 最大公约数为：" << gcd1(m, n) << endl;
        cout << "	gcd2(m, n) 最大公约数为：" << gcd2(m, n) << endl;
        cout << "	gcd3(m, n) 最大公约数为：" << gcd3(m, n) << endl;
        cout << "	!!!按任意键继续，Esc退出程序!!!" << endl;
    }
    while((c=getch())!=27);
    return 0;
}
