
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
} HTNode; 

typedef std::vector<HTNode> HuffmanTree;	//存储赫夫曼树
typedef std::vector<string> HuffmanCode;	//存储赫夫曼编码表

vector<char>			g_codes;
vector<unsigned int>	g_weights;
vector<unsigned int>	g_huff_code_len_ptr;
HuffmanTree		g_huff_tree;
HuffmanCode		g_huff_code;


/**
** 源文件： huffman_code.cpp. huffman_code.h
** 功能说明：
** 测试程序，霍夫曼编码的简单应用及其演示。如程序运行霍夫曼自动编码功能效果如下：
请输入你要进行编码的字符串：abbcccddddeeeeeffffff
          字符  权值  编码      编码长度
           a      1   1110      4
           b      2   1111      4
           c      3    110      3
           d      4     00      2
           e      5     01      2
           f      6     10      2
** wiki介绍：http://zh.wikipedia.org/zh/%E9%9C%8D%E5%A4%AB%E6%9B%BC%E7%BC%96%E7%A0%81
** 具体实现，详见源码与注释说明。

** 作者：junkun huang
** 创建日期：2008-11 前 /
*/

//---------------------------------------------------------------------------
//函数声明

int mmin( HuffmanTree& t, int i );
void select(HuffmanTree& t, int i, int &s1, int &s2);
void do_huff_code();
void free_data();
int init_huff_code();
void print_huff_code();
int	add_huff_code();
int	modify_huff_code();
int	delete_huff_code();
int	encode_telegra();
int	decode_telegra();
int auto_huff_code();
void menu();
void do_demo();
void say_goodbye();



