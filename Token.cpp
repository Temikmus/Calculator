#include "Token.h"



Token::Token(std::string tok, Name n, OperatorAssociativity asc)
{
    name=n;
    str=tok;
    opAsc = asc;
}

int Token::getPrecendance() const
{
    if (this->opAsc==RIGHT)
    {
        if (this->str=="+" || this->str=="-")
            return 4;
        //else
    }
    else if (this->opAsc==LEFT)
    {
        if (this->str=="-" || this->str=="+")
            return 2;
        else if (this->str=="/" || this->str=="*" || this->str=="%")
            return 4;
        else if (this->str=="^" || this->str=="!")
            return 5;
        //else
    }
    return -1;
    //else
}
