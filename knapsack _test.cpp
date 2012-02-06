
/*
Practice 11
Solving the knapsack problem by the memory function algorithm; the weight and
value of those items are produce by rand or acquired from the keyboard.
  */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <cmath>
#include <ctime>
#include <cassert>

using namespace std;

/**
** 源文件： knapsack _test.cpp
** 功能说明：
** 测试程序，背包问题与记忆功能。算法详细介绍详见《算法分析与设计》8.4背包问题与记忆功能。
** 作者：junkun huang  e-mail：huangjunkun@gmail.com
** 创建日期：2008-11 /
*/

int**	calcValues = NULL;
int		*pWeight = NULL, *pValue = NULL;

int MFKnapsack(int i, int j)
{
    if (calcValues[i][j]<0)
    {
        int		value;
        if (j<pWeight[i])
            value = MFKnapsack(i-1, j);
        else
        {
            int		value1 = MFKnapsack(i-1, j);
            int		value2 = pValue[i] + MFKnapsack(i-1, j-pWeight[i]);
            value = max(value1, value2);

            calcValues[i][j] = value;
        }


    }
    return	calcValues[i][j];
}
void PrinrCalcValue(int** values, int m, int n)
{
	for (int i=0; i<m+1; i++)
	{
		cout << "	";
		for (int j=0; j<n+1; j++)
		{
			cout << " " << values[i][j];
		}
		cout << endl;
	}
}

int main()
{
    time_t t;
    srand((unsigned) time(&t));

    char c;
    do
    {
        system("cls");
        cout << "\n\n	对背包问题实现记忆功能方法演示：（如下）\n";
        cout << "	请输入物品数量M，背包承重量N ：";
        int		M, N;
        cin >> M >> N;
        pValue = new int [M+1];
        pWeight = new int [N+1];
		assert (pValue && pWeight);
        //随机初始化Value ，Weight
        for (int i=1; i<=M; i++)
        {
            pValue[i] = rand()%20+1;
            pWeight[i] = rand()%(N/2)+1 ;
        }
        cout << "\n	随机产生物品为：（如下） \n";
        for (int i=1; i<=M; i++)
        {
            cout << "	Value[" << i << "] = " << pValue[i]
                 << ",   Weight[" << i << "] = " << pWeight[i] <<endl;
        }
        //动态申请V[][]空间
		calcValues = new int*[M+1];
		assert (calcValues);
        for (int i=0; i<M+1; i++)
        {
            calcValues[i] = new int [N+1];
			assert (calcValues[i]);
        }
        //初始化V[][]
        for (int i=0; i<M+1; i++)
            for (int j=0; j<N+1; j++)
            {
                if (i==0||j==0)
                    calcValues[i][j] = 0;
                else
                    calcValues[i][j] = -1;
            }
        PrinrCalcValue(calcValues, M, N);

        MFKnapsack(M,N);
        PrinrCalcValue(calcValues, M, N);

		//释放V[][]空间
		for (int i=0; i<M+1; i++)
			delete[] calcValues[i];
		delete[] calcValues;
		delete[] pWeight;
		delete[] pValue;

        cout << "\n\n	!!!按任意键继续，Esc退出程序!!!" << endl;

    }
    while( (c=getch())!=27 );
    return 0;
}
