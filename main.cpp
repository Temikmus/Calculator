#include <iostream>
#include "tokenizer.h"
#include "rpn.h"
#include <string>

int main()
{
    std::vector<Token> tokensInfix, tokensRPN;

    std::string expr;//В expr НАДО ДОБАВИТЬ ПОЛУЧИВШ. СТРОКУ ИЗ КАЛЬКУЛЯТОРА
    std::cin>>expr;
    std::cout << "Expression: " << expr << std::endl;
    try
    {
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
                case Token::FUNCTION_KNOW:
                    type = "FUNCTION_KNOW";
                    break;
                case Token::FUNCTION_UNKNOWN:
                    type = "FUNCTION_UNKNOWN";
                    break;
                case Token::SEPARATOR:
                    type = "SEPARATOR";
                    break;
                case Token::VARIABLE:
                {
                    if (i.getStr()=="e")
                    {
                        i.str="2.7182818284";
                        i.name=Token::FLOAT_N;
                        i.opAsc=Token::NONE;
                    }
                    else if(i.getStr()=="pi")
                    {
                        i.str="3.1415926535";
                        i.name=Token::FLOAT_N;
                        i.opAsc=Token::NONE;
                    }
                    else
                    {
                        type = "VARIABLE";
                    }
                    break;
                }
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
            //std::cout << i.getStr() << "\t" << type << "\t" << asc << "\n";
        }

        shuntingYard(tokensInfix, tokensRPN);
        auto answer=countRPN(tokensRPN); // answer - ОТВЕТ. ЕГО НАДО ВЫВЕСТИ.
        std::cout << "Answer: " << answer << "\n";
    }
    catch (std::invalid_argument ex)
    {
        std::cerr << ex.what() <<std::endl;
    }
    return 0;
}