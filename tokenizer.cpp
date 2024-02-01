#include <iostream>
#include <string>
#include <vector>
#include "Token.h"

//0, Стартовое
//1, Токенизация скобки/оператора
//2, Запись целого числа в буфер
//3, Запись floating-point числа в буфер
//4, Запись функции в буфер
//5, Токенизация записанного числа/функции из буфера

void tokenize(const std::string &expr, std::vector<Token> &tokens)
{
    int state =0;
    std::string validOp="+-*^/%!";
    bool isDigit, isLetter, isOp, isParanth, isPoint, isSep, isLParanth, isRParanth;
    std::string buffer;
    Token::Name bufferTokenType=Token::INT_N;
    for (int i=0; i<expr.length(); i++)
    {
        char s=expr[i];
        isDigit = std::isdigit(s);
        isLetter = std::isalpha(s);
        isLParanth = s == '(';
        isRParanth = s == ')';
        isParanth = isLParanth || isRParanth;
        isPoint = s == '.';
        isSep = s == ',';
        isOp = validOp.find(s) != -1;
        //if(!(isDigit || isLetter || isParanth || isPoint || isSep || isOp))
        //    throw Error(std::format("Unknown symbol: {}", s), Error::Syntax);
        switch(state)
        {
            case 0:
                if (isOp || isParanth)
                    state = 1;
                else if (isDigit)
                    state = 2;
                else if (isLetter)
                    state = 4;
                //else if (isPoint || isSep)
                //    throw Error(std::format("Unexpected symbol: \"{}\"", s), Error::Syntax);
                break;
            case 1:
                if (isDigit)
                    state = 2;
                else if (isLetter)
                    state = 4;
                //else if (isPoint || isSep)
                //    throw Error(std::format("Unexpected symbol: \"{}\"", s), Error::Syntax);
                break;
            case 2:
                bufferTokenType = Token::INT_N;
                if (isPoint)
                    state = 3;
                else if (isParanth || isOp || isSep)
                    state = 5;
                //else if (isLetter)
                //    throw Error(std::format("Unexpected symbol: \"{}\"", s), Error::Syntax);
                break;
            case 3:
                bufferTokenType = Token::FLOAT_N;
                if (isParanth || isOp || isSep)
                    state = 5;
                //else if (isPoint)
                //    throw Error(std::format("Unexpected symbol: \"{}\"", s), Error::Syntax);
                break;
            case 4:
                bufferTokenType = Token::FUNCTION;
                if(isLParanth)
                    state = 5;
                //else if(isOp || isRParanth || isSep)
                //    throw Error(std::format("Unexpected symbol \"{}\"", s), Error::Syntax);
                break;
            case 5:
                if (isParanth || isOp)
                    state = 1;
                else if (isDigit)
                    state = 2;
                else if (isLetter)
                    state = 4;
                //else if (isPoint || isSep)
                //    throw Error(std::format("Unexpected symbol: \"{}\"", s), Error::Syntax);
                break;
            default:
                break;
        }

        switch(state)
        {
            case 1:
                if(isOp)
                {
                    if(tokens.empty() || tokens[tokens.size()-1].getType() == Token::L_BRACKET)
                        tokens.push_back({std::string{s}, Token::OPERATOR, Token::RIGHT});
                    else
                        tokens.push_back({std::string{s}, Token::OPERATOR, Token::LEFT});
                }
                else if(isParanth)
                {
                    if (isRParanth)
                        tokens.push_back({std::string{s}, Token::R_BRACKET});
                    else
                        tokens.push_back({std::string{s}, Token::L_BRACKET});
                }
                else if(isSep)
                {
                    tokens.push_back({std::string{s}, Token::SEPARATOR});
                }
                break;
            case 2: case 3: case 4:
                buffer.push_back(s);
                break;
            case 5:
                tokens.push_back({buffer, bufferTokenType});
                buffer.clear();
                if(isOp)
                {
                    if(tokens.empty() || tokens[tokens.size()-1].getType() == Token::L_BRACKET)
                        tokens.push_back({std::string{s}, Token::OPERATOR, Token::RIGHT});
                    else
                        tokens.push_back({std::string{s}, Token::OPERATOR, Token::LEFT});
                }
                else if(isParanth)
                {
                    if (isRParanth)
                        tokens.push_back({std::string{s}, Token::R_BRACKET});
                    else
                        tokens.push_back({std::string{s}, Token::L_BRACKET});
                }
                else if(isSep)
                {
                    tokens.push_back({std::string{s}, Token::SEPARATOR});
                }
                break;
            default:
                break;
        }
    }
    if(!buffer.empty())
        tokens.push_back({buffer, bufferTokenType});
}
