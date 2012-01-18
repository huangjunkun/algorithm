
/*
Using Horner's Rule evaluating a polynomial p(x) at x = a;
 then compute the quotient and the remainder of the division of p(x) by x - a;(x-a !=0)
 the coefficients of the polynomial is produced by random;
*/
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
** 源文件： horner_rule.cpp
** 功能说明：
** 测试程序，霍纳法则用于计算多项式值的一种古老的算法，但却十分优雅和高效。
** 霍纳法则还有一些有用的副产品，例如有多项式P(x)，在计算P(a)的值过程产生的中间数字，
	可组织作为P(X)除以X-a商与余数。详见《算法分析与设计》6.5.1霍纳法则。
** 关于霍纳法则，详见http://baike.baidu.com/view/3060869.htm
** 作者：junkun huang  e-mail：huangjunkun@gmail.com
** 创建日期：2008-11 /
*/

typedef	unsigned int ParmaType;

ParmaType Horner(ParmaType H[], int n, ParmaType x, vector<ParmaType>& h_vec)
{
    ParmaType	result = H[n];
    for (int i=n-1; i>=0; i--)
    {
        h_vec.push_back(result);
        result = x * result + H[i];
    }
    return	result;
}

int main()
{
    time_t t;
    srand((unsigned) time(&t));
    char c;
    do
    {
        system("cls");
        cout << "\n\n\n	请输入多项式的最高幂：";
        int n;
        ParmaType P;
        cin >> n;
        ParmaType*	hData = new ParmaType[n+1];
        assert (hData);
        vector<ParmaType>	hVec;
        cout << "\n 随机产生的多项式P(x)为：";
        for (int i=n; i>=0; i--)
        {
            hData[i] = rand()%100;
            cout << hData[i] << "X^" << i;
            if (i!=0)
                cout  << " + ";
        }

        cout << "\n	请输入X=a的值：";
        int x;
        cin >> x;

        P = Horner(hData, n, x, hVec);

        cout << "	当X = " << x << " 时，多项式的值为：" << P << endl;
        cout << "\n 多项式P(x)除以X-a商：";
        for (int i=0; i<hVec.size(); i++)
        {
            cout << hVec[i] << "X^" << n-i-1;
            if (i!=n-1)
                cout  << " + ";
        }
        cout << "\n 多项式P(x)除以X-a余数：" << P;
        delete[] hData;
        cout << "\n\n	!!!按任意键继续，Esc退出程序!!!" << endl;

    }
    while( (c=getch())!=27 );

    return 0;
}
