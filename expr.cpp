#include "expr.h"
#include "stdlib.h"

namespace rpn
{
	bool is_op(char op) 
	{
		return op == '+' || op == '-' || op == '*' || op == '/';
	}

	bool is_bracket(char op) 
	{
		return op == '(' || op == ')';
	}

	int get_prior(char op) 
	{
		if (op == '+' || op == '-') 
		{
			return 1;
		}
		else if (op == '*' || op == '/') 
		{
			return 2;
		}

		return 0;
	}

	std::shared_ptr<Item> create_op(char op)
	{
		switch (op)
		{
		case '+': return std::make_shared<Add>();
		case '-': return std::make_shared<Sub>();
		case '*': return std::make_shared<Mul>();
		case '/': return std::make_shared<Div>();
		}
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

		std::stack<char> stack;

		auto buf = str.c_str();

		while (*buf != 0) 
		{
			const auto c = *buf;

			if (!is_op(c) && !is_bracket(c)) 
			{
				char* end;
				expor_type val = strtol(buf, &end, 10);

				m_expr.push_back(std::make_shared<Value>(val));

				buf = end;
			}
			else 
			{
				buf++;

				if (c == '(') 
				{
					stack.push(c);
				}
				else if (c == ')') 
				{
					auto stack_top = stack.top();
					stack.pop();

					while (stack_top != '(') 
					{
						m_expr.push_back(create_op(stack_top));

						stack_top = stack.top();
						stack.pop();
					}
				}
				else if (is_op(c)) 
				{
					if (!stack.empty()) 
					{
						char stack_top = stack.top();

						while (get_prior(c) <= get_prior(stack_top)) {
							m_expr.push_back(create_op(stack_top));

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

					stack.push(c);
				}
			}
		}

		while (!stack.empty()) {
			auto stack_top = stack.top();
			stack.pop();

			m_expr.push_back(create_op(stack_top));
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
