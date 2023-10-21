#include <gtest/gtest.h>
#include "../source/interpolant/interpolant.hpp"
#include "../source/tools/grids.hpp"
#include "../source/tools/write_points.hpp"
#include "../source/num_differentiation/num_differentiation.hpp"

#include <iostream>
#include<iomanip>
#include <cmath>

TEST(test1, N3){
    
    constexpr std::size_t N = 10;
    double step = 1;
    double x0 = 1;

    std::array<double, N - 1> grid = make_derivative_coefs_grid<double, N>();

    DerivativeCoef<double, N - 1> der_coefs = calcDerivativeCoef<double, N - 1>(grid);

    // for(auto& el: der_coefs.otherCoefs){
    //     std::cout << el << ' ';
    // }
    // std::cout << std::endl << der_coefs.centralCoef << std::endl;

    DerivativeCoef<double, N - 1> f_coefs = der_coefs;

    f_coefs.centralCoef = std::exp(1);
    for(std::size_t i = 0; i < N - 1; i++){
        f_coefs.otherCoefs[i] = std::exp(grid[i] * step + x0);
    }

    double derivative = calcFirstDerivative<double, double, N - 1>(der_coefs, f_coefs, step); 
    std::cout << derivative << std::endl;

    std::cout << std::endl << std::exp(1.0) << std::endl;

}

int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
