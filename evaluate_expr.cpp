
#include<iostream>
#include<stack>
#include<string>
#include<cstdlib>
#include <conio.h>
#include<windows.h>
#include<string>
#include <cassert>
using namespace std;


/**
** 源文件： evaluate_ expr.cpp
** 功能说明：
** 测试程序，表达式求值解法，栈数据结构经典应用，需要预先定义运算符op的优先级。
	1. 中缀表达式到后缀表达式的转换；
	2. 后缀表达式求值。
转：

中缀表达式到后缀表达式的转换
　　要把表达式从中缀表达式的形式转换成用后缀表示法表示的等价表达式，必须了解操作符的优先级和结合性。
  优先级或者说操作符的强度决定求值顺序；优先级高的操作符比优先级低的操作符先求值。 如果所有操作符优先级一样，
  那么求值顺序就取决于它们的结合性。操作符的结合性定义了相同优先级操作符组合的顺序（从右至左或从左至右）。
  转换过程包括用下面的算法读入中缀表达式的操作数、操作符和括号：
	1. 初始化一个空堆栈，将结果字符串变量置空。
	2. 从左到右读入中缀表达式，每次一个字符。
	3. 如果字符是操作数，将它添加到结果字符串。
	4. 如果字符是个操作符，弹出（pop）操作符，直至遇见开括号（opening parenthesis）、优先级较低的操作符或者同一优先级的右结合符号。
	把这个操作符压入（push）堆栈。
	5. 如果字符是个开括号，把它压入堆栈。
	6. 如果字符是个闭括号（closing parenthesis），在遇见开括号前，弹出所有操作符，然后把它们添加到结果字符串。
	7. 如果到达输入字符串的末尾，弹出所有操作符并添加到结果字符串。

后缀表达式求值
对后缀表达式求值比直接对中缀表达式求值简单。在后缀表达式中，不需要括号，而且操作符的优先级也不再起作用了。
您可以用如下算法对后缀表达式求值：
	1. 初始化一个空堆栈
	2. 从左到右读入后缀表达式
	3. 如果字符是一个操作数，把它压入堆栈。
	4. 如果字符是个操作符，弹出两个操作数，执行恰当操作，然后把结果压入堆栈。如果您不能够弹出两个操作数，后缀表达式的语法就不正确。
	5. 到后缀表达式末尾，从堆栈中弹出结果。若后缀表达式格式正确，那么堆栈应该为空。


** 作者：junkun huang
** 创建日期：2008-09 前 /
*/

double four_operations(double a,char theta,double b);
char pre_proccess(char a,char b);
template <class T>
void out_stack (const stack<T>& s);
int is_symbol (char c);
void say_goodbye();

double evaluate_expr(const std::string& expr )
{
    stack<double> data_stack;
    stack<char>	 symbol_stack, temp_symbols;
    symbol_stack.push('#');
    int mul_flag = 0;

    const char* next_ptr = expr.c_str();
    char symbol, next, pre_next = '#', after_next;
    next = *(next_ptr++);
    while ( next != '#' || symbol_stack.top()!='#')
    {
        if (!is_symbol(next) || (next=='-' && is_symbol(pre_next)) )//不是运算符，并区分负号和减号（“-”）
        {
            if (!is_symbol(next) && !isdigit(next) && next!='.' )//判断是否非法字符--或isalpha(next) ||next == ' '
            {
                std::cerr << " 1. The expression of input is error.\n";
                break;
            }
            int j=0;
            char num[10] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '} ;//
            while ( isdigit(next) || next == '.'||(next=='-'&&is_symbol(pre_next)))
            {
                num[j] = next;
                j++;
                pre_next = next;
                next = *(next_ptr++);
            }

            if ( num[0]=='-'&& !isdigit(num[1]) )//负号后面为非法字符
            {
                std::cerr << " 4. The data after '-' is error.\n";
                break;
            }
            double d_num = atof(num);
            data_stack.push(d_num);
        }
        else switch ( pre_proccess(symbol_stack.top(), next) )
            {
            case '<' ://栈顶元素优先权低
                symbol_stack.push(next);
                pre_next = next;

                if	(mul_flag == 1)
                {
                    next = after_next;
                    mul_flag = 0;
                }
                else
                    next = *(next_ptr++);

                break;
            case '=' ://脱括号并接受下一个字符
                if ( (next != '#') )
                    temp_symbols.push( next );
                temp_symbols.push( symbol_stack.top() );
                symbol_stack.pop();
                pre_next = next;

                if	(mul_flag == 1)
                {
                    next = after_next;
                    mul_flag = 0;
                }
                else
                    next = *(next_ptr++);

                break;
            case '>' ://退栈并将运算结果入栈
            {
                if (data_stack.size() < 2 )
                {
                    std::cerr << " 2. The data of input is too little.\n";
                    symbol_stack.pop();
                    break;
                }

                symbol = symbol_stack.top();
                temp_symbols.push(symbol);
                symbol_stack.pop();
                double b = data_stack.top();
                data_stack.pop();
                double a = data_stack.top();
                data_stack.pop();
                if (symbol == '/' && b == 0 )
                {
                    std::cerr << " 3. Division by zero.\n";
                    break;
                }

                data_stack.push(four_operations(a, symbol, b));
                break;
            }

            default:
                std::cerr << "\n 5. The symbol of input is error.\n";
            }

        if ( next=='(' && (isdigit(pre_next)|| pre_next==')') ||(isdigit(next)&& pre_next==')'))
        {
            //处理两括号相乘情况如：(5+6)(3-5)
            after_next = next;
            next = '*';
            mul_flag = 1;
        }
    }

    cout << " The result of the Expression is:\n";
    double ret = data_stack.empty() ? 0 : data_stack.top();
    out_stack (data_stack);
    cout << " At the end the data in stack:\n";
    out_stack (symbol_stack);
    cout << " The sequence of pop from the stack while do calculating:\n";
    out_stack (temp_symbols);

    return ret;
}

int main ()
{
    do
    {
        cin.clear();
        cout << "\n\n\n Input the expression(Tips: q. exit). Expr:";
        std::string expr;
        std::getline(std::cin, expr);
        if ( expr[0]=='q'||expr[0]=='Q'||expr[0]=='27')
            break;
        // 插入结束字符 '#'
        expr.push_back('#');
        evaluate_expr(expr);

    }
    while (true);
    /// test-case.
    std::cout << " (1+2-(-1))*5/(3+1) = " << evaluate_expr("(1+2-(-1))*5/(3+1)#") << "\n";
    std::cout << " (5+2)(7-2) = " << evaluate_expr("(5+2)(7-2)#") << "\n";
    std::cout << " ((5+5)/(7-2)) = " << evaluate_expr("((5+5)/(7-2))#") << "\n";
    std::cout << " 2+1*10/5 = " << evaluate_expr("2+1*10/5#") << "\n";
    say_goodbye();
    return 0;
}
int is_symbol (char c)
{
    int flag;
    switch(c)
    {
    case'#' :
    case'+' :
    case'-' :
    case'*' :
    case'/' :
    case'(' :
    case')' :
        flag = 1;
        break;
    default:
        flag = 0;
        break;
    }
    return flag;
}

template <class T>
void out_stack (stack<T> s)
{
    while ( !s.empty() )
    {
        cout << " " << s.top();
        s.pop();
        cout << "\n";
    }
    cout << endl;
}
double four_operations(double a, char symbol, double b)
{
    double sum = 0;
    switch (symbol)
    {
    case '+':
        sum	= a + b;
        break;
    case '-' :
        sum	= a - b;
        break;
    case '*' :
        sum	= a * b;
        break;
    case '/' :
        sum	= a / b;
        break;
    default	:
        assert (false);
    }
    return	sum;
}


char pre_proccess(char a, char b)
{
    if (a == '#' && b == '#')
        return	'=';

    if (a == '#')
        return	'<';
    if (b == '#')
        return	'>';

    if (a == '(' && b == ')')
        return	'=';
    if (a == '(' && b != ')')
        return	'<';
    if (a != '(' && b == ')')
        return	'>';
    if (a == ')')
        return	'>';
    if (b == ')')
        return	'>';
    if (b == '(')
        return	'<';
    if ( (a == '+' && b == '+')||(a == '+' && b == '-')||(a == '-' && b == '-')||(a == '-' && b == '+') )
        return	'>';
    if ( (a == '*' && b == '*')||(a == '*' && b == '/')||(a == '/' && b == '/')||(a == '/' && b == '*') )
        return	'>';
    if ( (b == '+' || b == '-')&&(a == '*' || a == '/') )
        return	'>';
    if ( (a == '+' || a == '-')&&(b == '*' || b == '/') )
        return	'<';

    assert (false);
    return '0';//error
}
void say_goodbye()
{
    std::cout << " Hello Goodbye.\n";
    system("pause");
}
