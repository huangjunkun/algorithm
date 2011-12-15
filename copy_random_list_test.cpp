#include <iostream>

#include "copy_random_list.h"

using namespace std;
using namespace test_namespace;

void test_random_list()
{
    random_list test_list = test_construct_list(10);
    random_list test_list_bak = copy_random_list(test_list);
    std::cout << ">---   test_list   --->\n";
    print_list(std::cout, test_list);
    std::cout << "<---   test_list   ---<\n";
    std::cout << ">---   test_list_bak   --->\n";
    print_list(std::cout, test_list_bak);
    std::cout << "<---   test_list_bak   ---<\n";
    deallocate_list(test_list);
    deallocate_list(test_list_bak);
}

int main()
{
    test_random_list();
    /** =   =   =   =   =   =   =   =   =   =*/
    cout << "Hello world!" << endl;
    return 0;
}
