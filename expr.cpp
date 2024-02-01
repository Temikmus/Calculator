#include "expr.h"
#include "stdlib.h"
#include <unordered_map>
#include <cctype>

//"log(2,8)-3^2+4"

namespace rpn
{
	const char BrackO = '(';
	const char BrackC = ')';

	struct TokenOp
	{
		int prior = 0;
		std::shared_ptr<Item> op;
	};


	std::unordered_map<std::string, TokenOp> operations
	{
		{"+", {1, std::make_shared<Add>()}},
		{"-", {1, std::make_shared<Sub>()}},
		{"*", {2, std::make_shared<Mul>()}},
		{"/", {2, std::make_shared<Div>()}},
		{"_", {3, std::make_shared<Minus>()}},
		{"^", {4, std::make_shared<Exp>()}},
	};


	TokenOp get_op(char op, bool is_right)
	{
		if (is_right) op = '_';

		return operations[std::string(1, op)];
	}

	void Value::process(expr_stack& stack) const
	{
		stack.push(m_val);
	}

	expor_type Op::get_value(expr_stack& stack) const
	{
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

	void Expr::parse(const std::string& str)
	{
		m_expr.clear();

		std::stack<TokenOp> stack;

		auto buf = str.c_str();

		auto is_right = true;

		while (*buf != 0) 
		{
			const auto c = *buf;

			if (std::isdigit(c)) 
			{
				char* end;
				expor_type val = strtol(buf, &end, 10);

				m_expr.push_back(std::make_shared<Value>(val));

				buf = end;
			}
			else 
			{
				buf++;

				if (c == BrackO)
				{
					stack.push(TokenOp());
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
				else
				{
					auto cur_op = get_op(c, is_right);
					if (!cur_op.prior)
					{
						continue;
					}

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

			is_right = c == BrackO;
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
