#define _USE_MATH_DEFINES

#include "expr.h"
#include <cstdlib>
#include <unordered_map>
#include <cctype>
#include <cmath>

namespace rpn
{
	const char BrackO = '(';
	const char BrackC = ')';

	const auto InvalidExpression = "Invalid expression";

	struct Token
	{
		int prior = 0;
		std::shared_ptr<Item> op;
		bool is_right = false;
	};

	std::unordered_map<char, Token> operations
	{
		{'+', {1, std::make_shared<Add>()}},
		{'-', {1, std::make_shared<Sub>()}},
		{'*', {2, std::make_shared<Mul>()}},
		{'/', {2, std::make_shared<Div>()}},
	};

	void add_operation(char id, Item* imp, int priority, bool is_right)
	{
		operations[id] = Token{ priority, std::shared_ptr<Item>(imp), is_right };
	}

	std::unordered_map<std::string, Token> functions
	{
		{"e", {-1, std::make_shared<Value>(M_E)}},
		{"pi", {-1, std::make_shared<Value>(M_PI)}},
	};

	void add_function(const std::string& name, Item* imp, int priority)
	{
		functions[name] = Token{ priority, std::shared_ptr<Item>(imp) };
	}

	const auto UnaryMinus = Token{ 5, std::make_shared<Minus>() };
	const auto NoOp = Token{};

	Token get_op(const char* str, char** end, bool is_right)
	{
		auto op = *str;

		auto res = operations[op];
		if (res.prior)
		{
			if (!res.is_right && is_right)
			{
				if (op == '-')
				{
					res = UnaryMinus;
				}
				else if (op == '+')
				{
					res = NoOp;
				}
				else
				{
					throw InvalidExpression;
				}
			}

			*end = (char*)str + 1;
		}
		else
		{
			auto len = 0;
			while (std::isdigit(op) || isalpha(op))
			{
				len++;
				op = *(str + len);
			}

			if (len)
			{
				res = functions[std::string(str, len)];
				*end = (char*)str + len;
			}

			if (!res.prior)
			{
				throw InvalidExpression;
			}
		}

		return res;
	}

	void Value::process(expr_stack& stack) const
	{
		stack.push(m_val);
	}

	expor_type Op::get_value(expr_stack& stack) const
	{
		if (stack.empty())
		{
			throw InvalidExpression;
		}

		auto val = stack.top();
		stack.pop();

		return val;
	}

	void UnaryOp::process(expr_stack& stack) const
	{
		auto val = get_value(stack);

		stack.push(calc(val));
	}

	void BinaryOp::process(expr_stack& stack) const
	{
		auto right = get_value(stack);
		auto left = get_value(stack);

		stack.push(calc(left, right));
	}

	void Expr::parse(std::string str)
	{
		m_expr.clear();

		//auto end_pos = std::remove(str.begin(), str.end(), ' ');
		//str.erase(end_pos, str.end());

		std::stack<Token> stack;

		auto buf = str.c_str();

		auto is_right = true;
		auto is_op = false;

		while (*buf != 0)
		{
			const auto c = *buf;

			is_op = false;

			if (std::isdigit(c))
			{
				char* end;
				expor_type val = strtod(buf, &end);

				m_expr.push_back(std::make_shared<Value>(val));

				buf = end;
			}
			else
			{
				buf++;

				if (c == BrackO)
				{
					stack.push(Token());
				}
				else if (c == BrackC)
				{
					auto stack_top = stack.top();
					stack.pop();

					while (stack_top.prior > 0)
					{
						m_expr.push_back(stack_top.op);

						stack_top = stack.top();
						stack.pop();
					}
				}
				else if (c != ',')
				{
					buf--;
					char* end;

					auto cur_op = get_op(buf, &end, is_right);

					buf = end;

					if (!cur_op.prior)
					{
						continue;
					}

					if (cur_op.prior < 0)
					{
						m_expr.push_back(cur_op.op);
						is_right = false;

						continue;
					}

					is_op = !cur_op.is_right;

					if (!stack.empty())
					{
						auto stack_top = stack.top();

						while (cur_op.prior <= stack_top.prior) {
							m_expr.push_back(stack_top.op);

							stack.pop();
							if (!stack.empty())
							{
								stack_top = stack.top();
							}
							else
							{
								break;
							}
						}
					}

					stack.push(cur_op);
				}
			}

			is_right = c == BrackO || is_op;
		}

		while (!stack.empty()) {
			auto stack_top = stack.top();
			stack.pop();

			m_expr.push_back(stack_top.op);
		}
	}

	expor_type Expr::calc()
	{
		expr_stack stack;

		for (const auto& item : m_expr)
		{
			item->process(stack);
		}

		return stack.top();
	}
};
