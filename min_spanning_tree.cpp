
#include <iostream>
#include <vector>
#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <limits.h>

using namespace std;

/**
** 源文件： min_spanning_tree.cpp
** 功能说明：
** 测试程序，最小生成树问题CMST解决方案Prim算法与Kruskal算法。
** 作者：junkun huang  e-mail：huangjunkun@gmail.com
** 创建日期：2008-11 /
*/

// 定义用于Prim算法求解最小生成树结构体：
// flag， 标志对应的点是否加入最小生成树（点）集合
// A[i][j]，存放点i到点j的权重
// points，记录该最小生成树的点数
typedef	struct P_Chart
{
    bool	*flag;
    int		**A;
    int		points;
} P_Chart;

// 存放一条边的两个点
typedef	struct Point
{
    int		P1;
    int		P2;
} Point;
// /*定义用于Kruskal算法求解最小生成树结构体：
// value ，记录边的权重
// point，存放该边的两个点
//  */
typedef	struct K_Chart
{
    int		value;
    Point	point;
} K_Chart;
//存放点的集合--向量
typedef	vector<int> Int_Vec;
//存放点集的集合--（向量的）向量
typedef vector<Int_Vec>	Int_Vec_Vec;//

Int_Vec_Vec		int_vec_vec;
Int_Vec		    int_vec;

P_Chart		G,  E;
K_Chart		*K;
int		K_i = 0;
long	distance_P, distance_K;

void Print_P_Chart(const P_Chart& G, const K_Chart *K );


void Merge( K_Chart *K, K_Chart *TR,int i,int m,int n)
{
    // 将有序的K1[i..m]和K1[m+1..n]归并为有序的TR[i..n] 算法10.12
    int j,k,l;
    for (j=m+1,k=i; i <=m&&j<=n; ++k) // 将K1中记录由小到大地并入TR
    {
        if ( K[i].value < K[j].value )
            TR[k]=K[i++];
        else
            TR[k]=K[j++];

    }
    if (i <=m)
        for (l=0; l<=m-i; l++)
        {
            TR[k+l]=K[i+l]; // 将剩余的K1[i..m]复制到TR

        }
    if (j<=n)
        for (l=0; l<=n-j; l++)
        {
            TR[k+l]=K[j+l]; // 将剩余的K1[j..n]复制到TR

        }
}

void MSort( K_Chart *K1, K_Chart *K2, int s, int t)
{
    // 将K1[s..t]归并排序为K2[s..t]。
    int m;
    K_Chart *TR2 = new K_Chart[K_i+1];//
    //K_Chart TR2[101];
    if (s==t)
        K2[s]=K1[s];
    else
    {
        m=(s+t)/2; // 将K1[s..t]平分为K1[s..m]和K1[m+1..t]
        MSort(K1,TR2,s,m); // 递归地将K1[s..m]归并为有序的TR2[s..m]
        MSort(K1,TR2,m+1,t); // 递归地将K1[m+1..t]归并为有序的TR2[m+1..t]
        Merge(TR2,K2,s,m,t); // 将TR2[s..m]和TR2[m+1..t]归并到K2[s..t]
    }
    delete[] TR2;//
}
/// 构造最小生成树的Prim算法
///	输入：加权连通图 G
///	输出：E ，组成 G 的最小生成树的边的集合
void Prim( P_Chart& G, P_Chart& E )
{
    //初始化最小生成树顶点集合
    G.flag[0] = true;

    for (int i=0; i < G.points-1; i++)
    {
        int		P1, P2;
        int		min = INT_MAX;

        for (int j=1; j< G.points; j++)
        {
            if (G.flag[j]==false )
            {
                for (int k=0; k< G.points; k++)
                    if (  G.flag[k]==true )//G.flag[j]==false &&
                    {
                        if ( G.A[j][k] < min )
                        {
                            min = G.A[j][k];
                            P1 = j;
                            P2 = k;
                        }
                    }
            }
        }
        G.flag[P1] = true;
        distance_P += E.A[P1][P2] = E.A[P2][P1] = min;

    }

}
//Point	Find_i( int point )
int		Find_i( int point )
{
    //查找点point 在哪一个点集集合int_vec_vec的哪一个点集，
    //查找成功返回该点集位置，否则返回-1
    for (int i=0; i < int_vec_vec.size(); i++)
        for (int j=0; j< int_vec_vec[i].size(); j++)
        {
            if ( point==int_vec_vec[i][j] )
            {
                //position = i;
                return	i;
            }
        }
    return -1;
}
void Print_Vec()
{
    //输出所有点集int_vec_vec
    for (int i=0; i < int_vec_vec.size(); i++)
    {
        for (int j=0; j< int_vec_vec[i].size(); j++)
        {
            cout << int_vec_vec[i][j] <<"  " ;
        }
        cout << endl;
    }

}

void Kruskal( K_Chart *K, P_Chart& E )
{
    /*构造最小生成树的Kruskal算法
    输入：加权连通图 K
    输出：E ，组成 G 的最小生成树的边的集合 */
    for (int i=0; i < E.points; i++)
    {
        E.flag[i] = false;
        for (int j=i; j< E.points; j++)
        {
            E.A[j][i] = E.A[i][j] = INT_MAX;
        }
    }
    MSort( K, K, 0, K_i-1);

    int		k = 0,  counter = 0;
    int		P1;
    int		P2;
    do
    {
        P1 = K[k].point.P1;
        P2 = K[k].point.P2;

        if ( E.flag[P1]==false && E.flag[P2]==false)
        {
            E.flag[P1] = true;
            E.flag[P2] = true;

            int_vec.clear();
            int_vec.push_back(P1);
            int_vec.push_back(P2);
            int_vec_vec.push_back(int_vec);

            counter++;
            distance_K += E.A[P1][P2] = E.A[P2][P1] = K[k].value;
            //continue;
        }
        else
        {
            if ( E.flag[P1 ]==false || E.flag[P2]==false)
            {
                int		i;

                if ( E.flag[P1]==false )
                {
                    E.flag[P1] = true;
                    //
                    i  = Find_i(P2);
                    int_vec_vec[i].push_back(P1);
                }
                else//if ( E.flag[P2]==false )
                {
                    E.flag[P2] = true;
                    //
                    i  = Find_i(P1);
                    int_vec_vec[i].push_back(P2);
                }
                distance_K += E.A[P1][P2] = E.A[P2][P1] = K[k].value;
                counter++;
            }

            else//if ( E.flag[P1 ]==true && E.flag[P2]==true)
            {
                int		P1_i = Find_i(P1);
                int		P2_i = Find_i(P2);
                if (P1_i != P2_i )
                {
                    if (int_vec_vec[P1_i].size() > int_vec_vec[P2_i].size() )
                    {
                        for (int i=0; i < int_vec_vec[P2_i].size(); i++)
                        {
                            int_vec_vec[P1_i].push_back( int_vec_vec[P2_i][i] );
                        }
                        int_vec_vec.erase(int_vec_vec.begin()+P2_i);//删除点集
                    }
                    else
                    {
                        for (int i=0; i < int_vec_vec[P1_i].size(); i++)
                        {
                            int_vec_vec[P2_i].push_back( int_vec_vec[P1_i][i] );
                        }
                        int_vec_vec.erase(int_vec_vec.begin()+P1_i);//删除点集
                    }

                    distance_K += E.A[P1][P2] = E.A[P2][P1] = K[k].value;
                    counter++;
                }
            }
        }
        k++;
    }
    while( counter < E.points-1 );

    return;
}
//为G，E ，K申请空间，且初始化、、、
void Init_P_Chart(int points)
{
    //为G，E ，K申请空间
    G.A = new int*[points];
    E.A = new int*[points];
    G.flag = new bool[points];
    E.flag = new bool[points];
    K = new K_Chart [points*(points-1)/2];

    E.points = G.points = points;

    for (int i=0; i < points; i++)
    {
        G.A[i] = new int [points];
        E.A[i] = new int [points];
        G.flag[i] = E.flag[i] = false;
    }
    //	//为 G, E , K初始化、、、
    K_i = 0;

    for (int i=0; i < points; i++)
        for (int j=i; j< points; j++)
        {
            E.A[j][i] = E.A[i][j] = INT_MAX;
            if ( i==j )
            {
                G.A[j][i] = G.A[i][j] = 0;
                //continue;
            }/**/
            else
            {
                K[K_i].value = G.A[j][i] = G.A[i][j] = rand()%20+1;
                K[K_i].point.P1 = i;
                K[K_i++].point.P2 = j;
            }

        }

}
//释放图的空间G ，E ，K
void Delete_Chart(int points)
{
    for (int i=0; i < points; i++)
    {
        delete[] G.A[i];
        delete[] E.A[i];

    }
    delete[] K;
    delete[] G.A;
    delete[] E.A;

}
//输出图P, 图K
void Print_P_Chart(const P_Chart& G, const K_Chart *K )
{
    cout << "\n\n";
    for (int i=0; i < G.points; i++)
    {
        cout << "	";
        for (int j=0; j< G.points; j++)
        {
            if (G.A[i][j]==INT_MAX)
                cout << "∞" <<"  ";
            else
                cout << G.A[i][j] <<"  ";
        }
        cout << endl;
    }
    /*
    for (i=0; i < K_i; i++)
    {
    	cout << "	"<< K[i].point.P1 << " -- " << K[i].point.P2 << " :  " <<K[i].value << endl;
    }
    */
}

int main()
{
    time_t		t;
    srand((unsigned) time(&t));

    char c;
    do
    {
        //清空初始化
        int_vec_vec.clear();
        distance_P = 0;
        distance_K = 0;
        int		points;
        do
        {
            system("cls");
            cout << "\n\n\n	请输入生成树的点数( > 0 ) ：";
            cin >> points;
        }
        while( points <=0 );
        //为G，E 申请空间，且初始化、、、
        Init_P_Chart( points);
        Print_P_Chart( G, K );


        Prim( G, E );//
        cout << "\n	以上生成树由Prim算法求得最小生成树为（如下）： ";//
        Print_P_Chart( E,  K );//
        cout << "	以上最小生成树路径长度： " <<  distance_P << endl;//

        Kruskal( K, E );
        cout << "\n	以上生成树由Kruskal算法求得最小生成树为（如下）： ";//
        Print_P_Chart( E,  K  );
        cout << "	以上最小生成树路径长度： " <<  distance_K << endl;//

        Delete_Chart(points);
        cout << "\n\n	!!!按任意键继续，Esc退出程序!!!" << endl;

    }
    while((c=getch())!=27 );
    return 0;
}

