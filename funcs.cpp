#define _USE_MATH_DEFINES

#include "funcs.h"
#include <cmath>

namespace funcs
{
    const double eps = 1e-12;

    rpn::expor_type Sin::calc(rpn::expor_type val) const
    {
        val = val * 2 * M_PI / 360;

        int sign = (val < 0) ? -1 : 1;
        val = fmod(fabs(val), 2 * M_PI);

        if (val > M_PI)
        {
            val -= M_PI;
            sign *= -1;
        }

        if (val > M_PI / 2)
        {
            val = M_PI - val;
        }

        const auto val_sq = val * val;

        auto t = val;
        auto s = val;
        for (int n = 3; fabs(t) > eps; n += 2)
        {
            t = -t * val_sq / n / (n - 1);
            s += t;
        }

        return s * sign;
    }

    rpn::expor_type Cos::calc(rpn::expor_type val) const
    {
        val = val * 2 * M_PI / 360;

        int sign = 1;
        val = fmod(fabs(val), 2 * M_PI);

        if (val < 0)
        {
            val = -val;
        }

        if (val > M_PI)
        {
            val -= M_PI;
            sign *= -1;
        }

        if (val > M_PI / 2)
        {
            val = M_PI - val;
            sign *= -1;
        }
        
        const auto val_sq = val * val;

        rpn::expor_type t = 1;
        rpn::expor_type s = 1;
        for (int n = 2; fabs(t) > eps; n += 2)
        {
            t = -t * val_sq / n / (n - 1);
            s += t;
        }

        return s;
    }

    rpn::expor_type Fac::calc(rpn::expor_type val) const
    {
        long long n = val;
        long long f = 1;

        for (long long i = 2; i <= n; i++)
        {
            f *= i;
        }

        return f;
    }

    void add_functions()
    {
        rpn::add_function("ln", new Ln());
        rpn::add_function("log10", new Log10());
        rpn::add_function("log2", new Log2());
        rpn::add_function("sin", new Sin());
        rpn::add_function("cos", new Cos());
        rpn::add_function("sqrt", new Sqrt());
        rpn::add_function("min", new Min());
        rpn::add_function("max", new Max());
        rpn::add_function("pow", new Exp());
    }

    void add_operations()
    {
        rpn::add_operation('^', new Exp(), 4);
        rpn::add_operation('!', new Fac(), 5, true);
    }
};
