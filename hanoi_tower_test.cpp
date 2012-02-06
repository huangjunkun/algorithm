
#include <iostream>
#include <cstdio>
#include <conio.h>
#include <cmath>
#include <cassert>

using namespace std;

/**
** 源文件： hanoi_tower_test.cpp
** 功能说明：
** 测试程序，汉若塔的计算（搬运次数）与演示搬运过程。
** 作者：junkun huang  e-mail：huangjunkun@gmail.com
** 创建日期：2008-11 /
*/

int loop_num = 0;

unsigned move(char x, int n, char z)
{
	cout << x << "->" << z <<"; "; 
	loop_num++;
	return 1;
}

unsigned hanoi(int n, char x, char y, char z)
{
	/// 因为该函数递归调用的频率会很高所有，若在函数内定义变量move_times那么就加大了，函数的递归代价；
	/// 若使用外面变量记录搬运次数，减轻递归负担，但降低耦合度。
	/// 需要程序设计者自行取舍。
	unsigned move_times = 0;
	if(n == 1)
		move_times += move(x, 1, z);
	else
	{
		move_times += hanoi(n-1, x, z, y);
		move_times += move(x, n, z);
		move_times += hanoi(n-1, y, x, z);
	}
	return move_times;
}

int main()
{
	char c;
	do
	{
		char x = 'A',y = 'B', z = 'C';
		loop_num = 0;
		int	hanoi_num;

		cout <<"	请输入汉诺塔上的盘子数目：";
		cin >> hanoi_num;

		hanoi(hanoi_num, x, y, z);	
		cout << "\n\n搬运次数：" << loop_num << endl;
		cout << "	!!!按任意键继续，Esc退出程序!!!" << endl;

	}while( (c=getch())!=27 );

	return 0;
}