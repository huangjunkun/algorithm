// test_special_sort.cpp : 定义控制台应用程序的入口点。
//

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <conio.h>

using namespace std;
int test_special_sort()
{
	// 引用自：http://groups.google.com/group/pongba/t/54146dfb71a67827
	// 特殊排序题目说明：请按照名次顺序输出她们的名字，要求O(N)时间。
	// 姓名集合names，名次集合ranks，如下：

	string names[] = {"张含韵", "李宇春", "曾轶可", "张靓颖", "郭美美", "张韶涵" };
	unsigned ranks[] = { 3, 2, 4, 0, 5, 1};
	assert (sizeof(ranks) / sizeof(ranks[0]) == sizeof(names) / sizeof(names[0]) );
	const all_count = sizeof(ranks) / sizeof(ranks[0]);

	// 解法一，不改变原来集合顺序，O(N)时间， O(N)空间。
	vector<unsigned> ranks_bak(all_count);
	for (size_t i = 0; i < all_count; ++i)
	{	// 数组下标相当于姓名索引，新空间已名次顺序记录着姓名索引。
		ranks_bak[ranks[i]] = i;
	}
	// 输出结果。
	for (size_t i = 0; i < all_count; ++i)
		std::cout << names[ranks_bak[i]] << " ";
	std::cout << "\n";

	//////////////////////////////////////////////////////////////////////////

	// 解法二，在位重新排序，改变原来集合顺序，O(N)时间， O(1)空间。
	for (size_t i = 0; i < all_count; ++i)
	{
		// 每次swap确定一元素位置，最多共N次swap能全部定位。
		while (i != ranks[i])
		{
			std::swap(names[ranks[i]], names[i]);
			std::swap(ranks[ranks[i]], ranks[i]);
			//std::cout << " ranks[i]:" << ranks[i] << "\n";
		}
	}
	// 输出结果。
	for (size_t i = 0; i < all_count; ++i)
		std::cout << names[i] << " ";
	std::cout << "\n";



// 肯爷爷(Knuth)证明，任何基于比较的排序不可能小于O(N \lg N)么？
// 而此题之所以可以O(N)解决，是因为其元素的特殊性，均在一定较小的范围之内。
	return 0;
}

int main(int argc, char* argv[])
{
	test_special_sort();
	/**     */
	cout << "\n Input any char to end.\n" << endl;
	getch();
	return 0;
}

