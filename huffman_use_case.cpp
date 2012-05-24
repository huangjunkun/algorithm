#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <exception>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <limits.h>

using namespace std;

namespace test_namespace
{

/// 来自Google groups论坛讨论，转：http://groups.google.com/group/pongba/t/bf95272e7543d0aa
/// 把一块长度为L的木棒切成N块，每段的大小必须为a1,a2,…,an，每一次切木棒的代价为当前木棒的长度，
/// 完成切割任务的最小代价？
////Input
////首先输入T，有T个测试用例
////每个测试用例输入两行
////第一行整数L和N。接下来一行是N个数表示每一段的木棒长度。
////Output
////求完成任务的最小代价
////Sample Input
////2
////10 4
////1 2 3 4
////306 8
////120 37 42 42 32 2 7 24
////Sample Output
////19
////785

/// 反过来想每次合并是两段长度之和。于是就变成了Huffman问题了。
/// 解释一下样例一，10分割为4和6，代价为10，6分割为3和3，代价为6，3分割为1和2，代价为3。
/// 总代价为10+6+3，即Huffman树中非叶节点的 权值和。


struct test_case
{
    unsigned wood_all_len;
    unsigned part_count;
    unsigned* part_len_ptr;

    test_case()
    : wood_all_len(0), part_count(0), part_len_ptr(0)
    {
    }
    test_case(const test_case& obj)
    {
        wood_all_len = obj.wood_all_len;
        if (part_count < obj.part_count)
        {
            if (part_len_ptr)
                delete[] part_len_ptr;
            assert (obj.part_count);
            part_len_ptr = new unsigned[obj.part_count];
            memcpy(part_len_ptr, obj.part_len_ptr, sizeof(unsigned) * obj.part_count);
        }
        else
        {
            memcpy(part_len_ptr, obj.part_len_ptr, sizeof(unsigned) * obj.part_count);
        }


        part_count = obj.part_count;
    }
    ~test_case()
    {
        if (part_len_ptr)
            delete part_len_ptr;
    }
};

unsigned calc_min_cost(const test_case& a_case)
{ /// 有问题解法。当出现有3以上元素相同时，该解法存在问题。
    unsigned cost = 0;
    unsigned all_len = a_case.wood_all_len;

    if (a_case.part_count > 2)
    {
        for (size_t i = 0; i < a_case.part_count-1; ++i)
        {
            if (a_case.part_len_ptr[i] != a_case.part_len_ptr[i+1])
            {
                cost += all_len;
                all_len -= a_case.part_len_ptr[i];
            }
            else
            { /// case ==
                cost += all_len;
                all_len -= 2 * a_case.part_len_ptr[i];

                cost += 2 * a_case.part_len_ptr[i];
                ++i; /// pass elements[i+1]
            }
        }
        all_len -= a_case.part_len_ptr[a_case.part_count-1];
    }
    else
    {
        cost = a_case.wood_all_len;
        all_len -= a_case.wood_all_len;
    }
    assert (0 == all_len);
    return cost;
}

typedef struct
{
    unsigned int weight;
    unsigned int parent, lchild, rchild;
} HTNode;
typedef std::vector<HTNode> HuffmanTree;	//存储赫夫曼树
//  求赫夫曼编码。
//---------------------------------------------------------------------------
int mmin( HuffmanTree& t, int i )
{
    int flag;
    unsigned int k = UINT_MAX; // 取k为不小于可能的值
    for(int j = 1; j<= i; j++)
        if (t[j].weight< k&& t[j].parent == 0)
            k = t[j].weight, flag = j;
    t[flag].parent = 1;
    return flag;
}
//---------------------------------------------------------------------------
void select(HuffmanTree& t, int i, int &s1, int &s2)
{ /// s1为最小的两个值中序号小的那个
    s1 = mmin(t, i);
    s2 = mmin(t, i);
    if (s1>s2)
    {
        int j = s1;
        s1 = s2;
        s2 = j;
    }
}
unsigned calc_min_cost2(const test_case& a_case)
{
    int i, m = 2*a_case.part_count-1;
    HuffmanTree huff_tree;
	huff_tree.resize(m+1); // 0号单元未用
    for(i = 1; i<= a_case.part_count; ++i)
    {
        huff_tree[i].weight = a_case.part_len_ptr[i-1];//
        huff_tree[i].parent = 0;
		huff_tree[i].lchild = 0;
        huff_tree[i].rchild = 0;
    }
    for(; i<= m; ++i)
        huff_tree[i].parent = 0;

    for(i = a_case.part_count+1; i<= m; ++i) // 建赫夫曼树
    {
        // 在HT[1~i-1]中选择parent为0且weight最小的两个结点, 其序号分别为s1和s2
		int s1, s2;
        select(huff_tree, i-1, s1, s2);
        huff_tree[s1].parent = huff_tree[s2].parent = i;
        huff_tree[i].lchild = s1;
        huff_tree[i].rchild = s2;
        huff_tree[i].weight = huff_tree[s1].weight+huff_tree[s2].weight;
    }
    unsigned cost = 0;
    for(i = a_case.part_count+1; i<= m; ++i)
        cost += huff_tree[i].weight;

    return cost;
}

unsigned test(test_case& a_case)
{
    std::copy(a_case.part_len_ptr, a_case.part_len_ptr+a_case.part_count, ostream_iterator<unsigned> (cout ," ") );
    cout << "\nlength:" << a_case.wood_all_len << ", part count:" << a_case.part_count << "\n";
    // algo 2.
    cout << "min cost2:" << calc_min_cost2(a_case) << "\n";
    // algo 1 must pre-sort .
    std::sort(a_case.part_len_ptr, a_case.part_len_ptr+a_case.part_count, greater<unsigned>());
    cout << "min cost:" << calc_min_cost(a_case) << "\n";
    cout << "\n";
}

#define LOAD_A_CASE_TO_TEST_CASE_AND_PRINT(part_len_case, case_n) \
    test_case case_n; \
    case_n.wood_all_len = 0; \
    case_n.part_count = sizeof(part_len_case) / sizeof(unsigned); \
    for (size_t i = 0; i < case_n.part_count; ++i) \
        case_n.wood_all_len += part_len_case[i]; \
    case_n.part_len_ptr = new unsigned[case_n.part_count]; \
    memcpy(case_n.part_len_ptr, part_len_case, case_n.part_count*sizeof(unsigned)); \
    test(case_n);

#define LOAD_ALL_TEST 0

void run_test_case()
{
    // initalize cases.
    unsigned PART_LEN_CASE1[] = {1, 2, 3, 4};
    unsigned PART_LEN_CASE2[] = {120, 37, 42, 42, 32, 2, 7, 24};
    unsigned PART_LEN_CASE3[] = {1, 2, 2, 2, 2, 3};
    unsigned PART_LEN_CASE4[] = {1, 100};
    unsigned PART_LEN_CASE5[] = {120, 37, 42, 42, 42, 42, 32, 2, 32, 32, 7, 24, 24};

    LOAD_A_CASE_TO_TEST_CASE_AND_PRINT(PART_LEN_CASE1, case1);
    LOAD_A_CASE_TO_TEST_CASE_AND_PRINT(PART_LEN_CASE2, case2);
    LOAD_A_CASE_TO_TEST_CASE_AND_PRINT(PART_LEN_CASE3, case3);
    LOAD_A_CASE_TO_TEST_CASE_AND_PRINT(PART_LEN_CASE4, case4);
    LOAD_A_CASE_TO_TEST_CASE_AND_PRINT(PART_LEN_CASE5, case5);
//
//    test(case1);
//    test(case2);
//    test(case3);
//    test(case4);
//
//    test_case case1, case2, case3;
//    case1.wood_all_len = 0;
//    case1.part_count = sizeof(PART_LEN_CASE1) / sizeof(unsigned);
//    for (size_t i = 0; i < case1.part_count; ++i)
//        case1.wood_all_len += PART_LEN_CASE1[i];
//    case1.part_len_ptr = new unsigned[case1.part_count];
//    memcpy(case1.part_len_ptr, PART_LEN_CASE1, case1.part_count*sizeof(unsigned));
//
//    case2.wood_all_len = 306;
//    case2.part_count = sizeof(PART_LEN_CASE2) / sizeof(unsigned);
//    case2.part_len_ptr = new unsigned[case2.part_count];
//    memcpy(case2.part_len_ptr, PART_LEN_CASE2, case2.part_count*sizeof(unsigned));
//
//    case3.wood_all_len = 12;
//    case3.part_count = sizeof(PART_LEN_CASE3) / sizeof(unsigned);
//    case3.part_len_ptr = new unsigned[case3.part_count];
//    memcpy(case3.part_len_ptr, PART_LEN_CASE3, case3.part_count*sizeof(unsigned));
//    // Pre-sort .
//    std::sort(case1.part_len_ptr, case1.part_len_ptr+case1.part_count, greater<unsigned>());
//    std::sort(case2.part_len_ptr, case2.part_len_ptr+case2.part_count, greater<unsigned>());
//    std::sort(case3.part_len_ptr, case3.part_len_ptr+case3.part_count, greater<unsigned>());
//
//    std::copy(case1.part_len_ptr, case1.part_len_ptr+case1.part_count, ostream_iterator<unsigned> (cout ," ") );
//    cout << "\n";
//    std::copy(case2.part_len_ptr, case2.part_len_ptr+case2.part_count, ostream_iterator<unsigned> (cout ," ") );
//    cout << "\n";
//    std::copy(case3.part_len_ptr, case3.part_len_ptr+case3.part_count, ostream_iterator<unsigned> (cout ," ") );
//    cout << "\n";
//
//    cout << calc_min_cost(case1) << "\n";
//    cout << calc_min_cost(case2) << "\n";
//    cout << calc_min_cost(case3) << "\n";
}
} /// namespace test_namespace


int main()
{
    using namespace test_namespace;
    run_test_case();

    /*********/
    //assert (!" assert false here.");
    cout << " Hello world!" << endl;
    return 0;
}
