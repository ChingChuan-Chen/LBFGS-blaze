#include <blaze/Blaze.h>

#include <iomanip>
#include <iostream>

#include "lbfgs.hpp"

class MinimizationExample {
   public:
    using BlazeVector = blaze::CustomVector<double, blaze::aligned, blaze::padded>;

    int run(const size_t n) {
        double finalCost;

        std::size_t padded_size = blaze::nextMultiple<std::size_t>(n, blaze::SIMDTrait<double>::size);
        std::unique_ptr<double[], blaze::Deallocate> data(blaze::allocate<double>(padded_size));
        BlazeVector x(data.get(), n, padded_size);

        // Set the initial guess
        for (std::size_t i = 0; i < n; i += 2) {
            x[i] = -1.2;
            x[i + 1] = 1.0;
        }

        // Set the minimization parameters
        lbfgs::lbfgs_parameter_t params;
        params.g_epsilon = 1.0e-8;
        params.past = 3;
        params.delta = 1.0e-8;

        // Start minimization
        int ret = lbfgs::lbfgs_optimize(x, finalCost, costFunction, nullptr, monitorProgress, this, params);

        // Print the results
        std::cout << std::setprecision(4) << "================================" << std::endl
                  << "L-BFGS Optimization Returned: " << ret << std::endl
                  << "Minimized Cost: " << finalCost << std::endl
                  << "Optimal Variables: " << std::endl
                  << blaze::trans(x) << std::endl;

        return ret;
    }

   private:
    /**
     * Default evaluator adopted from liblbfgs sample.c
     *
     * @param x A double vector. The current values of variables.
     * @param gx A double vector which represents the gradient on x. The callback
     * function must compute the gradient values for the current variables.
     * @return An evaluated value, double precision.
     */
    static double costFunction(void *instance, const BlazeVector &x, BlazeVector &g) {
        const std::size_t n = x.size();
        double fx = 0.0, t1, t2;
        for (std::size_t i = 0UL; i < n; i += 2) {
            t1 = 1.0 - x[i];
            t2 = 10.0 * (x[i + 1] - x[i] * x[i]);
            g[i + 1] = 20.0 * t2;
            g[i] = -2.0 * (x[i] * g[i + 1UL] + t1);
            fx += t1 * t1 + t2 * t2;
        }
        return fx;
    }

    /**
     * Progress monitor
     *
     * @param instance,x,g,fx,step,k,ls Refer to the function `lbfgs_progress_t`.
     * @return An integer to indicate the status of the optimization.
     */
    static int monitorProgress(void *instance, const BlazeVector &x, const BlazeVector &g, const double fx,
                               const double step, const int k, const int ls) {
        std::cout << std::setprecision(4) << "================================" << std::endl
                  << "Iteration: " << k << std::endl
                  << "Function Value: " << fx << std::endl
                  << "Variable Inf Norm: " << blaze::linfNorm(x) << std::endl
                  << "Gradient Inf Norm: " << blaze::linfNorm(g) << std::endl
                  << "Step: " << step << std::endl
                  << "Variables: " << std::endl
                  << blaze::trans(x) << std::endl;
        return 0;
    };
};

int main(int argc, char **argv) {
    MinimizationExample example;
    return example.run(200UL);
}
