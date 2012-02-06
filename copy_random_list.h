#ifndef COPY_RANDOM_LIST_H_INCLUDED
#define COPY_RANDOM_LIST_H_INCLUDED

#include <iostream>
#include <cstdio>
#include <cassert>

#include <iomanip>
#include <limits.h>
#include <string>
#include <memory>
#include <iterator>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <strstream>


/**
** 源文件： random_list_node.h, random_list_node_test.cpp
** 功能：拷贝“随机链表”，即节点带有一个指针可能指向链表随机另一个节点的链表。
** 一般的简单蛮力算法，可完成该功能，但时间复杂度为 O(n*m)。而以下算法较高效，相比时间复杂度为O(m).
** 具体操作，需要遍历源链表三遍。包括拷贝链表+复制随机指针+回复源链表NEXT指针。
** 作者：junkun huang  e-mail：huangjunkun@gmail.com
** 日期：2011-06-10 /
*/
///
namespace test_namespace
{
    using namespace std;

	struct random_list_node
	{
		random_list_node()
			: value(0), next_ptr(NULL), random_ptr(NULL)
		{}
		random_list_node(int v)
			: value(v), next_ptr(NULL), random_ptr(NULL)
		{}
		~random_list_node() {}

		int value;
		random_list_node* next_ptr;
		random_list_node* random_ptr;
	};

	typedef random_list_node* random_list;

	random_list_node* test_construct_list(unsigned list_size = 7)
	{
		// just test ...
		if (0 == list_size)
			return NULL;
		random_list_node* head_ptr = NULL;
		head_ptr = new random_list_node;
		head_ptr->value = 0;
		random_list_node* move_ptr = head_ptr;
		for (unsigned i = 1; i < list_size; ++i)
		{
			random_list_node* new_node = new random_list_node;
			new_node->value = i;
			move_ptr->next_ptr = new_node;
			move_ptr = new_node;
		}
		move_ptr = head_ptr;
		for (unsigned i = 1; i < list_size; i+=2)
		{
			move_ptr->random_ptr = move_ptr->next_ptr->next_ptr;
			move_ptr = move_ptr->next_ptr->next_ptr;
		}
		return head_ptr;
	}
	/// 算法步骤，复制完链表，遍历两遍即完成拷贝操作。详细步骤见下：
	///1. ABCD是原来的链表，A’B’C’D’是复制的链表，第一遍扫描顺序复制next指针，
	///2. 把ABCD的next分别指向A’B’C’D’，将A’的next指针指向B，B’的next指针指向C，依次类推
	///3. 复制random指针： A’->random=A->random->next
	///4. 恢复:A->next=A’->next; A’->next=A’->next->next;
	random_list_node* copy_random_list(random_list_node* head_ptr)
	{
		if (NULL == head_ptr) return NULL;

		random_list_node* new_head_ptr = new random_list_node;
		new_head_ptr->value = head_ptr->value;
		new_head_ptr->next_ptr = head_ptr->next_ptr;
		head_ptr->next_ptr = new_head_ptr;
		// copy random_list
		random_list_node* move_ptr = new_head_ptr->next_ptr;
		while (move_ptr)
		{
			random_list_node* new_node = new random_list_node;
			new_node->value = move_ptr->value;
			new_node->next_ptr = move_ptr->next_ptr;
			move_ptr->next_ptr = new_node;
			move_ptr = new_node->next_ptr;
		}

		// scan random_list twice, for random_ptr and next_ptr.
		move_ptr = head_ptr;
		while (move_ptr)
		{
			random_list_node* new_move_ptr = move_ptr->next_ptr;
			if (move_ptr->random_ptr)
				new_move_ptr->random_ptr = move_ptr->random_ptr->next_ptr;

			assert(NULL != new_move_ptr);
			move_ptr = new_move_ptr->next_ptr;
			//new_move_ptr = move_ptr->next_ptr;
		}

		move_ptr = head_ptr;
		random_list_node* new_move_ptr = move_ptr->next_ptr;
		while (new_move_ptr)
		{
			move_ptr->next_ptr = new_move_ptr->next_ptr;
			if (new_move_ptr->next_ptr)
				new_move_ptr->next_ptr = new_move_ptr->next_ptr->next_ptr;
			move_ptr = move_ptr->next_ptr;
			new_move_ptr = new_move_ptr->next_ptr;
		}

		return new_head_ptr;
	}

	void deallocate_list(random_list_node* head_ptr)
	{
		while (head_ptr)
		{
			random_list_node* delete_node = head_ptr;
			head_ptr = head_ptr->next_ptr;
			delete delete_node;
		}

		return;
	}

	void print_list(ostream& os, random_list_node* head_ptr)
	{
		unsigned index = 0;
		os << "[index](value, random_ptr->value): ";
		while (head_ptr)
		{
			os << "[" << index << "](" << head_ptr->value << ", ";
			if (head_ptr->random_ptr)
				os << head_ptr->random_ptr->value << ") ";
			else
				os << "NULL) ";

			head_ptr = head_ptr->next_ptr;
			++index;
		}

		os << std::endl;
		return;
	}

//////////////////////////////////////////////////////////////////////////


}/// namespace test_namespace


#endif // TIMER_CLASS_H_INCLUDED
