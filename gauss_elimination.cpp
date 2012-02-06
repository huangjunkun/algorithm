/***
Solve a system of n linear equations in n unknows using Gaussian elimination; assume that the coefficient matrix is not singular( if the coefficient matrix is produced by random,  you may verify singular );
Hints to the solution :
Step1: Gaussian elimination; page207, BetterGaussElimination
Step2: Backward substitution;
Backward substitution algorithm
for j ← n downto 1 do
      t ← 0
      for k ← j +1 to n do
            t ← t + A[j, k] * x[k]
      x[j] ← (A[j, n+1] - t) / A[j, j]

  */

/**
** 源文件： gauss_elimination.cpp
** 功能说明：
** 测试程序，用高斯消去法求解方程组，详见《算法分析与设计》6.2高斯消去法。
** 用到方程组的初等变换：
	1. 交换方程组中两个方程的位置；
	2. 把一个方程替换为它的非零倍；
	3. 把一个方程替换为它和另一个方程倍数之间的和或差。
** 作者：junkun huang  e-mail：huangjunkun@gmail.com
** 创建日期：2008-11 /
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

// 用部分选主元法实现高斯消去法。
// 输入：矩阵A[1...n, 1...n], B[1...n]。
// 输出：一个代替A的上三角形等价矩阵图，相应的右边的值位于第n+1列中。
void BetterGaussElimination( double **A, double B[], int n )
{
    for (int i=1; i<=n; i++)
    {
        A[i][n+1] = B[i];
    }
    for (int i=1; i<=n-1; i++)
    {
        //逐个消元
        int pivotrow = i;
        for (int j=i+1; j<=n; j++)
        {
            //保证系数不为0，取元素绝对值最大值
            if ( fabs(A[j][i]) > fabs(A[pivotrow][i]) )
                pivotrow = j;
        }
        if (pivotrow != i)
        {
            for (int k=i; k<=n+1; k++)
            {
                //只交换非0元素 A[][k]
                double	temp;
                temp = A[i][k];
                A[i][k] = A[pivotrow][k];
                A[pivotrow][k] = temp;
            }
        }
        for (int j=i+1; j<=n; j++)
        {
            //逐行消元
            double	temp = A[j][i]/A[i][i];//比例因子
            for (int k=i; k<=n+1; k++)
            {
                //单列消元
                A[j][k] = A[j][k]-A[i][k]*temp;
            }
        }
    }
}
void BackwardSubstitution(double **A, double *C, int n)
{
    /*
    for j ← n downto 1 do
         t ← 0
         for k ← j +1 to n do
               t ← t + A[j, k] * x[k]
         x[j] ← (A[j, n+1] - t) / A[j, j]		*/
    for (int i=n; i>=1; i--)
    {
        double	t = 0;
        for (int j=i+1; j<=n; j++)
        {
            t = t + A[i][j]*C[j];
        }
        C[i] = (A[i][n+1] - t) / A[i][i];
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

        double	**A,  *B;
        cout << "\n\n\n	请输入多元方程式的组数: ";
        int n;
        cin >> n;

        A = new double*[n+1];//行
        assert (A);
        for (int i=0; i <n+1; i++)
        {
            //列
            A[i] = new double[n+2];
            assert (A[i]);
        }
        B = new double[n+1];//
        assert (B);

        for (int i=1; i <n+1; i++)
        {
            for (int j=1; j<n+1; j++)
            {
                A[i][j] = rand()%20+1;
            }
            B[i] = rand()%100+1;
        }
        for (int i=1; i <n+1; i++)
        {
            for (int j=1; j<n+1; j++)
            {
                cout << A[i][j] << "	";
            }
            cout << B[i];
            cout << endl;
        }

        BetterGaussElimination(A, B, n );

        cout <<"\n\n	上三角等价矩阵（如下）：\n";
        for (int i=1; i <n+1; i++)
        {
            int j=1;
            for (; j<n+2; j++)
            {
                cout << A[i][j] << "	";
            }
            B[i] = A[i][j-1];//B[]存储各方程式右边的值
            //cout << B[i];
            cout << endl;
        }
        //求解方程组A[][]--存放系数--的解，结果存放B[]
        BackwardSubstitution(A, B, n);
        /*	*/
        cout <<"\n\n	以上方程组的解为（如下）：\n";
        for (int i=1; i <n+1; i++)
        {
            cout << "	X"<< i  <<" = " << B[i];
            cout << endl;
        }

        delete[] B;
        for (int i=0; i <n+1; i++)
            delete[] A[i];
        delete[] A;
        cout << "\n\n	!!!按任意键继续，Esc退出程序!!!" << endl;

    }
    while( (c=getch())!=27 );
    return 0;

    /*	*/
}

