#pragma once
#include "rpn.h"
#include <iostream>
#include <stack>
#include <cmath>
#include <tuple>

void shuntingYard(const std::vector<Token> &expr, std::vector<Token> &outQueue)
{
    std::stack<Token> stack;
    auto fromStackToQueue = [&]() { outQueue.push_back(stack.top()); stack.pop(); };
    for(const auto& token : expr)
    {
        switch(token.getType())
        {
            case Token::INT_N:
            case Token::FLOAT_N:
            case Token::VARIABLE:
                outQueue.push_back(token);
                break;
            case Token::L_BRACKET:
            case Token::FUNCTION_KNOW:
            case Token::FUNCTION_UNKNOWN:
                stack.push(token);
                break;
            case Token::OPERATOR:
                if(!stack.empty())
                {
                    while(stack.top().getType() == Token::OPERATOR && ((stack.top().getPrecendance() > token.getPrecendance())
                                                                       || (stack.top().getPrecendance() == token.getPrecendance() && token.getAsc() == Token::LEFT)))
                    {
                        fromStackToQueue();
                        if(stack.empty())
                            break;
                    }
                }
                stack.push(token);
                break;

            case Token::R_BRACKET:
                if(stack.empty())
                    throw std::invalid_argument("Non-balanced on paranthesis expression");
                while (stack.top().getType() != Token::L_BRACKET)
                {
                    fromStackToQueue();
                    if (stack.empty())
                        throw std::invalid_argument("Non-balanced on paranthesis expression");
                }
                stack.pop();
                if(!stack.empty() && stack.top().getType() == Token::FUNCTION_KNOW || !stack.empty() && stack.top().getType() == Token::FUNCTION_UNKNOWN)
                    fromStackToQueue();
                break;

            case Token::SEPARATOR:
                if(stack.empty())
                    throw std::invalid_argument("Paranthesis or separator missed!");
                while(stack.top().getType() != Token::L_BRACKET)
                {
                    fromStackToQueue();
                    if(stack.empty())
                        throw std::invalid_argument("Paranthesis or separator missed!");
                }
                break;
        }
    }
    while(!stack.empty())
    {
        if(stack.top().getType() == Token::L_BRACKET)
            throw std::invalid_argument("Paranthesis-unbalanced expression!");
        else
            fromStackToQueue();
    }
}

auto getOneToken(std::stack<double>& stack)
{
    if(stack.empty())
    {
        throw std::invalid_argument("Not enough arguments in function!");
    }
    double x = stack.top();
    stack.pop();
    return x;
}

auto getTwoTokens(std::stack<double> &stack)
{
    double x = getOneToken(stack);
    double y = getOneToken(stack);
    return std::tuple{y,x};
}

auto checkedDivision(double a, double b)
{
    if(b == 0.f)
        throw std::invalid_argument("Division by zero");
    return a / b;
}


double countRPN(const std::vector<Token> &expr)
{
    std::stack<double> stack;
    double res;
    for (auto &token : expr)
    {
        const std::string &str = token.getStr();
        switch(token.getType())
        {
            case Token::INT_N:
                stack.push(std::stof(str));
                break;
            case Token::FLOAT_N:
                stack.push(std::stof(str));
                break;
            case Token::OPERATOR:
                switch(token.getAsc())
                {
                    case Token::LEFT:
                    {
                        auto [a,b] = getTwoTokens(stack);
                        if      (str == "+") res = a + b;
                        else if (str == "-") res = a - b;
                        else if (str == "*") res = a * b;
                        else if (str == "/") res = checkedDivision(a, b);
                        else if (str == "^") res = std::pow(a,b);
                        else throw std::invalid_argument("Unknown operator!");
                        break;
                    }
                    case Token::RIGHT:
                    {
                        auto a = getOneToken(stack);
                        if   (str == "-") res = -a;
                        else throw std::invalid_argument("Unknown operator!");
                        break;
                    }
                    case Token::NONE:
                        throw std::invalid_argument("Operator must have associativity!");
                        break;
                }
                stack.push(res);
                break;
            case Token::FUNCTION_KNOW:
                if(str == "log")
                {
                    auto [a,b] = getTwoTokens(stack);
                    //if(a <= 0.f || a == 1.0f) throw Error(std::format("log(a,x): not defined for a = {}", a), Error::Math);
                    //if(b <= 0.f) throw Error("log(a,x): out of function's domain", Error::Math);
                    res = std::log(b) / std::log(a);
                }
                else if (str == "log2")
                {
                    auto a = getOneToken(stack);
                    //if(a <= 0.f) throw Error("log2(x): out of function's domain", Error::Math);
                    res = std::log2(a);
                }
                else if(str == "ln")
                {
                    auto a = getOneToken(stack);
                    //if(a <= 0.f) throw Error("ln(x): out of function's domain", Error::Math);
                    res = std::log(a);
                }
                else if(str == "lg")
                {
                    auto a = getOneToken(stack);
                    //if(a <= 0.f) throw Error("lg(x): out of function's domain", Error::Math);
                    res = std::log10(a);
                }
                else if(str == "max")
                {
                    auto[a,b] = getTwoTokens(stack);
                    res = a > b ? a : b;
                }
                else if(str == "min")
                {
                    auto[a,b] = getTwoTokens(stack);
                    res = a < b ? a : b;
                }
                else if(str == "sqrt")
                {
                    auto a = getOneToken(stack);
                    res = std::sqrt(a);
                }
                else if(str == "sin")
                {
                    auto a = getOneToken(stack);
                    res = std::sin(a);
                }
                else if(str == "cos")
                {
                    auto a = getOneToken(stack);
                    res = std::cos(a);
                }
                else if (str == "tg")
                {
                    auto a = getOneToken(stack);
                    res = std::tan(a);
                }
                else if (str == "ctg")
                {
                    auto a = getOneToken(stack);
                    res = 1 / std::tan(a);
                }
                else
                    throw std::invalid_argument("Unknown function!");
                stack.push(res);
                break;
            default:
                break;
        }
    }
    return stack.top();
}