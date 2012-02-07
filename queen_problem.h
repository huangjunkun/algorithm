
#ifndef	_QUEEN_PROBLEM_H_
#define _QUEEN_PROBLEM_H_
//---------------------------------------------------------------------------
#include<string>
#include<ctype.h>
#include<vector>
#include<stack>
#include<queue>
#include<malloc.h>
#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<process.h>
#include<iostream>
#include<windows.h>
#include<time.h>
#include <conio.h>
#include <fstream>
#include <assert.h>
#include<time.h>
using namespace std;

//---------------------------------------------------------------------------
class	Board  //一盘棋n*n
{
private:

    char**		_ppBoard;
    int*		_pRows,  *_pDiagsLR, *_pDiagsRL;
    unsigned	**_ppNumBoard;
    std::string	_output_solution_file, _output_data_file;

private:
    void _printSolution(ostream& os = std::cout);
    void _printResult(ostream& os);
public:
    const int	nQueen;
    unsigned	lSolutionCount;
    unsigned	incrementSol(unsigned uAdd);

    Board();
    Board(int nQ);
    ~Board();
    void initBoard();
    void initFile();//初始化文件
    bool isAttacked(int, int);
    void placeQueen(int, int);
    void removeQueen(int, int);

    void saveSolution();
    void printSolution();
    void saveResult();
    void printResult();
};
//---------------------------------------------------------------------------
/*定义计算程序运行时间类型cout_time*/
class	count_timer
{
public:
    //设置程序开始运行时间
    void set_begin();
    //设置程序运行结束时间
    void set_end();
    //计算运行时间
    void count_result();
    //输出运行时间
    void print_result(ostream& os) const;
private:
    //定义时间变量：开始运行时间，结束运行时间，运行时间
    enum { TIME_BUFFER_SIZE = 9 };
    char	_t_begin[TIME_BUFFER_SIZE], _t_end[TIME_BUFFER_SIZE], _t_result[TIME_BUFFER_SIZE];
    long	_ticktime;

    //格式化运行时间
    void _format_result(int i);
};


ostream& operator << (ostream& os, const count_timer& t)
{
    t.print_result(os);
    return os;
}
//---------------------------------------------------------------------------

//定义计算程序运行时间类
count_timer	g_timer;

//---------------------------------------------------------------------------
Board::Board(int nQ)
    : lSolutionCount(0), nQueen(nQ)
{
    _ppBoard = new char*[nQueen];
    _ppNumBoard = new unsigned*[nQueen];
    for (int i=0; i<nQueen; i++)
    {
        _ppBoard[i] = new char[nQueen];
        _ppNumBoard[i] = new unsigned[nQueen];
    }
    _pRows = new int[nQueen];
    _pDiagsLR = new int[2*nQueen-1] ;
    _pDiagsRL = new int[2*nQueen-1] ;


	for (int i=0; i<nQueen; i++)
		for (int j=0; j<nQueen; j++)
			_ppNumBoard[i][j] = 0;
	initBoard();
    initFile(); //初始化文件
}
//---------------------------------------------------------------------------

Board::Board() //构造函数，申请空间初始化为空
    : lSolutionCount(0), nQueen(8)
{
    _ppBoard = new char*[nQueen];
    _ppNumBoard = new unsigned*[nQueen];
    for (int i=0; i<nQueen; i++)
    {
        _ppBoard[i] = new char[nQueen];
        _ppNumBoard[i] = new unsigned[nQueen];
    }
    _pRows = new int[nQueen];
    _pDiagsLR = new int[2*nQueen-1] ;
    _pDiagsRL = new int[2*nQueen-1] ;

    for (int i=0; i<nQueen; i++)
        for (int j=0; j<nQueen; j++)
            _ppNumBoard[i][j] = 0;
	initBoard();
    initFile(); //初始化文件
}
//---------------------------------------------------------------------------
Board::~Board() //析构函数
{
    for (int i=0; i<nQueen; i++)
        delete[] _ppBoard[i];
    delete[] _ppBoard;
    delete[] _pRows;
    delete[] _pDiagsLR;
    delete[] _pDiagsRL;
}

//---------------------------------------------------------------------------
void Board::initBoard()
{
    //申请存储空间
    for (int i=0; i<nQueen; i++)
    {
        _pRows[i] = 0;
        for (int j=0; j<nQueen; j++)
            _ppBoard[i][j] = '*';
    }
    for (int k=0; k<2*nQueen-1; k++)
        _pDiagsLR[k] = _pDiagsRL[k] = 0;
}
//---------------------------------------------------------------------------
void Board::_printSolution(ostream& os)
{
//     os << "\n		┌";
//     for (int i=0; i<nQueen-1; i++)
//         os << "─┬"; //─┬─┬─┬─┬─┬─┬
//
//     os <<	"─┐";
//     os << "\n		";
//     for (int i=0; i<nQueen; i++)
//     {
//         for (int j=0; j<nQueen; j++)
//             os << "│" << _ppBoard[i][j] << " ";
//         os << "│";
//         os << "\n		├";
//         for (int k=0; k<nQueen-1; k++)
//             os << "─┼";
//         os <<	"─┤"; //─┼─┼─┼─┼─┼─┼─┼─┤";
//         os << "\n		";
//     }
    os << "\n		|-";
    for (int i=0; i<nQueen-1; i++)
        os << "-+-";
    os << "-+";
    os << "\n		";
    for (int i=0; i<nQueen; i++)
    {
        for (int j=0; j<nQueen; j++)
            os << "|" << _ppBoard[i][j] << " ";
        os << "|";
        os << "\n		+";
        for (int k=0; k<nQueen; k++)
            os << "--+";
        os << "\n		";
    }

    os << nQueen << "-Queen-Problem Solution:" << lSolutionCount  << endl;
}
//---------------------------------------------------------------------------
void Board::saveSolution()
{
    //文件输出，保存记录！
    ofstream fout;
    fout.open(_output_solution_file.c_str(), ios::app);
    assert (fout.is_open());
    _printSolution(fout);
    fout.close();

    return;
}

void Board::printSolution()
{
    //显示一组排列结果
    _printSolution(std::cout);
    return;
}

//---------------------------------------------------------------------------
// 皇后摆法是否冲突！
bool Board::isAttacked(int row, int col)
{
    int diagLR = col-row+nQueen-1;
    int diagRL = row+col;
    if (_pRows[row] == 1 || _pDiagsLR[diagLR] == 1 || _pDiagsRL[diagRL] == 1)
        return true;

    return false;
}

//---------------------------------------------------------------------------
void Board::placeQueen(int row, int col) //放皇后
{
    int diagLR = col-row+nQueen-1; //左对角线元素
    int diagRL = row+col;  //右对角线元素
    _ppBoard[row][col] = 'Q';
    _pRows[row] = 1;//同行元素
    _pDiagsLR[diagLR] = 1;
    _pDiagsRL[diagRL] = 1;
}

//---------------------------------------------------------------------------
void Board::removeQueen(int row, int col)  //移去皇后
{
    assert (row >= 0 && row < nQueen);
    assert (col >= 0 && col < nQueen);

    int diagLR = col-row+nQueen-1;
    int diagRL = row+col;
    _ppBoard[row][col] = '*';
    _pRows[row] = 0;
    _pDiagsLR[diagLR] = 0;
    _pDiagsRL[diagRL] = 0;
}
//---------------------------------------------------------------------------
void Board::initFile()//初始化文件
{
    char name[10];
    itoa(nQueen, name, 10);
    _output_solution_file = name;//文件命名！！
    _output_solution_file.append("-queen-problem.txt");
    ofstream fout;
    fout.open(_output_solution_file.c_str());
    fout.clear();
    fout.close();

    _output_data_file = name;//文件命名！！
    _output_data_file.append("-queen-problem-data.txt");
    fout.open(_output_data_file.c_str());
    fout.clear();
    fout.close();
}
//---------------------------------------------------------------------------

unsigned Board::incrementSol(unsigned row)
{
    _ppNumBoard[row][0]++;//增加定位一个皇后的一种解法
    ++lSolutionCount;

    return lSolutionCount;
}

void Board::saveResult()
{
    ofstream fout(_output_data_file.c_str(), ios::app);
    _printResult(fout);
}

void Board::printResult()
{
    _printResult(std::cout);
}

void Board::_printResult(ostream& os)
{
    os << nQueen << "-Queen-Problem, the count of all solution is " << lSolutionCount<< ".\n";
    os << "Fasten the first queen, and solve the " << nQueen << "Queen-Problem. Solutions with the matrix:\n";
    for (int i =0; i <nQueen; i++)
    {
        for (int j = 0; j <nQueen; j++)
            os << _ppNumBoard[i][j] << "    ";
        os << "\n\n";
    }
    //g_counter.print_result(os);
    os << "\n" << g_timer;
    os << "Tips: The Queen-Problem's matrix is symmetrical, and you can simplify the problem. \n";
}
//---------------------------------------------------------------------------
/*定义计算程序运行时间类型cout_time*/
//---------------------------------------------------------------------------
void count_timer::set_begin()
{
    _strtime(_t_begin);
    _ticktime = GetTickCount();
}
//---------------------------------------------------------------------------
void count_timer::set_end()
{
    _strtime(_t_end);
    _ticktime = GetTickCount() - _ticktime;
    count_result();
}
//---------------------------------------------------------------------------
void count_timer::_format_result(int i)
{
    if (_t_result[i] < _t_begin[i])
    {
        if (i == 7 || i == 4 || i == 1)
        {
            if (i == 1 && _t_begin[0] == '2')
                _t_result[i] = (_t_result[i] - _t_begin[i] + 4) + 48;
            else
                _t_result[i] = (_t_result[i] - _t_begin[i] + 10) + 48;
            _t_result[i-1]--;
        }
        else if (i == 6 || i == 3)
        {
            _t_result[i] = (_t_result[i] - _t_begin[i] + 6) + 48;
            _t_result[i-2]--;
        }
        else
            _t_result[i] = (_t_result[i] - _t_begin[i] + 3) + 48;
    }
    else
        _t_result[i] = (_t_result[i] - _t_begin[i]) + 48;
}
//---------------------------------------------------------------------------
void count_timer::print_result( ostream& os ) const
{
    os << "begin time: " << _t_begin << " end time: " << _t_end << " interval time:" << _t_result << " tick time:" << _ticktime << endl;
}

void count_timer::count_result()
{
    strcpy(_t_result,_t_end);
    for (int i=7; i>=0; i--)
    {
        if ( i!=2 && i!=5 )
            _format_result(i);
    }
    print_result(cout);
}
//---------------------------------------------------------------------------


#endif //_QUEEN_PROBLEM_H_
