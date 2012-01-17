#ifndef CONVEX_HULL_H_INCLUDED
#define CONVEX_HULL_H_INCLUDED

#include <iostream>
#include <fstream>
#include <limits.h>
using namespace std;

struct TPoint
{
    int x, y;
    friend ostream& operator << (ostream& os, const TPoint& p);
    bool    operator < (const TPoint& p)const
    {
        if( x<p.x )
            return true;
        else if(x==p.x )
            if(y<p.y)
                return true;
        return false;
    }
};
struct GreaterPoint : binary_function<bool, TPoint, TPoint>
{
    bool operator () (const TPoint& p1, const TPoint& p2)const
    {
        if( p1.x>p2.x )
            return true;
        else if(p1.x==p2.x )
            if(p1.y>p2.y)
                return true;
        return false;
    }
};
ostream& operator << (ostream& os, const TPoint& p)
{
    os << "(" << p.x << ", " << p.y << ") \n";
    return os;
}
template <typename T>
struct TypeTrait
{
    typedef const T& ParamType;
};
template <typename T>
struct TypeTrait<T*>
{
    typedef const T&  ParamType;
};
//template <class PointType>
//void PrintPoint(typename TypeTrait<PointType>::ParamType p)
void PrintPoint(const TPoint& p)
{
    std::cout << p;
    return;
}
void PrintPointPtr(TPoint* p)
{
    std::cout << *p;
    return;
}
typedef pair<TPoint,TPoint> PointPair;
void PrintPointPair(const PointPair& p)
{
    const TPoint& p1 = p.first;
    const TPoint& p2 = p.second;
    std::cout << "(" << p1.x << ", " << p1.y << ")-"
              << "(" << p2.x << ", " << p2.y << ") \n";
}
int     CountPmax(const TPoint& p1, const TPoint& p2, const TPoint& p3)
{
    return (p1.x*p2.y + p3.x*p1.y + p2.x*p3.y - p3.x*p2.y - p2.x*p1.y - p1.x*p3.y);
}
typedef vector<TPoint*>  VecPointPtr;
typedef pair<TPoint*,TPoint*> PointPairPtr;

void CountUppack(const PointPairPtr& pp, const VecPointPtr& points, \
                    VecPointPtr& selPoints)
{
    if(points.empty())
        return;
    VecPointPtr points1, points2;
    TPoint*     pointMax;
    int         max = INT_MIN;
    for(int i=0; i<points.size(); i++)
    {
        int temp = CountPmax(*(pp.first), *(pp.second), *points[i]);
        if(temp>max)
        {
            max = temp;
            pointMax = points[i];
        }
    }
    selPoints.push_back(pointMax);
    for(int i=0; i<points.size(); i++)
    {
        if(CountPmax(*(pp.first), *pointMax, *points[i])>0)
            points1.push_back(points[i]);
        if(CountPmax(*pointMax, *(pp.second), *points[i])>0)
            points2.push_back(points[i]);
    }

    CountUppack(PointPairPtr(pp.first, pointMax), points1, selPoints);
    CountUppack(PointPairPtr(pointMax, pp.second), points2, selPoints);

}
void CountDownpack(const PointPairPtr& pp, const VecPointPtr& points, \
                      VecPointPtr& selPoints)
{
    if(points.empty())
        return;
    VecPointPtr points1, points2;
    TPoint*     pointMax;
    int         min = INT_MAX;
    for(int i=0; i<points.size(); i++)
    {
        int temp = CountPmax(*(pp.first), *(pp.second), *points[i]);
        if(temp<min)
        {
            min = temp;
            pointMax = points[i];
        }
    }
    selPoints.push_back(pointMax);
    for(int i=0; i<points.size(); i++)
    {
        if(CountPmax(*(pp.first), *pointMax, *points[i])<0)
            points1.push_back(points[i]);
        if(CountPmax(*pointMax, *(pp.second), *points[i])<0)
            points2.push_back(points[i]);
    }

    CountDownpack(PointPairPtr(pp.first, pointMax), points1, selPoints);
    CountDownpack(PointPairPtr(pointMax, pp.second), points2, selPoints);
}
#endif // CONVEX_HULL_H_INCLUDED
