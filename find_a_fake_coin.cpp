
//---------------------------------------------------------------------------

#include  <iostream>
#include  <vector>
#include  <cstdio>
#include  <conio.h>
#include  <cstdlib>
#include  <ctime >
#include  <cmath >
#include  <cassert>
#include  <limits.h>

using namespace std;

/**
** 源文件： find_a_fake_coin.cpp
** 功能说明：
** 测试程序，假币问题：有若干金币【3-1000】，存有一假币，且不知假币较轻或较重，用一天枰找出其中的假币且知其轻重，
	要求比较次数越少越好。
** 以下程序以分治法，递归的形式求解包括，二分法，三分法和四分法。程序逻辑有一定相似性，但效率不一。整体上效率：
** 三分法 >= 四分法 >= 二分法
** 具体实现，详见源码与注释说明。

** 作者：junkun huang  e-mail：huangjunkun@gmail.com
** 创建日期：2008-11 前 /
*/

#define		WHICH_HEAVY_LEFT	-1
#define		WHICH_HEAVY_UNKNOWN	0
#define		WHICH_HEAVY_RIGHT	1

#define		FAKE_STATE_HEAVY	2
#define		FAKE_STATE_UNKNOWN	1
#define		FAKE_STATE_LIGHT	0

static int s_which_heavy = WHICH_HEAVY_UNKNOWN;//那一边比较重，初始化为0 ，即未确定
static int s_fake_state	= FAKE_STATE_UNKNOWN;//假币轻重标志,初始化为1 ，即未确定
static int s_fake_coin = -1; //初始化假币位置

/// 统计不同解法的递归次数
static size_t s_find_2_comp_count = 0;
static size_t s_find_3_comp_count = 0;
static size_t s_find_4_comp_count = 0;
void init()
{
    s_fake_coin = -1; //初始化假币位置
    s_fake_state = FAKE_STATE_UNKNOWN;//轻重标志,初始化为1 ，即未确定
    s_which_heavy = WHICH_HEAVY_UNKNOWN;//那一边比较重，初始化为0 ，即未确定

    s_find_2_comp_count = 0;
    s_find_3_comp_count = 0;
    s_find_4_comp_count = 0;

}
void print_find_result()
{
    cout <<  "	结果, 假币位置：" <<  s_fake_coin;
    if (s_fake_state == FAKE_STATE_LIGHT)
        cout <<  "	假币较轻！";
    else if (s_fake_state == FAKE_STATE_HEAVY)
        cout <<  "	假币较重！";
    else
        cout <<  "	无假币！";
    cout << "比较次数："<< s_find_2_comp_count+s_find_3_comp_count+s_find_4_comp_count << endl;
}
void uninit()
{
    print_find_result();
}

//二分法求解
int sum_coins(const int A[], int from, int to)
{
    int sum = 0;
    for (int i=from; i <=to; i++)
    {
        sum += 	A[i];
    }
    return	sum;
}
//---------------------------------------------------------------------------
bool calc_fake_coin(int A[], int c1, int c2)
{
    //在确定真币A[0]的前提下，剩下2个硬币或一个（c1==c2），检测假币的所在位置和轻重。
    if (c1 == c2)
    {
        if (A[0] != A[c1])
        {
            s_fake_coin = c1;
            s_fake_state = (A[0] < A[c1] ? FAKE_STATE_HEAVY : FAKE_STATE_LIGHT);
        }
        else
            return false;
    }
    if (A[0] == A[c1])
    {
        s_fake_coin = c2;
        if (s_fake_state == FAKE_STATE_UNKNOWN)
            s_fake_state = (A[0] < A[c2] ? FAKE_STATE_HEAVY : FAKE_STATE_LIGHT);

    }
    else
    {
        s_fake_coin = c1;
        if (s_fake_state == FAKE_STATE_UNKNOWN)
            s_fake_state = (A[0] < A[c1] ? FAKE_STATE_HEAVY : FAKE_STATE_LIGHT);

    }
    return true;
}

//---------------------------------------------------------------------------
bool find_a_fake_coin_2(const int A[], int from, int to)
{
    //    /*/*假币问题求解：二分法*/
    ++s_find_2_comp_count;
    if (to == from)
    {
        return calc_fake_coin(const_cast<int*>(A), from, to);
    }
    else
    {
        if ((to-from+1)%2 == 0)
        {
            int mid = (from+to)/2;
            if (sum_coins(A, from, mid) == sum_coins(A, mid+1, to))
                return	false;
            else
            {
                if (find_a_fake_coin_2(A, from, mid))
                    return	true;
                else
                    find_a_fake_coin_2(A, mid+1, to);
            }
        }
        else if (A[to] != A[0])
        {
            s_fake_coin = to;
            s_fake_state = A[to] > A[0] ? FAKE_STATE_HEAVY : FAKE_STATE_LIGHT;
            return	true;
        }
        else
        {
            to = to-1;
            int mid = (from+to)/2;
            if (sum_coins(A, from, mid) == sum_coins(A, mid+1, to))
                return	false;
            else
            {
                if (find_a_fake_coin_2(A, from, mid))
                    return	true;
                else
                    find_a_fake_coin_2(A, mid+1, to);
            }
        }
    }
    return	false;
}
//---------------------------------------------------------------------------
void find_a_fake_coin_3(int A[], int from, int to)
{
    ++s_find_3_comp_count;
//    /*假币问题求解：三分法*/
    if ((to-from+1) < 3)
    {
        //
        //确定真币的重量--币种
        if (from > 1)
            A[0] = A[1];
        else
            A[0] = A[to+1];
        calc_fake_coin(A, from, to);
    }
    else
    {
        int i = (to-from+1)/3;
        int mid1 = from+i-1;
        int mid2 = mid1+i;

        if (sum_coins(A, from, mid1) == sum_coins(A, mid1+1, mid2))
        {
            if (s_fake_state == FAKE_STATE_UNKNOWN)
            {
                //判断假币的轻重
                if (s_which_heavy == WHICH_HEAVY_LEFT)
                    s_fake_state = FAKE_STATE_LIGHT;
                if (s_which_heavy == WHICH_HEAVY_RIGHT)
                    s_fake_state = FAKE_STATE_HEAVY;
            }

            find_a_fake_coin_3(A, mid2+1, to);
        }
        else
        {
            if (s_fake_state == FAKE_STATE_UNKNOWN)
            {
                //记录轻重情况
                if (sum_coins(A, from, mid1) > sum_coins(A, mid1+1, mid2))
                    s_which_heavy = WHICH_HEAVY_LEFT;
                else
                    s_which_heavy = WHICH_HEAVY_RIGHT;
            }

            find_a_fake_coin_3(A, from, mid2);
        }
    }
}

//---------------------------------------------------------------------------
void find_a_fake_coin_4(int A[], int from, int to)
{
//    /*/*假币问题求解：四分法*/
    ++s_find_4_comp_count;
    if ((to-from+1) < 4)
    {
        find_a_fake_coin_3(A, from, to);
    }
    else
    {
        int i = (to-from+1)/4;
        int mid1 = from+i-1;
        int mid2 = mid1+i;
        if (sum_coins(A, from, mid1) == sum_coins(A, mid1+1, mid2))
        {
// 			/// 以下注释逻辑存在缺陷，仅适合于三分法。
// 			if (s_fake_state == FAKE_STATE_UNKNOWN)
// 			{	//判断假币的轻重
// 				if (s_which_heavy == WHICH_HEAVY_LEFT)
// 					s_fake_state = FAKE_STATE_LIGHT;
// 				if (s_which_heavy == WHICH_HEAVY_RIGHT)
// 					s_fake_state = FAKE_STATE_HEAVY;
// 			}
            find_a_fake_coin_4(A, mid2+1, to);
        }
        else
        {
// 			/// 以下注释逻辑存在缺陷，仅适合于三分法。
// 			if (s_fake_state == FAKE_STATE_UNKNOWN)
// 			{	//记录轻重情况
// 				if (sum_coins(A, from, mid1) > sum_coins(A, mid1+1, mid2))
// 					s_which_heavy = WHICH_HEAVY_LEFT;
// 				else
// 					s_which_heavy = WHICH_HEAVY_RIGHT;
// 			}
            find_a_fake_coin_4(A, from, mid2);
        }
    }
}

void print_coins(const int pCoins[], int count)
{
    cout <<  "[编号]轻重";
    for (int i=1; i <=count; ++i)
    {
        cout <<  " [" <<  i <<  "]" << pCoins[i];
    }
    cout <<  endl;
}

int main()
{
    time_t t;
    srand((unsigned) time(&t));
    char c;
    const unsigned MAX_COIN_COUNT = 1000;
    int pCoins[MAX_COIN_COUNT];
    do
    {
        system("cls");
        /// 至少需要有3个货币才有比较意义！
        cout <<  "\n\n	请输入货币总数【3-1000】： ";
        int coin_count = 100;
        cin >>  coin_count;
        if (coin_count <= MAX_COIN_COUNT && coin_count > 2)
        {

            int fake_s = rand()%2;//随机值:1 假币较重, 0 假币较轻.
            int fake_pos = (rand()%coin_count)+1;//随机值,假币出现的位置.
            // 测试样例 2 * 100
// 			for (int fake_s = 0; fake_s < 2; ++fake_s)
// 				for (int fake_pos = 1; fake_pos <= 100; ++fake_pos)
            {
                // 初始化pCoins[0]存放真币，作为判断标准！
                for (int i=0; i <=coin_count; ++i)
                    pCoins[i] = 1;

                if (fake_s == 0)
                    pCoins[fake_pos] = 0;
                else
                    pCoins[fake_pos] = 2;

                int pos2, pos3, pos4;
                int state2, state3, state4;
                print_coins(pCoins, coin_count);

                cout <<  "\n	二分法求解:\n";
                init();
                find_a_fake_coin_2(pCoins, 1, coin_count);
                uninit();
                pos2 = s_fake_coin;
                state2 = s_fake_state;

                cout <<  "\n	三分法求解:\n";
                init();
                find_a_fake_coin_3(pCoins, 1, coin_count);
                uninit();
                pos3 = s_fake_coin;
                state3 = s_fake_state;

                cout <<  "\n	四分法求解:\n";
                init();
                find_a_fake_coin_4(pCoins, 1, coin_count);
                uninit();
                pos4 = s_fake_coin;
                state4 = s_fake_state;
                cout << " pos:" << pos2 << " " << pos3 << " "  << pos4
                     << " state:" << state2 << " " << state3 << " " << state4 << "\n";

                /// 检测程序结果是否正确！
                if (!((pos2 == pos3 && pos3 == pos4) && (state2 == state3 && state3 == state4)))
                {
                    cout <<  " --- ERROR ---\n";
                    print_coins(pCoins, coin_count);
                }
            }

        }
        else
            cout <<  " 输入有误！";

        cout <<  "\n\n	!!!按任意键继续，Esc退出程序!!!" <<  endl;

    }
    while( (c=getch())!=27);

    return 0;
}
