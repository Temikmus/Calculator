#include <iostream>
#include "tokenizer.cpp"
#include "RPN.cpp"

int main()
{
    std::vector<Token> tokensInfix, tokensRPN;

    std::string expr = "log(2,8)*3+4";
    std::cout << "Expression: " << expr << std::endl;
    tokenize(expr, tokensInfix);
    for(auto& i : tokensInfix)
    {
        std::string type, asc;
        switch(i.getType())
        {
            case Token::OPERATOR:
                type = "OPERATOR";
                break;
            case Token::L_BRACKET:
                type = "L_BRACKET";
                break;
            case Token::R_BRACKET:
                type = "R_BRACKET";
                break;
            case Token::INT_N:
                type = "INT_LITERAL";
                break;
            case Token::FLOAT_N:
                type = "FLOAT_LITERAL";
                break;
            case Token::FUNCTION:
                type = "FUNCTION";
                break;
            case Token::SEPARATOR:
                type = "SEPARATOR";
                break;
        }

        switch(i.getAsc())
        {
            case Token::NONE:
                asc = "NONE";
                break;
            case Token::RIGHT:
                asc = "RIGHT";
                break;
            case Token::LEFT:
                asc = "LEFT";
                break;
        }
        std::cout << i.getStr() << "\t" << type << "\t" << asc << "\n";
    }

    shuntingYard(tokensInfix, tokensRPN);
    std::cout << "Reverse Polish Notation: ";
    for (auto &i : tokensRPN)
        std::cout << i.getStr() << " ";
    std::cout << "\n";

    std::cout << "Answer: " << countRPN(tokensRPN) << "\n";
    return 0;
}