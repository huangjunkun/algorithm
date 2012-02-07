

#include <iostream>
#include <stack>
#include "queen_problem.h"
using namespace std;
class Board;

//---------------------------------------------------------------------------

/**
** 源文件： queen_problem.cpp, queen_problem.h
** 功能说明：
** N皇后问题的解法。应用回溯法求解。

** 作者：junkun huang  e-mail：huangjunkun@gmail.com
** 创建日期：2008-11 前 /
*/


/// 回溯法实现主要该算法

void solve_problem(int nQ)
{
    int is_print_on_screen = 0;//初始化运行模式标志：1 ，直接运行全部结果，0 ，任意键运行一种结果
    Board myBoard(nQ); //初始化数据
    //for (qRow = 0;qRow <(myBoard.N_Queen+1)/2;qRow++)//(N_Queen+1)/2代替N_Queen，由于矩阵的对称性，结果亦正确！！！
    //for (qCol = 0;qCol <(myBoard.N_Queen+1)/2;qCol++)//同时大大提高了程序效率！！！
    for (int row0 = 0; row0 < myBoard.nQueen; ++row0)
	{
		myBoard.initBoard();
        myBoard.placeQueen(row0, 0);
        stack<int>	rowStack;
        int row = 0, col = 1;
        do
        {
            while(row < myBoard.nQueen)  //超界
            {
                if (!(myBoard.isAttacked(row, col)))
                {
                    //若无皇后，条件成立
                    myBoard.placeQueen(row, col); //放皇后
                    rowStack.push(row); //入栈以保存该行的具体位置方便之后的继续查找
                    row = 0;
                    col++;
                    break;
                }
                else
                    row++;    // 到下一行
            }

            if (col == myBoard.nQueen)
            {
                myBoard.incrementSol(row0);
                myBoard.saveSolution();
                //为控制除Esc外的任意键继续至结束--应该放在if里面、、、
                if (is_print_on_screen != 1)
                {
                    myBoard.printSolution();
                    if (27 == getch())//Esc的ACSII码
                    {
                        is_print_on_screen = 1;
                        system("cls");
                        cout << "\n\n\n\n\n	求解！！！N 皇后问题过程中，请耐心等待！！！\n";
                        g_timer.set_begin();//开始计时
                    }
                }
                row = myBoard.nQueen;
            }

            if (row == myBoard.nQueen)
            {
                if (!rowStack.empty())
                {
                    row = rowStack.top();
                    rowStack.pop();//出栈以继续查找符合条件的下一组皇后
                }
                col--; //退回到前一列
                if (col == 0)
                    col--;
                else if (col > 0)
                    myBoard.removeQueen(row, col); //移去皇后

                row++;  //找下一个位置--逐行查找
            }
        }
        while (col >= 0);   //回到0列
    }

    g_timer.set_end();//截止计时

    // 屏幕输出与文件保存！
    myBoard.printResult();
    myBoard.saveResult();

}

//---------------------------------------------------------------------------
void hello()
{
    system("cls");
    char 	next;
    ifstream	in_stream;
    in_stream.open("hello.txt");
    if (in_stream.fail())
        return;
    cout << "\n";
    while(in_stream.get(next))
    {
        cout << next;
    }


    cout <<"\n	以任意键开始演示八皇后问题求解。\n"
         <<"说明：程序运行时，按任意键求解下一种解法，按直接Esc求出全部解法\n\n";
    system("pause");
}
//---------------------------------------------------------------------------
int main()
{
    system("color 02");//初始化窗体背景和字体颜色
    char c;
    do
    {
        system("cls");
        cout << "\n\n\n\n\n	！！！欢迎学习《演示 N 皇后问题求解》程序！！！\n";
        cout << "						--黄俊坤(only)\n\n	";
        system("pause");
        hello();
        int nQ;
        do
        {
            system("cls");
            cout << "\n\n	请输入你要演示 N 皇后问题求解的 N(<15) : ";
            string	str;
            cin >> str;
            nQ = atoi(str.c_str());
        }
        while(nQ >= 16 || nQ <=0);

        solve_problem(nQ);

        cout << "\n你是否继续执行操作，请按q(Q)或Esc即退出,其他任意键退回： ";
        c = getch();
    }
    while (c != 'q' && c != 'Q' && c != 27);

    return 0;
}
//---------------------------------------------------------------------------

