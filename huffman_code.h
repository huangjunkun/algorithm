
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <cassert>
using namespace std;

//---------------------------------------------------------------------------
typedef struct
{
    unsigned int weight;
    unsigned int parent, lchild, rchild;
} HTNode, *HuffmanTree; // 动态分配数组存储赫夫曼树
typedef char*	*HuffmanCode; // 动态分配数组存储赫夫曼编码表

vector<char>	vec_char;
vector<unsigned int>	 vec_int;
HuffmanTree		huff_tree;
HuffmanCode		huff_code;

int*	huff_code_len_ptr;


//---------------------------------------------------------------------------
//函数声明

int mmin( HuffmanTree t, int i );
void select(HuffmanTree t, int i, int &s1, int &s2);
void do_huff_code(HuffmanTree &HT, HuffmanCode &HC, vector<unsigned int> vec_int, int n);
void menu();
int init_huff_code();
void print_huff_code();
int	add_huff_code();
int	modify_huff_code();
int	delete_huff_code();
int	encode_telegra();
int	decode_telegra();
int auto_huff_code();
void say_goodbye();
extern void play();



