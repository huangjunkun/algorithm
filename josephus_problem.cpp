
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
** 源文件： josephus_problem.cpp
** 功能说明：
** 测试程序，模拟约瑟夫问题的演示。以下采用两种数据结构实现：
	1. 数组；2. 循环链表。
	整体上，循环链表要优于数组，但数组的实现可能较易于理解与编码。

** 作者：junkun huang  e-mail：huangjunkun@gmail.com
** 创建日期：2008-11 /
*/

// 数组模拟约瑟夫问题
typedef struct Kill_Man
{
    int*	men;
    int killed_men;
    int order_survivors;
    int cur_survivors;
    int every_kill;

    Kill_Man()
        : men(0) {}
    ~Kill_Man()
    {
        if (men)
            delete men;
    }
} Kill_Man;


// n 为总人数，k为第一个开始报数的人，m为出列者喊到的数。
void JosephusProblem1(int n, int m, int k)
{
    Kill_Man	kill_man;
    kill_man.order_survivors = 1;

    int man_num = n;
    int sign = k;
    int killed = 0;

    kill_man.every_kill = m;

    kill_man.men = new int [man_num];
    assert (kill_man.men);
    kill_man.killed_men = 0;
    kill_man.cur_survivors = man_num;
    //编号

    for (int i=0; i<man_num; i++)
    {
        kill_man.men[i] = i+1;//编号
    }
    do
    {
        int count = 0;
        //int kill;
        do
        {
            //
            sign = sign%man_num;
            if (kill_man.men[sign] != -1)
            {
                count++;
            }
            sign++;
        }
        while(count != kill_man.every_kill);

        //Kill man
        kill_man.men[sign-1] = -1;
        cout << ++killed << "	Kill man : "<< sign << endl;//编号

        kill_man.killed_men++;
        kill_man.cur_survivors--;

    }
    while(kill_man.order_survivors !=kill_man.cur_survivors);

    for (int i=0; i<man_num; i++)
    {
        if (kill_man.men[i] != -1 )
        {
            //编号
            cout << "	Survivors : "<< kill_man.men[i] << endl;
        }
    }
    cout << endl;
}


// 循环链表模拟约瑟夫问题
typedef struct LNode
{
    int data;
    struct LNode *link;
} LNode, *LinkList;

// n 为总人数，k为第一个开始报数的人，m为出列者喊到的数。
void JosephusProblem2(int n, int m, int k)
{
    assert (n >= k);
    LinkList p, r, curr;
    p = (LinkList) malloc(sizeof(LNode));
    p->data = 1;
    p->link = p;
    curr = p;
    for (int i=2; i<=n; i++)
    {
        LinkList t = (LinkList)malloc(sizeof(LNode));
        t->data = i;
        t->link = curr->link;
        curr->link = t;
        curr = t;
    }
    r = curr;
    while(k--)
        r=p, p=p->link;
    while(n--)
    {
        for (int s=m-1; s--; r=p, p=p->link)
            ;
        r->link = p->link;
        printf("%d->", p->data);
        free(p);
        p = r->link;
    }
}

int main()
{
    char c;
    do
    {
        system("cls");
        int all, mark;
        cout << "\n\n\n	Josephus problem 演示 ！\n"
             << "	请输入人数： ";
        cin >> all;
        cout << "	请输入，间隔 Kill Man 数： ";
        cin >> mark;
        cout << "#1 数组模拟约瑟夫问题：\n";
        JosephusProblem1(all, mark, 0);
        cout << "#2 循环链表模拟约瑟夫问题：\n";
        JosephusProblem2(all, mark, 0);
        cout << "\n\n	!!!按任意键继续，Esc退出程序!!!" << endl;

    }
    while( (c=getch())!=27 );
    return 0;
}
