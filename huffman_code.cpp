
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <limits.h>
#include <cassert>
using namespace std;

#include "huffman_code.h"

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
{
    // s1为最小的两个值中序号小的那个
    s1 = mmin(t, i);
    s2 = mmin(t, i);
    if (s1>s2)
    {
        int j = s1;
        s1 = s2;
        s2 = j;
    }
}
//---------------------------------------------------------------------------
void do_huff_code()
{
	int n = g_codes.size();
    // w存放n个字符的权值(均>0), 构造赫夫曼树HT, 并求出n个字符的赫夫曼编码HC
    if (n < 1)
        return;
    int i, m = 2*n-1;
    //g_huff_tree = (HuffmanTree)malloc((m+1)*sizeof(HTNode));
	g_huff_tree.resize(m+1); // 0号单元未用
    for(i = 1; i<= n; ++i)
    {
        g_huff_tree[i].weight = g_weights[i-1];//
        g_huff_tree[i].parent = 0;
		g_huff_tree[i].lchild = 0;
        g_huff_tree[i].rchild = 0;
    }
    for(; i<= m; ++i)
        g_huff_tree[i].parent = 0;

    for(i = n+1; i<= m; ++i) // 建赫夫曼树
    {
        // 在HT[1~i-1]中选择parent为0且weight最小的两个结点, 其序号分别为s1和s2
		int s1, s2;
        select(g_huff_tree, i-1, s1, s2);
        g_huff_tree[s1].parent = g_huff_tree[s2].parent = i;
        g_huff_tree[i].lchild = s1;
        g_huff_tree[i].rchild = s2;
        g_huff_tree[i].weight = g_huff_tree[s1].weight+g_huff_tree[s2].weight;
    }
    // 从叶子到根逆向求每个字符的赫夫曼编码
    // 分配n个字符编码的头指针向量([0]不用)
	g_huff_code.resize(n+1);
	std::string temp;
	temp.resize(n);
    for(i = 1; i<= n; i++)
    {
        // 逐个字符求赫夫曼编码
        int start = temp.size(); // 编码结束符位置
        for(unsigned c = i, f = g_huff_tree[i].parent; f != 0;
			c = f, f = g_huff_tree[f].parent)
            // 从叶子到根逆向求编码
            if (g_huff_tree[f].lchild == c)
                temp[--start] = '0';
            else
                temp[--start] = '1';

        g_huff_code[i].assign(temp.begin() + start, temp.end());
    }
}
//---------------------------------------------------------------------------
void menu()
{
    system("cls");
    cout << "\n\n\n\n";
    cout<<"	┌─────────────────────────┐\n"
        <<"	│请选择操作功能以回车结束  0--显示编码内容         │\n"
        <<"	├────────────┬────────────┤\n"
        <<"	│1--初始化编码           │2--添加编码内容         │\n"
        <<"	│3--修改编码内容         │4--删除编码内容         │\n"
        <<"	│5--电文编码             │6--电文译码             │\n"
        <<"	│7--电文自动编码         │8--退出系统             │\n"
        <<"	└────────────┴────────────┘\n";

}

//---------------------------------------------------------------------------
int get_weight()
{
    unsigned int weight;
    int		i  =  0;
    char	ch_num, chars[10]  =  {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    cout << "\n请输入该字符的权值(整型)：";
    cin.get(ch_num);
    while(ch_num != '\n')
    {
        if ( !(isdigit(ch_num)) )
        {
            cout << "\n		对不起你的输入（权值）有误！\n";
            system("pause");
            return -1;
        }
        chars[i++]  =  ch_num;
        cin.get(ch_num);
    }
    weight  =  atoi(chars);

    return weight;
}
//---------------------------------------------------------------------------
int init_huff_code()
{
    g_codes.clear();
    g_weights.clear();

    void	print_HuffmanCode();
    char	ch;
    int		n = 0;//unsigned
    cout << "请输入编码字符（单个）Esc退出：";
    ch  =  getch();
    cout << ch;

    while(ch != 27)
    {
        unsigned int weight = 0;
        int	 nums;
        if ( (nums = get_weight()) != -1 )
            weight  =  nums;
        else
            return 0;

        g_codes.push_back(ch);
        g_weights.push_back(weight);
        do_huff_code();
        cout << "		!添加编码字符成功! \n\n";

        cout << "请继续输入编码字符（单个）Esc退出：";
        ch  =  getch();
        cout << ch;
        for(int i = 0; i<g_codes.size(); i++)
        {
            if (ch == g_codes[i])
            {
                cout << "\n	添加编码字符失败，字符集中已有" << ch <<"存在！！！" <<endl;
                system("pause");
                return 0;
            }
        }
    }
    print_huff_code();
    return 1;
}

//---------------------------------------------------------------------------
void print_huff_code()
{
    cout << "\n	  字符  权值  编码	编码长度\n" ;

    for(unsigned int m = 1; m<= g_codes.size(); m++) //static_cast<int>(vec_char_size)
    {
        cout << "	   "<< g_codes[m-1] <<setw(7)<<g_weights[m-1]<<setw(7)<< g_huff_code[m]<<setw(7)<<g_huff_code[m].size()<<endl;
    }
    system("pause");
}
//---------------------------------------------------------------------------
int	add_huff_code()
{
    char	ch;
    int		n = 0;//unsigned
    cout << "请输入你要添加的编码字符（单个）Esc退出：";
    ch  =  getch();
    cout << ch;
    for(int i = 0; i<g_codes.size(); i++)
    {
        if (ch == g_codes[i])
        {
            cout << "\n	添加编码字符失败，字符集中已有" << ch <<"存在！！！" <<endl;
            system("pause");
            return 0;
        }
    }

    while(ch != 27)
    {
        unsigned int weight;
        int		nums;
        if ( (nums = get_weight()) != -1 )
            weight  =  nums;
        else
            return 0;

        g_codes.push_back(ch);
        g_weights.push_back(weight);

        do_huff_code();
        cout << "		!添加编码字符成功! \n\n";

        cout << "请继续输入你要添加的编码字符（单个）Esc退出：";
        ch  =  getch();
        cout << ch;
        for(int i = 0; i<g_codes.size(); i++)
        {
            if (ch == g_codes[i])
            {
                cout << "\n	添加编码字符失败，字符集中已有" << ch <<"存在！！！" <<endl;
                system("pause");
                return 0;
            }
        }
    }
    print_huff_code();
    return 1;
}
//---------------------------------------------------------------------------
int	modify_huff_code()
{
    int		n = 0;
    int		pos;
	cout << "请输入你要修改的编码字符（单个）Esc退出：";
	char	pre_ch;
    pre_ch  =  getch();
    cout << pre_ch;
	char ch = pre_ch;
    while(ch != 27)
    {
        for(pos = 0; pos<g_codes.size(); pos++)
            if (g_codes[pos] == pre_ch)
                break;
        if (pos == g_codes.size())
        {
            cout << "\n抱歉，没有你要修改的编码字符: "<<ch <<endl;
            system("pause");
            return 0;
        }
        cout << "\n请输入正确的编码字符（单个）Esc退出：";
        ch  =  getch();
        cout << ch;
        for(int i = 0; i<g_codes.size(); i++)
            if (ch == g_codes[i] && ch != pre_ch)
            {
                cout << "\n	修改编码字符失败，字符集中已有" << ch <<"存在！！！" <<endl;
                system("pause");
                return 0;
            }
        unsigned int weight;
        int		nums;
        if ( (nums = get_weight()) != -1 )
            weight  =  nums;
        else
            return 0;

        g_codes[pos]  =  ch;
        g_weights[pos]  =  weight;
        do_huff_code();
        cout << "\n		!修改编码字符成功! ";

        cout << "\n请继续输入你要修改的编码字符（单个）Esc退出：";
        ch  =  getch();
        cout << ch;
    }

    print_huff_code();

    return 1;
}
//---------------------------------------------------------------------------
int	delete_huff_code()
{
    char	ch;
    int		n = 0, i = 0;//unsigned
    cout << "请输入你要删除的编码字符（单个）Esc退出：";
    ch  =  getch();
    cout << ch;

    int		delete_flag  =  0;
    while(ch != 27)
    {
        for(i = 0; i<g_codes.size(); i++)
            if (g_codes[i] == ch)
            {
                g_codes.erase(g_codes.begin()+i);//
                delete_flag  =  1;
                break;
            }
        if (delete_flag == 0)
        {
            cout << "\n抱歉，没有你要删除的编码字符: " <<ch <<endl;
            system("pause");
            return 0;
        }
        g_weights.erase(g_weights.begin()+i);

        do_huff_code();
        cout << "\n		!删除编码字符成功! ";

        cout << "\n继续输入你要删除的编码字符（单个）, Esc退出：";
        ch  =  getch();
        cout << ch;
    }

    print_huff_code();

    return 1;

}
//---------------------------------------------------------------------------
int	encode_telegra()
{

    string	telegra, telegra_code;

    cout << "\n	请输入你要进行编码的电文 ：";
    getline(cin, telegra);

    for(int i = 0; i<telegra.size(); i++)
    {
        int		character_exist_flag  =  0;
        for(int j = 0; j<g_codes.size(); j++)
            if (telegra[i] == g_codes[j])
            {
                telegra_code.append(g_huff_code[j+1]);
                character_exist_flag  =  1;
            }
        if ( character_exist_flag == 0 )
        {
            cout << "\n抱歉，没有字符"<<telegra[i]<<"的编码! "<<endl;
            system("pause");
            return 0;
        }
    }
    cout <<"编码结果为：";
    cout <<	telegra_code <<endl;
    print_huff_code();

    return 1;
}
//---------------------------------------------------------------------------
int	decode_telegra()
{
    string	telegra_code, str_telegra;
    vector<char>	telegra;
    int		trans_pos = 0;
    int		HT_length  =  2*g_codes.size();//0号单元未用！
    int		character_exist_flag  =  1;
    int		i = 0, j = 0;

    cout << "\n	请输入你要进行译码的电文 ：";
    cin >> telegra_code;

    for(trans_pos = 0, j  =  HT_length-1; trans_pos < telegra_code.size(); trans_pos++)
    {
        character_exist_flag  =  1;
        if (telegra_code[trans_pos] == '1')
            j  =  g_huff_tree[j].rchild;
        else if (telegra_code[trans_pos] == '0')
            j  =  g_huff_tree[j].lchild;

        if (j <=  g_codes.size())
        {
            telegra.push_back(g_codes[j-1]);
            j  =  HT_length-1;
            character_exist_flag = 0;
        }
    }

    if ( character_exist_flag == 1 )
    {
        cout << "\n		抱歉，译码出错！" <<endl;
        for(i = 0; i<telegra.size(); i++)
            cout << telegra[i];
        cout << "	？？？" <<endl;

        for(i = 0; i < trans_pos; i++)
            cout << telegra_code[i];
        cout << "在此出错了！\n";

        return 0;
    }
    cout <<"译码结果为：";
    for(i = 0; i<telegra.size(); i++)
        cout << telegra[i];
    cout << endl;

    return 1;
}
//---------------------------------------------------------------------------
int auto_huff_code()
{
    string		str_code;
    int 	char_exist_flag  =  1;
    cout << "请输入你要进行编码的字符串：";
	cin.ignore(100, '\n');
    getline(cin, str_code, '\n');
    for(int i = 0; i<str_code.size(); i++)
    {
        char_exist_flag  =  1;
        for(int j = 0; j<g_codes.size(); j++)
            if (str_code[i] == g_codes[j])
            {
                g_weights[j]++;
                char_exist_flag  =  0;
            }
        if (char_exist_flag == 1)
        {
            g_codes.push_back(str_code[i]);
            g_weights.push_back(1);
        }
    }
    do_huff_code();
    return 1;
}

//---------------------------------------------------------------------------
void say_goodbye()
{
    cout << "\n		       !!! GOODBYE, BYE-BYE !!!		\n";
}
//---------------------------------------------------------------------------
void do_demo(char which)
{
    switch (which)
    {
    case '0':
        print_huff_code();
        break;
    case '1':
        init_huff_code();

        break;
    case '2':
        print_huff_code();
        add_huff_code();
        break;
    case '3':
        print_huff_code();
        modify_huff_code();

        break;
    case '4':
        print_huff_code();
        delete_huff_code();
        break;
    case '5':
        encode_telegra();
        break;
    case '6':
        print_huff_code();
        decode_telegra();
        system("pause");

        break;
    case '7':
        auto_huff_code();
        print_huff_code();

        break;
    case '8':
        cout << " ... 退出系统...\n";

        break;
    default:
        printf(" \n	您的输入有误，请重新输入选择 !\n");
    }
    cout << endl;
}
//---------------------------------------------------------------------------
int main()
{
    do
    {
		menu();
		char c;
		cin >> c;
        do_demo(c);
		cin.ignore(100, '\n');
    }
	while (true);
	say_goodbye();
    return 0;
}

//---------------------------------------------------------------------------
