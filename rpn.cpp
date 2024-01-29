#include <iostream>
#include "expr.h"

int main()
{
    std::string str;
    std::cin >> str;

    rpn::Expr expr;
    expr.parse(str);

    std::cout << expr.calc() << std::endl;
}
