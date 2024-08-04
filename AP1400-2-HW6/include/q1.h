#ifndef Q1_H
#define Q1_H

#include <functional>

namespace q1
{
    template <typename ReturnType = double, typename Function>
    ReturnType gradient_descent(double initial,
                                double step, Function func = Function{},
                                double tolerance = 1e-8,
                                double delta = 1e-8)
    {
        double next = initial;
        double gradient = (func(next+delta) - func(next))/delta;
        while (gradient > tolerance || gradient < -tolerance) {
            next = next - gradient*step;
            gradient = (func(next + delta) - func(next))/delta;
        }
        return next;
    }
}

#endif //Q1_H