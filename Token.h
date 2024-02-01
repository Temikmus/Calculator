#pragma once
#include <string>

class Token{
public:
    enum Name
    {
        OPERATOR,
        L_BRACKET,
        R_BRACKET,
        INT_N,
        FLOAT_N,
        FUNCTION_KNOW,
        VARIABLE,
        SEPARATOR,
        FUNCTION_UNKNOWN
    };
    enum OperatorAssociativity
    {
        NONE,
        RIGHT,
        LEFT
    };
    Token(std::string token, Name type, OperatorAssociativity asc = NONE);

    int getPrecendance() const;
    Name getType() const  { return name; }
    OperatorAssociativity getAsc() const { return opAsc; }
    std::string getStr() const { return str; }

private:
    Name name;
    OperatorAssociativity opAsc;
    std::string str;
};
