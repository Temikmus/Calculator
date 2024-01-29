#pragma once

#include <stack>
#include <vector>
#include <memory>
#include <string>

namespace rpn 
{
	using expor_type = long long;
	using expr_stack = std::stack<expor_type>;

	class Item
	{
	public:
		virtual ~Item() {}
		virtual void process(expr_stack&) const = 0;
	};

	class Value : public Item
	{
	public:
		Value(expor_type val) : m_val(val)
		{

		}

		void process(expr_stack&) const override;

	private:
		expor_type m_val;
	};

	class Op : public Item
	{
	protected:
		expor_type get_value(expr_stack&) const;
	};

	class UnaryOp : public Op
	{
	public:
		void process(expr_stack&) const override;

	private:
		virtual expor_type calc(expor_type val) const = 0;
	};

	class BinaryOp : public Op
	{
	public:
		void process(expr_stack&) const override;

	private:
		virtual expor_type calc(expor_type left, expor_type right) const = 0;
	};

	class Add : public BinaryOp
	{
	public:
		expor_type calc(expor_type left, expor_type right) const override
		{
			return left + right;
		}
	};

	class Sub : public BinaryOp
	{
	public:
		expor_type calc(expor_type left, expor_type right) const override
		{
			return left - right;
		}
	};

	class Mul : public BinaryOp
	{
	public:
		expor_type calc(expor_type left, expor_type right) const override
		{
			return left * right;
		}
	};

	class Div : public BinaryOp
	{
	public:
		expor_type calc(expor_type left, expor_type right) const override
		{
			return left / right;
		}
	};

	class Expr
	{
	public:
		void parse(const std::string& str);

		expor_type calc();

	private:
		std::vector<std::shared_ptr<Item>> m_expr;
	};
}

