#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "../algorithm/convex_hull.h"

using namespace std;

int main()
{
    time_t t;
    srand(time(&t));
    const int POINTNUM = 100;
    const int SIDE = 20;

    TPoint  *points = new TPoint[POINTNUM];
    //vector<TPoint>  points(POINTNUM;
    for (int i=0; i<POINTNUM; i++)
    {
        points[i].x = rand()%SIDE;
        points[i].y = rand()%SIDE;
    }
    cout << "==========points   sourse======================\n";
    for_each(points, points+POINTNUM, PrintPoint);
    cout << "\n=======================================\n";
    cout << "==========points   sorted======================\n";
    sort(points, points+POINTNUM, less<TPoint>() );//GreaterPoint()
    for_each(points, points+POINTNUM, PrintPoint);
    cout << "\n=======================================\n";
    ///*
    vector<PointPair>  selPointPairs;
// --------------- 蛮力法 ------------
    for (int i=0; i<POINTNUM; i++)
        for (int j=i+1; j<POINTNUM; j++)
        {
            int a=points[j].y-points[i].y;
            int b=points[i].x-points[j].x;
            int c=points[i].x*points[j].y-points[i].y*points[j].x;
            // 标识points[k] 落在两点points[i], points[j] 哪一边.
            // 0 表示未知, 1 表示右边或同一条线上， -1 表示左边.
            int flag = 0;
            int k = 0;
            for (; k<POINTNUM; k++)
                if (k != i && k != j)
                {
                    // ... points[i] points[j] points[k] 存在相同点问题 ...

                    int temp = a*points[k].x+b*points[k].y-c;
#ifdef _DEBUG
                    if (temp==0)
                    {
                        cout << "temp==0 :\n" << points[i] << points[j] << points[k];
                    }
#endif
                    if (temp>=0&&flag>=0)// (flag==0||flag>0)
                    {
                        flag = 1;
                    }
                    else if (temp<0&& flag<=0)// (flag==0||flag<0)
                    {
                        flag = -1;
                    }
                    else
                        break;//error ...
                }
            if (POINTNUM == k)
                selPointPairs.push_back(PointPair(points[i], points[j]));
        }
    cout << "========selPointPairs  ==================\n";
    for_each(selPointPairs.begin(), selPointPairs.end(), PrintPointPair);
    cout << "\n=======================================\n";/*****/
// --------------- 分治法 ------------
    TPoint& p1 = points[0];
    TPoint& pn = points[POINTNUM-1];
    vector<TPoint*>  upPack, downPack;
    int     pmax=INT_MIN, pmin=INT_MAX;
    for (int i=1; i<POINTNUM-1; i++)
    {
        int temp = CountPmax(p1, pn, points[i]);
        if (temp>0)
        {
            upPack.push_back(&points[i]);
            if (temp>pmax)
                pmax=i;//temp
        }
        else
        {
            downPack.push_back(&points[i]);
            if (temp<pmin)
                pmin=i;
        }
    }
    cout << "========upPack  ==================\n";
    for_each(upPack.begin(), upPack.end(), PrintPointPtr);//PrintPointPtr
    cout << "\n=======================================\n";
    cout << "========downPack  ==================\n";
    for_each(downPack.begin(), downPack.end(), PrintPointPtr);//
    cout << "\n=======================================\n";
    cout << " pmax: " << pmax << "\n";
    cout << " pmin: " << pmin << "\n";
    VecPointPtr     selpoints;
    selpoints.push_back(&p1);
    selpoints.push_back(&pn);

    vector<TPoint*> vecPoints(POINTNUM);
    for (int i=0; i<vecPoints.size(); i++)
        vecPoints[i] = &points[i];
    //CountUppack(PointPairPtr(&points[0], &points[POINTNUM-1]), vecPoints, selpoints);//upPack
    //CountDownpack(PointPairPtr(&points[0], &points[POINTNUM-1]), vecPoints, selpoints);//downPack
    CountUppack(PointPairPtr(&points[0], &points[POINTNUM-1]), upPack, selpoints);//
    CountDownpack(PointPairPtr(&points[0], &points[POINTNUM-1]), downPack, selpoints);//
    cout << "========selpoints  ==================\n";
    for_each(selpoints.begin(), selpoints.end(), PrintPointPtr);//
    cout << "\n=======================================\n";
    cout << " selPointPairs.size(): " << selPointPairs.size()
         << ", selpoints.size(): " << selpoints.size() << "\n";
    delete[] points;
    /*=======================================*/
    cout << "Hello world!" << endl;
    return 0;
}
