#pragma once

#include "expr.h"
#include <cmath>

namespace funcs
{
	class Ln : public rpn::UnaryOp
	{
	public:
		rpn::expor_type calc(rpn::expor_type val) const
		{
			return std::log(val);
		}
	};

	class Log10 : public rpn::UnaryOp
	{
	public:
		rpn::expor_type calc(rpn::expor_type val) const
		{
			return std::log10(val);
		}
	};

	class Log2 : public rpn::UnaryOp
	{
	public:
		rpn::expor_type calc(rpn::expor_type val) const
		{
			return std::log2(val);
		}
	};

	class Sin : public rpn::UnaryOp
	{
	public:
		rpn::expor_type calc(rpn::expor_type val) const;
	};

	class Cos : public rpn::UnaryOp
	{
	public:
		rpn::expor_type calc(rpn::expor_type val) const;
	};

	class Fac : public rpn::UnaryOp
	{
	public:
		rpn::expor_type calc(rpn::expor_type val) const;
	};

	class Sqrt : public rpn::UnaryOp
	{
	public:
		rpn::expor_type calc(rpn::expor_type val) const
		{
			return std::sqrt(val);
		}
	};

	class Min : public rpn::BinaryOp
	{
	public:
		rpn::expor_type calc(rpn::expor_type left, rpn::expor_type right) const override
		{
			return std::min(left, right);
		}
	};

	class Max : public rpn::BinaryOp
	{
	public:
		rpn::expor_type calc(rpn::expor_type left, rpn::expor_type right) const override
		{
			return std::max(left, right);
		}
	};

	class Exp : public rpn::BinaryOp
	{
	public:
		rpn::expor_type calc(rpn::expor_type left, rpn::expor_type right) const override
		{
			return std::pow(left, right);
		}
	};

	void add_functions();
	void add_operations();
};
