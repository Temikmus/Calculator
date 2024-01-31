#include <iostream>
#include <string>
#include <algorithm>
#include "expr.h"
#include "funcs.h"

int main()
{
    funcs::add_functions();
    funcs::add_operations();

    std::string str;
    std::getline(std::cin, str);

    try
    {
        rpn::Expr expr;
        expr.parse(str);

        std::cout << expr.calc() << std::endl;
    }
    catch (const char* err)
    {
        std::cout << err << std::endl;
    }
}
