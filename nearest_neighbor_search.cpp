
#include <iostream>
#include <vector>
#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <limits.h>
#include <cmath>
using namespace std;

/**
** 源文件： nearest_neighbor_search.cpp
** 功能说明：
** 测试程序，最近点对问题解决方案，蛮力法与分治法。详见以下代码。
** 作者：junkun huang  e-mail：huangjunkun@gmail.com
** 创建日期：2008-11 /
*/

//---------------------------------------------------------------------------
//点结构
typedef	struct Pair
{
    int		x;
    int		y;
} Pair;

//最近点对结构
typedef	struct Closest_Pair
{
    Pair	pair_a, pair_b;
    double	distance;
} Closest_Pair;

//点对结构
typedef	struct Points
{
    Pair*	p_pair;
    int		pair_nums;//点对数目
} Points;

//---------------------------------------------------------------------------

Points			points;
Closest_Pair	closest_pair;
//int		pair_nums;

//---------------------------------------------------------------------------
double Account_Distance_2(const Pair& A, const Pair& B )
{

    return ( (A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y) );

}

//---------------------------------------------------------------------------
void Print_Points(ostream& outs, const Points&	points, const Closest_Pair&	closest_pair )
{
    outs << "\n\n	随机产生点对如下：\n";
    for(int i=0; i<points.pair_nums; ++i)
    {
        outs << "   (" << points.p_pair[i].x << ",  " << points.p_pair[i].y << " ) ";
        if((i+1)%5==0)
        {
            outs << endl;
        }
    }
    outs << "\n\n	由以上点对可得最近点对为： ( "
    << closest_pair.pair_a.x << ",  " << closest_pair.pair_a.y << " ), ( "
    << closest_pair.pair_b.x << ",  " << closest_pair.pair_b.y << " ) ";
    outs << "\n	该点对距离为：" << closest_pair.distance << endl;

}
//---------------------------------------------------------------------------

bool Brute_Force(const Points& points, Closest_Pair& closest_pair, int from, int to)
{


    for(int i=from; i<=to; ++i)
    {
        for(int j=i+1; j<=to; ++j)
        {
            double		next = Account_Distance_2(points.p_pair[i], points.p_pair[j]);//sqrt(  )
            if(closest_pair.distance > next )
            {
                closest_pair.pair_a = points.p_pair[i];
                closest_pair.pair_b = points.p_pair[j];
                closest_pair.distance = next;
            }
        }
    }

    return	true;
}
//---------------------------------------------------------------------------

// 对顺序表L作归并排序。

void Merge(char sign, Pair SR[], Pair TR[], long i, long m, long n)
{
    // 将有序的SR[i..m]和SR[m+1..n]归并为有序的TR[i..n]
    int j=m+1,k=i;
    for(; i<=m&&j<=n; ++k) // 将SR中记录由小到大地并入TR
    {

        if(sign=='x')
        {
            if ( SR[i].x < SR[j].x )
                TR[k]=SR[i++];
            else
                TR[k]=SR[j++];
        }
        else
        {
            if ( SR[i].y < SR[j].y )
                TR[k]=SR[i++];
            else
                TR[k]=SR[j++];
        }


    }
    if(i<=m)
    {
        for(int l=0; l<=m-i; l++)
        {
            TR[k+l]=SR[i+l]; // 将剩余的SR[i..m]复制到TR

        }
    }
    else  //if(j<=n)
    {
        for(int l=0; l<=n-j; l++)
        {
            TR[k+l]=SR[j+l]; // 将剩余的SR[j..n]复制到TR
        }
    }

}
//---------------------------------------------------------------------------

void MSort(char sign, Pair SR[], Pair TR1[], long s,  long t)
{
    // 将SR[s..t]归并排序为TR1[s..t].

    if(s==t)
    {
        TR1[s] = SR[s];
    }
    else
    {
//      int length = t-s+1;//
        Pair* TR2 = new Pair[points.pair_nums];
        long	m = (s+t)/2; // 将SR[s..t]平分为SR[s..m]和SR[m+1..t]
        MSort(sign, SR, TR2, s, m); // 递归地将SR[s..m]归并为有序的TR2[s..m]
        MSort(sign, SR, TR2, m+1, t); // 递归地将SR[m+1..t]归并为有序的TR2[m+1..t]
        Merge(sign, TR2, TR1, s, m, t); // 将TR2[s..m]和TR2[m+1..t]归并到TR1[s..t]

        delete[] TR2;
    }
}
//---------------------------------------------------------------------------

void Comp_CP(const Points& points, Closest_Pair& closest_pair, int	mid, int mid_value)
{
    int		i,  j;
    int		distance = sqrt( closest_pair.distance );

    i = mid;
    while( i >= 0 && points.p_pair[i].x >= (mid_value-distance) )
    {
        j = i + 1;
        for(; points.p_pair[j].x <= (mid_value+distance) && j < points.pair_nums; ++j)
        {
            if( points.p_pair[j].y > (points.p_pair[i].y+distance) ||
                    points.p_pair[j].y < (points.p_pair[i].y-distance) )
                //判断在y轴是否出界
                continue;

            double		next = Account_Distance_2( points.p_pair[i], points.p_pair[j]);//sqrt( )
            if(closest_pair.distance > next )
            {
                closest_pair.pair_a = points.p_pair[i];
                closest_pair.pair_b = points.p_pair[j];
                closest_pair.distance = next;

                //cout << "Comp_CP:	" << closest_pair.distance << endl;
            }

        }
        i--;
    }


}
//---------------------------------------------------------------------------

void Divide_and_Conquer(const Points& points, Closest_Pair& closest_pair, int from, int to)
{
    if( (to-from) <4 )
    {
        /*
        if( (to-from)==1 )
        {
        	double		next = Account_Distance_2( points.p_pair[from], points.p_pair[to]);//sqrt(  )
        	if(closest_pair.distance > next )
        	{
        		closest_pair.pair_a = points.p_pair[from];
        		closest_pair.pair_b = points.p_pair[to];
        		closest_pair.distance = next;
        	}
        	cout << "2	" << closest_pair.distance <<endl;

        }
        else		*/
        {
            Brute_Force(points, closest_pair, from, to );
            //cout << "<4	" << closest_pair.distance << endl;
            //system("pause");
        }

    }
    else
    {
        int		mid = (from+to)/2;
        int		mid_value = points.p_pair[mid].x;

        Divide_and_Conquer(points, closest_pair, from, mid);
        Divide_and_Conquer(points, closest_pair, mid+1, to);
        Comp_CP(points, closest_pair, mid, mid_value);
    }

    return	;
}
//---------------------------------------------------------------------------

int	main()
{
    time_t t;
    srand((unsigned) time(&t));

    char c;
    do
    {
        system("cls");

        cout << "\n\n	请输入你要随机产生点对的对数： ";
        cin >> points.pair_nums;
        if (points.pair_nums <= 0 || points.pair_nums > 1000)
        {
            cout << "输入有误，退出程序！\n";
            break;
        }

        points.p_pair = new Pair[points.pair_nums];

        for(int i=0; i<points.pair_nums; ++i)
        {
            points.p_pair[i].x= rand()%101;
            points.p_pair[i].y= rand()%101;
        }
        /// 分治法求解，先排序确保蛮力法与分治法求解的数据一致。
        MSort('x', points.p_pair, points.p_pair, 0, points.pair_nums-1 );

        //蛮力法求解
        cout << "\n\n--- 蛮力法求解 ---\n";
        closest_pair.distance = ULONG_MAX;//MAX_SIZE
        Brute_Force(points, closest_pair, 0, points.pair_nums );
        closest_pair.distance = sqrt( closest_pair.distance );
        Print_Points( cout,  points, closest_pair );

// 		/// 分治法求解，先排序
// 		MSort('x', points.p_pair, points.p_pair, 0, points.pair_nums-1 );

        //分治法求解
        cout << "\n\n--- 分治法求解 ---\n";
        closest_pair.distance = ULONG_MAX;//MAX_SIZE
        Divide_and_Conquer(points, closest_pair, 0, points.pair_nums );
        closest_pair.distance = sqrt( closest_pair.distance );
        Print_Points( cout,  points, closest_pair );
        delete[] points.p_pair;

        cout << "\n\n	!!!按任意键继续，Esc退出程序!!!" << endl;

    }
    while( (c=getch())!=27 );
    return 0;
}
//---------------------------------------------------------------------------

